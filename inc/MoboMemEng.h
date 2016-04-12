// MoboMemeng.h
// (c) Antti Juustila, 2003
//
// $Id: MoboMemEng.h,v 1.2 2004/02/24 20:57:21 Antti Exp $


#ifndef __MOBOMEMENG_H
#define __MOBOMEMENG_H

#include <e32base.h>
#include <e32std.h>

#include "MoboSymbol.h"


_LIT(KMoboMemCategory, "MOBOMEM");

const TInt KMemPanicInvalidArrayIndex = -1;
const TInt KMemPanicInvalidGameState = -2;


/**
* Actual game engine that handles the memory game symbols.
* @author Antti Juustila
* @version $Revision: 1.2 $
*/
class CMemoryGameBoard : public CBase
	{
public:
	/**
	* Constructor for the engine.
	*/
	CMemoryGameBoard();
	
	/**
	* The destructor.
	*/
	~CMemoryGameBoard();

	/**
	* Initializes the game engine to contain a certain amount of game symbols.
	* @param aCountOfSymbolPairs The number of symbols.
	*/
	void InitializeEngineL(TInt aCountOfSymbolPairs);

	/**
	* Retrieve a symbol based on its index.
	* @param aSymbolIndex The symbol to get.
	* @param aSymbol The place to put the symbol information.
	*/
	void GetSymbol(TInt aSymbolIndex, TMoboSymbol & aSymbol);
	
	/**
	* Hides a symbol based on its index.
	* @param aSymbolIndex The symbol to hide.
	*/
	void HideSymbol(TInt aSymbolIndex);
	
	/**
	* Reveals a symbol based on its index.
	* @param aSymbolIndex The symbol to show.
	*/
	void RevealSymbol(TInt aSymbolIndex);
	
	/**
	* Get the state of a symbol.
	* @param aSymbolIndex The index of the symbol to show.
	* @returns The state of the symbol.
	*/
	TMoboSymbol::TSymbolState SymbolState(TInt aSymbolIndex) const;
	
	/**
	* Tells if two symbols match.
	* @param aSymbolIndexA The first symbol.
	* @param aSymbolIndexB The second symbol.
	* @returns ETrue, if the symbols match, EFalse otherwise.
	*/
	TBool DoSymbolsMatch(TInt aSymbolIndexA, TInt aSymbolIndexB) const;
	
	/**
	* Checks if all symbols are already revealed.
	* @returns ETrue if all symbols are revealed, EFalse otherwise.
	*/
	TBool AreAllSymbolsRevealed() const;
	
	/**
	* Gets the number of symbol pairs in the game.
	* @returns The number of symbol pairs in the game.
	*/
	TInt SymbolPairCount() const;

	/**
	* Saves the engine into a stream.
	* @param aStream The stream to store the engine.
	*/
	void ExternalizeL(RWriteStream & aStream) const;

	/**
	* Reads the engine state from a stream.
	* @param aStream The stream to read from.
	*/
	void InternalizeL(RReadStream & aStream);
	
private:

	/**
	* Typedef'd array of symbols.
	*/
	typedef RArray<TMoboSymbol> RSymbolArray;

	/**
	* The number of symbol pairs generated.
	*/
	TInt iSymbolPairCount;
	
	/**
	* The symbols in the game.
	*/
	RSymbolArray iSymbols;
	
	/**
	* The seed number to use in generating random numbers.
	*/
	TInt64 iSeed;
	};

/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: MoboMemEng.h,v $
* Revision 1.2  2004/02/24 20:57:21  Antti
* Updated comments.
*
* Revision 1.1.1.1  2004/02/18 22:29:32  Antti
* Entering into cvs.
*
*
*/

#endif
