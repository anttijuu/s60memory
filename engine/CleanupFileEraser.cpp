// CleanupFileEraser.cpp
// (c) Antti Juustila, 2004
//
// $Id: CleanupFileEraser.cpp,v 1.1.1.1 2004/02/18 22:29:32 Antti Exp $
// See class documentation in the header file

#include <f32file.h>

#include "CleanupFileEraser.h"
	
/////////////////////////////////
// TCleanupFileEraser
////////////////////////////////

TCleanupFileEraser::TCleanupFileEraser(RFs & aFs, TDesC & aFileToDelete) : iFs(aFs)
{
	iFileName = aFileToDelete;
}
	
/**
* Destructor.
*/
TCleanupFileEraser::~TCleanupFileEraser()
{
}

/**
* Releases the file by deleting it.
*/
void TCleanupFileEraser::Release()
{
	iFs.Delete(iFileName);
}


/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: CleanupFileEraser.cpp,v $
* Revision 1.1.1.1  2004/02/18 22:29:32  Antti
* Entering into cvs.
*
*
*/


// EOF