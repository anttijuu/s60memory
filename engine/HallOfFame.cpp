// HallOfFame.cpp
// (c) Antti Juustila, 2003
//
// $Id: HallOfFame.cpp,v 1.1.1.1 2004/02/18 22:29:32 Antti Exp $
// See class documentation in the header file

#include "HallOfFame.h"
#include "HallOfFameItem.h"

CHallOfFame * CHallOfFame::NewL()
	{
	CHallOfFame * self = new (ELeave) CHallOfFame();
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop();
	return self;
	}

TBool CHallOfFame::CheckIfItemFitsToListL(THallOfFameItem & aItem)
	{
	// After adding the new element, list is sorted and does not exceed the max amount of items.
	TKeyArrayFix sortByPoints(THallOfFameItem::KeyOffset(), ECmpTInt);
	
	iItems->Sort(sortByPoints);
	
	TBool fitsInList = EFalse;
	TInt itemCount = iItems->Count();
	if (itemCount < KMaxItemsInHallOfFame)
		{
		// List is not full, can put the item there
		fitsInList = ETrue;
		}
	else
		{
		// If the points in the last item is less than the new item's, new item fits in the list.
		fitsInList = (*iItems)[itemCount-1].Points() > aItem.Points();
		}
	
	return fitsInList;
	}
	
TBool CHallOfFame::CheckAndAddNewItemL(THallOfFameItem & aItem)
	{
	// After adding the new element, list is sorted and does not exceed the max amount of items.
	TKeyArrayFix sortByPoints(THallOfFameItem::KeyOffset(), ECmpTInt);
	
	if (CheckIfItemFitsToListL(aItem))
		{
		iItems->AppendL(aItem);
		iItems->Sort(sortByPoints);

		// Take out the extra ones, if there.
		while (iItems->Count() > KMaxItemsInHallOfFame)
			{
			iItems->Delete(iItems->Count()-1);
			}
		return ETrue;
		}
	return EFalse;
	}
	
CHallOfFame::~CHallOfFame()
	{
	if (iItems)
		{
		iItems->Reset();
		}
	delete iItems;
	}
	
CHallOfFame::CHallOfFame()
	{
	}
	
void CHallOfFame::ConstructL()
	{
	iItems = new (ELeave) CArrayFixFlat<THallOfFameItem>(5);
	}
	

void CHallOfFame::FillHallOfFameListL(CDesCArray & aResults, const TDesC & aResultFormat, const TDesC & aDateFormat)
	{
	TInt thePoints;
	TInt64 theDateTime;
	TTime theTime;
	TBuf<KMaxPlayerNameLength> thePlayer;
	TBuf<20> timeBuf;
	TBuf<KMaxPlayerNameLength+20+20> listItemBuf;
		
	for (TInt counter = 0; counter < iItems->Count(); counter++)
		{
		thePoints = (*iItems)[counter].Points();
		theDateTime = (*iItems)[counter].DateTime();
		theTime = theDateTime;
		theTime.FormatL(timeBuf, aDateFormat);
		(*iItems)[counter].GetName(thePlayer);
		listItemBuf.Format(aResultFormat, thePoints, &thePlayer, &timeBuf);
		aResults.AppendL(listItemBuf);
		}
	}
	
void CHallOfFame::ClearList()
	{
	iItems->Reset();
	}
	
void CHallOfFame::ExternalizeL(RWriteStream& aStream) const
	{
	TInt itemCount = iItems->Count();
	
	aStream.WriteInt32L(itemCount);
	for (TInt counter = 0; counter < itemCount; counter++)
		{
		aStream << (*iItems)[counter];
		}
	}

void CHallOfFame::InternalizeL(RReadStream& aStream)
	{
	TInt itemCount = aStream.ReadInt32L();
	
	for (TInt counter = 0; counter < itemCount; counter++)
		{
		THallOfFameItem item;
		aStream >> item;
		iItems->AppendL(item);
		}
	}

	

/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: HallOfFame.cpp,v $
* Revision 1.1.1.1  2004/02/18 22:29:32  Antti
* Entering into cvs.
*
*
*/

