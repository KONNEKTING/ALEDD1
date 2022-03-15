/*
byte mapByte(byte x, byte in_min, byte in_max, byte out_min, byte out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
*/

word getLogValue(byte index, float gamma, byte startValue, word maxValue, word steps){
    if (index >0){
        word result = round(pow((float)index / (float)(steps - 1.0), gamma) * (float)(maxValue - startValue) + startValue);
        if(result > maxValue)
            return maxValue;
        else
            return result;
    }else{
        return 0;
    }
}


void setDimmingCurves(){
    word maxSteps = 256;
    for(word i = 0; i < maxSteps; i++){
        curveR[i] = getLogValue(i, gammaCorrection, firstOnValue, maxR, maxSteps);
        curveG[i] = getLogValue(i, gammaCorrection, firstOnValue, maxG, maxSteps);
        curveB[i] = getLogValue(i, gammaCorrection, firstOnValue, maxB, maxSteps);
        curveW[i] = getLogValue(i, gammaCorrection, firstOnValue, maxW, maxSteps);
    }
}

void progLed(bool state){
    digitalWrite(PROG_LED_PIN, state);
}

//test witch strip we have
/* choose what you see:
 *  LED 1 2 3 4 5 6 (x = OFF)
 *      R G B W x x -> RGBW
 *      G R B W x x -> GRBW
 *      R B x G x R -> RGB
 *      G B x R x G -> GRB
 */
void testStrip(){
    //there are only 600 LEDs alowed -> hardcoded
    if(neopixels) delete neopixels;
    neopixels = new Adafruit_NeoPixel_ZeroDMA(600, LED_STRIP_PIN, NEO_RGBW);
#ifdef DEVELPMENT    
    neopixels->begin(&sercom5, SERCOM5, SERCOM5_DMAC_ID_TX,  6, SPI_PAD_2_SCK_3, PIO_SERCOM);
#else
    neopixels->begin(&sercom4, SERCOM4, SERCOM4_DMAC_ID_TX, 22, SPI_PAD_0_SCK_3, PIO_SERCOM_ALT);
#endif
    neopixels->setPixelColor(0, 255 , 0, 0, 0);
    neopixels->setPixelColor(1, 0, 255, 0, 0);
    neopixels->setPixelColor(2, 0, 0, 255, 0);
    neopixels->setPixelColor(3, 0, 0, 0, 255);
    for(int i = 4; i < 600; i++){
        if((i % 10 == 0) && (i % 50 != 0)) neopixels->setPixelColor(i-1, 0, 255, 0, 0); //each 10.(10,20,30,40,60,70...) is green
        if(i % 50 == 0) neopixels->setPixelColor(i-1, 0, 0, 255, 0); //each 50.(50,100,150...) is blue
    }
    neopixels->setPixelColor(599, 255,0,0,0); //last one is red
    neopixels->show();
}

void showProgrammedLeds(){
    neopixels->setPixelColor(0, 255, 0, 0, 0);
    neopixels->setPixelColor(1, 0, 255, 0, 0);
    neopixels->setPixelColor(2, 0, 0, 255, 0);
    neopixels->setPixelColor(3, 0, 0, 0, 255);
    //each tens LED is red (10,20,30,40,60,70...)
    for(int i = 4; i < numberLeds; i++){
        if((i % 10 == 0) && (i % 50 != 0)) neopixels->setPixelColor(i-1, 0, 255, 0, 0); //each 10. is red
        if(i % 50 == 0) neopixels->setPixelColor(i - 1, 0, 0, 255, 0); //each 50. is blue
    }
    neopixels->setPixelColor(numberLeds - 1, 255, 0, 0, 0); //last one is green
    neopixels->show();
}
    

//led-stripe initialisation
void initStrip(word pixel, byte type){
    if(neopixels) delete neopixels;
    neopixels = new Adafruit_NeoPixel_ZeroDMA(pixel, LED_STRIP_PIN, type);
    pixelcanvas = new NeoPixelPainterCanvas(neopixels);
    pixelcanvas2 = new NeoPixelPainterCanvas(neopixels);
    pixelbrush = new NeoPixelPainterBrush(pixelcanvas);
    pixelbrush2 = new NeoPixelPainterBrush(pixelcanvas); 
    pixelbrush3 = new NeoPixelPainterBrush(pixelcanvas);
    pixelbrush4on2 = new NeoPixelPainterBrush(pixelcanvas2);
#ifdef DEVELPMENT    
    neopixels->begin(&sercom5, SERCOM5, SERCOM5_DMAC_ID_TX,  6, SPI_PAD_2_SCK_3, PIO_SERCOM);
#else
    neopixels->begin(&sercom4, SERCOM4, SERCOM4_DMAC_ID_TX, 22, SPI_PAD_0_SCK_3, PIO_SERCOM_ALT);
#endif
    neopixels->show();
    Debug.println(F("initPixel"));
}

