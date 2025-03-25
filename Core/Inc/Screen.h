/*
 * Screen.h
 *
 *  Created on: Feb 24, 2025
 *      Author: kobru
 */

#ifndef INC_SCREEN_H_
#define INC_SCREEN_H_

//#include <vector>
#include "Drawable.h"
#include "FrameBuffer.h"
#include "EPD_4in26.h"
#include "Container.h"
#include <memory>
#include "EPD_test.h"

#define MAX_SCREEN_DRAWABLES 10 // Define a reasonable limit for the array

#include "DrawableObjects.hpp"
//#include

extern DaySchedule schedule[];
extern UBYTE currentDay;
class Screen {
public:
	using Callback = void (*)(Button button);

    Screen(Callback cb = nullptr, UWORD Width_ = EPD_4in26_WIDTH, UWORD Height_  = EPD_4in26_HEIGHT, UWORD colour = WHITE, UWORD Rotate= ROTATE_0):
    	currentSelection(-1),
		elementCount(0),
//		selectableCount(0),
		buttonCb(cb),
		Colour(colour)
    {

    }

    ~Screen() {
    }

    virtual void removeDrawable(Drawable* obj) {
        for (int i = 0; i < elementCount; ++i) {
            if (elements[i] == obj) {
                // Found the object; shift all remaining elements left
                for (int j = i; j < elementCount - 1; ++j) {
                    elements[j] = elements[j + 1];
                }

                elements[elementCount - 1] = nullptr;  // Clear last slot
                elementCount--;

                // Adjust selection if needed
                if (currentSelection == i) {
                    currentSelection = -1;
                } else if (currentSelection > i) {
                    currentSelection--;
                }

                break;
            }
        }
    }



    virtual void addDrawable(Drawable* obj) {
    	if (elementCount < MAX_SCREEN_DRAWABLES) {

			if(obj->interactable() && currentSelection == -1){
				currentSelection = elementCount;
			}

			elements[elementCount++] = obj;
		}
    }

    virtual inline UBYTE* getImage() {
    	FrameBuffer& fb = FrameBuffer::getInstance();

    	return fb.getImage();
    }

    virtual void optimizedRender() {


    	FrameBuffer& fb = FrameBuffer::getInstance();

        for (int i = 0; i < elementCount; i++) {
            elements[i]->draw(fb);
        }
    }
    virtual void cleanRender() {
    	clear(Colour);

    	//safety highlight
        if (currentSelection > -1) {
        	elements[currentSelection]->highlight(true);
        }

    	FrameBuffer& fb = FrameBuffer::getInstance();

//        }
        for (int i = 0; i < elementCount; i++) {
        	elements[i]->resetUpdated();
            elements[i]->draw(fb);
        }
    }

    virtual void clear(UWORD colour){
    	FrameBuffer& fb = FrameBuffer::getInstance();

    	fb.Paint_Clear(colour);
    }

    virtual void selectNext() {
    	if (currentSelection > -1){
    		elements[currentSelection]->highlight(false);
            int previousSelection = currentSelection;
            do{
                currentSelection = (currentSelection + 1) % elementCount;
                if(elements[currentSelection]->interactable()){
                	break;
                }
            }while(currentSelection !=  previousSelection);
            elements[currentSelection]->highlight(true);
    	}
    }

    virtual void selectPrev() {
    	if (currentSelection > -1)
		{
    		elements[currentSelection]->highlight(false);

            int previousSelection = currentSelection;
            do{
                currentSelection = (currentSelection == 0) ? elementCount - 1 : currentSelection - 1;
                if(elements[currentSelection]->interactable()){
                	break;
                }
            }while(currentSelection !=  previousSelection);

//            currentSelection = (currentSelection == 0) ? elementCount - 1 : currentSelection - 1;
            elements[currentSelection]->highlight(true);
		}
    }

    virtual void interact() {
    	if (currentSelection > -1)
		{
    		elements[currentSelection]->triggerAction();
		}

    }


    virtual void buttonPress(Button bt){
    	if(buttonCb){
    		buttonCb(bt);
    	}
    }

    virtual void setButtonCallback(Callback cb){
    	buttonCb = cb;
    }



protected:


//    subset of elements
    signed int currentSelection = -1;

    Drawable* elements[MAX_SCREEN_DRAWABLES];
    int elementCount;

//    Drawable* selectableElements[MAX_SCREEN_DRAWABLES];
//    int selectableCount;

    Callback buttonCb;
    UWORD Colour;

//    std::vector<Container *> container;

};

class SetPointScreen: public Screen {
public:
	SetPointScreen(Callback cb = nullptr):
		Screen(cb), currentSetPointElement(0), setPointElementsCount (0),isNewSetPoint(false) {
		setPointHoursContainer.addDrawable(&setPointHoursRectangle);
		setPointHoursContainer.addDrawable(&setPointHoursText);

		setPointMinutesContainer.addDrawable(&setPointMinutesRectangle);
		setPointMinutesContainer.addDrawable(&setPointMinutesText);

		setPointTempContainer.addDrawable(&setPointTempRectangle);
		setPointTempContainer.addDrawable(&setPointTempText);

		isNewSetPoint = true;
		addDrawable(&setPointHoursContainer);
		addDrawable(&setPointMinutesContainer);
		addDrawable(&setPointTempContainer);

		isNewSetPoint = false;
//		setPointScreen.addDrawable(&setPointHoursContainer);
//		setPointScreen.addDrawable(&setPointMinutesContainer);
//		setPointScreen.addDrawable(&setPointTempContainer);
//		setPointScreen.addDrawable(&SetPointC);	}
	}

