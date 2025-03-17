/*
 * Screen.h
 *
 *  Created on: Feb 24, 2025
 *      Author: kobru
 */

#ifndef INC_SCREEN_H_
#define INC_SCREEN_H_

#include <vector>
#include "Drawable.h"
#include "FrameBuffer.h"
#include "EPD_4in26.h"
#include "Container.h"

//UBYTE defaultImage[];
#include "EPD_test.h"

class Screen {
public:
	using Callback = void (*)(Button button);
//	friend class EPD_4in26;

    Screen(Callback cb = nullptr, UWORD Width_ = EPD_4in26_WIDTH, UWORD Height_  = EPD_4in26_HEIGHT, UWORD colour = WHITE, UWORD Rotate= ROTATE_0):
//    	defaultfb( Width_, Height_, Rotate, colour),
    	buttonCb(cb),
		Colour(colour)
    {
    	clear(Colour);
//        imageBuffer = image_;
    }

    ~Screen() {
//    	delete[] imageBuffer;
    }

    void addDrawable(Drawable* obj) {
    	elements.push_back(obj);

    	if(obj->interactable()){
    		if(selectableElements.size() == 0){
    			currentSelection = 0;
    		}
    		selectableElements.push_back(obj);
    	}
    }

//    void addSelectable(Drawable * obj)

    inline UBYTE* getImage() {
    	FrameBuffer& fb = FrameBuffer::getInstance();

    	return fb.getImage();
    }

    //TODO complete rerender of the screen -> including clear (may always be needed since there is only one framebuffer) - expensive -> placce for optimization
    void render() {
    	clear(Colour);

    	//safety highlight
    	if(currentSelection > -1){
    		selectableElements[currentSelection]->highlight(true);

    	}

    	FrameBuffer& fb = FrameBuffer::getInstance();

        for (auto obj : elements) {
            obj->draw(fb);
        }
    }

    void clear(UWORD colour){
    	FrameBuffer& fb = FrameBuffer::getInstance();

    	fb.Paint_Clear(colour);
    }

    void selectNext() {
    	if (currentSelection > -1){
    		selectableElements[currentSelection]->highlight(false);
			currentSelection = (currentSelection + 1) % selectableElements.size();
			selectableElements[currentSelection]->highlight(true);
    	}
    }

    void selectPrev() {
    	if (currentSelection > -1)
		{
			selectableElements[currentSelection]->highlight(false);

			currentSelection = (currentSelection == 0) ? selectableElements.size() - 1 : currentSelection - 1;

			selectableElements[currentSelection]->highlight(true);
		}
    }

    void interact() {
    	if (currentSelection > -1)
		{
    		selectableElements[currentSelection]->triggerAction();
		}
    }


    void buttonPress(){
    	if(buttonCb){
    		buttonCb();
    	}
    }

    void setButtonCallback(Callback cb){
    	buttonCb = cb;
    }



private:
//    UBYTE img[Imagesize];
//    static FrameBuffer defaultfb;
    UWORD Colour;
    // ideally would be hash maps but ask me if i care
    // (I do not care)
    std::vector<Drawable*> elements;

//    subset of elements
    signed int currentSelection = -1;
    std::vector<Drawable*> selectableElements;

    Callback buttonCb;

//    std::vector<Container *> container;

};



#endif /* INC_SCREEN_H_ */
