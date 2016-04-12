// MoboSymbol.cpp
// (c) Antti Juustila, 2003
//
// $Id: MoboSymbol.cpp,v 1.1.1.1 2004/02/18 22:29:32 Antti Exp $
// See class documentation in the header file

#include <e32math.h>
#include <s32strm.h>

#include "MoboSymbol.h"


/////////////////////////////////////////
// TMoboSymbol
/////////////////////////////////////////

TMoboSymbol::TMoboSymbol() : iSymbol(0), iSymbolState(EHidden)
	{
	}


void TMoboSymbol::ExternalizeL(RWriteStream & aStream) const
	{
	aStream.WriteInt32L(iSymbol);
	aStream.WriteInt32L(iSymbolState);
	
	}
	
void TMoboSymbol::InternalizeL(RReadStream & aStream)
	{
	iSymbol = aStream.ReadInt32L();
	iSymbolState = (TMoboSymbol::TSymbolState)aStream.ReadInt32L();
	}


/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: MoboSymbol.cpp,v $
* Revision 1.1.1.1  2004/02/18 22:29:32  Antti
* Entering into cvs.
*
*
*/

