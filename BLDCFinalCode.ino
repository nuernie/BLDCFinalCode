  
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
  #define DEBUG    1        //Zum Debugen 1 ansonsten 0 eingeben
  #define BAUDRATE  115200  
  

  


  //Erstelle ein MotorControl Objekt
  MotorControl mc = MotorControl();


  void setup() {
    // Starte Kommunikation mit ArduinoUno zum Debugging
    if(DEBUG){
      Serial.begin(BAUDRATE); 
     }

  setPwmPin9_10();
  setPwmPin11();

    
    
  }


  void loop() {
  
    if (Serial.available() > 0)
  {
    uint8_t in = Serial.read();
    if(in == '+') mc.dtc += 10;          // Adapt the speed with keyboard input in the serial monitor
    if(in == '-') mc.dtc -= 10;
    Serial.println(mc.dtc);
  }


    //Lese Poti Werte aus
   // Serial.println(analogRead(A0));
   // mc.dtc = map(analogRead(A0),0,989,0,255);
    //Kommutiere
    
    mc.commutate();
   
     
  }

 void setPwmPin9_10(){
  // Reset Timer Register
  TCCR1A = 0;
  TCCR1B = 0;
  //Fast PWM Mode 
  TCCR1A |= (1<<WGM10);
  TCCR1B |= (1<<WGM12);
  //Setze Compare Modi non inverting Mode!
  TCCR1A |= (1<<COM1B1);
  TCCR1A |= (1<<COM1A1);

  //Setze Prescaler 8
  TCCR1B &= ~(1<<CS10);
  TCCR1B |=  (1<<CS11);
  TCCR1B &= ~(1<<CS12);
  //Setze Compare Values
  OCR1A = 0; // Pin 9 
  OCR1B = 0; // Pin 10
  
  //Setze Pin 9 und 10 für aktiven PWM ausgang
  DDRB |= (1<<PB1);
  DDRB |= (1<<PB2); 
 }

  void setPwmPin11(){
  // Reset Timer Register
  TCCR2A = 0;
  TCCR2B = 0;
  //Fast PWM Mode TOP 0xFF
  TCCR2A |=(1<<WGM21);
  TCCR2A |=(1<<WGM20); 
  //Setze Compare Modi non inverting Mode!
  TCCR2A |= (1<<COM2A1);
  // prescaler = 8
  TCCR2B &= ~(1<<CS22);
  TCCR2B |= (1<<CS21);
  TCCR2B &= ~(1<<CS20);
  //Setze Compare Value
  OCR2A = 0; //Pin 11
  //Setze Pin11 afür aktiven PWM ausgang
  DDRB |= (1<<PB3);
  }



  

//TODO:
//PWM hinzufügen
//PORT Statements weg nehmen einfach nur INH pins bestimmen lassen
//Welche high side mit pwm beaufschlagt wird
//Low Side weiterhin fest ohne pwm durchschalten
//GND konst durchschalten lassen
//Einfach PWM auf 0% stellen um const durch zu schalten
