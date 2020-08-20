/* ---------------------------------------------------------------------------------------------
ALEDD 0.4.0 beta (work in progress)
Hardware/Firmware/Sketch/kdevice.xml by E.Burkowski / e.burkowski@konnekting.de, GPL Licensed
Compatible with: KONNEKTING Device Library 1.0.0 beta 4b
*/

/* this libraries are required (click on link and download with library manager):
FlashStorage:                     http://librarymanager/All#FlashStorage
DimmerControl:                    http://librarymanager/All#DimmerControl
Adafruit Neopixel:                http://librarymanager/All#Adafruit_Neopixel 
Adafruit_ZeroDMA:                 http://librarymanager/All#Zero_DMA
Adafruit Neopixel ZeroDMA 1.0.8:  http://librarymanager/All#Adafruit_DMA_neopixel_library 
NeoPixel Painter:                 http://librarymanager/All#NeoPixel_Painter
KONNEKTING Device Library:        http://librarymanager/All#Konnekting
*/

//developer settings
//#define DEVELOPMENT
//#define FAKE_EEPROM  //don't use this ;) 
//#define KDEBUG // comment this line to disable DEBUG mode


#include <DimmerControl.h>
#include <FlashAsEEPROM.h>
#include <Adafruit_NeoPixel_ZeroDMA.h>
#include <NeoPixelPainter.h>

#include "src/KonnektingDeviceLibrary/KonnektingDevice.h"

#include "aledd1.h"
#include "kdevice_ALEDD1.h"
#include "defines.h"

#ifdef KDEBUG
#include "src/KonnektingDeviceLibrary/DebugUtil.h"
#endif

#ifdef FAKE_EEPROM
#include "fakeEEPROM.h"
#endif

//global variables
bool initialized = false;
byte currentTask = TASK_IDLE; //0xFE - idle
byte lastTask = TASK_IDLE;
byte lastTaskBeforeMessage = 0; // all LEDs are off
byte lastStaticColor[4] = {0, 0, 0, 0};
bool staticColorReady = false;
byte sendSceneNumber = 0xFF;
byte lastDimmerValue = 0;
unsigned long lastAnimMillis = 0;
bool nightMode = false;

byte curveR[256];
byte curveG[256];
byte curveB[256];
byte curveW[256];

word longClickDurationBtn = 500;
unsigned long clickMillis = 0;
bool buttonPressed = false;
bool ledTestMode = false;
bool pixelsShow = false;

//XML group: LED
uint8_t ledType = 0xC6; // ~ NEO_RGBW, see Adafruit_NeoPixel.h for more infos
bool rgbw = true;
byte mixedWhite[] = {255,240,224};
uint16_t numberLeds = 600; //amount of leds on a stripe
uint8_t firstOnValue = 1;
uint8_t maxR = 255; // to match the same brightness on different colors
uint8_t maxG = 255; // reduce brightnes of some colors
uint8_t maxB = 255; // also usefull to make not "to blueisch" white
uint8_t maxW = 255; // recomended values: R:255,G:176,B:240,W:255
//uint8_t whiteType = 0; // if RGBW strip used, 0=warm, 1=neutral, 2=cold
float gammaCorrection = 1.0;
//XML group: Dimmer
byte softOnOffTimeList[] = {0, 3, 5, 7, 10, 15, 20}; //hundreds of milliseconds: 0,300,500...
byte relDimTimeList[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 20}; //seconds
byte valueMinDay;
byte valueMaxDay;
byte valueMinNight;
byte valueMaxNight;
//XML group: Scenes
byte scene[64];
//XML group: User color 1-5
byte ucRed[USERCOLORS];
byte ucGreen[USERCOLORS];
byte ucBlue[USERCOLORS];
byte ucWhite[USERCOLORS];
byte new3Byte[3] = {0,0,0};
byte new6Byte[6] = {0,0,0,0,0,0};
byte newRGBW[4] = {0,0,0,0};
byte valuesRGBW[4] = {0,0,0,0};
byte newHSV[3] = {0,0,0};
byte valuesHSV[3] = {0,0,0};
bool rgbwChanged = false;
bool hsvChanged = false;
bool acceptNewRGBW = false;
bool acceptNewHSV = false;
unsigned long rgbwChangedMillis = 0;
unsigned long hsvChangedMillis = 0;
word rgbwhsvChangedDelay = 50;

