#include "EPD_4in26.h"
#include "FrameBuffer.h"
#include "Screen.h"
#include "Rectangle.h"
#include "Circle.h"
#include "main.h"
#include "ScreenManager.h"
#include <queue>
#include "Debug.h"
#include "Container.h"
#include "BitMap.hpp"
#include "image_data.hpp"
#include "DrawText.hpp"
#include <stdio.h>
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "EPD_test.h"


#define Imagesize (((EPD_4in26_WIDTH % 8 == 0)? (EPD_4in26_WIDTH / 8 ): (EPD_4in26_WIDTH / 8 + 1)) * EPD_4in26_HEIGHT)
//static UBYTE BlackImage[Imagesize];

//static UBYTE screen1img[Imagesize];
//static UBYTE frameBufferScreen[Imagesize];

extern SPI_HandleTypeDef hspi1;
extern QueueHandle_t buttonQueue;
extern QueueHandle_t stateQueue;

//enum class State {
//    Interact,
//	Message,
//	Next,
//	Previous,
//};


void EPD_MainMenuWithQueue(){


	float setPoint = 23.5;
	char buffer[50]; // Buffer for formatted string

	float temparature = 24.5;
	char temparatureBuffer[50]; // Buffer for formatted string

	UWORD containerYLength = 100;
	UWORD containerYStart = EPD_4in26_HEIGHT - containerYLength;

	UWORD ContainerxLength = 150;
	UWORD ContainerxStart = 325;


	PAINT_TIME time;

	time.Hour = 10;
	time.Min = 50;
	time.hasSeconds = false;


	EPD_4in26 ePaper(RST_GPIO_Port, RST_Pin,
							    		DC_GPIO_Port, DC_Pin,
										SPI_CS_GPIO_Port, SPI_CS_Pin,
							    		BUSY_GPIO_Port, BUSY_Pin,
							    		PWR_GPIO_Port, PWR_Pin,
										&hspi1
										);


	ScreenManager screenManager(&ePaper);


	Screen screen1 = Screen();

	Container container1 = Container(ContainerxStart,containerYStart,138,65, []() {

	});

	Rectangle rect1 = Rectangle(0, 0, ContainerxLength, containerYLength, BLACK, DOT_PIXEL_2X2, DRAW_FILL_EMPTY);

	BitMap bitmap = BitMap(gImage_icon, 27, 2, 96, 96, WHITE);

	container1.addDrawable(&rect1);
	container1.addDrawable(&bitmap);


	snprintf(buffer, sizeof(buffer), "Setpoint: %.1fC", setPoint);
	snprintf(temparatureBuffer, sizeof(temparatureBuffer), "Temperature: %.1fC", temparature);

	DrawText setPointText = DrawText(358,121,buffer,&Font16, WHITE, BLACK);
	DrawText actualTemperature = DrawText(302,174,temparatureBuffer,&Font24, WHITE, BLACK);


	DrawText timeText = DrawText(338,36,&time,&Font24, WHITE, BLACK);

	BitMap battery = BitMap(gImage_battery, 0, 0, 64, 64, WHITE);

	BitMap wifi = BitMap(gImage_wifi,730,0, 64,64,WHITE);

	screen1.addDrawable(&container1);
	screen1.addDrawable(&setPointText);
	screen1.addDrawable(&actualTemperature);
	screen1.addDrawable(&timeText);
	screen1.addDrawable(&battery);
	screen1.addDrawable(&wifi);

	screenManager.addScreen(&screen1);

	screenManager.initFirstTime();
//
	screenManager.displayActiveScreen();

	Button buttonReceivedState;

	State state;

	screen1.setButtonCallback([](Button bt){
		State currState = State::Error;
		switch(bt){
		case Button::Middle:
			currState = State::Interact;
		    xQueueSend(stateQueue, &currState, portMAX_DELAY);
			break;
		}
		default:
			break;
	});


	while(1){
		if (xQueueReceive(buttonQueue, &buttonReceivedState, portMAX_DELAY) == pdPASS) {
			screenManager.buttonPress();
		}
		if (xQueueReceive(stateQueue, &state, portMAX_DELAY) == pdPASS) {
			switch(state){
			case Home:
				break;


			case Back:
				screenManager.prevInteractable();

				break;
			case Next:
				screenManager.nextInteractable();
				break;
			case Interact:
				screenManager.onInteract();
				break;
			case Error:
				break;

			case NextScreen:
			}
		}
	}
}

