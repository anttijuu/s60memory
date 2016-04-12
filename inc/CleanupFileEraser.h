// CleanupFileEraser.h
// (c) Antti Juustila, 2003
//
// $Id: CleanupFileEraser.h,v 1.3 2004/02/24 20:57:21 Antti Exp $

#ifndef __CLEANUPFILEERASER_H
#define __CLEANUPFILEERASER_H

#include <e32std.h>

class RFs;

/**
* An utility class that deletes temporary files in case leave happens while
* writing to the temp file.
* <p>Construct with parameters, and push to cleanup stack using CleanupReleasePushL.
* On leave, Release is called, which deletes the file.
* <p>Why to use a class like this? If you write to the actual file and this leaves,
* the file will be closed if the file store is opened by using OpenLC, CreateLC or ReplaceLC.
* The cleanup stack will close the file as part of the handling of the exception. However,
* the app file is written only partially, so when trying to read all the data from a partially
* written file, this will lead to a Leave. The solution is to first write all the data into a 
* temporary file. If everything goes OK, the original file is deleted and replaced by the
* temporary file. However, if writing to a temp file fails with a leave, the partially written
* temporary file remains on the disk, wasting disk space. If every time we create a new
* temp file, these temp files will start filling the disk. The solution to this problem is to
* use this utility class. The temp file name together with an open session to file server
* is given to this TCleanupFileEraser object. Then this object is pushed to the cleanup stack
* using CleanupReleasePushL.
* Now, if a leave occurs, TCleanupFileEraser is on the cleanup stack, and error handling
* will call TCleanupFileEraser::Release(). The implementation will then use the RFs to delete
* the temporary file. This way, if the writing Leave's, original file remains in it's previous
* state, and the temporary file will be deleted.
* @see RFs
* @see CleanupStack
* @see CleanupReleasePushL
* @author Antti Juustila
* @version $Revision: 1.3 $
*/
class TCleanupFileEraser
	{
public:
	/**
	* Constructor.
	* @param aFs A file server session object.
	* @param aFileToDelete The name of the file. File must be closed, not read only, when released.
	*/
	TCleanupFileEraser(RFs & aFs, TDesC & aFileToDelete);
		
	/**
	* Destructor.
	*/
	~TCleanupFileEraser();

	/**
	* Releases the file named in iFileName by deleting it.
	*/
	void Release();
	
protected:
	/**
	* Normal constructor.
	*/
	TCleanupFileEraser();
	

private:
	/**
	* File server session, Connected elsewhere, also closed elsewhere.
	*/	
	RFs & iFs;
	
	/**
	* The file to be erased when Release called.
	*/
	TFileName iFileName;
	
	};



/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: CleanupFileEraser.h,v $
* Revision 1.3  2004/02/24 20:57:21  Antti
* Updated comments.
*
* Revision 1.2  2004/02/18 23:01:50  Antti
* Updated documentation.
*
* Revision 1.1.1.1  2004/02/18 22:29:32  Antti
* Entering into cvs.
*
*
*/


#endif
