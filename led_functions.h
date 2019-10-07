byte mapByte(byte x, byte in_min, byte in_max, byte out_min, byte out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

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
        curveR[i] = getLogValue(i, gammaCorrection, 1, maxR, maxSteps);
        curveG[i] = getLogValue(i, gammaCorrection, 1, maxG, maxSteps);
        curveB[i] = getLogValue(i, gammaCorrection, 1, maxB, maxSteps);
        curveW[i] = getLogValue(i, gammaCorrection, 1, maxW, maxSteps);
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
    neopixels->begin(&sercom4, SERCOM4, SERCOM4_DMAC_ID_TX,   22,   23,  24, SPI_PAD_0_SCK_3, SERCOM_RX_PAD_2, PIO_SERCOM_ALT);
    neopixels->setPixelColor(0, 255,0,0,0);
    neopixels->setPixelColor(1, 0,255,0,0);
    neopixels->setPixelColor(2, 0,0,255,0);
    neopixels->setPixelColor(3, 0,0,0,255);
    for(int i = 4; i < 600; i++){
        if((i % 10 == 0) && (i % 50 != 0)) neopixels->setPixelColor(i-1, 0,255,0,0); //each 10.(10,20,30,40,60,70...) is green
        if(i % 50 == 0) neopixels->setPixelColor(i-1, 0,0,255,0); //each 50.(50,100,150...) is blue
    }
    neopixels->setPixelColor(599, 255,0,0,0); //last one is red
    neopixels->show();
}

void showProgrammedLeds(){
    neopixels->setPixelColor(0, 255,0,0,0);
    neopixels->setPixelColor(1, 0,255,0,0);
    neopixels->setPixelColor(2, 0,0,255,0);
    neopixels->setPixelColor(3, 0,0,0,255);
    //each tens LED is red (10,20,30,40,60,70...)
    for(int i = 4; i < numberLeds; i++){
        if((i % 10 == 0) && (i % 50 != 0)) neopixels->setPixelColor(i-1, 0,255,0,0); //each 10. is red
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
    neopixels->begin(&sercom4, SERCOM4, SERCOM4_DMAC_ID_TX, 22, 23, 24, SPI_PAD_0_SCK_3, SERCOM_RX_PAD_2, PIO_SERCOM_ALT);
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
    if(value == 0)
        dimmer.taskSoftOff();
    else
        dimmer.taskSoftOn();
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
    currentTask = 0xFE; //TASK_IDLE
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
        neopixels->setPixelColor(i, r,g,b,w);
    }
    neopixels->show();
}

void setAllHsv(byte h, byte s, byte v){
    Debug.println(F("setAllHsv H: %d, S: %d, V: %d"), h, s, v);
    currentTask = 0xFE; //TASK_IDLE
    byte newRGB[3];
    hsvToRgb(h, s, v, newRGB);
 
    for(int i = 0; i < numberLeds; i++){
        neopixels->setPixelColor(i, newRGB[R], newRGB[G], newRGB[B]);
        neopixels->show();
    }
}

//function to set LED-Values
void setLeds(byte index){
    setAll(0, 0, 0, index);
//    Debug.println(F("setLeds %d"),index);
}
