// MoboMemController.cpp
// (c) Antti Juustila, 2003
//
// $Id: Controller.cpp,v 1.4 2004/06/04 07:08:50 Antti Exp $
// See class documentation in the header file

#include <s32file.h>
#include <s32strm.h> 
#include <s32std.h>

#include "MoboMemController.h"
#include "MoboMemEng.h"
#include "MoboMemEngineObserver.h"
#include "HallOfFame.h"
#include "HallOfFameItem.h"
#include "CleanupFileEraser.h"
	
/////////////////////////////////
// CMoboMemGameEngine
////////////////////////////////

_LIT(KHallOfFameFile, "C:\\System\\Apps\\MoboMemory\\HallOfFame");

CMoboMemGameEngine::CMoboMemGameEngine()
	{
	iFirstSymbolRevealed = -1;
	iSecondSymbolRevealed = -1;
	}

CMoboMemGameEngine::~CMoboMemGameEngine()
	{
	delete iEngine;
	delete iHallOfFame;
	}

EXPORT_C CMoboMemGameEngine * CMoboMemGameEngine::NewL()
	{
	CMoboMemGameEngine * self = new (ELeave) CMoboMemGameEngine();
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop();
	return self;
	}

void CMoboMemGameEngine::ConstructL()
	{
	iEngine = new (ELeave) CMemoryGameBoard;
	iGameState = EGameInitialized;
	iHallOfFame = CHallOfFame::NewL();
	RestoreGameStateL();
	}

EXPORT_C void CMoboMemGameEngine::SetObserver(MMoboMemGameEngineObserver * aObserver)
	{
	iObserver = aObserver;
	}


EXPORT_C void CMoboMemGameEngine::StartGameL(TInt aPairCount)
	{
	iGameState = EGameRunning;

	iFirstSymbolRevealed = -1;
	iSecondSymbolRevealed = -1;

	iWrongAttemptCount = 0;
		
	iEngine->InitializeEngineL(aPairCount);
	if (iObserver)
		iObserver->GameStartedNotifyL();
	iGameStarted.HomeTime();
	}

void CMoboMemGameEngine::EndGameL()
	{
	TTime now;
	iFirstSymbolRevealed = -1;
	iSecondSymbolRevealed = -1;
	now.HomeTime();
	iGameState = EGameEnded;
	now.SecondsFrom(iGameStarted,iGameLengthInSeconds);
	iGameLengthInSeconds = iGameLengthInSeconds.Int() + (iWrongAttemptCount * 5);

	TBuf<KMaxPlayerNameLength> player;
	THallOfFameItem theItem(player, iGameLengthInSeconds.Int(), now.Int64());

	TBool gotToHallOfFame = iHallOfFame->CheckIfItemFitsToListL(theItem);
	iObserver->GameEndedNotifyL(gotToHallOfFame);
	if (gotToHallOfFame)
		{
		iObserver->GetPlayerNameL(player);
		theItem.SetName(player);
		iHallOfFame->CheckAndAddNewItemL(theItem);
		// User got to the Hall of Fame; store the data.
		SaveGameStateL();
		}
	}

EXPORT_C void CMoboMemGameEngine::OpenSymbolL(TInt aSymbolIndex)
	{
	switch (iGameState)
		{
		case EGameInitialized: {
			// StartGameL must be called before trying to open any symbols.
			__ASSERT_DEBUG(EFalse, User::Panic(KMoboMemCategory, KMemPanicInvalidGameState));
			break; }
			
		case EGameRunning: {
			TMoboSymbol::TSymbolState state = iEngine->SymbolState(aSymbolIndex);
			if (state == TMoboSymbol::EHidden)
				{
				iEngine->RevealSymbol(aSymbolIndex);
				iGameState = EGameRevealedOne;
				iFirstSymbolRevealed = aSymbolIndex;
				iSecondSymbolRevealed = -1;
				}
			break; }
		
		case EGameRevealedOne: {
			if (aSymbolIndex == iFirstSymbolRevealed)
				return;
			TMoboSymbol::TSymbolState state = iEngine->SymbolState(aSymbolIndex);
			if (state == TMoboSymbol::EHidden)
				{
				iEngine->RevealSymbol(aSymbolIndex);
				iSecondSymbolRevealed = aSymbolIndex;
				TBool matchFound = iEngine->DoSymbolsMatch(iFirstSymbolRevealed, iSecondSymbolRevealed);
				if (matchFound)
					{
					if (iEngine->AreAllSymbolsRevealed()) // game over
						{
						EndGameL();
						}
					else // right pairs, game not finished
						{
						iFirstSymbolRevealed = -1;
						iSecondSymbolRevealed = -1;
						iGameState = EGameRunning;
						iObserver->PairsFoundNotifyL();
						}
					}
				else // wrong pairs
					{
					iGameState = EGameRunning;
					iWrongAttemptCount++;
					iObserver->InvalidPairsOpenedNotifyL();
					}
				}
			break; }

		case EGameEnded: {
			iObserver->GameEndedNotifyL(EFalse);
			break; }
		
		default: {
			__ASSERT_DEBUG(EFalse, User::Panic(KMoboMemCategory, KMemPanicInvalidGameState));
			break; }
		}
	}


EXPORT_C TTimeIntervalSeconds CMoboMemGameEngine::PlayTime() const
	{
		return iGameLengthInSeconds;
	}

EXPORT_C TTimeIntervalSeconds CMoboMemGameEngine::PenaltyTime() const
	{
		return iWrongAttemptCount * 5;
	}