void EPD_MainMenu() {
	EPD_4in26 ePaper(RST_GPIO_Port, RST_Pin,
					    		DC_GPIO_Port, DC_Pin,
								SPI_CS_GPIO_Port, SPI_CS_Pin,
					    		BUSY_GPIO_Port, BUSY_Pin,
					    		PWR_GPIO_Port, PWR_Pin,
								&hspi1
								);

	ScreenManager screenManager(&ePaper);

	Screen* screen1 = new Screen();



	UWORD containerWidth = 138;
	UWORD containerHeight = 65;

	Container* BackContainer = new Container(169,415,containerWidth,containerHeight);
	Rectangle* rect1 = new Rectangle(0, 0, containerWidth, containerHeight, BLACK, DOT_PIXEL_2X2, DRAW_FILL_EMPTY);
	DrawText* backText = new DrawText(20,20,"Back",&Font16, WHITE, BLACK);

	BackContainer->addDrawable(rect1);
	BackContainer->addDrawable(backText);
//
	Container* homeContainer = new Container(331,415,containerWidth,containerHeight);
	Rectangle* homeRectangle = new Rectangle(0, 0, containerWidth, containerHeight, BLACK, DOT_PIXEL_2X2, DRAW_FILL_EMPTY);
	DrawText* homeText = new DrawText(20,20,"Home",&Font16, WHITE, BLACK);

	homeContainer->addDrawable(homeRectangle);
	homeContainer->addDrawable(homeText);

	Container* selectContainer = new Container(493,415,containerWidth,containerHeight);
	Rectangle* selectRectangle = new Rectangle(0, 0, containerWidth, containerHeight, BLACK, DOT_PIXEL_2X2, DRAW_FILL_EMPTY);
	DrawText* selectText = new DrawText(20,20,"Select",&Font16, WHITE, BLACK);

	selectContainer->addDrawable(selectRectangle);
	selectContainer->addDrawable(selectText);

	UWORD mainMenuWidth = 747;
	UWORD mainMenuHeight = 93;
	Container* scheduleContainer = new Container(26,87,mainMenuWidth,mainMenuHeight);
	Rectangle* scheduleRectangle = new Rectangle(0, 0, mainMenuWidth, mainMenuHeight, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
	DrawText* scheduleText = new DrawText(20,20,"Schedule",&Font24, WHITE, BLACK);

	scheduleContainer->addDrawable(scheduleRectangle);
	scheduleContainer->addDrawable(scheduleText);


	PAINT_TIME time;

	time.Hour = 10;
	time.Min = 50;
	time.hasSeconds = false;
	time.isPM = false;

	DrawText* timeText = new DrawText(338,20,&time,&Font24, WHITE, BLACK);




	BitMap* battery = new BitMap(gImage_battery, 0, 0, 64, 64, WHITE);

	BitMap* wifi = new BitMap(gImage_wifi,730,0, 64,64,WHITE);
//
	screen1->addDrawable(BackContainer);
	screen1->addDrawable(homeContainer);
	screen1->addDrawable(selectContainer);

	screen1->addDrawable(scheduleContainer);

	screen1->addDrawable(timeText);
	screen1->addDrawable(battery);
	screen1->addDrawable(wifi);




	screenManager.addScreen(screen1);

	screenManager.initFirstTime();
//
	screenManager.displayActiveScreen();

	while(1){

	}

}

void EPD_MainScreen() {
	EPD_4in26 ePaper(RST_GPIO_Port, RST_Pin,
						    		DC_GPIO_Port, DC_Pin,
									SPI_CS_GPIO_Port, SPI_CS_Pin,
						    		BUSY_GPIO_Port, BUSY_Pin,
						    		PWR_GPIO_Port, PWR_Pin,
									&hspi1
									);
	ScreenManager screenManager(&ePaper);

	Screen* screen1 = new Screen(EPD_4in26_WIDTH, EPD_4in26_HEIGHT, WHITE);

	UWORD containerYLength = 100;
	UWORD containerYStart = EPD_4in26_HEIGHT - containerYLength;

	UWORD ContainerxLength = 150;
	UWORD ContainerxStart = 325;
	Container * container1 = new Container(ContainerxStart,containerYStart,138,65);

	Rectangle* rect1 = new Rectangle(0, 0, ContainerxLength, containerYLength, BLACK, DOT_PIXEL_2X2, DRAW_FILL_EMPTY);

	BitMap* bitmap = new BitMap(gImage_icon, 27, 2, 96, 96, WHITE);

//	container1->addDrawable(circle1);
	container1->addDrawable(rect1);
	container1->addDrawable(bitmap);

	float setPoint = 23.5;
	char buffer[50]; // Buffer for formatted string

	snprintf(buffer, sizeof(buffer), "Setpoint: %.1fC", setPoint);

	DrawText* setPointText = new DrawText(358,121,buffer,&Font16, WHITE, BLACK);

	float temparature = 24.5;
	char temparatureBuffer[50]; // Buffer for formatted string

	snprintf(temparatureBuffer, sizeof(temparatureBuffer), "Temperature: %.1fC", temparature);
	DrawText* actualTemperature = new DrawText(302,174,temparatureBuffer,&Font24, WHITE, BLACK);


	PAINT_TIME time;

	time.Hour = 10;
	time.Min = 50;
	time.hasSeconds = false;

	DrawText* timeText = new DrawText(338,36,&time,&Font24, WHITE, BLACK);


	BitMap* battery = new BitMap(gImage_battery, 0, 0, 64, 64, WHITE);

	BitMap* wifi = new BitMap(gImage_wifi,730,0, 64,64,WHITE);

	screen1->addDrawable(container1);
	screen1->addDrawable(setPointText);
	screen1->addDrawable(actualTemperature);
	screen1->addDrawable(timeText);
	screen1->addDrawable(battery);
	screen1->addDrawable(wifi);


	screenManager.addScreen(screen1);

	screenManager.initFirstTime();

//	ePaper.EPD_4in26_Display(fb.getImage());
	screenManager.displayActiveScreen();

	while(1){

	}


}


void EPD_Clear(){
	EPD_4in26 ePaper(RST_GPIO_Port, RST_Pin,
					    		DC_GPIO_Port, DC_Pin,
								SPI_CS_GPIO_Port, SPI_CS_Pin,
					    		BUSY_GPIO_Port, BUSY_Pin,
					    		PWR_GPIO_Port, PWR_Pin,
								&hspi1
								);
	ePaper.pinInit();
	ePaper.EPD_4in26_Init();

	ePaper.EPD_4in26_Clear();
}

void EPD_EventHandling(){

	std::queue<State> q;
//	q.push(State::Interact);

	EPD_4in26 ePaper(RST_GPIO_Port, RST_Pin,
				    		DC_GPIO_Port, DC_Pin,
							SPI_CS_GPIO_Port, SPI_CS_Pin,
				    		BUSY_GPIO_Port, BUSY_Pin,
				    		PWR_GPIO_Port, PWR_Pin,
							&hspi1
							);

	Screen* screen1 = new Screen(EPD_4in26_WIDTH, EPD_4in26_HEIGHT, WHITE);

	Rectangle* rect1 = new Rectangle(200, 70, 300, 120, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY,
			[]() {

//		q.push(State::Next);
//
//		q.push(State::Interact);

//		LOG_INFO("interacted!");
	});

	Rectangle* rect2 = new Rectangle(400, 70, 500, 120, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY
//			,[&]() {
//
//		q.push(State::Next);
//		q.push(State::Interact);
//
////		LOG_INFO("interacted!");
//	}
	);

	Rectangle* rect3 = new Rectangle(600, 70, 700, 120, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY,
			[]() {

//		q.push(State::Next);
////		q.push(State::Interact);

//		LOG_INFO("interacted!");
	});
//	Rectangle* rect2 = new Rectangle(400, 300, 600, 350, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);

//	Circle* circle1 = new Circle(80, 70, 120, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
//	Circle* circle2 = new Circle(150, 200, 240, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);

//	screen1->addDrawable(circle1);
	screen1->addDrawable(rect1);
	screen1->addDrawable(rect2);
	screen1->addDrawable(rect3);

//	screen1->addDrawable(circle2);

	ScreenManager screenManager(&ePaper);

	screenManager.addScreen(screen1);

	screenManager.initFirstTime();
	screenManager.displayActiveScreen();

	for (; !q.empty(); q.pop()){
		State myState = q.front();
//
//		if(myState == State::Interact){
//			screenManager.onInteract();
//		}
//
//		if(myState == State::Next){
//			screenManager.nextInteractable();
//			screenManager.updateActiveScreen();
////			LOG_INFO("MESSAGE WAS RECIEVED");
//		}


//		vTaskDelay(pdMS_TO_TICKS(1000);
	}
}

void EPD_ScreenManager_PartialRefresh(){
	EPD_4in26 ePaper(RST_GPIO_Port, RST_Pin,
				    		DC_GPIO_Port, DC_Pin,
							SPI_CS_GPIO_Port, SPI_CS_Pin,
				    		BUSY_GPIO_Port, BUSY_Pin,
				    		PWR_GPIO_Port, PWR_Pin,
							&hspi1
							);


		Screen* screen1 = new Screen(EPD_4in26_WIDTH, EPD_4in26_HEIGHT, WHITE);
//		Screen screen2(EPD_4in26_WIDTH, EPD_4in26_HEIGHT, WHITE);
//		Screen screen3(EPD_4in26_WIDTH, EPD_4in26_HEIGHT, WHITE);

		Rectangle* rect1 = new Rectangle(400, 70, 500, 120, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
		Rectangle* rect2 = new Rectangle(400, 300, 500, 350, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);

		Circle* circle1 = new Circle(80, 70, 120, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
		Circle* circle2 = new Circle(150, 200, 240, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);

		screen1->addDrawable(circle1);
		screen1->addDrawable(rect1);
		screen1->addDrawable(circle2);

		ScreenManager screenManager(&ePaper);

		screenManager.addScreen(screen1);


		screenManager.initFirstTime();
		screenManager.displayActiveScreen();

		vTaskDelay(pdMS_TO_TICKS(1000));

		rect1->setColor(WHITE);
		screen1->addDrawable(rect2);

		screenManager.updateActiveScreen();

		vTaskDelay(pdMS_TO_TICKS(1000));


		rect1->setColor(BLACK);
		rect2->setColor(WHITE);

		screenManager.updateActiveScreen();

		vTaskDelay(pdMS_TO_TICKS(1000));
//		screen1.render();
//
//		ePaper.EPD_4in26_WriteToBuffer(screen1.getImage(), 0, EPD_4in26_HEIGHT-1, EPD_4in26_WIDTH-1,0);
//		ePaper.EPD_4in26_WriteToBuffer(fb.getImage(), 0,50, width,height);
//		ePaper.EPD_4in26_TurnOnDisplay_Part();
//		for(int i = 0; i < 9; i++){
//
//			if(i==1){
//				screen1.addDrawable(rect2);
//				ePaper.EPD_4in26_WriteToBuffer(screen1.getImage(), 0, EPD_4in26_HEIGHT-1, EPD_4in26_WIDTH-1,0);
//				ePaper.EPD_4in26_TurnOnDisplay_Part();
//				vTaskDelay(pdMS_TO_TICKS(1000);
//
//			}
//			screenManager.updateActiveScreen();
//			vTaskDelay(pdMS_TO_TICKS(1000);
//
//		}
}

void EPD_ScreenManager_PartialRefreshAndScreenSwitching (){
	EPD_4in26 ePaper(RST_GPIO_Port, RST_Pin,
			    		DC_GPIO_Port, DC_Pin,
						SPI_CS_GPIO_Port, SPI_CS_Pin,
			    		BUSY_GPIO_Port, BUSY_Pin,
			    		PWR_GPIO_Port, PWR_Pin,
						&hspi1
						);


	Screen screen1(EPD_4in26_WIDTH, EPD_4in26_HEIGHT, WHITE);
	Screen screen2(EPD_4in26_WIDTH, EPD_4in26_HEIGHT, WHITE);
	Screen screen3(EPD_4in26_WIDTH, EPD_4in26_HEIGHT, WHITE);

	Rectangle* rect1 = new Rectangle(400, 70, 500, 120, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
	Rectangle* rect2 = new Rectangle(150, 200, 220, 240, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);

	Circle* circle1 = new Circle(80, 70, 120, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
	Circle* circle2 = new Circle(150, 200, 240, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);

	screen1.addDrawable(circle1);
	screen1.addDrawable(rect1);
	screen2.addDrawable(circle2);
	screen3.addDrawable(rect1);
	screen3.addDrawable(rect2);





	ScreenManager screenManager(&ePaper);

	screenManager.addScreen(&screen1);
	screenManager.addScreen(&screen2);
	screenManager.addScreen(&screen3);

//	screenManager.renderAll();

	screenManager.initFirstTime();
	for(int i = 0; i < 9; i++){
		int n = i%3;
		screenManager.setNewActiveScreen(n);
		vTaskDelay(pdMS_TO_TICKS(1000));

		if(i%3 == 0){
//			screen1.clear(i%2==0?BLACK:WHITE);
			rect1->setFill(i%2==0?DRAW_FILL_EMPTY:DRAW_FILL_FULL);
			screenManager.updateActiveScreen();
			vTaskDelay(pdMS_TO_TICKS(1000));
//
		}

	}

}


void EPD_partial_refresh(){
	EPD_4in26 ePaper(RST_GPIO_Port, RST_Pin,
		    		DC_GPIO_Port, DC_Pin,
					SPI_CS_GPIO_Port, SPI_CS_Pin,
		    		BUSY_GPIO_Port, BUSY_Pin,
		    		PWR_GPIO_Port, PWR_Pin,
					&hspi1
					);
    ePaper.pinInit();

    ePaper.EPD_4in26_Init();
    ePaper.EPD_4in26_Clear();
    vTaskDelay(pdMS_TO_TICKS(500));

	Screen screen1(EPD_4in26_WIDTH, EPD_4in26_HEIGHT, WHITE);
//	screen1.clear(BLACK);
	Rectangle* rect1 = new Rectangle(0, 0, EPD_4in26_WIDTH, EPD_4in26_HEIGHT, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);


//	UWORD height =50;
//	UWORD width = 50;
//	UWORD testImageSize = (((width % 8 == 0)? (width / 8 ): (width / 8 + 1)) * height);
//	UBYTE testIMAGE[testImageSize];
//    FrameBuffer fb(testIMAGE,width, height,ROTATE_0,WHITE);
//    fb.Paint_DrawRectangle(0, 0, width, height, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);

	screen1.addDrawable(rect1);
	screen1.render();


	ePaper.EPD_4in26_Display_Base(screen1.getImage());

	vTaskDelay(pdMS_TO_TICKS(1000));

	rect1->setColor(WHITE);
	screen1.render();

	ePaper.EPD_4in26_WriteToBuffer(screen1.getImage(), 0, 0, EPD_4in26_WIDTH,EPD_4in26_HEIGHT);
//	ePaper.EPD_4in26_WriteToBuffer(fb.getImage(), 0,50, width,height);
	ePaper.EPD_4in26_TurnOnDisplay_Part();

	vTaskDelay(pdMS_TO_TICKS(1000));


	rect1->setColor(BLACK);
	screen1.render();

	ePaper.EPD_4in26_WriteToBuffer(screen1.getImage(), 0, 0, EPD_4in26_WIDTH,EPD_4in26_HEIGHT );
	ePaper.EPD_4in26_TurnOnDisplay_Part();

	vTaskDelay(pdMS_TO_TICKS(1000));

	rect1->setColor(WHITE);
	screen1.render();

	ePaper.EPD_4in26_WriteToBuffer(screen1.getImage(), 0, 0, EPD_4in26_WIDTH,EPD_4in26_HEIGHT );
	ePaper.EPD_4in26_TurnOnDisplay_Part();

	vTaskDelay(pdMS_TO_TICKS(1000));

	printf("Clear...\r\n");
	ePaper.EPD_4in26_Init();
	ePaper.EPD_4in26_Clear();

    printf("Goto Sleep...\r\n");
	ePaper.EPD_4in26_Sleep();

	vTaskDelay(pdMS_TO_TICKS(2000));//important, at least 2s

	printf("close 5V, Module enters 0 power consumption ...\r\n");
	ePaper.pinExit();
}

//void EPD_screen_manager(){
//	EPD_4in26 ePaper(RST_GPIO_Port, RST_Pin,
//		    		DC_GPIO_Port, DC_Pin,
//					SPI_CS_GPIO_Port, SPI_CS_Pin,
//		    		BUSY_GPIO_Port, BUSY_Pin,
//		    		PWR_GPIO_Port, PWR_Pin,
//					&hspi1
//					);
//
//    //finish init
//
//	Screen screen1(EPD_4in26_WIDTH, EPD_4in26_HEIGHT, WHITE);
//	Screen screen2(EPD_4in26_WIDTH, EPD_4in26_HEIGHT, WHITE);
//	Screen screen3(EPD_4in26_WIDTH, EPD_4in26_HEIGHT, WHITE);
//
//    Rectangle* rect1 = new Rectangle(80, 70, 130, 120, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
//    Rectangle* rect2 = new Rectangle(150, 200, 220, 240, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
//
//    Circle* circle1 = new Circle(80, 70, 120, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
//    Circle* circle2 = new Circle(150, 200, 240, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
//
//    screen1.addDrawable(circle1);
//    screen2.addDrawable(circle2);
//    screen3.addDrawable(rect1);
//    screen3.addDrawable(rect2);
//
//
//
//
//
//	ScreenManager screenManager(&ePaper);
//
//	screenManager.addScreen(&screen1);
//	screenManager.addScreen(&screen2);
//	screenManager.addScreen(&screen3);
//
//	screenManager.renderAll();
//
//	screenManager.init();
//
//	for(int i = 0; i < 9; i++){
//		int n = i%3;
//		screenManager.setActiveScreen(n);
//		screenManager.display();
//
//		vTaskDelay(pdMS_TO_TICKS(1000);
//	}
//
//
//
//}

void EPD_multiple_Screens(){
	EPD_4in26 ePaper(RST_GPIO_Port, RST_Pin,
	    		DC_GPIO_Port, DC_Pin,
				SPI_CS_GPIO_Port, SPI_CS_Pin,
	    		BUSY_GPIO_Port, BUSY_Pin,
	    		PWR_GPIO_Port, PWR_Pin,
				&hspi1
				);
	    ePaper.pinInit();

	    ePaper.EPD_4in26_Init();
	    ePaper.EPD_4in26_Clear();
	    vTaskDelay(pdMS_TO_TICKS(500));
	    //finish init

	    //start FRAMEBUFFER INIT
	    Screen screen1(EPD_4in26_WIDTH, EPD_4in26_HEIGHT);
	    Screen screen2(EPD_4in26_WIDTH, EPD_4in26_HEIGHT);

	    screen1.clear(WHITE);
	    screen2.clear(BLACK);

	    Rectangle* rect1 = new Rectangle(80, 70, 130, 120, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
	    Rectangle* rect2 = new Rectangle(150, 200, 220, 240, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);

	    screen1.addDrawable(rect1);
	    screen1.addDrawable(rect2);

	    screen1.render();


	    Circle* circle1 = new Circle(80, 70, 120, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
	    Circle* circle2 = new Circle(150, 200, 240, WHITE, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);

	    screen2.addDrawable(circle1);
	    screen2.addDrawable(circle2);

	    screen2.render();


	    int loop = 0;
	    while (loop != 3){
		    ePaper.EPD_4in26_Display_Base(screen1.getImage());
			vTaskDelay(pdMS_TO_TICKS(2000));

		    ePaper.EPD_4in26_Display_Base(screen2.getImage());
			vTaskDelay(pdMS_TO_TICKS(2000));

			loop++;
	    }
//		vTaskDelay(pdMS_TO_TICKS(2000);
	    //work / testing




	    // finish testing

		printf("Clear...\r\n");
		ePaper.EPD_4in26_Init();
		ePaper.EPD_4in26_Clear();

	    printf("Goto Sleep...\r\n");
		ePaper.EPD_4in26_Sleep();

		vTaskDelay(pdMS_TO_TICKS(2000));//important, at least 2s

		printf("close 5V, Module enters 0 power consumption ...\r\n");
		ePaper.pinExit();
}



void EPD_screen_multiple_objects(){
	EPD_4in26 ePaper(RST_GPIO_Port, RST_Pin,
	    		DC_GPIO_Port, DC_Pin,
				SPI_CS_GPIO_Port, SPI_CS_Pin,
	    		BUSY_GPIO_Port, BUSY_Pin,
	    		PWR_GPIO_Port, PWR_Pin,
				&hspi1
				);
	    ePaper.pinInit();

	    ePaper.EPD_4in26_Init();
	    ePaper.EPD_4in26_Clear();
	    vTaskDelay(pdMS_TO_TICKS(500));
	    //finish init

	    //start FRAMEBUFFER INIT
	    Screen screen1;

	    screen1.clear(WHITE);

	    Rectangle* rect1 = new Rectangle(80, 70, 130, 120, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
	    Rectangle* rect2 = new Rectangle(150, 200, 220, 240, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);

	    screen1.addDrawable(rect1);
	    screen1.addDrawable(rect2);

	    screen1.render();
//	    FrameBuffer fb(BlackImage,EPD_4in26_WIDTH, EPD_4in26_HEIGHT,ROTATE_0,WHITE);
//	    fb.Paint_Clear(WHITE);
//	    fb.Paint_DrawRectangle(80, 70, 130, 120, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
//	    fb.Paint_DrawNum(10, 33, 123456789, &Font12, BLACK, WHITE);
	    ePaper.EPD_4in26_Display_Base(screen1.getImage());
		vTaskDelay(pdMS_TO_TICKS(2000));
	    //work / testing




	    // finish testing

		printf("Clear...\r\n");
		ePaper.EPD_4in26_Init();
		ePaper.EPD_4in26_Clear();

	    printf("Goto Sleep...\r\n");
		ePaper.EPD_4in26_Sleep();

		vTaskDelay(pdMS_TO_TICKS(2000));//important, at least 2s

		printf("close 5V, Module enters 0 power consumption ...\r\n");
		ePaper.pinExit();
}


void EPD_basic_controller_test() {
    EPD_4in26 ePaper(RST_GPIO_Port, RST_Pin,
    		DC_GPIO_Port, DC_Pin,
			SPI_CS_GPIO_Port, SPI_CS_Pin,
    		BUSY_GPIO_Port, BUSY_Pin,
    		PWR_GPIO_Port, PWR_Pin,
			&hspi1
			);
    ePaper.pinInit();

    ePaper.EPD_4in26_Init();
    ePaper.EPD_4in26_Clear();
    vTaskDelay(pdMS_TO_TICKS(500));
    vTaskDelay(pdMS_TO_TICKS(2000));

	printf("Goto Sleep...\r\n");
	ePaper.EPD_4in26_Sleep();

	vTaskDelay(pdMS_TO_TICKS(2000));//important, at least 2s
//	test1.;
}

extern UBYTE defaultImage[];
void EPD_frame_buffer_draw_test() {
    EPD_4in26 ePaper(RST_GPIO_Port, RST_Pin,
    		DC_GPIO_Port, DC_Pin,
			SPI_CS_GPIO_Port, SPI_CS_Pin,
    		BUSY_GPIO_Port, BUSY_Pin,
    		PWR_GPIO_Port, PWR_Pin,
			&hspi1
			);
    ePaper.pinInit();

    ePaper.EPD_4in26_Init();
    ePaper.EPD_4in26_Clear();
    vTaskDelay(pdMS_TO_TICKS(500));
    //finish init

    //start FRAMEBUFFER INIT
	FrameBuffer& fb = FrameBuffer::getInstance();

//    FrameBuffer fb(defaultImage, EPD_4in26_WIDTH, EPD_4in26_HEIGHT,ROTATE_0,WHITE);
    fb.Paint_Clear(WHITE);
    fb.Paint_DrawRectangle(80, 70, 130, 120, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    fb.Paint_DrawNum(10, 33, 123456789, &Font12, BLACK, WHITE);
    ePaper.EPD_4in26_Display_Base(fb.getImage());
    vTaskDelay(pdMS_TO_TICKS(2000));
    //work / testing




    // finish testing

	printf("Clear...\r\n");
	ePaper.EPD_4in26_Init();
	ePaper.EPD_4in26_Clear();

    printf("Goto Sleep...\r\n");
	ePaper.EPD_4in26_Sleep();

	vTaskDelay(pdMS_TO_TICKS(2000));//important, at least 2s

	printf("close 5V, Module enters 0 power consumption ...\r\n");
	ePaper.pinExit();
    //finishes init


}
