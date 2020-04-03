void knxEvents(byte comObjIndex) {
    Debug.println(F("knxEvents comObjIndex: %d"), comObjIndex);
    lastTask = currentTask;
    byte newTask = 0xFF;
    byte tmpValue = 0;
    bool tmpBool = false;
    powerSupplyTurnOn = true; //dirty solution: if PS is off and LEDs are off and next command is "turn all off" PS will go on... and after timeout off. Is this a real use case?!
    switch (comObjIndex) {
        case COMOBJ_dim_sw: // Switch
            newTask = TASK_DIMMER;
            tmpBool = Knx.read(comObjIndex);
            taskSoftOnOff(tmpBool);
//            if(!tmpBool) powerSupplyTurnOn = false;
            Debug.println(F("taskSoftOnOff: %d"), Knx.read(comObjIndex));
            break;
      
        case COMOBJ_dim_rel: // Relative dimming
            newTask = TASK_DIMMER;
            taskDimUpDownStop(Knx.read(comObjIndex));
            Debug.println(F("taskDimUpDownStop: %d"), Knx.read(comObjIndex));
            break;
      
        case COMOBJ_dim_abs: // Absolute dimming
            newTask = TASK_DIMMER;
            taskNewValue(Knx.read(comObjIndex));
            Debug.println(F("taskNewValue: %d"), Knx.read(comObjIndex));
            break;
      
        case COMOBJ_scene: // Scene
            newTask = Knx.read(comObjIndex);
            Debug.println(F("newTask: 0x%02X"), newTask);
      
            if (newTask != 0xFF) {
                currentTask = newTask;
                acceptNewRGBW = true;
                initialized = false;
            }
            break;
        case COMOBJ_RGB: // RGB 232.600
            acceptNewRGBW = true;
            newTask = TASK_RGB;
            Debug.println(F("newTask: 0x%02X"), newTask);
            Knx.read(comObjIndex, new3Byte);
            valuesRGBW[R] = new3Byte[R];
            valuesRGBW[G] = new3Byte[G];
            valuesRGBW[B] = new3Byte[B];
            valuesRGBW[W] = 0;
            if (newTask != 0xFF) currentTask = newTask;
            break;
        case COMOBJ_RGBW: // RGBW 251.600
            acceptNewRGBW = true;
            newTask = TASK_RGBW;
            Debug.println(F("newTask: 0x%02X"), newTask);
            Knx.read(comObjIndex, new6Byte);
            valuesRGBW[R] = new6Byte[2];
            valuesRGBW[G] = new6Byte[3];
            valuesRGBW[B] = new6Byte[4];
            valuesRGBW[W] = new6Byte[5];
            Debug.println(F("valuesRGBW R: %d, G: %d, B: %d, W: %d \n"),valuesRGBW[R],valuesRGBW[G],valuesRGBW[B],valuesRGBW[W]);

            if (newTask != 0xFF) currentTask = newTask;
            break;
        case COMOBJ_HSV: // HSV 232.600
            acceptNewHSV = true;
            newTask = TASK_HSV;
            Debug.println(F("newTask: 0x%02X"), newTask);
            Knx.read(comObjIndex, valuesHSV);
            Debug.println(F("valuesHSV H: %d, S: %d, V: %d\n"),valuesHSV[0],valuesHSV[1],valuesHSV[2]);

            if (newTask != 0xFF) currentTask = newTask;
            break;
      
        case COMOBJ_r:
            rgbwChanged = true;
            rgbwChangedMillis = millis();
            newRGBW[R] = Knx.read(comObjIndex);
            Debug.println(F("new R: %d / 0x%02x"), newRGBW[R], newRGBW[R]);
            newTask = TASK_RGBW;
            if (newTask != 0xFF) currentTask = newTask;
            break;
        case COMOBJ_g:
            rgbwChanged = true;
            rgbwChangedMillis = millis();
            newRGBW[G] = Knx.read(comObjIndex);
            Debug.println(F("new G: %d / 0x%02x"), newRGBW[G], newRGBW[G]);
            newTask = TASK_RGBW;
            if (newTask != 0xFF) currentTask = newTask;
            break;
        case COMOBJ_b:
            rgbwChanged = true;
            rgbwChangedMillis = millis();
            newRGBW[B] = Knx.read(comObjIndex);
            Debug.println(F("new B: %d / 0x%02x"), newRGBW[B], newRGBW[B]);
            newTask = TASK_RGBW;
            if (newTask != 0xFF) currentTask = newTask;
            break;
        case COMOBJ_w:
            rgbwChanged = true;
            rgbwChangedMillis = millis();
            newRGBW[W] = Knx.read(comObjIndex);
            Debug.println(F("new W: %d / 0x%02x"), newRGBW[W], newRGBW[W]);
            newTask = TASK_RGBW;
            if (newTask != 0xFF) currentTask = newTask;
            break;
            
        case COMOBJ_h:
            hsvChanged = true;
            hsvChangedMillis = millis();
            newHSV[0] = Knx.read(comObjIndex);
            Debug.println(F("new H"), newHSV[0]);
            newTask = TASK_HSV;
            if (newTask != 0xFF) currentTask = newTask;
            break;
        case COMOBJ_s:
            hsvChanged = true;
            hsvChangedMillis = millis();
            newHSV[1] = Knx.read(comObjIndex);
            Debug.println(F("new S"), newHSV[1]);
            newTask = TASK_HSV;
            if (newTask != 0xFF) currentTask = newTask;
            break;
        case COMOBJ_v:
            hsvChanged = true;
            hsvChangedMillis = millis();
            newHSV[2] = Knx.read(comObjIndex);
            Debug.println(F("new S"), newHSV[2]);
            newTask = TASK_HSV;
            if (newTask != 0xFF) currentTask = newTask;
            break;
            
        case COMOBJ_m1sw: // Message 1 switch
            if (Knx.read(comObjIndex)){
                newValueM1 = 255;
            }else{
                newValueM1 = 0;
            }
            statusM1 = true;
            break;
        case COMOBJ_m1perc: // Message 1 percentage
            newValueM1 = Knx.read(comObjIndex);
            statusM1 = true;
            break;
        case COMOBJ_m1rgb: //Message 1 RGB
            Knx.read(comObjIndex, new3Byte);
            ledColorM1[R] = new3Byte[R];
            ledColorM1[G] = new3Byte[G];
            ledColorM1[B] = new3Byte[B];
            ledColorM1[W] = 0;
             if(!ledColorM1[R] && !ledColorM1[G] && !ledColorM1[B]){ //RGBW = off
                newValueM1 = 0;
            }else{
                newValueM1 = 255;
            }
            statusM1 = true;
            break;
        case COMOBJ_m1rgbw: //Message 1 RGBW
            Knx.read(comObjIndex, new6Byte);
            ledColorM1[R] = new6Byte[2];
            ledColorM1[G] = new6Byte[3];
            ledColorM1[B] = new6Byte[4];
            ledColorM1[W] = new6Byte[5];
            if(!ledColorM1[R] && !ledColorM1[G] && !ledColorM1[B] && !ledColorM1[R]){ //RGBW = off
                newValueM1 = 0;
            }else{
                newValueM1 = 255;
            }
            statusM1 = true;
            break;
            
        case COMOBJ_m2sw: // Message 2 switch
            if (Knx.read(comObjIndex)){
                newValueM2 = 255;
            }else{
                newValueM2 = 0;
            }
            statusM2 = true;
            break;
        case COMOBJ_m2perc: // Message 2 percentage
            newValueM2 = Knx.read(comObjIndex);
            statusM2 = true;
            break;
        case COMOBJ_m2rgb: //Message 2 RGB
            Knx.read(comObjIndex, new3Byte);
            ledColorM2[R] = new3Byte[R];
            ledColorM2[G] = new3Byte[G];
            ledColorM2[B] = new3Byte[B];
            ledColorM2[W] = 0;
            if(!ledColorM2[R] && !ledColorM2[G] && !ledColorM2[B]){ //RGBW = off
                newValueM2 = 0;
            }else{
                newValueM2 = 255;
            }
            statusM1 = true;
            break;
        case COMOBJ_m2rgbw: //Message 2 RGBW
            Knx.read(comObjIndex, new6Byte);
            ledColorM2[R] = new6Byte[2];
            ledColorM2[G] = new6Byte[3];
            ledColorM2[B] = new6Byte[4];
            ledColorM2[W] = new6Byte[5];
            if(!ledColorM2[R] && !ledColorM2[G] && !ledColorM2[B] && !ledColorM2[W]){ //RGBW = off
                newValueM2 = 0;
            }else{
                newValueM2 = 255;
            }
            statusM2 = true;
            break;
            
        case COMOBJ_m3sw: // Message 3 switch
            if (Knx.read(comObjIndex)){
                newValueM3 = 255;
            }else{
                newValueM3 = 0;
            }
            statusM3 = true;
            break;
        case COMOBJ_m3perc: // Message 3 percentage
            newValueM3 = Knx.read(comObjIndex);
            statusM3 = true;
            break;
        case COMOBJ_m3rgb: //Message 3 RGB
            Knx.read(comObjIndex, new3Byte);
            ledColorM3[R] = new3Byte[R];
            ledColorM3[G] = new3Byte[G];
            ledColorM3[B] = new3Byte[B];
            ledColorM3[W] = 0;
            if(!ledColorM1[R] && !ledColorM1[G] && !ledColorM1[B]){ //RGBW = off
                newValueM1 = 0;
            }else{
                newValueM1 = 255;
            }
            statusM1 = true;
            break;
        case COMOBJ_m3rgbw: //Message 3 RGBW
            Knx.read(comObjIndex, new6Byte);
            ledColorM3[R] = new6Byte[2];
            ledColorM3[G] = new6Byte[3];
            ledColorM3[B] = new6Byte[4];
            ledColorM3[W] = new6Byte[5];
            if(!ledColorM3[R] && !ledColorM3[G] && !ledColorM3[B] && !ledColorM3[W]){ //RGBW = off
                newValueM3 = 0;
            }else{
                newValueM3 = 255;
            }
            statusM3 = true;
            break;
            
        case COMOBJ_m4sw: // Message 4 switch
            if (Knx.read(comObjIndex)){
                newValueM4 = 255;
            }else{
                newValueM4 = 0;
            }
            statusM4 = true;
            break;
        case COMOBJ_m4perc: // Message 4 percentage
            newValueM4 = Knx.read(comObjIndex);
            statusM4 = true;
            break;
        case COMOBJ_m4rgb: //Message 4 RGB
            Knx.read(comObjIndex, new3Byte);
            ledColorM4[R] = new3Byte[R];
            ledColorM4[G] = new3Byte[G];
            ledColorM4[B] = new3Byte[B];
            ledColorM4[W] = 0;
            if(!ledColorM4[R] && !ledColorM4[G] && !ledColorM4[B]){ //RGBW = off
                newValueM4 = 0;
            }else{
                newValueM4 = 255;
            }
            statusM1 = true;
            break;
        case COMOBJ_m4rgbw: //Message 1 RGBW
            Knx.read(comObjIndex, new6Byte);
            ledColorM4[R] = new6Byte[2];
            ledColorM4[G] = new6Byte[3];
            ledColorM4[B] = new6Byte[4];
            ledColorM4[W] = new6Byte[5];
            if(!ledColorM4[R] && !ledColorM4[G] && !ledColorM4[B] && !ledColorM4[R]){ //RGBW = off
                newValueM4 = 0;
            }else{
                newValueM4 = 255;
            }
            statusM4 = true;
            break;
        default:
            break;
    }
    if(newTask != lastTask && newTask < 64){
        //0 .. 63 are KNX scenes, 64 .. 255 for internal use only!
        sendSceneNumber = newTask;
    }
}
