#pragma once

enum class Button {
    Up,
	Down,
	Left,
	Middle,
	Right,
	Error,
};

enum class State {
    Home,
	Back,
	NextScreen,
	PrevScreen,
	MenuScreen,
	PrevElement,

	NextElement,
	Interact,
	Error,
};

void EPD_basic_controller_test();
void EPD_frame_buffer_draw_test();
void EPD_screen_multiple_objects();
void EPD_multiple_Screens();
void EPD_screen_manager();
void EPD_partial_refresh();

void EPD_ScreenManager_PartialRefreshAndScreenSwitching();
void EPD_ScreenManager_PartialRefresh();

void EPD_EventHandling();
void EPD_Clear();

void EPD_MainScreen();
void EPD_MainMenu();
void EPD_MainMenuWithQueue();

