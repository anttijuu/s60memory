/* Copyright (c) 2002, Nokia Mobile Phones. All rights reserved */

#ifndef __HELLOWORLDPLUS_DOCUMENT_H__
#define __HELLOWORLDPLUS_DOCUMENT_H__


#include <akndoc.h>

// Forward references
class CHelloWorldPlusAppUi;
class CEikApplication;

class MMoboMemGameEngine;

/**
* This class has been created by using the Series 60 HelloWorldPlus application
* as a template. The class is not documented further, except for the
* parts intimately related to the S60MoboMemory application.
*/
class CHelloWorldPlusDocument : public CAknDocument
    {
public:

/**  
  Construct a CHelloWorldPlusDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @returns a pointer to the created instance of CHelloWorldPlusDocument
  */
    static CHelloWorldPlusDocument* NewL(CEikApplication& aApp);

/**
  Construct a CHelloWorldPlusDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @returns a pointer to the created instance of CHelloWorldPlusDocument
  */
    static CHelloWorldPlusDocument* NewLC(CEikApplication& aApp);

/**
  Destroy the object and release all memory objects
  */
    ~CHelloWorldPlusDocument();

/**
  Create a CHelloWorldPlusAppUi object and return a pointer to it
  @returns a pointer to the created instance of the AppUi created
  */
    CEikAppUi* CreateAppUiL();

/**
  Returns a pointer to the game engine object.
  @returns The pointer to the game engine.
  */    
   MMoboMemGameEngine * Engine();
    
private:

/**
  Perform the second phase construction of a CHelloWorldPlusDocument object.
  Creates the engine object.
  */
    void ConstructL();

/**
  Perform the first phase of two phase construction 
  @param aApp application creating this document
  */
    CHelloWorldPlusDocument(CEikApplication& aApp);

private:

/**
  The game engine pointer. Owns the engine (creates and destroys the engine object).
  */
	MMoboMemGameEngine * iGameEngine;
    };


#endif // __HELLOWORLDPLUS_DOCUMENT_H__
