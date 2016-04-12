// MoboSymbol.h
// (c) Antti Juustila, 2003
//
// $Id: MoboSymbol.h,v 1.2 2004/02/24 20:57:21 Antti Exp $


#ifndef __MOBOSYMBOL_H
#define __MOBOSYMBOL_H

#include <e32std.h>

class RWriteStream;


/**
* Memory game symbol class.
* @author Antti Juustila
* @version $Revision: 1.2 $
*/
class TMoboSymbol {
public:
	/**
	* The states of the game symbol (memory card).
	*/
	enum TSymbolState
						{
						EHidden = 0, /**< Symbol is hidden. */
						ERevealed /**< Symbol is shown. */
						};

	/**
	* Default constructor initializes the default values.
	*/
	TMoboSymbol();
	
	/**
	* Externalizes the symbol into a stream.
	* @param aStream The stream to save the object.
	*/	
	void ExternalizeL(RWriteStream & aStream) const;

	/**
	* Internalizes the symbol from a stream.
	* @param aStream The stream to read from.
	*/	
	void InternalizeL(RReadStream & aStream);

	/**
	* The symbol value. Each symbol has an integer
	* value. User interface may display this value
	* directly, or use an icon related to the symbol
	* value in displaying a symbol (a game card) on the screen.
	*/
	TInt 				iSymbol;
	
	/**
	* The state of the symbol.
	* See the TSymbolState enum.
	*/
	TSymbolState	iSymbolState;
	};


/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: MoboSymbol.h,v $
* Revision 1.2  2004/02/24 20:57:21  Antti
* Updated comments.
*
* Revision 1.1.1.1  2004/02/18 22:29:32  Antti
* Entering into cvs.
*
*
*/

#endif
