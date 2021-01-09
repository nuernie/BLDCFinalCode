#include "MotorControl.h"



  /**
   *Konstruktor setzt die initialenPins 
   **/
  MotorControl::MotorControl(void){
      setAllSwSleep();
      setInitialPins();
  }

  /**
   * Erstelle Pin Configuration:
   * IN Pin  HIGH = oberer Fet schaltet ON
   *         LOW  = unterer Fet schaltet ON
   * IN..H Pin = 0 alle Schalter OFF
   * IN..H Pin = 1 erst dann können andere Schalter akitv werden 
  **/
  void MotorControl::setInitialPins(){
      //Setze Staus LED
      //D13 = PB5
      DDRB |= (1<<5);
      PORTB = 0;
      
      //D11 INU OUTPUT Pin  = PB3
      DDRB |= (1<<3);
      PORTB = 0;
      //D10 INV OUTPUT Pin  = PB2
      DDRB |= (1<<2);
      PORTB = 0;
      //D9 INW OUTPUT Pin   = PB1
      DDRB |= (1<<1);
      PORTB = 0;   
  }

  /**
   * Schalte Alle Switche aus 
   * Diesen Zustand im Fehler-Fall einnehmen
  **/
  void MotorControl::setAllSwSleep(){
      //D6 INHU OUTPUT Pin  = PD6
      //Setze INHU = 0
      DDRD |= (1<<6);
      PORTD &= ~(1<<6);
      //D5 INHV OUTPUT Pin  = PD5
      //Setze INHV = 0
      DDRD |= (1<<5);
      PORTD &= ~(1<<5);
      //D3 INHW OUTPUT Pin  = PD3
      //Setze INHW = 0
      DDRD |= (1<<3);
      PORTD &= ~(1<<3);
  }

  /**
   * Liest die Sensordaten ein und gibt die Zeile aus in welcher 
   * wir uns befinden 
  **/
  uint8_t MotorControl::readSensorState(){
  //TODO Switchcase und gebe output aus
  //Prüfe das die SensorDaten passend nacheinander ausgegeben werden! Dürfen nie springen!
  //min - max val [0-1023] thVal = 512
      
  bool hallU = 0;
  bool hallV = 0;
  bool hallW = 0;

    if(analogRead(ADC_U)<512){
        hallU = 0;
    }else{
        hallU = 1;
    }
    
       if(analogRead(ADC_V)<512){
        hallV = 0;
    }else{
        hallV = 1;
    }

       if(analogRead(ADC_W)<512){
        hallW = 0;
        
    }else{
        hallW = 1;
        
    }

  //Verrechne die Zustände zu einem gesamtzustand
  //Die return values entsprechen den KommutierungsZuständen
      if( hallU && !hallV &&  hallW) return 0;
      if( hallU && !hallV && !hallW) return 1;
      if( hallU &&  hallV && !hallW) return 2;
      if(!hallU &&  hallV && !hallW) return 3;
      if(!hallU &&  hallV &&  hallW) return 4;
      if(!hallU && !hallV &&  hallW) return 5;
  
  //Falls keiner der Zustände auftaucht Return Error
     return -1;
  }


  /**
   * Diese Funktion Kommutiert alle 6 Zustande nach dem 120 degree Toshiba Datasheet
   * zum passenden HallSensorOutput eine aktualiesierung muss stetig erfolgen
  **/
  void MotorControl::commutate(){
      
  //TODO erkenne Fehlerfall und gehe dann damit in den Sleep Mode der Schalter
  //Wichtig steps dürfen nur nacheinander abgearbeitet werden Springen nicht erlaubt! 
  //Einstiegspunkt beliebig dh wenn ein Sensorstate Springen will sollte ein Fehler ausgegeben werden!
  
  //Serial.println(readSensorState());
      
      
      
      switch (readSensorState())
      {
  
      case 0:
          step0();
          errorFlag = 0;
          break;
      case 1:
          step1();
          errorFlag =0;
          break;
      case 2:
          step2();
          errorFlag = 0;
          break;
      case 3:
          step3();
          errorFlag = 0;
          break;
      case 4:
          step4();
          errorFlag = 0;
          break;
      case 5:
          step5();
          errorFlag = 0;
          break;    
      default:
          //TODO Error LED has to Blink 
          //Alle Schalter auf Sleep Mode
          setAllSwSleep();
          setErrorLED();
          break;
      }
  }


  /**
  * KommutierungSchritte 0 -5 
  * Port D Inhibit Pins zum aktivieren / deaktivieren der Schalter
  * Port B Input Pins zum auswählen der Schalter
  **/
  void MotorControl::step0(){
      //Die Passenden Fets aktiv schalten
      //Setze INHU = 1
      PORTD |= (1<<6);
      //Setze INHV = 1
      PORTD |= (1<<5);
      //Rücksetze INHW = 0
      PORTD &= ~(1<<3);
  
      //Quh und Qvl müssen gesetzt werden
      //Quh 
       OCR2A = dtc; //PB3
      //PORTB |= (1<<3);
      //Qvl 
        OCR1B = 0; //PB2
      //PORTB &= ~(1<<2);
      //Qw ist inaktiv setze default auf low
       OCR1A = 0; //PB1
      //PORTB &= ~(1<<1);
  }

  void MotorControl::step1(){
      //Die Passenden Fets aktiv schalten
      //Setze INHU = 1
      PORTD |= (1<<6);
      //Rücksetze INHV = 0
      PORTD &= ~(1<<5);
      //Setze INHW = 1
      PORTD |= (1<<3);
  
      //Quh und Qwl müssen gesetzt werden
      //Quh
        OCR2A = dtc; //PB3
      //PORTB |= (1<<3);
      //Qv ist inaktiv setze default auf low
        OCR1B = 0; //PB2
      //PORTB &= ~(1<<2);
      //Qwl
       OCR1A = 0; //PB1
     // PORTB &= ~(1<<1);
  }

  void MotorControl::step2(){
      //Die Passenden Fets aktiv schalten
      //Rücksetze INHU = 0
      PORTD &= ~(1<<6);
      //Setze INHV = 1
      PORTD |= (1<<5);
      //Setze INHW = 1
      PORTD |= (1<<3);
  
      //Qu inaktiv setze default auf low
       OCR2A = 0; //PB3
      //PORTB &= ~(1<<3);
      //Qvh
        OCR1B = dtc; //PB2
      //PORTB |= (1<<2);
      //Qwl
        OCR1A = 0; //PB1
      //PORTB &= ~(1<<1);
  }
  void MotorControl::step3(){
      //Die Passenden Fets aktiv schalten
      //Setze INHU = 1
      PORTD |= (1<<6);
      //Setze INHV = 1
      PORTD |= (1<<5);
      //Rücksetze INHW = 0
      PORTD &= ~(1<<3);
  
      //Qul
        OCR2A = 0; //PB3
      //PORTB &= ~(1<<3);
      //Qvh
        OCR1B = dtc; //PB2
      //PORTB |= (1<<2);
      //Qw inaktiv setze default auf low
        OCR1A = 0; //PB1
      //PORTB &= ~(1<<1);
  
  }
  void MotorControl::step4(){
      //Die Passenden Fets aktiv schalten
      //Setze INHU = 1
      PORTD |= (1<<6);
      //Rücksetze INHV = 0
      PORTD &= ~(1<<5);
      //Setze INHW = 1
      PORTD |= (1<<3);
  
      //Qul
      OCR2A = 0; //PB3
      //PORTB &= ~(1<<3);
      //Qv inaktiv setze default auf low
        OCR1B = 0; //PB2
      //PORTB &= ~(1<<2);
      //Qwh
        OCR1A = dtc; //PB1
      //PORTB |= (1<<1);
  }
  void MotorControl::step5(){
      //Die Passenden Fets aktiv schalten
      //Rücksetze INHU = 0
      PORTD &= ~(1<<6);
      //Setze INHV = 1
      PORTD |= (1<<5);
      //Setze INHW = 1
      PORTD |= (1<<3);
  
      //Qu inaktiv setze default auf low
        OCR2A = 0; //PB3
      //PORTB &= ~(1<<3);
      //Qvl
        OCR1B = 0; //PB2
      //PORTB &= ~(1<<2);
      //Qwh
        OCR1A = dtc; //PB1
      //PORTB |= (1<<1);
  }

  /**
   * Error LED 13 blinkt bei einem Fehler
  **/
  void MotorControl::setErrorLED(){
    //TODO Setze noch einen Interrupt Timer
    //Toggle Led für einen ErrorState
    Serial.println("Error is occured !");
    errorFlag = 1;  
        
  }





  
