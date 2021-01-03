#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <Arduino.h> //Bindet ArduinoLibrary ein




class MotorControl
{
public:

    /**Erstelle Funktionsdeklarationen**/
    MotorControl(void);
    void setInitialPins();
    void setAllSwSleep();
    uint8_t readSensorState();
    void commutate();
    void step0();
    void step1();
    void step2();
    void step3();
    void step4();
    void step5();
    void setErrorLED();
    void measureCurrent();
    void setHighSidePWM(uint8_t poti);
    

    //Setze die analogen Eingänge
    uint8_t V_IS_RC = A5;
    uint8_t IS      = A4;
    uint8_t ADC_U   = A3;
    uint8_t ADC_V   = A2;
    uint8_t ADC_W   = A1;
    uint8_t POTI    = A0;

    //Setze Timer konstanten
    //Zähler und vergleichs Wert
    const uint16_t t1_load = 0;
    const uint16_t t1_comp = 31250;



    

    /**
    * Erstelle HallSensor output Matrix
    * Jede Zeile entspricht einem elektrischen 60° Schritt
    **/
    uint8_t hallOutput [6][3]=
    {
        {1,0,1},
        {1,0,0},
        {1,1,0},
        {0,1,0},
        {0,1,1},
        {0,0,1}
    };

    /**
     * Erstelle KommutationsMatrix
     * Definition der Schalter:
     * Q_u-h;Q_v-h;Q_w-H;Q_u-l;Q_v-l;Q_w-l
    **/
    uint8_t CommutationOutput [6][6]=
    {
        {1,0,0,0,1,0},
        {1,0,0,0,0,1},
        {0,1,0,0,0,1},
        {0,1,0,1,0,0},
        {0,0,1,1,0,0},
        {0,0,1,0,1,0}
    };

};

#endif 
