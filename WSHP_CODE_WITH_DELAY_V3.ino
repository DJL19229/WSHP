// C++ code

int CON1 = 0;
int HPS = 0;
int LPS = 0;
int FRZ = 0;
int SW1_REV_COOL_HEAT = 0;
int SW2_USE_FRZ_YES_NO = 0;
int SW3_USE_COND_PROT_YES_NO = 0;
int SW4_USE_CON1_CON2 = 0;
int SW5_USE_ISO_YES_NO = 0;
int FAN = 0;
int CON2 = 0;
int G5 = 0;
int Y5 = 0;
int O5 = 0;
int LED_FLASH_TIME = 0;
int counter;
int counter2;
int counter3;
int counter4;
int counter5;
int compressorInputState = LOW;       // Variable to store the state of the input pin
int previousCompressorInputState = LOW;    // Variable to store the previous state of the input pin
unsigned long previousTime = 0;   // Variable to store the previous time
unsigned long delayTime = 60000;   // COMPRESSOR TIMEOUT in milliseconds (60 seconds)
const unsigned long requiredDuration = 1000; // Fault state duration for safeties to lockout
bool delayInProgress = false;  // Flag to track delay progress

void setup()
{
  pinMode(A0, INPUT);  // Condensate Safety (1) Sensor Input
  pinMode(A1, INPUT);  // Fan Call Input
  pinMode(A2, INPUT);  // Compressor Call Input
  pinMode(A3, INPUT);  // Reversing Valve Call Input
  pinMode(A4, INPUT);  // Isolation Valve Used? (Yes or No)
  pinMode(A5, INPUT);  // Reversing Valve Engergized in ________ (Cooling or Heating)              
  pinMode(2, INPUT);   // Freeze Protection Used? (Yes or No)                                                                  
  pinMode(3, INPUT);   // Condensate Protection Used? (Yes or No)
  pinMode(4, INPUT);   // Condensate Safety Selector (1 or 2)
  pinMode(5, INPUT);   // Low Pressure Safety Switch
  pinMode(6, INPUT);   // High Pressure Safety Switch
  pinMode(7, INPUT);   // Freeze Stat Safety Switch
  pinMode(8, INPUT);   // Condensate Safety (2) Switch Input
  pinMode(9, OUTPUT);  // Isolation Valve Output
  pinMode(10, OUTPUT); // Reversing Valve Output
  pinMode(11, OUTPUT); // Compressor Output
  pinMode(12, OUTPUT); // Fan Output
  pinMode(13, OUTPUT); // Status LED

  LED_FLASH_TIME = 200; // DIAGNOSTIC LED FLASH CODE - FLASH SPEED

  delay(3000); // Startup delay for sensors to stabilize
}

