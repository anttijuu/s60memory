// MoboViewRenderer.h
// (c) Antti Juustila, 2003
//
// $Id: MoboViewRenderer.h,v 1.3 2004/06/04 07:07:59 Antti Exp $

#ifndef __MoboViewRenderer_H
#define __MoboViewRenderer_H

#include "MoboMemEngineInterface.h"

class CGraphicsContext;
class TRect;

/**
* A renderer to draw the game to the view of the application.
* Makes it easier to port the app to different phone families.
* @see MMoboMemGameEngine
* @author Antti Juustila
* @version $Revision: 1.3 $
*/
class CMoboViewRenderer : public CBase
	{
public:

	/** The possible moves user can make using the keyboard. */
	enum TMoboMemMove
					{
					EMoveUp, /**< User moves up to next game symbol */
					EMoveDown, /**< User moves down to next game symbol */
					EMoveLeft, /**< User moves left to next game symbol */
					EMoveRight, /**< User moves right to next game symbol */
					EMoveShowSymbol, /**< User wants to open up the game symbol */
					EMoveTopLeft /**< User moves up to the top left game symbol */
					};
		
	/**
	* Factory method for creating the new renderer object.
	* @param aEngine The engine the renderer needs to do the drawing.
	* @returns The new renderer.
	*/
	static CMoboViewRenderer * NewL(MMoboMemGameEngine * aEngine);
	
	/**
	* Destructor deallocates all resources allocated by the class.
	*/
	~CMoboViewRenderer();

	/**
	* Draws the game view.
	* @param aMap The graphics device map needed to create fonts and do device independent drawing.
	* @param aGc The graphics context to draw to.
	* @param aDrawRect The rectangle to draw to.
	*/
	void DrawL(MGraphicsDeviceMap & aMap, CGraphicsContext & aGc, const TRect & aDrawRect);
	
	/**
	* Make the move based on user commands.
	*/
	void MakeMoboMemMoveL(TMoboMemMove aMove);
	
private:

	/**
	* Normal constructor. Must not leave!
	*/
	CMoboViewRenderer(MMoboMemGameEngine * aEngine);
	
	/**
	* Second phase constructor.
	*/
	void ConstructL();
	

private:
	/** The engine used in drawing. */
	MMoboMemGameEngine * iEngine;
	/** The index to current game symbol that has the focus in the view. */
	TInt iFocusedSymbolIndex;	
	};



/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: MoboViewRenderer.h,v $
* Revision 1.3  2004/06/04 07:07:59  Antti
* MoboMemMove called a leaving function, so had to add the trailing L to the name.
*
* Revision 1.2  2004/02/24 20:57:21  Antti
* Updated comments.
*
* Revision 1.1.1.1  2004/02/18 22:29:32  Antti
* Entering into cvs.
*
*
*/


#endif
