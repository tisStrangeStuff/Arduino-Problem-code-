#include <Arduino.h>
int state;
bool over = false;
unsigned long codeStart;
unsigned long PREINTTIME;
unsigned long CURRINTTIM;
const long pulseMin = 690; //Each pulse should only last 562.5microSnds
const long pulseMAx = 500;
const long bitOneMax = 1689; //All one bits are follwed by a 1.6875ms pause
int i = 0; //counter for bit decoding
class BITREAD {
     
    public: 
          BITREAD(int a, unsigned long b, unsigned c) { //Pulls the times from the decode file, makes life easier
            state = a; //state var, helps find out when to start decdoing
            PREINTTIME = b; //last time intturp was triggerd
            CURRINTTIM = c; //current time inttrupt was triggered
            Serial.println(PREINTTIME);
          }

    static void readBit(){
        if (state == 4) {
            
            codeStart = micros();
            state++;
            
        } else if(PREINTTIME - codeStart > 56150) { //NEC has a total code transmision time of 54ms checks to see if it has ended.
            state = 0; 
            over = 1;
        }
        switch (i) {
        case 0:
            if (CURRINTTIM - PREINTTIME < pulseMAx && CURRINTTIM - PREINTTIME > pulseMin) {
                i++;
            }  
            break;
        case 1:
            if(CURRINTTIM - PREINTTIME < pulseMAx && CURRINTTIM - PREINTTIME > pulseMin) {
                Serial.println('0');

            }else{
                Serial.println('1');

            }
            i = 0;
            break;
        }
        
    }

};

int isOver() {
    return over;
}
