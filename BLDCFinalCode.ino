  
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
  
  int potiVal = 0;
  


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
    //potiVal = analogRead(mc.POTI);
    //Kommutiere
    mc.commutate();
     
  }

  






//TODO:
//PWM hinzufügen
//PORT Statements weg nehmen einfach nur INH pins bestimmen lassen
//Welche high side mit pwm beaufschlagt wird
//Low Side weiterhin fest ohne pwm durchschalten
//GND konst durchschalten lassen
//Einfach PWM auf 0% stellen um const durch zu schalten
