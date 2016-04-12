/* Copyright (c) 2002, Nokia Mobile Phones. All rights reserved */

#ifndef __HELLOWORLDPLUS_APPLICATION_H__
#define __HELLOWORLDPLUS_APPLICATION_H__

#include <aknapp.h>


/**
* This class has been created by using the Series 60 HelloWorldPlus application
* as a template. The class is not documented further, except for the
* parts intimately related to the S60MoboMemory application.
*/

class CHelloWorldPlusApplication : public CAknApplication
    {
public:  // from CApaApplication

/** 
  Returns the application DLL UID value
  @returns the UID of this Application/Dll
  */
    TUid AppDllUid() const;

protected: // from CEikApplication
/** 
  Create a CApaDocument object and return a pointer to it
  @returns a pointer to the created document
  */
    CApaDocument* CreateDocumentL();
    };

#endif // __HELLOWORLDPLUS_APPLICATION_H__
