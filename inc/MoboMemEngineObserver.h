// MoboMemEngineObserver.h
// (c) Antti Juustila, 2003
//
// $Id: MoboMemEngineObserver.h,v 1.2 2004/02/24 20:57:21 Antti Exp $


#ifndef __MOBOMEMENGOBSERVER_H
#define __MOBOMEMENGOBSERVER_H

#include <e32base.h>

/**
* This class is used by the game controller to report game events to client side.
* @author Antti Juustila
* @version $Revision: 1.2 $
*/
class MMoboMemGameEngineObserver
	{
public:

	/**
	* Used by the game engine to notify of the starting of the game.
	*/
	virtual void GameStartedNotifyL() = 0;
	/**
	* Used by the game engine to notify that a symbol pair was found.
	*/
	virtual void PairsFoundNotifyL() = 0;
	/**
	* Used by the game engine to notify that an invalid pair was found.
	*/
	virtual void InvalidPairsOpenedNotifyL() = 0;
	/**
	* Used by the game engine to notify that the game has ended.
	* @param aEnteredHallOfFame If ETrue, the user entered the hall of fame.
	*/
	virtual void GameEndedNotifyL(TBool aEnteredHallOfFame) = 0;
	/**
	* Used by the game engine to query the player's name after game
	* has ended and the user enters the hall of fame.
	* @param aPlayerName The descriptor where the observer saves the player's name.
	*/
	virtual void GetPlayerNameL(TDes & aPlayerName) = 0;
	};


/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: MoboMemEngineObserver.h,v $
* Revision 1.2  2004/02/24 20:57:21  Antti
* Updated comments.
*
* Revision 1.1.1.1  2004/02/18 22:29:32  Antti
* Entering into cvs.
*
*
*/



#endif