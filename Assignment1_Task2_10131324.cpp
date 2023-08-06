/*Ariana Estefania Escobar Chalen
ID:10131324
Group 3
Task #2: Development of a class to allow a program to read the state of the Application Shield’s joystick
Specifications: Centre: red
Right: green
Up: blue
Other positions should not cause any LED to be illuminated */

#include "mbed.h"

    class LED{              //class to turn on and off the LEDs
        private:
        DigitalOut LEDs;
        public:
        LED(PinName pin) : LEDs(pin) {}
        void on(void) {LEDs = 0;}   //LEDs have inverted logic
        void off(void) {LEDs = 1;}
        void toggle(void) {
            if (LEDs.read()) 
                LEDs = 0;
            else 
                LEDs = 1;
            }
    
        int status(void) {return LEDs.read();}
            };

    class Joystick {
        private:
        DigitalIn Up, Right, Centre;        //positions required in the joystick
        public:
        Joystick(PinName u, PinName r, PinName c) : Up (u), Right (r), Centre (c) {}
        bool uppressed(void){return Up;};           //test wheter the joystick button is pressed or not
        bool rightpressed(void){return Right;};
        bool centrepressed(void){return Centre;};
        }; 


    int main() {
        Joystick J (A2, A5, D4);
        LED RED (D5);
        LED BLUE (D8);
        LED GREEN (D9);
    
    while (1) {
        if (J.rightpressed () == true){     //according to each position of the joystick turn on one colour of the LEDs
       RED.off ();
       BLUE.off ();
       GREEN.on ();}
        else {                              //if joystick is not pressed, do not turn on any light
        RED.off ();
       BLUE.off ();
       GREEN.off ();}
       
           
        if (J.uppressed () == true){
       RED.off ();
       BLUE.on ();
       GREEN.off ();}
        else {
        RED.off ();
       BLUE.off ();
       GREEN.off ();} 
   
       
        if (J.centrepressed () == true){
       RED.on ();
       BLUE.off ();
       GREEN.off ();}
        else {
        RED.off ();
       BLUE.off ();
       GREEN.off ();}
    
        }
    }


