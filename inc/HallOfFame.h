// HallOfFame.h
// (c) Antti Juustila, 2003
//
// $Id: HallOfFame.h,v 1.2 2004/02/24 20:57:21 Antti Exp $


#ifndef __HALLOFFAME_H
#define __HALLOFFAME_H

#include <e32std.h>
#include <badesca.h>
#include <e32base.h>
#include <s32file.h>

#include "MoboMemDefines.h"

class THallOfFameItem;

/**
* There can be only 10 items in the Hall of Fame list.
*/
const TInt KMaxItemsInHallOfFame = 10;

/**
* This class takes care of managing the Top-10 list in the  game.
* It must be allocated by using the NewL method.
* New items can be added by using the <code>CheckAndAddNewItemL</code>
* method, which will check if the new item can be put on the list.
* This class also takes care of storing and restoring the list to/from a file.
* Data file name will be HallOfFame, and it is located at \\Documents\\ folder
* in the C: disk.
* @author Antti Juustila
* @version $Revision: 1.2 $
*/

class CHallOfFame : public CBase {

public:
	/**
	* The factory method for creating a new Hall of Fame.
	* @returns New Hall of Fame object.
	*/
	static CHallOfFame * NewL();
	
	/**
	* Add a new item to the Hall of Fame.
	* If the points are not enough, the item will not be added.
	* Assumes the list is sorted and will sort the list after adding the new item.
	* Will make sure there are not more than max number of items in the list after adding.
	* @param aItem To be added to the Hal of Fame.
	* @returns ETrue if the item was added to the Hall Of Fame.
	*/
	TBool CheckAndAddNewItemL(THallOfFameItem & aItem);
	
	/**
	* Checks if a new item fits to the Hall of Fame.
	* If the points are not enough, the item will not fit into the list.
	* Will not add the new item to the list.
	* @param aItem To be added to the Hal of Fame.
	* @returns ETrue if the item fits to the Hall Of Fame.
	*/
	TBool CheckIfItemFitsToListL(THallOfFameItem & aItem);

	/**
	* Releases the array of items in the Hall of Fame.
	*/
	~CHallOfFame();

	/**
	* Puts the items in the Hall of Fame as descriptors into the descriptor array.
	* The array must be managed by the caller.
	*/
	void FillHallOfFameListL(CDesCArray & aResults, const TDesC & aResultFormat, const TDesC & aDateFormat);

	/**
	* Clears the Hall of Fame list.
	*/
	void ClearList();
	
	/**
	* Externalizes the items in the Hall of Fame into a stream.
	*/
	void     ExternalizeL(RWriteStream& aStream) const;
	/**
	* Internalizes the items in the Hall of Fame from a Stream.
	*/
	void     InternalizeL(RReadStream& aStream);
	
protected:
	/**
	* Default constructor.
	* Called by the NewL factory method.
	*/
	CHallOfFame();
	
	/**
	* Second phase constructor.
	* Called by the NewL factory method.
	*/
	void ConstructL();

private:
	/** The array of items in the Hall Of Fame. */
	CArrayFixFlat<THallOfFameItem> *iItems;
};


/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: HallOfFame.h,v $
* Revision 1.2  2004/02/24 20:57:21  Antti
* Updated comments.
*
* Revision 1.1.1.1  2004/02/18 22:29:32  Antti
* Entering into cvs.
*
*
*/


#endif // __HALLOFFAME_H