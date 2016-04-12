/* Copyright (c) 2002, Nokia Mobile Phones. All rights reserved */

#include <coesndpy.h>
#include <bassnd.h>

#include <aknnotewrappers.h>
#include <avkon.hrh>

//#include <aknquerydialog.h> 
#include <aknselectionlist.h> 
#include <avkon.rsg>

#include <MoboMemory.rsg>

#include "HelloWorldPlus.pan"
#include "HelloWorldPlusAppUi.h"
#include "HelloWorldPlusAppView.h"
#include "HelloWorldPlus.hrh"
#include "HelloWorldPlusDocument.h"

#include "MoboMemEngineInterface.h"

// ConstructL is called by the application framework
void CHelloWorldPlusAppUi::ConstructL()
	{
	BaseConstructL();

	iEngine = static_cast<CHelloWorldPlusDocument*>(Document())->Engine();
	iEngine->SetObserver(this);

	iAppView = CHelloWorldPlusAppView::NewL(ClientRect(), iEngine);    


	AddToStackL(iAppView);
	}

CHelloWorldPlusAppUi::CHelloWorldPlusAppUi()                              
	{
	// add any construction that cannot leave here
	}

CHelloWorldPlusAppUi::~CHelloWorldPlusAppUi()
	{
	if (iAppView)
		{
		RemoveFromStack(iAppView);
		delete iAppView;
		iAppView = NULL;
		}
	}

// handle any menu commands
void CHelloWorldPlusAppUi::HandleCommandL(TInt aCommand)
	{
	switch(aCommand)
		{
		case EMoboMemGameNewCommand:
			{
			TInt pairCount = iEngine->NumberOfPairs();
			if (pairCount == 0)
				pairCount = 9; // nice size of game to start.
			CAknNumberQueryDialog * dlg = CAknNumberQueryDialog::NewL(pairCount);
			dlg->PrepareLC(R_AVKON_DIALOG_QUERY_VALUE_NUMBER);
			dlg->SetMinimumAndMaximum(4, 15);
			HBufC * prompt = iEikonEnv->AllocReadResourceLC(R_NUMBER_OF_PAIRS_PROMPT);
			dlg->SetPromptL(*prompt);
			CleanupStack::PopAndDestroy(); // prompt
			if (dlg->RunLD())
				{
				iEngine->StartGameL(pairCount);
				}
			}
			break;

		case EMoboMemGameClearHallofFameCommand:
			{
			HBufC * query = iEikonEnv->AllocReadResourceLC(R_CLEAR_HALL_OF_FAME_PROMPT);
			CAknQueryDialog * qDlg = CAknQueryDialog::NewL();
			qDlg->PrepareLC(R_MOBOMEM_CLEAR_HALL_OF_FAME_CONFIRMATION);
			qDlg->SetPromptL(*query);
			if (qDlg->RunLD())
				{
				iEngine->ClearListL();
				}
			CleanupStack::PopAndDestroy(); // query
			break;
			}

		case EMoboMemGameViewHallOfFame:
			{
			TInt dummy;
			CAknListQueryDialog * dlg2 = new (ELeave) CAknListQueryDialog(&dummy);
			HBufC * dateFormat = iEikonEnv->AllocReadResourceLC(R_HALL_OF_FAME_DATE_FORMAT);
			HBufC * resultFormat = iEikonEnv->AllocReadResourceLC(R_HALL_OF_FAME_RESULT_FORMAT);
			MDesCArray * array = iEngine->HallOfFameDesCArrayLC(*resultFormat, *dateFormat);
		   dlg2->PrepareLC(R_HALL_OF_FAME_DIALOG);
			dlg2->SetItemTextArray(array);
			dlg2->SetOwnershipType(ELbmDoesNotOwnItemArray);
			dlg2->RunLD();
			CleanupStack::PopAndDestroy(3); // dateFormat, resultFormat, array
			break;
			}

		case EEikCmdExit:
		case EAknSoftkeyExit:
			{
			// Exiting should not fail, so do not allow leave here.
			TRAPD(err, iEngine->SaveGameStateL());
			__ASSERT_DEBUG(err == KErrNone, User::Panic(MoboMemPanic, EMoboMemSaveFailed));
			Exit();
			break;
			}
			
		default:
			{
			User::Panic(MoboMemPanic, EMoboMemPanicBasicUi);
			break;
			}
		}
	}


void CHelloWorldPlusAppUi::GameStartedNotifyL()
	{
	// make a nice sound
	TBaSystemSoundType soundType;
	soundType.iMajor = KSystemSoundRingUID;
	CoeSoundPlayer::PlaySoundNow(soundType);
	iAppView->ResetViewL();
	}
	
void CHelloWorldPlusAppUi::PairsFoundNotifyL()
	{
	// make a nice sound
	TBaSystemSoundType soundType;
	soundType.iMajor = KSystemSoundMessageUID;
	CoeSoundPlayer::PlaySoundNow(soundType);
	}

void CHelloWorldPlusAppUi::InvalidPairsOpenedNotifyL()
	{
	// make an ugly sound
	TBaSystemSoundType soundType;
	soundType.iMajor = KSystemSoundAlarmUID;
	CoeSoundPlayer::PlaySoundNow(soundType);
	}

void CHelloWorldPlusAppUi::GameEndedNotifyL(TBool aEnteredHallOfFame)
	{
	iAppView->DrawNow();
	HBufC* textResource = iEikonEnv->AllocReadResourceLC(R_GAME_ENDED_STRING);
	HBufC* hallOfFameText = 0;
	TInt totalLength = textResource->Length() + 10;
	TInt inCleanupStack = 1;
	if (aEnteredHallOfFame)
		{
		hallOfFameText = iEikonEnv->AllocReadResourceLC(R_ENTERED_HALL_OF_FAME);
		inCleanupStack++;
		totalLength += hallOfFameText->Length();
		}
	HBufC* outBuf = HBufC::NewLC(totalLength);
	inCleanupStack++;
	TTimeIntervalSeconds gameTime = iEngine->PlayTime();
	TTimeIntervalSeconds penaltyTime = iEngine->PenaltyTime();
	TPtr ptr = outBuf->Des();
	ptr.Format(*textResource, gameTime.Int(), penaltyTime.Int());
	if (aEnteredHallOfFame)
		{
		ptr.Append(*hallOfFameText);
		}
   CAknInformationNote* informationNote = new (ELeave) CAknInformationNote(ETrue);
   informationNote->ExecuteLD(*outBuf);
	CleanupStack::PopAndDestroy(inCleanupStack); // textResource, outBuf, possibly hallOfFameText
	}

void CHelloWorldPlusAppUi::GetPlayerNameL(TDes & aPlayerName)
	{
	HBufC * prompt = iEikonEnv->AllocReadResourceLC(R_GET_PLAYER_NAME_PROMPT);
	CAknTextQueryDialog * dlg = CAknTextQueryDialog::NewL(aPlayerName);
	CleanupStack::PushL(dlg);
	dlg->SetPromptL(*prompt);
	CleanupStack::Pop(); // dlg
	dlg->SetMaxLength(KMaxPlayerNameLength);
	dlg->ExecuteLD(R_AVKON_DIALOG_QUERY_VALUE_TEXT);
	CleanupStack::PopAndDestroy(); // prompt;
	}
	
