// HallOfFameItem.cpp
// (c) Antti Juustila
//
// $Id: HallOfFameItem.cpp,v 1.2 2004/02/24 20:51:50 Antti Exp $
// See class documentation in the header file

#include "HallOfFame.h"
#include "HallOfFameItem.h"

/**
* The implementation of the THallOfFameItem class.
* For more documentation, see the header file.
* @author Antti Juustila
* @version $Revision: 1.2 $
*/

THallOfFameItem::THallOfFameItem(const TDesC & aPlayerName, TInt aPoints, TInt64 aDateTime)
	{
	iPlayer = aPlayerName;
	iPoints = aPoints;
	iDateTime = aDateTime;
	}

TInt THallOfFameItem::Points() const
	{
	return iPoints;
	}
	
TInt64 THallOfFameItem::DateTime() const
	{
	return iDateTime;
	}
	
void THallOfFameItem::GetName(TDes & aName) const
	{
	aName = iPlayer;
	}
	
THallOfFameItem::THallOfFameItem() : iPoints(0), iDateTime(0)
	{
	}

void THallOfFameItem::SetName(const TDesC & aName)
	{
	iPlayer = aName;
	}
	

void THallOfFameItem::ExternalizeL(RWriteStream& aStream) const
	{
	aStream << iPlayer;
	aStream.WriteInt32L(iPoints);
	// There is no WriteInt64L, so we must write
	// the date info in two 32 bit TInts.
	aStream.WriteUint32L(iDateTime.High());
	aStream.WriteUint32L(iDateTime.Low());
	}
	
void THallOfFameItem::InternalizeL(RReadStream& aStream)
	{
	TUint32 high;
	TUint32 low;
	TPtr ptr(iPlayer.Des());
	aStream >> ptr;
	iPoints = aStream.ReadInt32L();
	// There is no WriteInt64L, so we must read
	// the date info to two 32 bit TInts.
	high = aStream.ReadUint32L();
	low = aStream.ReadUint32L();
	iDateTime.Set(high, low);
	}

TInt THallOfFameItem::KeyOffset()
	{
	return _FOFF(THallOfFameItem, iPoints);
	}


/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: HallOfFameItem.cpp,v $
* Revision 1.2  2004/02/24 20:51:50  Antti
* Added comments.
* Changed the player name from TBuf to TBufC.
*
* Revision 1.1.1.1  2004/02/18 22:29:32  Antti
* Entering into cvs.
*
*
*/

