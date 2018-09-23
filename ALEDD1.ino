/* ---------------------------------------------------------------------------------------------
ALEDD 0.1 beta (work in progress)
Hardware/Firmware/Sketch/kdevice.xml by E.Burkowski / e.burkowski@konnekting.de, GPL Licensed
Compatible with: KONNEKTING Device Library 1.0.0 beta 4b
*/

/* this libraries are required (click on link and download with library manager):
FlashStorage:              http://librarymanager/All#FlashStorage
DimmerControl:             http://librarymanager/All#DimmerControl
Adafruit Neopixel:         http://librarymanager/All#Adafruit_Neopixel 
Adafruit_ZeroDMA:          http://librarymanager/All#Zero_DMA
Adafruit Neopixel ZeroDMA: http://librarymanager/All#Adafruit_DMA_neopixel_library 
NeoPixel Painter:          http://librarymanager/All#NeoPixel_Painter
KONNEKTING Device Library: http://librarymanager/All#Konnekting
*/

//developer settings
//#define FAKE_EEPROM  //don't use this ;) 
//#define KDEBUG // comment this line to disable DEBUG mode


#include <DimmerControl.h>
#include <FlashAsEEPROM.h>
#include <Adafruit_NeoPixel_ZeroDMA.h>
#include <NeoPixelPainter.h>

#include "src/KonnektingDeviceLibrary/KonnektingDevice.h"

#include "aledd1.h"
#include "kdevice_ALEDD1.h"



//DPT3.007 stuff
#define DPT3_007_MASK_DIRECTION B1000
#define DPT3_007_INCREASE       B1000
#define DPT3_007_DECREASE       B0000
#define DPT3_007_MASK_STEP      B0111
#define DPT3_007_STOP           B0000


#ifdef KDEBUG
#include "src/KonnektingDeviceLibrary/DebugUtil.h"
#endif

#ifdef FAKE_EEPROM
#include "fakeEEPROM.h"
#endif

//global variables

#define USERCOLORS 5

bool initialized = false;
byte currentTask = 0xFE; //0xFE - idle
byte lastTask = 0xFE;

byte curveR[256];
byte curveG[256];
byte curveB[256];
byte curveW[256];

#define DEBOUNCE 80 //ms
word longClickDurationBtn = 500;
unsigned long clickMillis = 0;
bool buttonPressed = false;
bool ledTestMode = false;

//XML group: LED
uint8_t ledType = 0xC6; // ~ NEO_RGBW, see Adafruit_NeoPixel.h for more infos
bool rgbw = true;
byte mixedWhite[] = {255,240,224};
uint16_t numberLeds = 600; //amount of leds on a stripe
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
bool rgbwhsvChanged = false;
bool acceptNewValues = false;
unsigned long rgbwhsvChangedMillis = 0;
word rgbwhsvChangedDelay = 50;



//XML group: Power supply control
bool powerSupplyState = false;
bool powerSupplyControl = false;
unsigned long powerSupplyOffDelay = 0; //munutes
bool powerSupplyOffDelayOnGoing = false;
unsigned long powerSupplyOffMillis = 0;

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

#include "animations.h"
#include "led_functions.h"
#include "scenes.h"

void progButtonPressed(){
    bool btnState = !digitalRead(PROG_BUTTON_PIN);
    //button pressed
    if(btnState){
        if(!buttonPressed){
            clickMillis = millis();
        }
        buttonPressed = true;
    }
    //button released
    if(!btnState){
        unsigned long clickDuration = millis() - clickMillis;
        buttonPressed = false;
        if(clickDuration >= DEBOUNCE)
            if(clickDuration > longClickDurationBtn){
                    taskOnLongClick();
            }else{
                    taskOnShortClick();
            }
    }

}
void taskOnShortClick(){
    //toggle ProgMode
    Konnekting.setProgState(!Konnekting.isProgState());

    //if already programmed, show LED settings
    if(!Konnekting.isFactorySetting() && !ledTestMode){
        if(Konnekting.isProgState())
            showProgrammedLeds();
        else
            neopixels->clear();
            neopixels->show();
    }
    Debug.println(F("free ram: %d bytes"), Debug.freeRam());
}
void taskOnLongClick(){
    //ATTENTION: we creating a new neopixel object with 600(!) LED that consumes alot of RAM!
    //MCU will be reseted after this test!
    ledTestMode = !ledTestMode;
    if(ledTestMode){
        Debug.println(F("free ram before testStrip(): %d bytes"), Debug.freeRam());
        testStrip();
        Debug.println(F("free ram after testStrip(): %d bytes"), Debug.freeRam());
    }else{
        Debug.println(F("reboot!"));
        NVIC_SystemReset() ;
        while (true);
    }

}