//XML group messages:
//Message 1
bool statusM1 = false; //false = wait and do nothing, true = show message1Value
byte newValueM1 = 0; //0 = all LEDs off, 1-255 corresponds to percentage of leds (255 = all LEDs are on, 127 = only 50% of LEDs are on)
byte lastValueM1 = 0;
word ledFirstM1;
word ledLastM1;
byte ledColorM1[4] = {0, 0, 0, 0};
//Message 2
bool statusM2 = false; //false = wait and do nothing, true = show message1Value
byte newValueM2 = 0; //0 = all LEDs off, 1-255 corresponds to percentage of leds (255 = all LEDs are on, 128 = only 50% of LEDs are on)
byte lastValueM2 = 0;
word ledFirstM2;
word ledLastM2;
byte ledColorM2[4] = {0, 0, 0, 0};
//Message 3
bool statusM3 = false; //false = wait and do nothing, true = show message1Value
byte newValueM3 = 0; //0 = all LEDs off, 1-255 corresponds to percentage of leds (255 = all LEDs are on, 127 = only 50% of LEDs are on)
byte lastValueM3 = 0;
word ledFirstM3;
word ledLastM3;
byte ledColorM3[4] = {0, 0, 0, 0};
//Message 4
bool statusM4 = false; //false = wait and do nothing, true = show message1Value
byte newValueM4 = 0; //0 = all LEDs off, 1-255 corresponds to percentage of leds (255 = all LEDs are on, 128 = only 50% of LEDs are on)
byte lastValueM4 = 0;
word ledFirstM4;
word ledLastM4;
byte ledColorM4[4] = {0, 0, 0, 0};

//XML group: Power supply control
bool allLedsOff = true;
bool powerSupplyState = false;
bool powerSupplyTurnOn = false;
bool powerSupplyTurnOff = false;
bool powerSupplyControl = false;
unsigned long powerSupplyOffDelay = 30000; 
unsigned long powerSupplyOffMillis = 0;
bool psStateChecked = false;
unsigned long psStateCheckedMillis = 0;
bool lastState = false;

//create some instances
Adafruit_NeoPixel_ZeroDMA *neopixels;
NeoPixelPainterCanvas *pixelcanvas;
NeoPixelPainterCanvas *pixelcanvas2;
NeoPixelPainterBrush *pixelbrush;
NeoPixelPainterBrush *pixelbrush2;
NeoPixelPainterBrush *pixelbrush3;
NeoPixelPainterBrush *pixelbrush4on2; //brush 4 on cancas 2
HSV brushcolor;
DimmerControl dimmer;

//make functions known
void showPixels ();

#include "hsvrgb.h"
#include "animations.h"

#include "led_functions.h"
#include "scenes.h"
#include "button.h"
#include "knx_events.h"

