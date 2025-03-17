
#include "ScreenManager.h"
#include "FreeRTOS.h"
#include "task.h"


void ScreenManager::initFirstTime(){
	if (EPDController){
		EPDController->pinInit();
		EPDController->EPD_4in26_Init();

		vTaskDelay(500);

	}
}

void ScreenManager::addScreen(Screen* scr) {
	screens.push_back(scr);
	if (screens.size() == 1){
		currentScreen = scr;
	}
}

void ScreenManager::updateActiveScreen(){
	if(currentScreen){
		currentScreen->render();
		const UBYTE* Image = currentScreen->getImage();

		//writes the image to the full back buffer
		EPDController->EPD_4in26_WriteToBuffer(Image, 0, 0,  EPD_4in26_WIDTH,EPD_4in26_HEIGHT);

		//updates the screen witht eh back buffer
		EPDController->EPD_4in26_TurnOnDisplay_Part();
	}
}
void ScreenManager::setNewActiveScreen(size_t index){
	if (index < screens.size()) {
		currentScreen = screens[index];
		displayActiveScreen();
	}
}

void ScreenManager::displayActiveScreen(){
	if(currentScreen){
		currentScreen->render();
		UBYTE* img = currentScreen->getImage();
		EPDController->EPD_4in26_Display_Base(img);
	}
}

void ScreenManager::onInteract(){
	if(currentScreen){
		currentScreen->interact();
	}
}


void ScreenManager::nextInteractable(){
	if(currentScreen){
		currentScreen->selectNext();
	}
}

void ScreenManager::prevInteractable(){
	if(currentScreen){
		currentScreen->selectPrev();
	}
}

void ScreenManager::buttonPress(){
	if(currentScreen){
		currentScreen->buttonPress();
	}
}