void setup() {
    pinMode(PROG_LED_PIN, OUTPUT);
    pinMode(PROG_BUTTON_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(PROG_BUTTON_PIN), progButtonPressed, CHANGE);
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
//  Konnekting.init(SerialKNX, PROG_BUTTON_PIN, PROG_LED_PIN, MANUFACTURER_ID, DEVICE_ID, REVISION); 
  
#ifndef FAKE_EEPROM
    for (int i = 0; i < Konnekting.getFreeEepromOffset(); i++) {
        Debug.println(F("writeMemory(%d,0x%02X);"), i, EEPROM.read(i));
    }
#endif
    if (!Konnekting.isFactorySetting()){
        //XML group: LED
        ledType = Konnekting.getUINT8Param(PARAM_led_type);
        if(ledType == NEO_RGB || ledType == NEO_RBG || ledType == NEO_GRB || 
           ledType == NEO_GBR || ledType == NEO_BRG || ledType == NEO_BGR) rgbw = false;
        numberLeds = Konnekting.getUINT16Param(PARAM_number_leds_strip);
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
      
        //XML group: scenes
        for (byte sc = 0; sc < 64; sc++) {
            scene[sc] = Konnekting.getUINT8Param(PARAM_scene01 + sc);
        }
        //XML group: User colors
        for (byte uc = 0; uc < USERCOLORS; uc++) {
            ucRed[uc]   = Konnekting.getUINT8Param(PARAM_uc1r + 4 * uc);
            ucGreen[uc] = Konnekting.getUINT8Param(PARAM_uc1g + 4 * uc);
            ucBlue[uc]  = Konnekting.getUINT8Param(PARAM_uc1b + 4 * uc);
            ucWhite[uc] = Konnekting.getUINT8Param(PARAM_uc1w + 4 * uc);
        }
#ifdef KDEBUG
        Debug.println(F("Idx\tR\tG\tB\tW"));
        for (byte uc = 0; uc < USERCOLORS; uc++) {
            Debug.println(F("%d\t%d\t%d\t%d\t%d"),uc,ucRed[uc],ucGreen[uc],ucBlue[uc],ucWhite[uc]);
        } 
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

void loop() {
    Knx.task();
    if (Konnekting.isReadyForApplication()) {
        dimmer.task();
        taskFunction();
        if(rgbwhsvChanged){
            if(millis() - rgbwhsvChangedMillis > rgbwhsvChangedDelay && !acceptNewValues){
                Debug.println(F("apply new rgb(w) / hsv values"));
                acceptNewValues = true;
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
            }
            Knx.write(COMOBJ_dim_value, dimmer.getCurrentValue());
            Debug.println(F("Send to Obj: %d value: %d"), COMOBJ_dim_value, dimmer.getCurrentValue());
            dimmer.resetUpdateFlag();
        }
    }
}



void knxEvents(byte comObjIndex) {
    Debug.println(F("knxEvents comObjIndex: %d"), comObjIndex);
    lastTask = currentTask;
    byte newTask = 0xFF;
    initialized = false;
    switch (comObjIndex) {
        case COMOBJ_dim_sw: // Switch
            newTask = DIMMER;
            
            taskSoftOnOff(Knx.read(comObjIndex));
            Debug.println(F("taskSoftOnOff: %d"), Knx.read(comObjIndex));
//            powerSupplyTask();
            break;
      
        case COMOBJ_dim_rel : // Relative dimming
            newTask = DIMMER;
            taskDimUpDownStop(Knx.read(comObjIndex));
            Debug.println(F("taskDimUpDownStop: %d"), Knx.read(comObjIndex));
//            powerSupplyTask();
            break;
      
        case COMOBJ_dim_abs : // Absolute dimming
            newTask = DIMMER;
            taskNewValue(Knx.read(comObjIndex));
            Debug.println(F("taskNewValue: %d"), Knx.read(comObjIndex));
//            powerSupplyTask();
            break;
      
        case COMOBJ_scene : // Scene
            newTask = scene[Knx.read(comObjIndex)];
            Debug.println(F("newTask: 0x%02X"), newTask);
            if (newTask != 0xFF) currentTask = newTask;
//            powerSupplyTask();
            break;
        case COMOBJ_RGB : // RGB 232.600
            acceptNewValues = true;
            newTask = TASK_RGB;
            Debug.println(F("newTask: 0x%02X"), newTask);
            Knx.read(comObjIndex,new3Byte);
            if (newTask != 0xFF) currentTask = newTask;
//            powerSupplyTask();
            break;
        case COMOBJ_RGBW : // RGBW 251.600
            acceptNewValues = true;
            newTask = TASK_RGBW;
            Debug.println(F("newTask: 0x%02X"), newTask);
            Knx.read(comObjIndex,new6Byte);
            if (newTask != 0xFF) currentTask = newTask;
//            powerSupplyTask();
            break;
        case COMOBJ_HSV : // HSV 232.600
            acceptNewValues = true;
            newTask = TASK_HSV;
            Debug.println(F("newTask: 0x%02X"), newTask);
            Knx.read(comObjIndex,new3Byte);
            if (newTask != 0xFF) currentTask = newTask;
//            powerSupplyTask();
            break;
      
        case COMOBJ_r :
//      if(!rgbwhsvChanged) {
            rgbwhsvChanged = true;
            rgbwhsvChangedMillis = millis();
//      }
            new6Byte[2] = Knx.read(comObjIndex);
            Debug.println(F("new R: %d"), new6Byte[2]);
            newTask = TASK_RGBW;
            if (newTask != 0xFF) currentTask = newTask;
            break;
        case COMOBJ_g :
//      if(!rgbwhsvChanged) {
            rgbwhsvChanged = true;
            rgbwhsvChangedMillis = millis();
//      }
            new6Byte[3] = Knx.read(comObjIndex);
            Debug.println(F("new G: %d"), new6Byte[3]);
            newTask = TASK_RGBW;
            if (newTask != 0xFF) currentTask = newTask;
            break;
        case COMOBJ_b :
//      if(!rgbwhsvChanged) {
            rgbwhsvChanged = true;
            rgbwhsvChangedMillis = millis();
//      }
            new6Byte[4] = Knx.read(comObjIndex);
            Debug.println(F("new B: %d"), new6Byte[4]);
            newTask = TASK_RGBW;
            if (newTask != 0xFF) currentTask = newTask;
            break;
        case COMOBJ_w :
//      if(!rgbwhsvChanged) {
            rgbwhsvChanged = true;
            rgbwhsvChangedMillis = millis();
//      }
            new6Byte[5] = Knx.read(comObjIndex);
            Debug.println(F("new W: %d"), new6Byte[5]);
            newTask = TASK_RGBW;
            if (newTask != 0xFF) currentTask = newTask;
            break;
        case COMOBJ_h :
//      if(!rgbwhsvChanged) {
            rgbwhsvChanged = true;
            rgbwhsvChangedMillis = millis();
//      }
            new3Byte[0] = Knx.read(comObjIndex);
            Debug.println(F("new H"), new3Byte[0]);
            newTask = TASK_HSV;
            if (newTask != 0xFF) currentTask = newTask;
            break;
        case COMOBJ_s :
//      if(!rgbwhsvChanged) {
            rgbwhsvChanged = true;
            rgbwhsvChangedMillis = millis();
//      }
            new3Byte[1] = Knx.read(comObjIndex);
            Debug.println(F("new S"), new3Byte[1]);
            newTask = TASK_HSV;
            if (newTask != 0xFF) currentTask = newTask;
            break;
        case COMOBJ_v :
//      if(!rgbwhsvChanged) {
            rgbwhsvChanged = true;
            rgbwhsvChangedMillis = millis();
//      }
            new3Byte[2] = Knx.read(comObjIndex);
            Debug.println(F("new S"), new3Byte[2]);
            newTask = TASK_HSV;
            if (newTask != 0xFF) currentTask = newTask;
            break;

        default:
            break;
    }
}