void setup() {
    pinMode(PROG_LED_PIN, OUTPUT);
    pinMode(PROG_BUTTON_PIN, INPUT_PULLUP);
    pinMode(POWER_SUPPLY_PIN, INPUT);
    attachInterrupt(PROG_BUTTON_PIN, progButtonPressed, CHANGE);

#ifdef KDEBUG
    SerialUSB.begin(115200);
    while (!SerialUSB);
    Debug.setPrintStream(&SerialUSB);
#endif
#ifdef FAKE_EEPROM
    initFakeEeprom();
#endif

    Konnekting.setMemoryReadFunc(&readMemory);
    Konnekting.setMemoryWriteFunc(&writeMemory);
    Konnekting.setMemoryUpdateFunc(&updateMemory);
    Konnekting.setMemoryCommitFunc(&commitMemory);
    Konnekting.init(SerialKNX, &progLed, MANUFACTURER_ID, DEVICE_ID, REVISION);
 
#ifndef FAKE_EEPROM
    for (int i = 0; i < Konnekting.getFreeEepromOffset(); i++) {
        Debug.println(F("\t\twriteMemory(%d,0x%02X);"), i, EEPROM.read(i));
    }
#endif
    if (!Konnekting.isFactorySetting()){
        //XML group: LED
        ledType = Konnekting.getUINT8Param(PARAM_led_type);
        if(ledType == NEO_RGB || ledType == NEO_RBG || ledType == NEO_GRB || 
           ledType == NEO_GBR || ledType == NEO_BRG || ledType == NEO_BGR) rgbw = false;
        numberLeds = Konnekting.getUINT16Param(PARAM_number_leds_strip);
        firstOnValue = Konnekting.getUINT8Param(PARAM_first_on_value);
        maxR = Konnekting.getUINT8Param(PARAM_r_correction);
        maxG = Konnekting.getUINT8Param(PARAM_g_correction);
        maxB = Konnekting.getUINT8Param(PARAM_b_correction);
        maxW = Konnekting.getUINT8Param(PARAM_w_correction);
        gammaCorrection = Konnekting.getUINT8Param(PARAM_gamma_correction) * 0.1;
        mixedWhite[0] = Konnekting.getUINT8Param(PARAM_wr);
        mixedWhite[1] = Konnekting.getUINT8Param(PARAM_wg);
        mixedWhite[2] = Konnekting.getUINT8Param(PARAM_wb);
        //XML group: Dimmer
        dimmer.setDurationAbsolute(softOnOffTimeList[Konnekting.getUINT8Param(PARAM_time_soft)] * 100);
        dimmer.setDurationRelative(relDimTimeList[Konnekting.getUINT8Param(PARAM_time_rel)] * 1000);
        dimmer.setValueFunction(&setLeds);
        valueMinDay = Konnekting.getUINT8Param(PARAM_day_min);
        valueMaxDay = Konnekting.getUINT8Param(PARAM_day_max);
        valueMinNight = Konnekting.getUINT8Param(PARAM_night_min);
        valueMaxNight = Konnekting.getUINT8Param(PARAM_night_max);
        //set day values until we know if it is day or night
        setDayNightValues(false);
        //XML group: User colors
        for (byte uc = 0; uc < USERCOLORS; uc++) {
            ucRed[uc]   = Konnekting.getUINT8Param(PARAM_uc1r + 4 * uc);
            ucGreen[uc] = Konnekting.getUINT8Param(PARAM_uc1g + 4 * uc);
            ucBlue[uc]  = Konnekting.getUINT8Param(PARAM_uc1b + 4 * uc);
            ucWhite[uc] = Konnekting.getUINT8Param(PARAM_uc1w + 4 * uc);
        }
        //XML group: Message 1:
        ledFirstM1    = Konnekting.getUINT16Param(PARAM_m1first) - 1; //Code: count from 0.., Suite: Count from 1..
        ledLastM1     = Konnekting.getUINT16Param(PARAM_m1last) - 1;
        ledColorM1[R] = Konnekting.getUINT8Param(PARAM_m1r);
        ledColorM1[G] = Konnekting.getUINT8Param(PARAM_m1g);
        ledColorM1[B] = Konnekting.getUINT8Param(PARAM_m1b);
        ledColorM1[W] = Konnekting.getUINT8Param(PARAM_m1w);
        //XML group: Message 2:
        ledFirstM2    = Konnekting.getUINT16Param(PARAM_m2first) - 1;
        ledLastM2     = Konnekting.getUINT16Param(PARAM_m2last) - 1;
        ledColorM2[R] = Konnekting.getUINT8Param(PARAM_m2r);
        ledColorM2[G] = Konnekting.getUINT8Param(PARAM_m2g);
        ledColorM2[B] = Konnekting.getUINT8Param(PARAM_m2b);
        ledColorM2[W] = Konnekting.getUINT8Param(PARAM_m2w);
        //XML group: Message 3:
        ledFirstM3    = Konnekting.getUINT16Param(PARAM_m3first) - 1; //Code: count from 0.., Suite: Count from 1..
        ledLastM3     = Konnekting.getUINT16Param(PARAM_m3last) - 1;
        ledColorM3[R] = Konnekting.getUINT8Param(PARAM_m3r);
        ledColorM3[G] = Konnekting.getUINT8Param(PARAM_m3g);
        ledColorM3[B] = Konnekting.getUINT8Param(PARAM_m3b);
        ledColorM3[W] = Konnekting.getUINT8Param(PARAM_m3w);
        //XML group: Message 4:
        ledFirstM4    = Konnekting.getUINT16Param(PARAM_m4first) - 1;
        ledLastM4     = Konnekting.getUINT16Param(PARAM_m4last) - 1;
        ledColorM4[R] = Konnekting.getUINT8Param(PARAM_m4r);
        ledColorM4[G] = Konnekting.getUINT8Param(PARAM_m4g);
        ledColorM4[B] = Konnekting.getUINT8Param(PARAM_m4b);
        ledColorM4[W] = Konnekting.getUINT8Param(PARAM_m4w);
        //XML group: power supply
        powerSupplyControl = Konnekting.getUINT8Param(PARAM_ps_control);
        powerSupplyOffDelay = Konnekting.getUINT8Param(PARAM_ps_delay_off) * 60000;
        if(!powerSupplyControl){
            powerSupplyState = true;
        }
#ifdef KDEBUG
        Debug.println(F("User Colors:"));
        Debug.println(F("Idx\tR\tG\tB\tW"));
        for (byte uc = 0; uc < USERCOLORS; uc++) {
            Debug.println(F("%d\t%d\t%d\t%d\t%d"),uc,ucRed[uc],ucGreen[uc],ucBlue[uc],ucWhite[uc]);
        }
        Debug.println(F("Message 1: first LED: %d, last LED: %d, R: %d, G: %d, B: %d, W: %d"), ledFirstM1, ledLastM1, ledColorM1[R], ledColorM1[G], ledColorM1[B], ledColorM1[W]);
        Debug.println(F("Message 2: first LED: %d, last LED: %d, R: %d, G: %d, B: %d, W: %d"), ledFirstM2, ledLastM2, ledColorM2[R], ledColorM2[G], ledColorM2[B], ledColorM2[W]);
        Debug.println(F("Message 3: first LED: %d, last LED: %d, R: %d, G: %d, B: %d, W: %d"), ledFirstM3, ledLastM3, ledColorM3[R], ledColorM3[G], ledColorM3[B], ledColorM3[W]);
        Debug.println(F("Message 4: first LED: %d, last LED: %d, R: %d, G: %d, B: %d, W: %d"), ledFirstM4, ledLastM4, ledColorM4[R], ledColorM4[G], ledColorM4[B], ledColorM4[W]);
#endif
        setDimmingCurves();
        initStrip(numberLeds, ledType);
    }
    Debug.println(F("free ram: %d bytes"), Debug.freeRam());
    Debug.println(F("Setup ready"));
  
    if (Konnekting.isFactorySetting())
    {
        Debug.println(F("Device is in factory mode. Starting programming mode..."));
        testStrip();
        Konnekting.setProgState(true);
        Debug.println(F("free ram: %d bytes"), Debug.freeRam());
    }
}

