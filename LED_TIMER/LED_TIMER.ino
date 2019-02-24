#include <FastLED.h>

#if FASTLED_VERSION < 3001000
#error "Requires" FastLED 3.1 or later: check github for latest code."
#endif

// How many leds in your strip?
#define NUM_LEDS 30
#define NUM_STEPS 3

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 7
#define CLOCK_PIN 13

// Define the array of leds
CRGB leds[NUM_LEDS];
const int buttonPin = 2;     // the number of the pushbutton pin
const int buzzerPin =  4;
const int ledPin =  5;
const int timerInterval = 60000;
const int delayStep = 2000; //timerInterval/NUM_LEDS;
const int shortBeep = 500; //delayStep/4;
const int longBeep = 1000; //delayStep/2;
const int maxLongBeep = 1900; //delayStep-delayStep/20;

int beepState = 0;
int colorIndex=0;
int buttonState = 0;         // variable for reading the pushbutton status
void turnOffAllLeds();
void beep(int duration);

void setup() { 
  	   FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
    
       pinMode(buttonPin, INPUT);
       // initialize the LED pin as an output:
       pinMode(ledPin, OUTPUT);
       pinMode(buzzerPin, OUTPUT);
       turnOffAllLeds();
}

void loop() { 
  colorIndex=0;
  beepState = 0;
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  digitalWrite(buzzerPin, HIGH);        

  if (buttonState == LOW) {
    
    turnOffAllLeds();
    // turn LED off(HIGH)
    digitalWrite(ledPin, HIGH);
      for (int ledPosition=0; ledPosition<NUM_LEDS; ledPosition++){
        switch (colorIndex){
          case 0:
            leds[ledPosition] = CRGB::Green;
            break;
          case 1:
            leds[ledPosition] = CRGB::Yellow;
            break;
          case 2: 
            leds[ledPosition] = CRGB::Red;
            break;
          default:
            leds[ledPosition] = CRGB::Black;
        }
        FastLED.show();
        switch (ledPosition){
          case 0:
            beepState=2;
            break;
          case 9:
            colorIndex = 1;
            break;
          case 19:
            beepState=1;
            colorIndex = 2;
            break;
            
          case 25:
            beepState=1;
            break;
          case 26:
            beepState=1;
            break;
          case 27:
            beepState=1;
            break;
          case 28:
            beepState=1;
            break;
          case 29:
            beepState=3;
            break;
         default:;
        }
        switch(beepState){
          case 0:
            delay(delayStep);
            beepState=0;
            break;
          case 1:
            beep(shortBeep);
            delay(delayStep-shortBeep);
            beepState=0;
            break;
          case 2:
            beep(longBeep);
            delay(delayStep-longBeep);
            beepState=0;
            break;
          case 3:
            beep(maxLongBeep);
            delay(delayStep-maxLongBeep);
            beepState=0;
            break;
          default:
            delay(delayStep);
            beepState=0;        
      }
    }
  } else{
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }
  
}

void turnOffAllLeds(){
  for (int i=0; i<NUM_LEDS; i++){
    // Now turn the LED off, then pause
        leds[i] = CRGB::Black;
        FastLED.show();
  }
}

void beep(int duration){
  digitalWrite(buzzerPin, LOW);
  delay(duration);
  digitalWrite(buzzerPin, HIGH);
}
