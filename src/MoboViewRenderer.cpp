// MoboViewRenderer.cpp
// (c) Antti Juustila, 2004
//
// $Id: MoboViewRenderer.cpp,v 1.4 2004/06/04 07:05:42 Antti Exp $
// See class documentation in the header file

#include <gdi.h>


#include "MoboViewRenderer.h"

const TInt KSymbolsPerRow = 6;

CMoboViewRenderer * CMoboViewRenderer::NewL(MMoboMemGameEngine * aEngine)
	{
	CMoboViewRenderer * self = new (ELeave) CMoboViewRenderer(aEngine);
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop();
	return self;
	}


CMoboViewRenderer::~CMoboViewRenderer()
	{
	}
	
CMoboViewRenderer::CMoboViewRenderer(MMoboMemGameEngine * aEngine)
		: iEngine(aEngine)
	{
	}
	
void CMoboViewRenderer::ConstructL()
	{
	}
	
void CMoboViewRenderer::MakeMoboMemMoveL(TMoboMemMove aMove)
	{
	iEngine->HideRevealedSymbolsIfTwo();
	switch (aMove)
		{
		case EMoveUp: 
			{
			TInt tmp = iFocusedSymbolIndex - KSymbolsPerRow;
			if (tmp >= 0)
				iFocusedSymbolIndex = tmp;
			break;
			}
		case EMoveDown: 
			{
			TInt tmp = iFocusedSymbolIndex + KSymbolsPerRow;
			if (tmp < (iEngine->NumberOfPairs()*2))
				iFocusedSymbolIndex = tmp;
			break;
			}
		case EMoveLeft: 
			{
			iFocusedSymbolIndex--;
			if (iFocusedSymbolIndex < 0)
				iFocusedSymbolIndex = 0;
			break;
			}
		case EMoveRight: 
			{
			iFocusedSymbolIndex++;
			if (iFocusedSymbolIndex >= (iEngine->NumberOfPairs()*2))
				iFocusedSymbolIndex = (iEngine->NumberOfPairs()*2)-1;
			break;
			}
		case EMoveShowSymbol:
			{
			if (iFocusedSymbolIndex >= 0 && iFocusedSymbolIndex < (iEngine->NumberOfPairs()*2))
				iEngine->OpenSymbolL(iFocusedSymbolIndex);
			break;
			}
		case EMoveTopLeft:
			{
			iFocusedSymbolIndex = 0;
			break;
			}
		}
	}

/*
* DrawL may leave, for example, if creating fonts or if allocating resources needed for drawing.
*/		
void CMoboViewRenderer::DrawL(MGraphicsDeviceMap & aMap, CGraphicsContext & aGc, const TRect & aDrawRect)
	{
	// All measurements are in pixels; should use twips for device independent
	// drawing instead, but did not have time to implement this here...
	_LIT(KLitFaceName, "Symbian Viking");

	TRect boardRect(aDrawRect);
	boardRect.Shrink(5,5);
	
	CFont *font; 
	User::LeaveIfError(aMap.GetNearestFontInTwips(font, TFontSpec(KLitFaceName,10*20)));
	aGc.UseFont(font);

	const TInt KKGapBwSymbols = 2;
	const TInt KSymbolRectSize = (boardRect.Size().iWidth / KSymbolsPerRow) - 1;
	TRect symbolRect = boardRect;
	TInt baseline = font->AscentInPixels() + 7; 
	
	TInt pairs = iEngine->NumberOfPairs();
	TSize rectSize(KSymbolRectSize, KSymbolRectSize);
	symbolRect.SetSize(rectSize);

	TBuf<5> buf; // should be enough.
	TPoint textOrigin;
	aGc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	for (TInt counter = 0; counter < pairs*2; counter++)
		{
		if (iEngine->IsSymbolShown(counter))
			{
			aGc.SetBrushColor(KRgbYellow);
			buf.AppendNum(iEngine->SymbolID(counter));
			}
		else
			{
			aGc.SetBrushColor(KRgbGray);
			buf.Zero();			
			}
		if (iFocusedSymbolIndex == counter)
			{
			aGc.SetPenSize(TSize(3,3));
			aGc.SetPenColor(KRgbBlack);
			}
		else
			{
			aGc.SetPenColor(KRgbDarkGray);
			aGc.SetPenSize(TSize(1,1));
			}
		aGc.DrawRect(symbolRect);
		textOrigin = symbolRect.iTl;
		textOrigin.iX += (symbolRect.Width()/2)-2;
		textOrigin.iY += 2;
		if (buf.Length())
			{
			symbolRect.Shrink(1,1);
			aGc.DrawText(buf, symbolRect, baseline, CGraphicsContext::ECenter);
			symbolRect.Grow(1,1);
			}
		aGc.SetPenSize(TSize(1,1));
		aGc.SetPenColor(KRgbBlack);
		buf.Zero();
		if (!((counter+1) % KSymbolsPerRow))
			{
			symbolRect.iTl.iY += KSymbolRectSize + KKGapBwSymbols;
			symbolRect.iTl.iX = boardRect.iTl.iX;
			symbolRect.SetSize(rectSize);
			}
		else 
			{
			symbolRect.Move(KSymbolRectSize+KKGapBwSymbols, 0);
			}
		}
	aMap.ReleaseFont(font);
	}
	


/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: MoboViewRenderer.cpp,v $
* Revision 1.4  2004/06/04 07:05:42  Antti
* MoboMemMove called a leaving function, so had to add the trailing L to the name.
* Also changed the constants to follow Symbian naming convention (begin with K).
*
* Revision 1.3  2004/02/25 15:13:18  Antti
* Added a check that nonsensible symbols are not even tried to open.
* (index out of range).
*
* Revision 1.2  2004/02/24 20:57:43  Antti
* Updated comments.
*
* Revision 1.1.1.1  2004/02/18 22:29:32  Antti
* Entering into cvs.
*
*
*/

	