//Scene 1 .. 9
#define ALL_OFF 0x00
#define WHITE 0x01
#define RED 0x02
#define YELLOW 0x03
#define GREEN 0x04
#define CYAN 0x05
#define BLUE 0x06
#define PURPLE 0x07
#define ORANGE 0x08

//Scenes 21 .. 25
#define USER_COLOR_1 0x14 
#define USER_COLOR_2 0x15
#define USER_COLOR_3 0x16
#define USER_COLOR_4 0x17
#define USER_COLOR_5 0x18

//Scenes 41 .. 52
#define RAINBOW 0x28  //41
#define SINGLERGB 0x29 //42
#define SPARKLER 0x2A  //43
#define TWINKYSTARS 0x2B  //44
#define CHASER 0x2C  //45
#define HUEFADER 0x2D  //46
#define SPEEDTRAILS 0x2E  //47
#define BOUNCYBALLS 0x2F  //48
#define TWOBRUSHCOLORMIXING 0x30 //49


#define WHIREMIDDLEON 0x32
#define WHIREMIDDLEOFF 0x33



//Scene 61 .. 64
#define TASK_RGB 0x3C
#define TASK_RGBW 0x3D
#define TASK_HSV 0x3E
#define DIMMER 0x3F






#define TASK_IDLE 0xFE



void taskFunction(){
//    Debug.println(F("currentTask: 0x%02X"), currentTask);
    switch(currentTask){
        case ALL_OFF:
            setAll(0,0,0,0);
            dimmer.taskOff();
            break;
        case WHITE:
            setAll(0,0,0,255);
            dimmer.taskOn();
            break;
        case RED:
            setAll(255,0,0,0);
            break;
        case YELLOW:
            setAll(255,255,0,0);
			      break;
        case GREEN:
            setAll(0,255,0,0);
            break;
        case CYAN:
            setAll(0,255,255,0);
            break;
        case BLUE:
            setAll(0,0,255,0);
            break;
        case PURPLE:
            setAll(255,0,255,0);
            break;
        case ORANGE:
            setAll(255,81,0,0);
            break;

        case USER_COLOR_1:
            setAll(ucRed[0],ucGreen[0],ucBlue[0],ucWhite[0]);
            break;
        case USER_COLOR_2:
            setAll(ucRed[1],ucGreen[1],ucBlue[1],ucWhite[1]);
            break;
        case USER_COLOR_3:
            setAll(ucRed[2],ucGreen[2],ucBlue[2],ucWhite[2]);
            break;
        case USER_COLOR_4:
            setAll(ucRed[3],ucGreen[3],ucBlue[3],ucWhite[3]);
            break;
        case USER_COLOR_5:
            setAll(ucRed[4],ucGreen[4],ucBlue[4],ucWhite[4]);
            break;
            
        case RAINBOW:
            rainbow();
            break;
		    case SINGLERGB:
            singlergb();
            break;
        case TWINKYSTARS:
            twinkystars();
            break;
        case CHASER:
            chaser();
            break;
        case HUEFADER:
            huefader();
            break;
        case SPEEDTRAILS:
            speedtrails();
            break;
        case BOUNCYBALLS:
            bouncyballs();
            break;
        case TWOBRUSHCOLORMIXING:
            twobrushcolormixing();
            break;
        case SPARKLER:
            sparkler();
            break;
        case WHIREMIDDLEON:
            whitemiddleon();
            break;
        case WHIREMIDDLEOFF:
            whitemiddleoff();
            break;

        case TASK_RGB:
            if(acceptNewRGBW){
//                Debug.println(F("valuesRGBW R: %d, G: %d, B: %d, W: %d"),valuesRGBW[R],valuesRGBW[G],valuesRGBW[B],valuesRGBW[W]);
                setAll(valuesRGBW[R], valuesRGBW[G], valuesRGBW[B], valuesRGBW[W]);

                acceptNewRGBW = false;
                rgbwChanged = false;
                //reset color because of time out (acceptNewRGBW)
                new3Byte[0] = 0;
                new3Byte[1] = 0;
                new3Byte[2] = 0;
                Debug.println(F("TASK_RGB done"));
            }
            break;
        case TASK_RGBW:
            if(acceptNewRGBW){
                //first 12 bits not defined, 4 bits ignored
//                Debug.println(F("valuesRGBW R: %d, G: %d, B: %d, W: %d"), valuesRGBW[R], valuesRGBW[G], valuesRGBW[B], valuesRGBW[W]);
                setAll(valuesRGBW[R], valuesRGBW[G], valuesRGBW[B], valuesRGBW[W]);
                acceptNewRGBW = false;
                rgbwChanged = false;
                //reset color because of time out (acceptNewRGBW)
//                new6Byte[2] = 0;
//                new6Byte[3] = 0;
//                new6Byte[4] = 0;
//                new6Byte[5] = 0;
                Debug.println(F("TASK_RGBW done"));
            }
            break;
        case TASK_HSV:
            if(acceptNewHSV){
                setAllHsv(valuesHSV[0], valuesHSV[1], valuesHSV[2]);
                acceptNewHSV = false;
                hsvChanged = false;
                //reset color because of time out (acceptNewRGBW)
//                new3Byte[0] = 0;
//                new3Byte[1] = 0;
//                new3Byte[2] = 0;
                Debug.println(F("TASK_HSV done"));
            }
            break;
        case DIMMER:
            setAll(0, 0, 0, lastDimmerValue);
//			      taskNewValue(lastDimmerValue);
            break;

            
        case TASK_IDLE:
        default:
            break;
    }
}
