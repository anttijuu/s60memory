// MoboMemEngineInterface.h
// (c) Antti Juustila, 2004
//
// $Id: MoboMemEngineInterface.h,v 1.2 2004/02/24 20:57:21 Antti Exp $

#ifndef __MOBOMEMENGINEINTERFACE_H
#define __MOBOMEMENGINEINTERFACE_H

#include <e32base.h>
#include <e32std.h>
#include <badesca.h>

#include "MoboMemDefines.h"

class MMoboMemGameEngineObserver; // Forward declaration

/**
 * Interface to the game controller.
 * This interface will be used by the client side classes to access
 * the MoboMem game controller and engine object.
 * @author Antti Juustila
 * @version $Revision: 1.2 $
*/

class MMoboMemGameEngine
	{
public:
	virtual ~MMoboMemGameEngine() {};

	/**
	* Game is started by calling this method.
	* @param aPairCount How many symbol pairs to generate.
	*/
	virtual void StartGameL(TInt aPairCount) = 0;
	
	/**
	* As the user opens a symbol, this method is called.
	* @param aSymbolIndex The symbol's index number.
	*/
	virtual void OpenSymbolL(TInt aSymbolIndex) = 0;
	
	/**
	* The game engine observer is set by this method.
	* One of the UI objects will act as the observer.
	* @param aObserver The observer for the controller.
	*/
	virtual void SetObserver(MMoboMemGameEngineObserver * aObserver) = 0;
	
	/**
	* Call this method to get the time user took to finish the game.
	* The time includes the penalty points!
	* @return The time user took to finish the game, in seconds.
	*/
	virtual TTimeIntervalSeconds PlayTime() const = 0;

	/**
	* Call this method to get the penalty time user took while playing.
	* @return The penalty time in seconds.
	*/
	virtual TTimeIntervalSeconds PenaltyTime() const = 0;

	/**
	* Saves the state of the game.
	* It must be possible to continue the game from the state
	* it was left to.
	*/
	virtual void SaveGameStateL() = 0;

	/**
	* Restores the state of the game.
	* User can continue to play the game from the state
	* the game was stored.
	*/
	virtual void RestoreGameStateL() = 0;
	
	/**
	* Gets the number of pairs in the current game.
	* @returns The number of pairs in the game.
	*/
	virtual TInt NumberOfPairs() const = 0;
	
	/**
	* Gets the state of a symbol; is it shown or not.
	* @return Returns ETrue if symbol is shown.
	*/
	virtual TBool IsSymbolShown(TInt aSymbolIndex) const = 0;

	/**
	* Gets the symbol ID of nth symbol.
	* @param aSymbolIndex The index of the symbol
	* @returns The ID of the Symbol.
	*/
	virtual TInt SymbolID(TInt aSymbolIndex) const = 0;
	
	/**
	* Hides the symbols user tried to turn, that weren't right.
	*/
	virtual void HideRevealedSymbolsIfTwo() = 0;
	
	/**
	* Gets the Hall of Fame items as an array of descriptors.
	* Use the format parameters to format a single game result information into a
	* descriptor. These descriptors are then added to an array of descriptors
	* (for example, to a <code>CDesCArrayFlat object</code>). CDesCArrayFlat and other
	* descriptor arrays implement the interface class MDesCArray, which is returned by this function.
	* For instructions on how to do the formatting, see SDK docs for <code>TDes16::Format</code>,
	* and <code>TTime::Format</code> on how to format time data into a descriptor.
	* @param aResultFormat The formatting string for showing the results.
	* @param aDateFormat The formatting string used to format the date information.
	* @returns A pointer to an array of descriptors (left on the Cleanup stack!).
	*/
	virtual MDesCArray * HallOfFameDesCArrayLC(const TDesC & aResultFormat, const TDesC & aDateFormat) = 0;
	
	/**
	* Clears the hall of fame. Optionally can also store the data, so that
	* the stored data is always up to date.
	*/
	virtual void ClearListL() = 0;
};

/**
* A factory class for creating the concrete game controller.
* The purpose of this class is to hide the details of creating the game controller
* from the client class. This class here knows which implementation to create and how.
*/
class MoboMemEngineFactory {
public:
	/**
	* Creates the game engine.
	* The game engine must implement the <code>MMoboMemGameEngine</code>
	* interface. <b>Students must implement this method</b>!
	* @returns A pointer to the game engine object.
	*/
	IMPORT_C static  MMoboMemGameEngine * CreateEngineL();

	/**
	* A destructor for the factory.
	* Does nothing.
	*/	
	IMPORT_C virtual ~MoboMemEngineFactory();
};


/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: MoboMemEngineInterface.h,v $
* Revision 1.2  2004/02/24 20:57:21  Antti
* Updated comments.
*
* Revision 1.1.1.1  2004/02/18 22:29:32  Antti
* Entering into cvs.
*
*
*/


#endif