EXPORT_C void CMoboMemGameEngine::SaveGameStateL()
	{
	RFs fileServer;
	TParse	fileStoreName;
	TFileName fileName;

	User::LeaveIfError(fileServer.Connect());
	CleanupClosePushL(fileServer);

	fileServer.MkDirAll(KHallOfFameFile);
	fileServer.Parse(KHallOfFameFile, fileStoreName);
	fileName = fileStoreName.DriveAndPath();
	_LIT(KTmpFile, "Tempfile");
	fileName.Append(KTmpFile);

	TCleanupFileEraser eraser(fileServer, fileName);
	CleanupReleasePushL(eraser);
	// Since eraser is on the cleanupstack, if ReplaceLC leaves, the file
	// is attempted to be deleted even though it doesn't exist. This is no problem, however.
	CFileStore* store = CDirectFileStore::ReplaceLC(fileServer, fileName, EFileWrite);
	
	// Must say what kind of file store.
	store->SetTypeL(KDirectFileStoreLayoutUid);

	// Construct the output stream.
	RStoreWriteStream outstream;
	TStreamId id = outstream.CreateLC(*store);

	// Stream out the data
	outstream  << *this; 
	
	outstream.CommitL();

	CleanupStack::PopAndDestroy(); // stream

	// Set this stream id as the root
	store->SetRootL(id);

	// Commit changes to the store
	store->CommitL();

	CleanupStack::PopAndDestroy();	//store; close temp file now.

	TInt error = fileServer.Delete(KHallOfFameFile);
	if (error != KErrNone && error != KErrNotFound)
		User::Leave(error);
	// Rename temp file, if leaves, eraser deletes the temp file.
	error = fileServer.Rename(fileName, KHallOfFameFile);
	User::LeaveIfError(error);
	
	CleanupStack::Pop(); //eraser, file is already renamed, no need to delete (i.e. PopAndDestroy).
	
	CleanupStack::PopAndDestroy();	//fileServer
	}
	
EXPORT_C void CMoboMemGameEngine::RestoreGameStateL()
	{
	RFs fileServer;
	TParse	fileStoreName;

	User::LeaveIfError(fileServer.Connect());
	CleanupClosePushL(fileServer);

	TEntry entry;
	TInt ret = fileServer.Entry(KHallOfFameFile, entry);     //test if the file exists
	if (ret==KErrNone)
		{
		fileServer.Parse(KHallOfFameFile, fileStoreName);
		CFileStore* store = CDirectFileStore::OpenLC(fileServer, fileStoreName.FullName(), EFileRead);

		// Construct the input stream.
		RStoreReadStream instream;
		instream.OpenLC(*store, store->Root());

		// Stream out the hall of fame
		instream  >> *this; 

		// Destroy the the stream object, direct file store object (closes the file)
		CleanupStack::PopAndDestroy(2);	
		}
	CleanupStack::PopAndDestroy();	//  close the file server session
	}

EXPORT_C TInt CMoboMemGameEngine::NumberOfPairs() const
	{
	return iEngine->SymbolPairCount();
	}
	
EXPORT_C TBool CMoboMemGameEngine::IsSymbolShown(TInt aSymbolIndex) const
	{
	return (iEngine->SymbolState(aSymbolIndex) == TMoboSymbol::ERevealed);

	}

EXPORT_C TInt CMoboMemGameEngine::SymbolID(TInt aSymbolIndex) const
	{
	TMoboSymbol theSymbol;
	iEngine->GetSymbol(aSymbolIndex, theSymbol);
	return theSymbol.iSymbol;
	}

EXPORT_C void CMoboMemGameEngine::HideRevealedSymbolsIfTwo()
	{
	if (iFirstSymbolRevealed >= 0 && iSecondSymbolRevealed >= 0)
		{
		iEngine->HideSymbol(iFirstSymbolRevealed);
		iEngine->HideSymbol(iSecondSymbolRevealed);
		iFirstSymbolRevealed = -1;
		iSecondSymbolRevealed = -1;
		}
	}

EXPORT_C MDesCArray * CMoboMemGameEngine::HallOfFameDesCArrayLC(const TDesC & aResultFormat, const TDesC & aDateFormat)
	{
	CDesCArray * array = new (ELeave) CDesCArrayFlat(10);
	CleanupStack::PushL(array);
	iHallOfFame->FillHallOfFameListL(*array, aResultFormat, aDateFormat);
	return array;
	}


EXPORT_C void CMoboMemGameEngine::ClearListL()
	{
	iHallOfFame->ClearList();
	SaveGameStateL();	
	}


void CMoboMemGameEngine::ExternalizeL(RWriteStream & aStream) const
	{
	aStream.WriteInt32L(iGameState);
	aStream.WriteInt32L(iGameLengthInSeconds.Int());
	aStream.WriteInt32L(iFirstSymbolRevealed);
	aStream.WriteInt32L(iSecondSymbolRevealed);
	aStream.WriteInt32L(iWrongAttemptCount);
	aStream << *iEngine;
	aStream << *iHallOfFame;
	}

void CMoboMemGameEngine::InternalizeL(RReadStream & aStream)
	{
	iGameState = (TMoboMemGameState)aStream.ReadInt32L();
	iGameLengthInSeconds = aStream.ReadInt32L();
	iFirstSymbolRevealed = aStream.ReadInt32L();
	iSecondSymbolRevealed = aStream.ReadInt32L();
	iWrongAttemptCount = aStream.ReadInt32L();
	aStream >> *iEngine;
	aStream >> *iHallOfFame;
	}


	
/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: Controller.cpp,v $
* Revision 1.4  2004/06/04 07:08:50  Antti
* Fixed a typing error in comments.
*
* Revision 1.3  2004/02/25 15:26:42  Antti
* Fixed an initialization bug.
*
* Revision 1.2  2004/02/24 20:55:54  Antti
* Changes due to naming changes in code.
*
* Revision 1.1.1.1  2004/02/18 22:29:32  Antti
* Entering into cvs.
*
*
*/


// EOF