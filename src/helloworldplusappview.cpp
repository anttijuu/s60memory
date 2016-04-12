/* Copyright (c) 2002, Nokia Mobile Phones. All rights reserved */

#include <coemain.h>
#include <aknnotewrappers.h>

#include "HelloWorldPlusAppView.h"
#include "MoboViewRenderer.h"

// Standard construction sequence
CHelloWorldPlusAppView* CHelloWorldPlusAppView::NewL(const TRect& aRect, MMoboMemGameEngine * aEngine)
	{
	CHelloWorldPlusAppView* self = CHelloWorldPlusAppView::NewLC(aRect, aEngine);
	CleanupStack::Pop(self);
	return self;
	}

CHelloWorldPlusAppView* CHelloWorldPlusAppView::NewLC(const TRect& aRect, MMoboMemGameEngine * aEngine)
	{
	CHelloWorldPlusAppView* self = new (ELeave) CHelloWorldPlusAppView(aEngine);
	CleanupStack::PushL(self);
	self->ConstructL(aRect);
	return self;
	}

void CHelloWorldPlusAppView::ConstructL(const TRect& aRect)
	{
	// Create a window for this application view
	CreateWindowL();

	// Set the windows size
	SetRect(aRect);

	iRenderer = CMoboViewRenderer::NewL(iEngine);

	// Activate the window, which makes it ready to be drawn
	ActivateL();
	}

CHelloWorldPlusAppView::CHelloWorldPlusAppView(MMoboMemGameEngine * aEngine) : iEngine(aEngine)
	{
	// Add any construction code that can not leave here
	}


CHelloWorldPlusAppView::~CHelloWorldPlusAppView()
	{
	// Add any destruction code here
	delete iRenderer;
	}


// Draw this application's view to the screen
void CHelloWorldPlusAppView::Draw(const TRect& /*aRect*/) const
	{
	// Get the standard graphics context 
	CWindowGc& gc = SystemGc();

	// Gets the control's extent
	TRect rect = Rect();

	// Clears the screen
	gc.Clear(rect);

	TRAPD(err,iRenderer->DrawL(*gc.Device(), gc, rect));
	}


void CHelloWorldPlusAppView::ResetViewL()
	{
	iRenderer->MakeMoboMemMoveL(CMoboViewRenderer::EMoveTopLeft);
	}
	

TKeyResponse CHelloWorldPlusAppView::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
	{
	TKeyResponse response = EKeyWasNotConsumed;
	// we only want the key press, not the key up/down event
	if (aType == EEventKey)
		{
		// check if the 2 key was pressed
		switch (aKeyEvent.iCode)
			{
			case '1':
				{
				iRenderer->MakeMoboMemMoveL(CMoboViewRenderer::EMoveTopLeft);
				response = EKeyWasConsumed;
				break;
				}
			case EKeyUpArrow:
				{
				iRenderer->MakeMoboMemMoveL(CMoboViewRenderer::EMoveUp);
				response = EKeyWasConsumed;
				break;
				}
			case EKeyDownArrow:
				{
				iRenderer->MakeMoboMemMoveL(CMoboViewRenderer::EMoveDown);
				response = EKeyWasConsumed;
				break;
				}
			case EKeyLeftArrow:
				{
				iRenderer->MakeMoboMemMoveL(CMoboViewRenderer::EMoveLeft);
				response = EKeyWasConsumed;
				break;
				}
			case EKeyRightArrow:
				{
				iRenderer->MakeMoboMemMoveL(CMoboViewRenderer::EMoveRight);
				response = EKeyWasConsumed;
				break;
				}
			case EKeyEnter:
			case EKeyOK:
				{
				iRenderer->MakeMoboMemMoveL(CMoboViewRenderer::EMoveShowSymbol);
				response = EKeyWasConsumed;
				break;
				}
			}
			if (response == EKeyWasConsumed)
				DrawDeferred();			
		}
	return response;
	// return the default functionality
	//return CCoeControl::OfferKeyEventL(aKeyEvent, aType);
	}


TCoeInputCapabilities CHelloWorldPlusAppView::InputCapabilities() const
	{
	// this class does not implement any 'unusual' input capabilities
	return TCoeInputCapabilities::ENone;
	}

void CHelloWorldPlusAppView::UserDraw() const
	{
	ActivateGc();
	Draw(Rect());
	DeactivateGc();
	}