void powerSupply(){
    if(powerSupplyControl){
        if(!lastStaticColor[R] && !lastStaticColor[G] && !lastStaticColor[B] && !lastStaticColor[W] &&
           !lastValueM1 && !lastValueM2 && !lastValueM3 && !lastValueM4 && currentTask == TASK_IDLE){
            allLedsOff = true;
        }else{
            allLedsOff = false;
        }
        if(powerSupplyTurnOn && !powerSupplyState){
            Knx.write(COMOBJ_power_supply, DPT1_001_on);
            Debug.println(F("Turn PS on!"));
            powerSupplyTurnOn = false;
        }
        if(powerSupplyState && allLedsOff && !powerSupplyTurnOff){//power supply is on and all LEDs are off => start to 'turn off power supply' routine
            powerSupplyTurnOff = true;
            powerSupplyOffMillis = millis();
            Debug.println(F("All LEDs are off, start 'turn off power supply' routine"));
        }
        if(powerSupplyState && !allLedsOff && powerSupplyTurnOff){//power supply is on and some LEDs are on => PS stays on
            powerSupplyTurnOff = false;
            Debug.println(F("Some LEDs are on, stop 'turn off power supply' routine"));
        }
        if(!powerSupplyState && allLedsOff && powerSupplyTurnOff){//stop "power off" routine, PS is already off
            Debug.println(F("All LEDs are off, Power Supply is also off, stop 'turn off power supply' routine"));
            powerSupplyTurnOff = false;
        }
        if(powerSupplyTurnOff && (millis() - powerSupplyOffMillis) >= powerSupplyOffDelay){
            Debug.println(F("Time is over, turn PS off"));
            Knx.write(COMOBJ_power_supply, DPT1_001_off);
            powerSupplyTurnOff = false;
        }
    }
}