void loop()
{
  // CONDENSATE SENSOR SAFETY
  CON1 = analogRead(0);
  	delay(10);
  SW3_USE_COND_PROT_YES_NO = digitalRead(3);
  	delay(10);
  SW4_USE_CON1_CON2 = digitalRead(4);
  	delay(10);
  if (SW3_USE_COND_PROT_YES_NO == HIGH && SW4_USE_CON1_CON2 == HIGH) {
    if (CON1 < 500) {
    unsigned long durationCount5 = millis();
    while (millis() - durationCount5 < requiredDuration) {
      CON1 = analogRead(0);
        delay(10);
      if (CON1 >= 500){
        break;
      }
    }
    if (CON1 < 500) {
    	if (SW3_USE_COND_PROT_YES_NO == HIGH && SW4_USE_CON1_CON2 == HIGH && CON1 < 500) {
          while (true) {
      		digitalWrite(11, LOW);
      		for (counter4 = 0; counter4 < 5; ++counter4) {
        	digitalWrite(13, LOW);
        	delay(LED_FLASH_TIME); // Wait for LED_FLASH_TIME millisecond(s)
        	digitalWrite(13, HIGH);
        	delay(LED_FLASH_TIME); // Wait for LED_FLASH_TIME millisecond(s)
        	digitalWrite(13, LOW);
        	delay(LED_FLASH_TIME); // Wait for LED_FLASH_TIME millisecond(s)
            }
           delay (3000);
           Y5 = analogRead(A2);
            delay(10);
            if (Y5 <= 500) {
              break;
            }
          	}
      	}
    }
    }      
  }
   else {
    digitalWrite(13, HIGH);
   }
  
  
  // CONDENSATE SWITCH SAFETY
  CON2 = digitalRead(8);
  	delay(10);
  SW3_USE_COND_PROT_YES_NO = digitalRead(3);
  	delay(10);
  SW4_USE_CON1_CON2 = digitalRead(4);
  	delay(10);
  if (SW3_USE_COND_PROT_YES_NO == HIGH && SW4_USE_CON1_CON2 == LOW) {
    if (CON2 == LOW) {
    unsigned long durationCount4 = millis();
    while (millis() - durationCount4 < requiredDuration) {
      CON2 = digitalRead(8);
      delay(10);
      if (CON2 == HIGH) {
        break;
      }
    }
    if (CON2 == LOW) {
    	if (CON2 == LOW) {
          while (true) {
      		digitalWrite(11, LOW);
      		for (counter4 = 0; counter4 < 5; ++counter4) {
        	digitalWrite(13, LOW);
        	delay(LED_FLASH_TIME); // Wait for LED_FLASH_TIME millisecond(s)
        	digitalWrite(13, HIGH);
        	delay(LED_FLASH_TIME); // Wait for LED_FLASH_TIME millisecond(s)
        	digitalWrite(13, LOW);
        	delay(LED_FLASH_TIME); // Wait for LED_FLASH_TIME millisecond(s)
            }
           delay (3000);
           Y5 = analogRead(A2);
            delay(10);
            if (Y5 <= 500) {
              break;
            }
          	}
      	}
    }
    }      
  }
   else {
    digitalWrite(13, HIGH);
   }
  
  
  // HIGH PRESSURE SWITCH SAFETY
  HPS = digitalRead(6);
  	delay(10);
  if (HPS == LOW) {
    unsigned long durationCount2 = millis();
    while (millis() - durationCount2 < requiredDuration) {
      HPS = digitalRead(6);
        delay(10);
      if (HPS == HIGH) {
        break;
      }
    }
    if (HPS == LOW) {
    	if (HPS == LOW) {
          while (true) {
      		digitalWrite(11, LOW);
      		for (counter4 = 0; counter4 < 2; ++counter4) {
        	digitalWrite(13, LOW);
        	delay(LED_FLASH_TIME); // Wait for LED_FLASH_TIME millisecond(s)
        	digitalWrite(13, HIGH);
        	delay(LED_FLASH_TIME); // Wait for LED_FLASH_TIME millisecond(s)
        	digitalWrite(13, LOW);
        	delay(LED_FLASH_TIME); // Wait for LED_FLASH_TIME millisecond(s)
            }
           delay (3000);
           Y5 = analogRead(A2);
            delay(10);
            if (Y5 <= 500) {
              break;
            }
          	}
      	}
    }      
  }
   else {
    digitalWrite(13, HIGH);
   }
  
  
  // LOW PRESSURE SWITCH SAFETY
  LPS = digitalRead(5);
  	delay(10);
  if (LPS == LOW) {
    unsigned long durationCount = millis();
    while (millis() - durationCount < requiredDuration) {
      LPS = digitalRead(5);
        delay(10);
      if (LPS == HIGH) {
        break;
      }
    }  
    if (LPS == LOW) {
      if (LPS == LOW) {
          while (true) {
      		digitalWrite(11, LOW);
      		for (counter4 = 0; counter4 < 3; ++counter4) {
        	digitalWrite(13, LOW);
        	delay(LED_FLASH_TIME); // Wait for LED_FLASH_TIME millisecond(s)
        	digitalWrite(13, HIGH);
        	delay(LED_FLASH_TIME); // Wait for LED_FLASH_TIME millisecond(s)
        	digitalWrite(13, LOW);
        	delay(LED_FLASH_TIME); // Wait for LED_FLASH_TIME millisecond(s)
            }
           delay (3000);
           Y5 = analogRead(A2);
            delay(10);
            if (Y5 <= 500) {
              break;
            }
          	}
      	}
    }      
  }
   else {
    digitalWrite(13, HIGH);
  }
  
  
  // FREEZE PROTECTION SWITCH SAFETY
  FRZ = digitalRead(7);
  	delay(10);
  SW2_USE_FRZ_YES_NO = digitalRead(2);
    delay(10);
  if (SW2_USE_FRZ_YES_NO == HIGH && FRZ == LOW) {
    unsigned long durationCount3 = millis();
    while (millis() - durationCount3 < requiredDuration) {
      FRZ = digitalRead(7);
        delay(10);
      if (FRZ == HIGH) {
        break;
      }
    }
    if (FRZ == LOW) {
    	if (FRZ == LOW) {
          while (true) {
      		digitalWrite(11, LOW);
      		for (counter4 = 0; counter4 < 4; ++counter4) {
        	digitalWrite(13, LOW);
        	delay(LED_FLASH_TIME); // Wait for LED_FLASH_TIME millisecond(s)
        	digitalWrite(13, HIGH);
        	delay(LED_FLASH_TIME); // Wait for LED_FLASH_TIME millisecond(s)
        	digitalWrite(13, LOW);
        	delay(LED_FLASH_TIME); // Wait for LED_FLASH_TIME millisecond(s)
            }
           delay (3000);
           Y5 = analogRead(A2);
            delay(10);
            if (Y5 <= 500) {
              break;
            }
          	}
      	}
    }      
  }
   else {
    digitalWrite(13, HIGH);
   }
  
  
  // FAN CALL
  G5 = analogRead(A1);
  	delay(10);
  if (G5 > 500) {
    digitalWrite(12, HIGH);
    delay(10); // Wait for 10 millisecond(s)
  } else {
    digitalWrite(12, LOW);
    delay(10); // Wait for 10 millisecond(s)
  }
  
  
  // ISOLATION VALVE CALL
  SW5_USE_ISO_YES_NO = analogRead(A4);
  	delay(10);
  Y5 = analogRead(A2);
    delay(10);
  if (SW5_USE_ISO_YES_NO > 500 && Y5 > 500) {
    digitalWrite(9, HIGH);
    delay(10); // Wait for 10 millisecond(s)
  } else {
    digitalWrite(9, LOW);
    delay(10); // Wait for 10 millisecond(s)
  }
  
  
  // COMPRESSOR CALL
  Y5 = analogRead(A2);
  	delay(10);
  if (Y5 > 500) {
    compressorInputState = HIGH;
  }
  if (Y5 <= 500) {
    compressorInputState = LOW;
  }

  if (compressorInputState == HIGH && previousCompressorInputState == LOW) {
    // Input state transitioned from LOW to HIGH
    previousTime = millis();  // Record the current time
    delayInProgress = true;
  }

  if (delayInProgress && (millis() - previousTime >= delayTime)) {
    // Delay completed
    digitalWrite(11, HIGH);
    delayInProgress = false;
  }

  if (compressorInputState == LOW) {
    // Input state is LOW, turn off the output immediately
    digitalWrite(11, LOW);
    delayInProgress = false;
  }

  previousCompressorInputState = compressorInputState;
  
  
  // REVERSING VALVE CALL (ENERGIZING IN COOL)
  SW1_REV_COOL_HEAT = analogRead(A5);
  	delay(10);
  O5 = analogRead(A3);
  	delay(10);
  if (SW1_REV_COOL_HEAT > 500) {
    O5 = analogRead(A3);
  	delay(10);
    if (O5 > 500) {
      digitalWrite(10, HIGH);
      delay(10); // Wait for 10 millisecond(s)
    } else {
      digitalWrite(10, LOW);
      delay(10); // Wait for 10 millisecond(s)
    }
  }
  

  // REVERSING VALVE CALL (ENERGIZING IN HEAT)
  SW1_REV_COOL_HEAT = analogRead(A5);
  	delay(10);
  O5 = analogRead(A3);
  	delay(10);
  if (SW1_REV_COOL_HEAT <= 500){
    Y5 = analogRead(A2);
  	delay(10);
    if (Y5 <= 500 && O5 <= 500){
      digitalWrite(10, LOW);
      delay(10);
    }
  }
  
  if (SW1_REV_COOL_HEAT <= 500) {
    Y5 = analogRead(A2);
  	delay(10);
    if (Y5 > 500 && O5 > 500) {
      digitalWrite(10, LOW);
      delay(10); // Wait for 10 millisecond(s)
    }
  }
  
  if (SW1_REV_COOL_HEAT <= 500) {
    Y5 = analogRead(A2);
  	delay(10);
    if (Y5 <= 500 && O5 > 500) {  
      digitalWrite(10, LOW);
      delay(10); // Wait for 10 millisecond(s)
    }
  }
  
  if (SW1_REV_COOL_HEAT <= 500) {
    Y5 = analogRead(A2);
  	delay(10);
    if (Y5 > 500 && O5 <= 500) {
      digitalWrite(10, HIGH);
      delay(10); //Wait for 10 millisecond(s)
    }
  }
  
  delay(10); // Wait for 10 millisecond(s)
}