/*Ariana Estefania Escobar Chalen
ID:10131324
Group 3
Task #4: Modification of the LED class in Example Program 2 to enable the user to vary the frequency
of flashing using one of the potentiometers. The flashing frequencies when the potentiometer
is in its left- and right-most positions will be specified (fTL and fTR), and a linear variation of
frequency with position is required between these 2 extremes.
The potentiometer output should be used to set the interval of a Timeout object that is a
member of this class.
Specifications: fTL = 2 Hz and fTR = 10 Hz  */

#include "mbed.h"

    class LED {                 //class to turn on and off the LEDs
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

    class Potentiometer {                //class to get values fromthe potentiometer
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

    class Sequencer {
        private:
        bool state;
        LED blue;
        public:
        Sequencer(PinName p1) : blue(p1) {state = false;}
        void sequence(void) {       //this function will perform the flashing of the LED, changing between on and off sequentially
            if (state == false)
                {blue.off ();
                state = !state;}
            else if (state == true)
                {blue.on ();
                state = !state;} 
                }
        };

    class RotationRate {            //class to define the linearity of the changes in the potentiometer
        private:
        const float smin, smax, fmin, fmax; // define voltage-freq relationship
        float gdt, incpt, period;
        Timeout to;
        Sequencer* seq;
        Potentiometer* pot;
        // gradient and intercept of linear voltage-freq relationship
        float calc_gdt(void) { return (fmax-fmin)/(smax-smin); }
        float calc_incpt(void) { return (fmax - gdt*smax);}
        public:
        RotationRate(Potentiometer* p,
        Sequencer* s,
        float xmn, float xmx, float ymn, float ymx): pot(p), seq(s), smin(xmn), smax(ymx), fmin(ymn), fmax(ymx) {
        gdt = calc_gdt();
        incpt = calc_incpt();
        to.attach(callback(this, &RotationRate::updateRate), 0.01);
        };

        void updateRate(void) {
        seq->sequence(); // callback
        period = 1.0f/(gdt*pot->getCurrentSampleVolts() + incpt); // set next to
        to.attach(callback(this, &RotationRate::updateRate), period/3.0f);
        }
        }; 

    int main(void) {

    Potentiometer* leftHand = new Potentiometer(A0, 3.3);
    Sequencer* s = new Sequencer(D8);
    RotationRate r(leftHand, s, 0.0, 3.3, 2.0, 10.0);

        while (1) {
            leftHand->sample();     //getting the sample values from the potentiometer
            wait(0.01);
            }
    }