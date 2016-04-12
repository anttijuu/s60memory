/* Copyright (c) 2002, Nokia Mobile Phones. All rights reserved */

#ifndef __HELLOWORLDPLUSAPPVIEW_H__
#define __HELLOWORLDPLUSAPPVIEW_H__


#include <coecntrl.h>


class MMoboMemGameEngine;
class CMoboViewRenderer;

/** 
  An instance of the Application View object for the HelloWorldPlus 
  example application
  */
class CHelloWorldPlusAppView : public CCoeControl
    {
public:

/**
  Create a CHelloWorldPlusAppView object, which will draw itself to aRect
  @param aRect the rectangle this view will be drawn to
  @param aEngine The engine used in drawing the view.
  @returns a pointer to the created instance of CHelloWorldPlusAppView
  */
    static CHelloWorldPlusAppView* NewL(const TRect& aRect, MMoboMemGameEngine * aEngine);

/**
  Create a CHelloWorldPlusAppView object, which will draw itself to aRect
  @param aRect the rectangle this view will be drawn to
  @param aEngine The engine used in drawing the view.
  @returns a pointer to the created instance of CHelloWorldPlusAppView
  */
    static CHelloWorldPlusAppView* NewLC(const TRect& aRect, MMoboMemGameEngine * iEngine);


/**
  Destroy the object and release all memory
  */
     ~CHelloWorldPlusAppView();

/**
  Draw this CHelloWorldAppView to the screen
  @param aRect the rectangle of this view that needs updating
  */
    void UserDraw() const;

/**
  Resets the game view.
  */
	void ResetViewL();
	
public:  // from CCoeControl
/**
  Draw this CHelloWorldPlusAppView to the screen
  @param aRect the rectangle of this view that needs updating
  */
    void Draw(const TRect& aRect) const;

/**
  Handle any user keypresses
  @param aKeyEvent holds the data for the event that occurred
  @param aType holds the type of key event that occured
  @returns a TKeyResponse indicating if the key was consumed or not
  */
    TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);

/**
  Return the capabilities of the OfferKeyEventL 
              method for this class
  @returns a TCoeInputCapabilities indicating the capabilities 
          for this class
  */
	TCoeInputCapabilities InputCapabilities() const;

private:

/**
   Perform the second phase construction of a CHelloWorldPlusAppView object
  @param aRect the rectangle this view will be drawn to
  */
    void ConstructL(const TRect& aRect);

/**
  Perform the first phase of two phase construction 
  */
    CHelloWorldPlusAppView(MMoboMemGameEngine * aEngine);
    
 private:
/**
  The game engine. This object does not own the engine, just uses it.
  */
 	MMoboMemGameEngine * iEngine;
/**
  The renderer that actually draws the game state to the view.
  By encapsulating the drawing to a separate object, it is easier
  to port the application to a different Symbian phone with different Ui's.
  */
 	CMoboViewRenderer * iRenderer;
    };


#endif // __HELLOWORLDPLUSAPPVIEW_H__