void setDayNightValues(bool night){
    if(night){
        //night values
        dimmer.setMinValue(valueMinNight);
        dimmer.setMaxValue(valueMaxNight);
    }else{
        //day values
        dimmer.setMinValue(valueMinDay);
        dimmer.setMaxValue(valueMaxDay);
    }
}

void taskSoftOnOff(byte value){
    if(value)
        dimmer.taskSoftOn();
    else
        dimmer.taskSoftOff();
}

void taskDimUpDownStop(byte value){
    //use only 3 last bits
    byte step = value & DPT3_007_MASK_STEP;
    //true = increase, false = decrease
    bool direction = value & DPT3_007_MASK_DIRECTION;
    Debug.println(F("value: %d, step: %d, direction: %d"), value, step, direction);
    //if step == B?????000 then stop
    if(step == DPT3_007_STOP)
        dimmer.taskStop();
    else
        if(direction)
            dimmer.taskDimUp();
        else
            dimmer.taskDimDown();
}

void taskNewValue(byte value){
    dimmer.taskNewValue(value);
}

void setAll(byte r, byte g, byte b, byte w){
    currentTask = TASK_IDLE; //TASK_IDLE
    //staticColorReady = true;
    //if we have RGB only, try to display mixed white
    if(!rgbw && w != 0 && r == 0 && g == 0 && b == 0){
        r = getLogValue(w, gammaCorrection, 1, mixedWhite[0], 256);
        g = getLogValue(w, gammaCorrection, 1, mixedWhite[1], 256);
        b = getLogValue(w, gammaCorrection, 1, mixedWhite[2], 256);
        w = 0;
    }
    if(rgbw){
        r = curveR[r];
        g = curveG[g];
        b = curveB[b];
        w = curveW[w];
    }
#ifdef KDEBUG
    Debug.println(F("setAll log: R: %d, G: %d, B: %d, W: %d, HEX: 0x%02x 0x%02x 0x%02x 0x%02x"),r,g,b,w,r,g,b,w);
#endif
    for(int i = 0; i < numberLeds; i++){
        neopixels->setPixelColor(i, r, g, b, w);
    }
    //save color, we need it for messages
    lastStaticColor[R] = r;
    lastStaticColor[G] = g;
    lastStaticColor[B] = b;
    lastStaticColor[W] = w;
    pixelsShow = true;
}

void setAllHsv(byte h, byte s, byte v){
    Debug.println(F("setAllHsv H: %d, S: %d, V: %d"), h, s, v);
    currentTask = TASK_IDLE; //TASK_IDLE
    byte newRGB[3];
    hsvToRgb(h, s, v, newRGB);
 
    for(int i = 0; i < numberLeds; i++){
        neopixels->setPixelColor(i, newRGB[R], newRGB[G], newRGB[B]);
        pixelsShow = true;
    }
}

//function to set LED-Values
void setLeds(byte value){
    setAll(0, 0, 0, value);
//    Debug.println(F("setLeds %d"),index);
}

//function to set LED-values via dimmer library
void setLeds(byte ch, byte value){
    new6Byte[2+ch] = value;
}

/*neopixels->show() tranfers buffer data to physical LEDs
we can modify buffer before this step to show e.g. message-animation on top of normal animation
in addition we are setting ledsOn status.

*/

void showPixels (){
    if(pixelsShow){
  	    pixelsShow = false;
  	    neopixels->show();
    }
}

/*
this function overrides selected pixels with specific color
attention: if message color matches current stripe color, it's not possible to identify message state
*/

