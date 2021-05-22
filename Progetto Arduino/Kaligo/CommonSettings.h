#ifndef __COMMON__
#define __COMMON__

//-------------------PINS----------------------
#define RED_CHANNEL_LED 32
#define GREEN_CHANNEL_LED 34
#define BLUE_CHANNEL_LED 36
#define COOLING_DOWN_FAN_PIN 33
#define FRONT_MAGNET_PIN 35
#define BACK_MAGNET_PIN 37
#define FRONT_DOOR_READ_PIN 20
#define BACK_DOOR_READ_PIN 21
#define UVLAMP_PIN 40
#define BOILER_PIN 41
#define BOILER_PUMP_PIN 42
#define BLUETOOTH_TX 11
#define BLUETOOTH_RX 10
#define SCK_PIN 5
#define CS_PIN 6
#define SO_PIN 7

//-------------------COMMAND----------------------
#define SATURATION_SECOND_COMMAND "saturSecond"
#define PARKING_SECOND_COMMAND "parkingSecond"
#define EXTRACTION_SECOND_COMMAND "extraSecond"
#define NIGHT_SECOND_COMMAND "nightSecond"
#define FOTOCATALISI_SECOND_COMMAND "fotocatalisiSecond"
#define STOP_COMMAND "stop"
#define START_COMMAND "start"
#define OPEN_DOOR_FRONT_COMMAND "openFront"
#define OPEN_DOOR_BACK_COMMAND "openBack"
#define MODE_CYCLE "mode"

//-------------------CONSTVALUE----------------------
#define BOUNCE_TIME 50
#define BOUNCE_TIME_READ 100
#define THRESHOLD_SUP 270
#define THRESHOLD_WORKING 260
#define THRESHOLD_INF 240
#define DEFAULT_NEBULIZATION_WAIT_TO_WARM_UP 10
#define DEFAULT_PARKING_SECOND 900
#define DEFAULT_FOTOCATALISI_SECOND 1800
#define DEFALUT_TIMER_RESET 1800

//-------------------CYCLE PERIODS----------------------
#define DEFAULT_NEBULIZATION_SECOND 20
#define DEFAULT_FOTOCATALISI_SECOND 1800
#define DEFAULT_NIGHT_SECOND 600

//-------------------TASKS PERIOD----------------------
#define SCHEDULER_PERIOD 10
#define TIMER_TASK_PERIOD 50
#define NEBULIZATION_PERIOD 50
#define NIGHTMODE_PERIOD 50
#define PHOTOCATALYSIS_PERIOD 50
#define BOILER_PERDIOD 100
#define COMUNICATION_PERIOD 100

//-------------------ENUMS----------------------
enum Color { BLUE, LIGHTBLUE, RED, GREEN, WHITE, YELLOW, PURPLE };
enum CycleMode {NEBULIZATION, PHOTOCATALYSIS, NIGHT_MODE};

void resetApplication();

void emptyFunction();

#endif