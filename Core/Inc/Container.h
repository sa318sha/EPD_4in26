/*
 * Container.h
 *
 *  Created on: Feb 25, 2025
 *      Author: kobru
 */

#ifndef INC_CONTAINER_H_
#define INC_CONTAINER_H_

#include "Drawable.h"
#include <vector>

class Container: public Drawable {
public:
	Container(UWORD xStart, UWORD yStart, UWORD xEnd, UWORD yEnd, Callback cb = nullptr):
		Drawable(cb),
		xStart(xStart), yStart(yStart), xEnd(xEnd), yEnd(yEnd)
//	, XLength(XEnd-XStart), YLength(YEnd - YStart)
	{

	}
//	void draw()
    void draw(FrameBuffer& fb, UWORD xMove = 0, UWORD yMove =0) override{
    	//TODO displace draws in the container?

//    	FrambeBuffer duplicate = Framebuffer(XLength, YLength, fb.getRotate(),fb.getColor());
    	UWORD x = xStart + xMove;
    	UWORD y = yStart + yMove;


    	for (Drawable* draws: drawables){
    		draws->draw(fb, x,y);
    	}

//    	fb.apply(duplicate);
    }

    void highlight(bool isSelected) override{
    	for (Drawable* draws: drawables){
			draws->highlight(isSelected);
		}
    }

    void addDrawable(Drawable * draw){
    	drawables.push_back(draw);
    }

private:
    UWORD xStart;
    UWORD yStart;
    UWORD xEnd;
    UWORD yEnd;
//    UWORD XLength;
//    UWORD YLength;
	std::vector<Drawable *> drawables;
};



#endif /* INC_CONTAINER_H_ */
