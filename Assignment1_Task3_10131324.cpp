/*Ariana Estefania Escobar Chalen
ID:10131324
Group 3
Task #3: Modification of the speaker class from Task 1 to generate a tone of fixed frequency fT by using a Ticker
callback that executes a class member function
Specifications: tone frequency fT in Hz =2000 */

#include "mbed.h"


    class Speaker{
        private:
            DigitalOut S;
            Ticker t;
            bool state;
        public:
            Speaker(PinName pin) : S(pin) {t.attach(callback(this, &Speaker::toggle), 0.5/2000); state = false;}  //ticker callback is in the instance of this declaration
            void on(void) {S = 1;} //turn on the speaker
            void off(void) {S = 0;} //turn off the speaker
            void toggle(void) {     //the function toggle will allow us to turn the speaker on and off sequentially
            if (state == true)      
                {S = 1;
                state = !state;}        
            else if (state == false){
                        S=0;
                        state = !state;}
                    }
        
 };

int main() {
    Speaker X (D6);         // this ceclartion turns on the speaker
    while (1) {             //keep the speaker working
        }
    }


