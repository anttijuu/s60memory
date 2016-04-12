// HallOfFameItem.h
// (c) Antti Juustila, 2004
//
// $Id: HallOfFameItem.h,v 1.2 2004/02/24 20:52:12 Antti Exp $

#ifndef __HALLOFFAMEITEM_H
#define __HALLOFFAMEITEM_H

#include <e32std.h>
#include <e32base.h>
#include <s32file.h>
#include <s32strm.h> 
#include <s32std.h>

class CHallOfFame; // Forward declaration

/**
* This class represents an item in a Top-10 list, alias Hall of Fame.
* Objects of this type are allocated from the stack. Add these objects into
* The Hall Of Fame after constructing them using
* <code>CHallOfFame::CheckAndAddNewItemL</code>.
*
* @author Antti Juustila
* @version $Revision: 1.2 $
*/
class THallOfFameItem  {

public:
	/**
	* This constructor is used only when CHallOfFame internalizes
	* items from a stream store.
	*/
	THallOfFameItem();

	/**
	* Constructs an item for the Hall of Fame.
	* @param aPlayerName The name of the player.
	* @param aPoints The points of the player.
	* @param aDateTime The date/time of the result.
	*/
	THallOfFameItem(const TDesC & aPlayerName, TInt aPoints, TInt64 aDateTime);
	
	/**
	* The points the user got.
	* @returns The points user got as a 32 bit integer.
	*/
	TInt Points() const;
	
	/**
	* The date and time of the result.
	* @returns The date/time as 64 bit integer.
	*/
	TInt64 DateTime() const;
	
	/**
	* Use to get the name of the player.
	* @param aName The name is stored into this descriptor.
	*/
	void GetName(TDes & aName) const;

	/**
	* Sets the name of the player.
	* @param aName Player's name.
	*/
	void SetName(const TDesC & aName);
	
	/**
	* Stores the item into a stream.
	* @param aStream The stream to store to.
	*/
	void     ExternalizeL(RWriteStream& aStream) const;
	
	/**
	* Reads an item from a stream.
	* @param aStream The stream to read from.
	*/
	void     InternalizeL(RReadStream& aStream);

	/** Offset to the attribute used in sorting the items.
	* Used by the <code>CHallOfFame</code> when sorting
	* the items in the Hall of Fame.
	* @returns The offset to the attribute used as the sort key.
	* @see CArrayFixFlat::Sort()
	* @see CHallOfFame
	*/
	static TInt KeyOffset();
			
private:
	/**
	* The points the user got in the game.
	*/
	TInt iPoints;
	
	/**
	* The date/time as a 64 bit integer.
	* See Symbian TTime class for more information.
	*/
	TInt64 iDateTime;
	
	/**
	* The name of the player who got the result.
	* We save, by using TBufC instead of TBuf, 32 * [number of hall of fame objects] bits of memory.
	*/
	TBufC<KMaxPlayerNameLength> iPlayer;
};



/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: HallOfFameItem.h,v $
* Revision 1.2  2004/02/24 20:52:12  Antti
* Added comments.
* Changed the player name from TBuf to TBufC.
*
* Revision 1.1.1.1  2004/02/18 22:29:32  Antti
* Entering into cvs.
*
*
*/


#endif