    virtual void optimizedRender() {
    	FrameBuffer& fb = FrameBuffer::getInstance();

        for (int i = 0; i < setPointElementsCount; i++) {
        	setPointElements[i]->draw(fb);
        }
    	Screen::optimizedRender();
    }
    virtual void cleanRender() {
    	Screen::cleanRender();

    	FrameBuffer& fb = FrameBuffer::getInstance();
    	setPointUpdate();

        for (int i = 0; i < setPointElementsCount; i++) {
        	setPointElements[i]->resetUpdated();
        	setPointElements[i]->draw(fb);
        }
    }

    virtual void interact() override{
    	if(isNewSetPoint){
//    		if( setPointSelection > -1){
    			setPointElements[currentSetPointElement]->triggerAction();
//    		}
    	}
    	else{
    		Screen::interact();
    	}

    }

    void setPointUpdate() {
    	int currSelection = Screen::currentSelection;
    	DaySchedule day = schedule[currentDay];
    	if(currSelection < day.setpointCount){
    		SetPointData data = day.setpoints[currSelection];
//    		UWORD minutes = data.minute;
    		setPointTempText.setNumber(data.temperature);
    		setPointMinutesText.setNumber(data.minute);
    		setPointHoursText.setNumber(data.hour);
    		setPointHoursText.setDigit(0);
    		setPointMinutesText.setDigit(0);
    		setPointTempText.setDigit(1);


    	}else{
    		setPointTempText.setNumber(22);
    		setPointMinutesText.setNumber(0);
    		setPointHoursText.setNumber(11);
    		setPointHoursText.setDigit(0);
    		setPointMinutesText.setDigit(0);
    		setPointTempText.setDigit(1);
    	}
    }

    virtual void selectPrev() override{
    	if(isNewSetPoint){
				setPointElements[currentSetPointElement]->highlight(false);

				if(currentSetPointElement == 0){
					isNewSetPoint = false;
					return; //?
				}

				currentSetPointElement = currentSetPointElement - 1;
				setPointElements[currentSetPointElement]->highlight(true);
    	}
    	else {
    		Screen::selectPrev();
    	}
    	setPointUpdate();
    }

    virtual void selectNext() override {
    	if(isNewSetPoint){
			setPointElements[currentSetPointElement]->highlight(false);

			currentSetPointElement = (currentSetPointElement + 1) % setPointElementsCount;

			setPointElements[currentSetPointElement]->highlight(true);

    	}
    	else {
    		Screen::selectNext();
    	}
    	setPointUpdate();
    }

    virtual void addDrawable(Drawable* obj) {
    	if(isNewSetPoint){
    		if (setPointElementsCount < MAX_SCREEN_DRAWABLES) {

				if(obj->interactable() && currentSetPointElement == -1){
					currentSetPointElement = setPointElementsCount;
				}

				setPointElements[setPointElementsCount++] = obj;
			}
    	}
    	else{
    		Screen::addDrawable(obj);
    	}

    }

    void addSetpoint(){
    	isNewSetPoint = true;
    }
    void editCurrentSetPoint(){
    	isNewSetPoint = true;
    }
private:


//    char hoursBuffer[50];
    int minutes;
	int hours;
    float temperature;
    bool isAm;

    Container setPointHoursContainer = Container(340,60,120,130);
    HighLightOnInteractRectangle setPointHoursRectangle = HighLightOnInteractRectangle(0, 0, 120, 131, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);;
    HighlightableDrawText setPointHoursText = HighlightableDrawText(20,20,hours,&Font24,1, WHITE, BLACK);

//    char minutesBuffer[50];
    Container setPointMinutesContainer = Container(502,60,120,130);
    HighLightOnInteractRectangle setPointMinutesRectangle = HighLightOnInteractRectangle(0, 0, 120, 131, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);;
    HighlightableDrawText setPointMinutesText = HighlightableDrawText(20,20,minutes,&Font24, 1, WHITE, BLACK);

//    char tempBuffer[50];
    Container setPointTempContainer = Container(502,240,120,131);
    HighLightOnInteractRectangle setPointTempRectangle = HighLightOnInteractRectangle(0, 0, 120, 131, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);;
    HighlightableDrawText setPointTempText = HighlightableDrawText(20,20,temperature,&Font24,1, WHITE, BLACK);

    bool isNewSetPoint;

    int currentSetPointElement;
	Drawable* setPointElements[MAX_SCREEN_DRAWABLES];
	int setPointElementsCount;
//	bool isNewSetPoint;
};

//
//class SetPointScreen: public Screen {
//
//private:
//	std::unique_ptr<Drawable, FreeRTOSDeleter> dynamicDrawables;
//};



#endif /* INC_SCREEN_H_ */