void setMessageLeds(word firstLed, word lastLed, byte newValue, byte newColor[4]){
/*
  we can display up to 4 messages on a single strip
  each message has it own stripe range
  the range is defined in KONNEKTING Suite "from LED number x up to LED number y"
  message 2 will override (or part of) message 1 if message 2 range overlaps message 1 range

Examples:

LED strip with 20 LEDs (0..19):
 0   1   2   3   4
19               5 
18               6 
17               7 
16               8 
15               9 
14  13  12  11  10

Message 1 range: 10 - 4 => 7 LEDs (25%: 10,9; 50%: 10,9,8,7; 75%: 10,9,8,7,6)
Message 2 range: 14 - 0 => 7 LEDs, not possible in direct way. Please set LED 0 as LED 20, LED 1 as LED 21 and so on... (LED number from LED 0 + string length)
                 (25%: 14,15; 50%: 14,15,16,17; 75%: 14,15,16,17,18; 100%: 14,15,16,17,18,19,0)
                 if LED 0 will be set as 0, than the range will be 15 LEDs: 14,13,12...2,1,0

*/
    if(newValue){ //if 0, do nothing, we have already wiped with animation or static color
        if(lastLed >= firstLed){
            word amount = (lastLed - firstLed + 1) * newValue / 255; //round up //floor()
            for(word led = firstLed; led < firstLed + amount; led++){
                if(led < numberLeds) {
                    neopixels->setPixelColor(led, newColor[R], newColor[G], newColor[B], newColor[W]);
                }else{
                    neopixels->setPixelColor(led - numberLeds, newColor[R], newColor[G], newColor[B], newColor[W]); //see examples
                }
            }
        }else{//firstLed > lastLed
            word amount = ceil((firstLed - lastLed + 1) * newValue / 255); //round up //floor()
            for(word led = firstLed; led > firstLed - amount; led--){
                if(led < numberLeds) {
                    neopixels->setPixelColor(led, newColor[R], newColor[G], newColor[B], newColor[W]);
                }else{
                    neopixels->setPixelColor(led - numberLeds, newColor[R], newColor[G], newColor[B], newColor[W]); //see examples
                }
            }
        }
    }
}

void showMessage(){
    //set color only if we are in NOT in WAIT state 
    if(statusM1 || statusM2 || statusM3 || statusM4){
        //just overlay with messages, animation will do "wipe"
        if(RAINBOW <= currentTask && currentTask <= WHIREMIDDLEOFF){
            setMessageLeds(ledFirstM1, ledLastM1, newValueM1, ledColorM1);
            lastValueM1 = newValueM1;
            setMessageLeds(ledFirstM2, ledLastM2, newValueM2, ledColorM2);
            lastValueM2 = newValueM2;
            setMessageLeds(ledFirstM3, ledLastM3, newValueM3, ledColorM3);
            lastValueM3 = newValueM3;
            setMessageLeds(ledFirstM4, ledLastM4, newValueM4, ledColorM4);
            lastValueM4 = newValueM4;
            pixelsShow = true; //show result 
        }
        //turn Message LEDs on/off if it's not an animation (static color)
        if((ALL_OFF  <= lastTaskBeforeMessage && lastTaskBeforeMessage <= USER_COLOR_5) || 
           (TASK_RGB <= lastTaskBeforeMessage && lastTaskBeforeMessage <= TASK_DIMMER )){
            //"wipe" messages if we will show less message LEDs as before                
            if(lastValueM1 > newValueM1 || lastValueM2 > newValueM2 || lastValueM3 > newValueM3 || lastValueM4 > newValueM4){
                setAll(lastStaticColor[R], lastStaticColor[G], lastStaticColor[B], lastStaticColor[W]);
                Debug.println(F("Messages: set last color: R: %d, G: %d, B: %d, W: %d, statusM2: %d"), lastStaticColor[R], lastStaticColor[G], lastStaticColor[B], lastStaticColor[W], statusM2);
            }
            //and show messages on top of static color
            setMessageLeds(ledFirstM1, ledLastM1, newValueM1, ledColorM1);
            if(statusM1) {
                statusM1 = false; //set message WAIT state
#ifdef KDEBUG
                Debug.println(F("Message 1: pause routine and wait until TASK will be changed"));
#endif                
                lastValueM1 = newValueM1;
            }
            setMessageLeds(ledFirstM2, ledLastM2, newValueM2, ledColorM2);
            if(statusM2) {
                statusM2 = false; //set message WAIT state
#ifdef KDEBUG
                Debug.println(F("Message 2: pause routine and wait until TASK will be changed"));
#endif                
                lastValueM2 = newValueM2;
            }
            setMessageLeds(ledFirstM3, ledLastM3, newValueM3, ledColorM3);
            if(statusM3) {
                statusM3 = false; //set message WAIT state
#ifdef KDEBUG
                Debug.println(F("Message 3: pause routine and wait until TASK will be changed"));
#endif                
                lastValueM3 = newValueM3;
            }
            setMessageLeds(ledFirstM4, ledLastM4, newValueM4, ledColorM4);
            if(statusM4) {
                statusM4 = false; //set message WAIT state
#ifdef KDEBUG
                Debug.println(F("Message 4: pause routine and wait until TASK will be changed"));
#endif
                lastValueM4 = newValueM4;
            }
        pixelsShow = true; //show result 
        }
//       
    }
}
