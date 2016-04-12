/* Copyright (c) 2002, Nokia Mobile Phones. All rights reserved */

#ifndef __HELLOWORLDPLUS_APPUI_H__
#define __HELLOWORLDPLUS_APPUI_H__

#include <aknappui.h>

#include "MoboMemEngineObserver.h"

class CHelloWorldPlusAppView;
class MMoboMemGameEngine;


/**
* This class has been created by using the HelloWorldPlus application
* as a template. The class is not documented further, except for the
* parts intimately related to the S60MoboMemory application.
*/

class CHelloWorldPlusAppUi : public CAknAppUi, public MMoboMemGameEngineObserver
    {
public:
/**
  Perform the second phase construction of a CHelloWorldPlusAppUi object
  this needs to be public due to the way the framework constructs the AppUi 
  */
    void ConstructL();

/**
  Perform the first phase of two phase construction.
  This needs to be public due to the way the framework constructs the AppUi 
  */
    CHelloWorldPlusAppUi();

/**
  Destroy the object and release all memory objects
  */
    ~CHelloWorldPlusAppUi();


public: // from CEikAppUi
/**
  Handle user menu selections
  @param aCommand the enumerated code for the option selected
  */
    void HandleCommandL(TInt aCommand);

	// from MMoboMemEngineObserver
	virtual void GameStartedNotifyL();
	virtual void PairsFoundNotifyL();
	virtual void InvalidPairsOpenedNotifyL();
	virtual void GameEndedNotifyL(TBool aEnteredHallOfFame);
	virtual void GetPlayerNameL(TDes & aPlayerName);

private:
/** The application view */
    CHelloWorldPlusAppView* iAppView;
/** The game engine. Not owned by this class, only used. */    
    MMoboMemGameEngine * iEngine;

    };


#endif // __HELLOWORLDPLUS_APPUI_H__

