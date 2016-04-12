// MoboMemController.h
// (c) Antti Juustila, 2003
//
// $Id: MoboMemController.h,v 1.2 2004/02/24 20:57:21 Antti Exp $

#ifndef __MOBOMEMCONTROLLER_H
#define __MOBOMEMCONTROLLER_H

#include "MoboMemEngineInterface.h"

class CMemoryGameBoard;
class RWriteStream;
class RReadStream;
class CHallOfFame;

/**
* An implementation of the <code>MMoboMemGameEngine</code> interface.
* This should be implemented by the students.
* Things not documented here are documented in the <code>MMoboMemGameEngine</code>
* @see MMoboMemGameEngine
* @author Antti Juustila
* @version $Revision: 1.2 $
*/
class CMoboMemGameEngine : public CBase, public MMoboMemGameEngine
	{
public:
	/**
	* Factory method for creating the new game controller.
	* @returns The new controller object.
	*/
	IMPORT_C static CMoboMemGameEngine * NewL();
	
	/**
	* Destructor deallocates all resources allocated by the class.
	*/
	~CMoboMemGameEngine();

	// From MMoboMemGameEngine:
	IMPORT_C void StartGameL(TInt aPairCount);
	IMPORT_C void OpenSymbolL(TInt aSymbolIndex);
	IMPORT_C void SetObserver(MMoboMemGameEngineObserver * aObserver);
	IMPORT_C TTimeIntervalSeconds PlayTime() const;
	IMPORT_C TTimeIntervalSeconds PenaltyTime() const;
	IMPORT_C void SaveGameStateL();
	IMPORT_C void RestoreGameStateL();
	IMPORT_C TInt NumberOfPairs() const;
	IMPORT_C TBool IsSymbolShown(TInt aSymbolIndex) const;
	IMPORT_C TInt SymbolID(TInt aSymbolIndex) const;
	IMPORT_C void HideRevealedSymbolsIfTwo();
	IMPORT_C MDesCArray * HallOfFameDesCArrayLC(const TDesC & aResultFormat, const TDesC & aDateFormat);
	IMPORT_C void ClearListL();

	/**
	* Externalizer, stores the object into a stream.
	*/
	void ExternalizeL(RWriteStream & aStream) const;
	
	/**
	* Internalizer, reads the object from a stream.
	*/
	void InternalizeL(RReadStream & aStream);

private:
	/**
	* The game states.
	*/
	enum TMoboMemGameState {
									EGameInitialized = 0, /**< Game is not started. */
									EGameRunning, /**< Game is started. */
									EGameRevealedOne, /**< User revealed one symbol. */
									EGameEnded /**< Game has ended. */
									};

	/**
	* Normal constructor. Must not leave!
	*/
	CMoboMemGameEngine();
	
	/**
	* Second phase constructor.
	*/
	void ConstructL();
	
	/**
	* Ends the game, resets state, calculates points.
	*/
	void EndGameL();

private:
	/**
	* The game engine pointer.
	* Is owned by the controller.
	*/	
	CMemoryGameBoard * iEngine;
	
	/**
	* The game controller observer pointer.
	* This is the view class in the application client side.
	*/
	MMoboMemGameEngineObserver * iObserver;

	/**
	* The hall of fame contains the best game results.
	*/
	CHallOfFame * iHallOfFame;
	
	/** The current state of the game. */
	TMoboMemGameState iGameState;
	
	/** Start time of the game. */
	TTime iGameStarted;					
	
	/** Length the game took this time (in seconds). */
	TTimeIntervalSeconds iGameLengthInSeconds;					
	
	/**
	* The first of current symbols opened. 
	* If the second one differs from this one, symbols are hidden.
	*/
	TInt iFirstSymbolRevealed;

	/**
	* The second of current symbols opened. 
	* If the first one differs from this one, symbols are hidden.
	*/
	TInt iSecondSymbolRevealed;
	
	/**
	* The counter for opened wrong pairs.
	* The greater the counter value, the more points player gets.
	*/
	TInt iWrongAttemptCount;
	};



/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: MoboMemController.h,v $
* Revision 1.2  2004/02/24 20:57:21  Antti
* Updated comments.
*
* Revision 1.1.1.1  2004/02/18 22:29:32  Antti
* Entering into cvs.
*
*
*/


#endif
