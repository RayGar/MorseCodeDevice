//Note: this code was written using the header file library and the github repository's code samples. Both credits to this belong to Seeed and their employees.
// I also used this guide for the algorithm on long presses/short presses: http://www.instructables.com/id/Arduino-Dual-Function-Button-Long-PressShort-Press/

#include <Wire.h>
#include "rgb_lcd.h"


rgb_lcd lcd;

const int colorR = 66;
const int colorG = 241;
const int colorB = 244;

const int buttonPin = 3;

// Set the timer system for the button presses
long buttonPressTime = 0;
long longPressTime = 2000;    //a long button press is two seconds, in morse code



// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

//Queue data structure/system
boolean isPrintQueueEmpty = true;       //state of the print queue to know when we should print out put characters
int morseColumn = 0;
int englishColumn = 0;

// constants won't change:
const long interval = 5000;           // interval at which to blink (milliseconds)

// Set the state system of the button presses
boolean isButtonActive = false;                                                                   // for telling if the button is being pressed so we that we only have to use digitalRead() once
boolean isLongPressActive = false;


void setup()
{
   // set up the LCD
  lcd.begin(16, 2);
  lcd.setRGB(colorR, colorG, colorB);
  lcd.setCursor(0, 0);

  //setup the morse code associative array
  
}

void loop()
{
  
  if (digitalRead(buttonPin) == HIGH) {                                                               // if the button is being pressed ...
    if (isButtonActive == false) {                                                                    // if the last saved state of the button was set to false i.e it's the first run of the program ...
      isButtonActive = true;                                                                          // set it to true
      buttonPressTime = millis();                                                                     // save the time when the button was pressed
      
      
    }
    if ((millis() - buttonPressTime > longPressTime) && (isLongPressActive == false)) {               // if the current time - the time the button was pressed is the long button press time
                                                                                                      // AND the last saved state of the Long button press is set to false (to avoid recording two long presses)
      isLongPressActive = true;                                                                       // set the state of isLongPressActive to true
      lcd.setCursor(morseColumn++,0);                                                                             // specify the next column in the "morse row"
      lcd.print("_");                                                                                 // print a dat
      //charBreakTimer = 0;
    }
  } 
  
  else {                                                                                                // happens if the long press case failed
    if (isButtonActive == true) {                                                                       // if the button is being pressed
      if (isLongPressActive == true) {                                                                  // if the long press state is set to true ...
        isLongPressActive = false;                                                                      // set it to false
      } 
      else {
        lcd.setCursor(morseColumn++,0);
        lcd.print(".");                                                                                 // print a dit
        //charBreakTimer = 0;
      }
      isButtonActive = false;                                                                           // set button active to false (we don't check how short a short press is)
    }
  }


  //it is my understanding that the character timer does not depend on whether or not a button was presses, just time, so new if statement
  //TODO: this codefires when it's supposed to but it needs to print thecharacter only once. Maybe have this statement inside theprevious one?

   unsigned long currentMillis = millis();

  //if ((currentMillis - previousMillis >= interval)) {
  if ((currentMillis - previousMillis >= interval)) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // set the LED with the ledState of the variable:
    lcd.setCursor(englishColumn++,1);
    lcd.print("n");
  }

  
}