#include <iostream>
#include <string>
#include <strstream>

// Logitech Wheel SDK
#pragma comment(lib, "LogitechSteeringWheelLib.lib")
#include "LogitechSteeringWheelLib.h"

using namespace std;

/* tool fucntion : parse button value to string*/
string toGear(unsigned char * button);
string toLRSlice(unsigned char * button);

int _tmain(int argc, _TCHAR* argv[]) {
	int times = argc>1?argv[1]:-1;//run forever in default
    bool done = false;
    int i = 0;
    DIJOYSTATE2ENGINES* pState;


    if(LogiSteeringInitialize(true)) {
        printf("init finish\n");
    } else {
    	printf("init error:could not find device\n");
        return ;
    }

    while (!done) {
        if (LogiUpdate()) {
            pState = LogiGetStateENGINES(0);

            //to get the return results in string
            strstream ss;
            string wheel = "wheel=";
            string pedal = "pedal=";
            string brake = "brake=";
            string clutch = "clutch=";
            /*	Notice what the value represents
            			(steering) wheel
				left ---- middle ---- right
				-32768      0         32767
            	
            	(accelerator) pedal, brake, clutch
            	press --------------- release
				-32768				  32767
            */
            ss << wheel << pState->lX << "&" << pedal << pState->lY << "&" << brake << pState->lRz;
            ss<< "&" << clutch << pState->rglSlider[1]<<"&"<<toGear(pState->rgbButtons);
			ss << "&" << toLRSlice(pState->rgbButtons);
         
            string strResult;
            ss >> strResult;
            cout << strResult << endl;

            cout << endl;
            done = (i++ == times);
        }
    }

    system("pause");
    return 0;
}

/*	According to SDK
	the button 8 ~ 14 represents Gear
	if the button is pressed, the value is 128
	otherwise, the value is 0
*/
string toGear(unsigned char * button) {
    if (button[8] != 0) {
        return "Gear=1";
    } else if (button[9] != 0) {
        return "Gear=2";
    } else if (button[10] != 0) {
        return "Gear=3";
    } else if (button[11] != 0) {
        return "Gear=4";
    } else if (button[12] != 0) {
        return "Gear=5";
    } else if (button[13] != 0) {
        return "Gear=6";
    } else if (button[14] != 0) {
        return "Gear=R";
    }

    return  "Gear=N";
}

/*  Using binary representation
	left       right
    button[5] button[4] LRSlice
    0          0         0
    0          128       1
    128        0         2
    128        128       3
*/
string toLRSlice(unsigned char * button) {
	//TODO: need debounce
    if (button[4] == button[5]) {
        return button[4] == 0 ? "LR=0" : "LR=3";
    } else {
        return button[4] > button[5] ? "LR=1" : "LR=2";
    }
}