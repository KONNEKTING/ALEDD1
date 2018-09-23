#define ALL_OFF 0x00
#define RED 0x01
#define GREEN 0x02
#define BLUE 0x03
#define CYAN 0x04 
#define YELLOW 0x05
#define ORANGE 0x06
#define PURPLE 0x07
#define WHITE 0x08


#define USER_COLOR_1 0x1F
#define USER_COLOR_2 0x20
#define USER_COLOR_3 0x21
#define USER_COLOR_4 0x22
#define USER_COLOR_5 0x23

#define RAINBOW 0x32
#define SPARKLER 0x33
#define TWINKYSTARS 0x34
#define CHASER 0x35
#define HUEFADER 0x36
#define SPEEDTRAILS 0x37
#define BOUNCYBALLS 0x38
#define TWOBRUSHCOLORMIXING 0x39
#define WHIREMIDDLEON 0x3C
#define WHIREMIDDLEOFF 0x3D

#define TASK_RGB 0xF0
#define TASK_RGBW 0xF1
#define TASK_HSV 0xF2

#define DIMMER 0xFA

#define TASK_IDLE 0xFE



void taskFunction(){
    switch(currentTask){
        case ALL_OFF:
            setAll(0,0,0,0);
            dimmer.taskOff();
            break;
        case RED:
            setAll(255,0,0,0);
            break;
        case GREEN:
            setAll(0,255,0,0);
            break;
        case BLUE:
            setAll(0,0,255,0);
            break;
        case YELLOW:
            setAll(255,255,0,0);
            break;
        case ORANGE:
            setAll(255,81,0,0);
            break;
        case PURPLE:
            setAll(255,0,255,0);
            break;
        case CYAN:
            setAll(0,255,255,0);
            break;
        case WHITE:
            setAll(0,0,0,255);
            dimmer.taskOn();
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
            if(acceptNewValues){
                setAll(new3Byte[0],new3Byte[1],new3Byte[2],0);
                acceptNewValues = false;
                rgbwhsvChanged = false;
                //reset color because of time out (acceptNewValues)
                new3Byte[0] = 0;
                new3Byte[1] = 0;
                new3Byte[2] = 0;
                Debug.println(F("TASK_RGB done"));
            }
            break;
        case TASK_RGBW:
            if(acceptNewValues){
                //first 12 bits not defined, 4 bits ignored
                setAll(new6Byte[2],new6Byte[3],new6Byte[4],new6Byte[5]);
                acceptNewValues = false;
                rgbwhsvChanged = false;
                //reset color because of time out (acceptNewValues)
                new6Byte[2] = 0;
                new6Byte[3] = 0;
                new6Byte[4] = 0;
                new6Byte[5] = 0;
                Debug.println(F("TASK_RGBW done"));
            }
            break;
        case TASK_HSV:
            if(acceptNewValues){
                setAllHsv(new3Byte[0],new3Byte[1],new3Byte[2]);
                acceptNewValues = false;
                rgbwhsvChanged = false;
                //reset color because of time out (acceptNewValues)
                new3Byte[0] = 0;
                new3Byte[1] = 0;
                new3Byte[2] = 0;
                Debug.println(F("TASK_HSV done"));
            }
            break;
        case DIMMER:

            break;

            
        case TASK_IDLE:
        default:
            break;
    }
}

