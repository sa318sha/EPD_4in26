#pragma once

#include "main.h"

enum class Button {
    Up,
	Down,
	Left,
	Middle,
	Right,
	Error,
};

enum class ScreenOperations {

};

enum class DataOperations {
	Create,
	Delete
};



typedef struct {
    float temperature;
    uint8_t hour;
    uint8_t minute;
    bool AM;
} SetPointData;

typedef struct {
	SetPointData setpoints[MAX_SETPOINTS_PER_DAY];
    uint8_t setpointCount;
} DaySchedule;

enum class State {

	RefreshActiveScreen,
	FullRefreshActiveScreen,

    HomeScreen,
    MainMenuScreen,
    LowBatteryScreen,
	ScheduleScreen,
	AlertScreen,
	ClockDateScreen,

	SetPointScreen,
	Save,
	Cancel,
	IncreaseSetPoint,
	DecreaseSetPoint,
	TemperatureUpdate,
	Delete,

//	UpdateSetPointIncrease,
//	UpdateSetPointDecrease,


	NextScreen,
	PrevScreen,
	MenuScreen,
	PrevElement,
	NextElement,
	Interact,
	Error,
};

void setPointScreenCallback2(Button bt);
void setPointScreenCallback1(Button bt);
void updateSetPointDynamicElements(UBYTE index);
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

