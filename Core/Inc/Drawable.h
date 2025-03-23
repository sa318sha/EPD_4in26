/*
 * Drawable.h
 *
 *  Created on: Feb 24, 2025
 *      Author: kobru
 */

#ifndef INC_DRAWABLE_H_
#define INC_DRAWABLE_H_

#include "main.h"
#include "../Fonts/fonts.h"
#include "FrameBuffer.h"
#include <functional>  // For std::function

class Drawable {

public:
//	?
	using Callback = void (*)();

	Drawable(Callback onSelect = nullptr,UWORD Rotate_ = ROTATE_0, UWORD Mirror_ = MIRROR_NONE, UWORD layer_ = 0):
		localRotate(Rotate_), localMirror(Mirror_), layer(layer_), onSelect(onSelect), updated(false), firstDraw(true), hide(false)
	{
		if(onSelect){
			isInteractable = true;
		}
		else{
			false;
		}
	}

    virtual void draw(FrameBuffer& fb, UWORD xMove = 0, UWORD yMove =0) = 0;

    virtual void onInteract(){
    	if(onSelect)
    		onSelect();
    };

    virtual void clearArea(FrameBuffer& fb, UWORD xStart = 0, UWORD yStart =0){}

    virtual void highlight(bool isSelected){};

    virtual void resetUpdated(){
    	updated = true;
    }

    void triggerAction() {
    	if (onSelect)
    		onSelect();
    }

    bool interactable(){
    	if (onSelect)
    		return true;
    	return false;
    }

    void setInteractability(bool i){
    	isInteractable = i;
    }

    void addCallback(Callback cb){
    	onSelect = cb;
    }

    virtual ~Drawable() = default;

    void setHide(bool h){
    	hide =h;
    }
    bool getHide(){
    	return hide;
    }

protected:


	UWORD localRotate;
	UWORD localMirror;

	UWORD layer;

	Callback onSelect;

	bool updated;
	bool firstDraw;
	bool hide;
	bool isInteractable;


};


#endif /* INC_DRAWABLE_H_ */
