/*
 * ScreenManager.h
 *
 *  Created on: Feb 25, 2025
 *      Author: kobru
 */

#ifndef INC_SCREENMANAGER_H_
#define INC_SCREENMANAGER_H_

#include <vector>
#include "Screen.h"
#include "ScreenState.h"
#include "EPD_4in26.h"

class ScreenManager {
public:
	ScreenManager() = delete;
	ScreenManager(EPD_4in26 * _EPDController):  EPDController(_EPDController), currentScreen(nullptr) {}

	//TODO:
	void initFirstTime();
	void initFromSleep();

	void addScreen(Screen * screen);
	void updateActiveScreen();

	void setNewActiveScreen(size_t index);
//	void switchScreens(size_t index);

	void displayActiveScreen();



	//STATE FUNCTIONS

	void buttonPress();
	void onInteract();
	void nextInteractable();
	void prevInteractable();


private:
	EPD_4in26* EPDController;
	Screen * currentScreen;

	std::vector<Screen*> screens;

	//TODO
//	std::vector<Screen*> inactiveScreen
};



#endif /* INC_SCREENMANAGER_H_ */
