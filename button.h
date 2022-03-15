void taskOnShortClick(){
    //toggle ProgMode
    Konnekting.setProgState(!Konnekting.isProgState());

    //if already programmed, show LED settings
    if(!Konnekting.isFactorySetting() && !ledTestMode){
        neopixels->clear();
        neopixels->show();
        if(Konnekting.isProgState()) showProgrammedLeds();
        
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
