// MoboMemeng.cpp
// (c) Antti Juustila, 2003
//
// $Id: Engine.cpp,v 1.1.1.1 2004/02/18 22:29:32 Antti Exp $
// See class documentation in the header file

#include <e32math.h>
#include <s32strm.h>

#include "MoboMemeng.h"


/////////////////////////////////////////
// CMemoryGameBoard
/////////////////////////////////////////

CMemoryGameBoard::CMemoryGameBoard()
	{
	TTime now;
	now.HomeTime();
	iSeed = now.Int64();
	}


CMemoryGameBoard::~CMemoryGameBoard()
	{
	iSymbols.Reset();
	}


void CMemoryGameBoard::InitializeEngineL(TInt aCountOfSymbolPairs)
	{
	TInt index;
	TMoboSymbol theSymbol;
	
	iSymbolPairCount = aCountOfSymbolPairs;

	iSymbols.Reset();

	// Add each symbol twice in the array, in order.
	for (index = 1; index <= iSymbolPairCount; index++)
		{
		theSymbol.iSymbol = index;
		User::LeaveIfError(iSymbols.Append(theSymbol));
		User::LeaveIfError(iSymbols.Append(theSymbol));
		}	

	// Then randomly scramble the symbols in the array.
	TInt indexToSwitch;
	for (index = 0; index < iSymbolPairCount*2; index++)
		{
		do
			{
			indexToSwitch = (Math::Rand(iSeed) % iSymbolPairCount*2);
			} while (indexToSwitch == index);
		theSymbol = iSymbols[index];
		iSymbols[index] = iSymbols[indexToSwitch];
		iSymbols[indexToSwitch] = theSymbol;
		}		
	}

void CMemoryGameBoard::GetSymbol(TInt aSymbolIndex, TMoboSymbol & aSymbol)
	{
	__ASSERT_DEBUG(aSymbolIndex < iSymbols.Count() && aSymbolIndex >= 0,
			User::Panic(KMoboMemCategory,KMemPanicInvalidArrayIndex));
		
	aSymbol = iSymbols[aSymbolIndex];
	}

void CMemoryGameBoard::HideSymbol(TInt aSymbolIndex)
	{
	__ASSERT_DEBUG(aSymbolIndex < iSymbols.Count() && aSymbolIndex >= 0,
			User::Panic(KMoboMemCategory,KMemPanicInvalidArrayIndex));

	iSymbols[aSymbolIndex].iSymbolState = TMoboSymbol::EHidden;
	}
	
void CMemoryGameBoard::RevealSymbol(TInt aSymbolIndex)
	{
	__ASSERT_DEBUG(aSymbolIndex < iSymbols.Count() && aSymbolIndex >= 0,
			User::Panic(KMoboMemCategory,KMemPanicInvalidArrayIndex));

	iSymbols[aSymbolIndex].iSymbolState = TMoboSymbol::ERevealed;
	}

TMoboSymbol::TSymbolState CMemoryGameBoard::SymbolState(TInt aSymbolIndex) const
	{
	__ASSERT_DEBUG(aSymbolIndex < iSymbols.Count() && aSymbolIndex >= 0,
			User::Panic(KMoboMemCategory,KMemPanicInvalidArrayIndex));

	return iSymbols[aSymbolIndex].iSymbolState;
	}

TBool CMemoryGameBoard::DoSymbolsMatch(TInt aSymbolIndexA, TInt aSymbolIndexB) const
	{
	__ASSERT_DEBUG(aSymbolIndexA < iSymbols.Count() && aSymbolIndexA >= 0,
			User::Panic(KMoboMemCategory,KMemPanicInvalidArrayIndex));
	__ASSERT_DEBUG(aSymbolIndexB < iSymbols.Count() && aSymbolIndexB >= 0,
			User::Panic(KMoboMemCategory,KMemPanicInvalidArrayIndex));

	return iSymbols[aSymbolIndexA].iSymbol == iSymbols[aSymbolIndexB].iSymbol;
	}


TBool CMemoryGameBoard::AreAllSymbolsRevealed() const
	{
	TBool allRevealed = ETrue;
	for (TInt index = 0; index < iSymbolPairCount*2; index++)
		{
		if (iSymbols[index].iSymbolState == TMoboSymbol::EHidden)
			{
			allRevealed = EFalse;
			break;
			}
		}
		return allRevealed;	
	}

TInt CMemoryGameBoard::SymbolPairCount() const
	{
	return iSymbolPairCount;
	}

void CMemoryGameBoard::ExternalizeL(RWriteStream & aStream) const
	{
	aStream.WriteInt32L(iSymbols.Count());
	for (TInt index = 0; index < iSymbolPairCount*2; index++)
		{
		aStream << iSymbols[index];
		}
	}
	
void CMemoryGameBoard::InternalizeL(RReadStream & aStream)
	{
	TMoboSymbol symbol;
	iSymbolPairCount = aStream.ReadInt32L()/2;
	for (TInt index = 0; index < iSymbolPairCount*2; index++)
		{
		aStream >> symbol;
		User::LeaveIfError(iSymbols.Append(symbol));
		}
	}


/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: Engine.cpp,v $
* Revision 1.1.1.1  2004/02/18 22:29:32  Antti
* Entering into cvs.
*
*
*/

