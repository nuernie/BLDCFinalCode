
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
      //Reset Timer1 Control Register 
  TCCR1A = 0;
  //Setze Prescaler von 256
  TCCR1B != (1<<CS12);
  TCCR1B &= ~(1<<CS11);
  TCCR1B &= ~(1<<CS10);
  //Reset Timer1 and set compare value
  TCNT1 = mc.t1_load;
  OCR1A = mc.t1_comp;
  //Enable Timer1 compare interrupt
  TIMSK1 = (1<<OCIE1A);
  //Enable global Interrupts
  sei();


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
