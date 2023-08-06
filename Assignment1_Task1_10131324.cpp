/*Ariana Estefania Escobar Chalen
ID:10131324
Group 3
Task #1: Development of a class to generate tones with the loudspeaker on the Application Shield
Specifications: tone frequency fT in Hz = 2000 */

#include "mbed.h"


class Speaker{            
private:
    DigitalOut S;
public:
    Speaker(PinName pin) : S(pin) {}
    void on(void) {S = 1;} //turn on the speaker
    void off(void) {S = 0;} //turn off the speaker
    void toggle(void) {
        if (S.read()) 
            S = 1;
        else 
            S = 0;
    }
    
    int status(void) {return S.read();}
};

int main() {
    float freq = 2000; 
    Speaker Spkr(D6);
    while(1) {
            Spkr.on();
            wait(1.0f/(2*freq));    //time to wait must be half of the period
            Spkr.off();
            wait(1.0f/(2*freq));
        }
    }




    
