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
		localRotate(Rotate_), localMirror(Mirror_), layer(layer_), onSelect(onSelect)
//	, selected(false)
	{}
    virtual void draw(FrameBuffer& fb, UWORD xMove = 0, UWORD yMove =0) = 0;
    virtual void onInteract(){
    	if(onSelect)
    		onSelect();
    };
    virtual void clearArea(FrameBuffer& fb){}
    virtual void highlight(bool isSelected){};
    void triggerAction() {
    	if (onSelect)
    		onSelect();
    }

    bool interactable(){
    	if (onSelect)
    		return true;
    	return false;
    }

    void addCallback(Callback cb){
    	onSelect = cb;
    }

    virtual ~Drawable() = default;

protected:


	UWORD localRotate;
	UWORD localMirror;

	UWORD layer;

//	bool interactable;
	Callback onSelect;
//	bool selected;

};


#endif /* INC_DRAWABLE_H_ */
