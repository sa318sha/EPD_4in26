/*
 * DrawText.hpp
 *
 *  Created on: Mar 5, 2025
 *      Author: kobru
 */

#ifndef INC_DRAWTEXT_HPP_
#define INC_DRAWTEXT_HPP_


#include "Drawable.h"

class DrawText: public Drawable
{
private:

	UWORD Xstart;
	UWORD Ystart;

	const char * pString;
	PAINT_TIME* pTime ;

	sFONT* Font;
	UWORD Color_Foreground;
	UWORD Color_Background;
  /* data */
public:

    void draw(FrameBuffer& fb, UWORD xMove = 0, UWORD yMove = 0) override{
    	if(pTime == nullptr)
    		fb.Paint_DrawString_EN( Xstart + xMove,  Ystart + yMove,  pString, Font,  Color_Foreground,  Color_Background); // we want to pass in a array
    	else{
    		fb.Paint_DrawTime(Xstart + xMove, Ystart + yMove, pTime, Font, Color_Foreground, Color_Background);
    	}
    }

    void highlight(bool isSelected) override{

    }

    DrawText() = delete;

    DrawText(UWORD Xstart, UWORD Ystart, const char * pString, sFONT* Font, UWORD Color_Foreground, UWORD Color_Background):
    	Drawable(),
		Xstart(Xstart), Ystart(Ystart), pString(pString), pTime(nullptr), Font(Font), Color_Foreground(Color_Foreground), Color_Background(Color_Background) {}

    DrawText(UWORD Xstart, UWORD Ystart, PAINT_TIME *pTime, sFONT* Font,UWORD Color_Foreground, UWORD Color_Background):
		Drawable(),
		Xstart(Xstart), Ystart(Ystart), pString(nullptr), pTime(pTime), Font(Font), Color_Foreground(Color_Foreground), Color_Background(Color_Background) {}


    ~DrawText(){}
};






#endif /* INC_DRAWTEXT_HPP_ */
