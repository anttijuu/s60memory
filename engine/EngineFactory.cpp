// EngineFactory.cpp
// (c) Antti Juustila, 2003
//
// $Id: EngineFactory.cpp,v 1.2 2004/02/24 20:53:15 Antti Exp $
// See class documentation in the header file

#include "MoboMemEngineInterface.h"

// The header included here must be the header file for the student implementation of the game controller.
#include "MoboMemController.h"


EXPORT_C MMoboMemGameEngine * MoboMemEngineFactory::CreateEngineL()
	{
	// Replace this code with the construction of your own implementation!
	return CMoboMemGameEngine::NewL();
	}


EXPORT_C MoboMemEngineFactory::~MoboMemEngineFactory()
	{
	}
	

// requirement for E32 DLLs
EXPORT_C TInt E32Dll(TDllReason)
	{
	return 0;
	}
	

/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: EngineFactory.cpp,v $
* Revision 1.2  2004/02/24 20:53:15  Antti
* Changes due to naming changes in code.
*
* Revision 1.1.1.1  2004/02/18 22:29:32  Antti
* Entering into cvs.
*
*
*/

	