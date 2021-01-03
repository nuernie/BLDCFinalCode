
/**
 * Hall-MotorControll
 * v 1.0.0 
 * 
 * In dieser Reihenfolge werden die
 * Hallsensor Kabel angeschlossen
 * orange v
 * weiß w
 * blau u
**/

#include "MotorControl.h"
#define DEBUG     1        //Zum Debugen 1 ansonsten 0 eingeben
#define BAUDRATE  115200  

int potiVal;



//Erstelle ein MotorControl Objekt
MotorControl mc = MotorControl();


void setup() {
  // Starte Kommunikation mit ArduinoUno zum Debugging
  if(DEBUG){
    Serial.begin(BAUDRATE); 
   }



}


void loop() {
//Lese PotiWert aus
potiVal = analogRead(mc.POTI);
//Setze die PWM für die HighSide
//mc.setHighSidePWM(potiVal);
//Kommutiere
mc.commutate();
//Messe den Strom
mc.measureCurrent();
}





//TODO PWM hinzufügen
//HIGH Side mit PWM beaufschlagen
//GND konst durchschalten lassen
//TODO ErrorState hinzufügen