void loop() {
    Knx.task();
    if (Konnekting.isReadyForApplication()) {
        if(psStateChecked && millis() - psStateCheckedMillis >= 100){ //debounce
            psStateChecked = false;
        }
        if(!psStateChecked){
            powerSupplyState = !digitalRead(POWER_SUPPLY_PIN); //low = ON, high = OFF
            psStateCheckedMillis = millis();
            psStateChecked = true;
            if(lastState != powerSupplyState){
                lastState = powerSupplyState;
                Debug.println(F("PowerSupply state: %d"), powerSupplyState);
            }
        }

        if(powerSupplyState) { //wait until PS is on...
            dimmer.task();
            taskFunction();
        }
        powerSupply();
        if(rgbwChanged){
            if(millis() - rgbwChangedMillis > rgbwhsvChangedDelay && !acceptNewRGBW){
                Debug.println(F("apply new rgb(w) values"));
                Debug.println(F("newRGBW R: %d, G: %d, B: %d, W: %d"), newRGBW[R], newRGBW[G], newRGBW[B], newRGBW[W]);
                Debug.println(F("valuesRGBW R: %d, G: %d, B: %d, W: %d \n"), valuesRGBW[R], valuesRGBW[G], valuesRGBW[B], valuesRGBW[W]);

                valuesRGBW[R] = newRGBW[R];
                valuesRGBW[G] = newRGBW[G];
                valuesRGBW[B] = newRGBW[B];
                valuesRGBW[W] = newRGBW[W];
                acceptNewRGBW = true;
            }
        }
        if(hsvChanged){
            if(millis() - hsvChangedMillis > rgbwhsvChangedDelay && !acceptNewHSV){
                Debug.println(F("apply new hsv values"));

                valuesHSV[0] = newHSV[0];
                valuesHSV[1] = newHSV[1];
                valuesHSV[2] = newHSV[2];
                acceptNewHSV = true;
            }
        }
        if (dimmer.updateAvailable()) {
            if (dimmer.getCurrentValue()) {
                Knx.write(COMOBJ_dim_state, DPT1_001_on); //state = on
                Debug.println(F("Send to Obj: %d value: 1"), COMOBJ_dim_state);
                //if one of channels is on... all can't be off
                //                  allChannelsOff = false;
            } else {
                Knx.write(COMOBJ_dim_state, DPT1_001_off); //state = off
                Debug.println(F("Send to Obj: %d value: 0"), COMOBJ_dim_state);
                //if one of channels is off... all can't be on
                //                  allChannelsOn = false;
				    sendSceneNumber = 0; //all off
            }
            Knx.write(COMOBJ_dim_value, dimmer.getCurrentValue());
            Debug.println(F("Send to Obj: %d value: %d"), COMOBJ_dim_value, dimmer.getCurrentValue());
			      lastDimmerValue = dimmer.getCurrentValue();
            dimmer.resetUpdateFlag();
        }
    		if(sendSceneNumber < 64){
            Debug.println(F("Send to Obj: %d value: %d"), COMOBJ_scene_state, sendSceneNumber);
      			Knx.write(COMOBJ_scene_state, sendSceneNumber);
      			sendSceneNumber = 0xFF;
    		}
    }
}
