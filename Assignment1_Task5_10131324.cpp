/*Ariana Estefania Escobar Chalen
ID:10131324
Group 3
Task #5: Modification of the joystick class of Task 2 to work with InterruptIn callbacks. Combination of this with
the modified LED class of Task 4 to create a program that uses the joystick to switch between
the display of each of the coloured LEDs flashing at a frequency controlled one of the
potentiometers. 
Specifications: fTL = 2 Hz and fTR = 10 Hz  
Centre: red
Right: green
Up: blue
Other positions should not cause any LED to be illuminated */

#include "mbed.h"

    class LED {                         //class to turn on and off the LEDs
        private:
        DigitalOut outputSignal;
        public:
        LED(PinName pin) : outputSignal(pin) {}
        void on(void) {outputSignal = 0;}       //LEDs have inverted logic
        void off(void) {outputSignal = 1;}
        void toggle(void) {
            if (outputSignal.read()) 
                outputSignal = 0;
            else 
                outputSignal = 1;
             }
    
        int status(void) {return outputSignal.read();}
        };

    class Potentiometer {               //class to get values fromthe potentiometer
        private:
        AnalogIn inputSignal;
        float VDD, currentSamplePC, currentSampleVolts;
        public:
        Potentiometer(PinName pin, float v) : inputSignal(pin), VDD(v) {}
        float amplitudeVolts(void) { return (inputSignal.read()*VDD); }
        float amplitudePC(void) { return inputSignal.read(); }
        void sample(void) {
        currentSamplePC = inputSignal.read();
        currentSampleVolts = currentSamplePC * VDD;
        }
        float getCurrentSampleVolts(void) { return currentSampleVolts; }
        float getCurrentSamplePC(void) { return currentSamplePC; }
        };

    
    class RotationRate{             //class to define the linearity of the changes in the potentiometer, and also which led corresponds to which joystick position
        private:
        const float smin, smax, fmin, fmax; // define voltage-freq relationship
        float gdt, incpt, period;
        Timeout to;
        Potentiometer* pot;
        LED red, green, blue;
        // gradient and intercept of linear voltage-freq relationship
        float calc_gdt(void) { return (fmax-fmin)/(smax-smin); }
        float calc_incpt(void) { return (fmax - gdt*smax);}
        public:
        RotationRate(Potentiometer* p,
        float xmn, float xmx, float ymn, float ymx, PinName p1, PinName p2, PinName p3): pot(p), smin(xmn), smax(ymx), fmin(ymn), fmax(ymx), red(p1), green(p2), blue(p3)  {
        gdt = calc_gdt();
        incpt = calc_incpt();
        to.attach(callback(this, &RotationRate::noled), 0.01); }        //initiate the leds off
        void upled(void)            //up position is linked to blue LED
            {green.off();
            blue.toggle();
            red.off();
            period = 1.0f/(gdt*pot->getCurrentSampleVolts() + incpt);
            to.attach(callback(this, &RotationRate::upled), period/2.0f);}      //keep looping to make the flashing of the LED
        void rightled(void)         //right position is linked to green LED
            {green.toggle();
            blue.off();
            red.off ();
            period = 1.0f/(gdt*pot->getCurrentSampleVolts() + incpt);
            to.attach(callback(this, &RotationRate::rightled), period/2.0f);}   //keep looping to make the flashing of the LED
        void centreled(void)         //centre position is linked to red LED
            {green.off();
            blue.off();
            red.toggle (); 
            period = 1.0f/(gdt*pot->getCurrentSampleVolts() + incpt);
            to.attach(callback(this, &RotationRate::centreled), period/2.0f);}  //keep looping to make the flashing of the LED
        void noled(void)                    //create an state where al the LEDs are off (to use it at the beginning of the program)
            {green.off();
            blue.off();
            red.off (); 
            }
        };
       
        class Joystick {
        private:
        RotationRate x1;            //we need to link the RotationRate class to the actual positions of the joystick
        InterruptIn Up, Right, Centre;
        public:
        Joystick(PinName u, PinName r, PinName c, RotationRate x) : Up(u), Right(r), Centre(c), x1(x) {
        Up.rise (callback (&x1, &RotationRate::upled));             //Callbacks to the functions to assign the led and position of the joystick to the rising edge of the Interrupt
        Right.rise (callback (&x1, &RotationRate::rightled));
        Centre.rise (callback (&x1, &RotationRate::centreled));
       }
        
        }; 
    
   
    int main(void) {

    Potentiometer* leftHand = new Potentiometer(A0, 3.3);
    RotationRate r(leftHand, 0.0, 3.3, 2.0, 10.0, D5, D9, D8);
    Joystick* J = new Joystick(A2, A5, D4, r);
   

        while (1) {
            leftHand->sample();
            wait(0.01);
            }
    }