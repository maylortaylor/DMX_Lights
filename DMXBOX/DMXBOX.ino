/***************************************************************************************
****************************************************************************************

Project: Christmas 2016 LED Display Box

Description: Controls a WS2811 based strands of LEDs. Accepts input from a Rotary
             Encoder (pattern select) and Potentiometer (brightness). Stores current 
             pattern in to memory for recall after power loss.

    
Connections:

  VCC = 5v
  
  WS2811:
    GND -> GND
    VCC -> VCC
    DAT -> Digital 6
    
  Rotary Encoder:
    D 3 <-   -> D 4 
    GND <- O  |
    D 2 <-   -> GND 

  Potentiometer:
    /-> GND (alternative A0)
    Q-> A2
    \-> VCC (alternative A1)

Change log: 

Version 0.9
  12/10/16 - Matt/Brian - Created baseline code to interface with rotary encoder
                          and potentiometer. Ported simplex noise code and created
                          basic color changers and hues.
                          
Version 0.9.1                        
  12/13/16 - Matt       - Added more colors and refined rainbow/noise flows.

Version 0.9.2
  12/15/16 - Brian      - Optimized output code for higher frame rate    


Future Improvements:

  Catch overflow on Simplex Noise function (xoffset/yoffset)
  
****************************************************************************************
***************************************************************************************/


/***************************************************************************************
  Libraries
***************************************************************************************/
/* Encoder Library - Basic Example
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 *
 * This example code is in the public domain.
 */
#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>        // Persistent memory
#ifdef __AVR__
  #include <avr/power.h>
#endif
#include <avr/pgmspace.h>
#include <DMXSerial.h>

/***************************************************************************************
  !!!! >>>>> LOOK HERE <<<<<< !!!! ------ S   E   T    U   P
***************************************************************************************/
#define PWM_MaxPixels 60 // number of lights being used
#define PIN 6
//#define RGBW true
#define INVERTED 1      //Define keyword

/***************************************************************************************
  General Variables
***************************************************************************************/
//const PROGMEM  dataType  variableName[] = {};

int currBrightness = 0;
int brightnessRead = 0;
int upperLimit = 22; // max number of patterns (encoder)
int lowerLimit = 1; // minimum number of patterns (encoder)
int encoderButton = 0;
int lastSavedEncoderPosition = 0;
int counter = 0;

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PWM_MaxPixels, PIN, NEO_RGB + NEO_KHZ800);

/***************************************************************************************
  Encoder Variables
***************************************************************************************/
static int pinA = 2; // Our first hardware interrupt pin is digital pin 2
static int pinB = 3; // Our second hardware interrupt pin is digital pin 3
volatile byte aFlag = 0; // let's us know when we're expecting a rising edge on pinA to signal that the encoder has arrived at a detent
volatile byte bFlag = 0; // let's us know when we're expecting a rising edge on pinB to signal that the encoder has arrived at a detent (opposite direction to when aFlag is set)
volatile byte encoderPos = 1; //this variable stores our current value of encoder position. Change to int or uin16_t instead of byte if you want to record a larger range than 0-255
volatile byte oldEncPos = 0; //stores the last encoder position value so we can compare to the current reading and see if it has changed (so we know when to print to the serial monitor)
volatile byte reading = 0; //somewhere to store the direct values we read from our interrupt pins before checking to see if we have moved a whole detent

/***********************************************************
  Simplex Noise Variable Declaration
***********************************************************/
//Define simplex noise node for each LED
const int LEDs_in_strip = PWM_MaxPixels;
const int LEDs_for_simplex = 5;

// Extra fake LED at the end, to avoid fencepost problem.
// It is used by simplex node and interpolation code.
float LED_array_red[LEDs_in_strip+1];
float LED_array_green[LEDs_in_strip+1];
float LED_array_blue[LEDs_in_strip+1];
int node_spacing = LEDs_in_strip / LEDs_for_simplex;

// Math variables
int i, j, k, A[] = {0, 0, 0};
float x1,y1,x2,y2;
float u, v, w, s, h;
static float onethird = 0.333333333;
static float onesixth = 0.166666667;
int T[] = {0x15, 0x38, 0x32, 0x2c, 0x0d, 0x13, 0x07, 0x2a};

// Simplex noise parameters:
float timeinc = 0.0025;
float spaceinc = 0.05;
int intensity_r = 734;
int intensity_g = 734;
int intensity_b = 734;
float yoffset = 0.0;
float xoffset = 0.0;
float saturation = 1.0;
int red, green, blue;
int red2, green2, blue2;  //used in HSV color functions 


/***************************************************************************************
  Other Variables
***************************************************************************************/
/***********************************************************
  Lookup table for WS2803 calculations
***********************************************************/


/***************************************************************************************
  Setup
***************************************************************************************/
void setup() {
  /***************************************************************************************
    General Setup
  ***************************************************************************************/
  //Serial.begin(115200); // start the serial monitor link


// encoder button
  //pinMode(4, INPUT);
  //digitalWrite(4, HIGH);
  //for lazy GRND problem solving
  //pinMode(5, OUTPUT);
  //digitalWrite(5, LOW);
// encoder 1
  //pinMode(A0, OUTPUT); // set Analog_0 to OUTPUT
  //digitalWrite(A0, LOW); // set Analog_0 to LOW
// encoder 2
  //pinMode(A2, OUTPUT); // set Analog_1 to OUTPUT
  //digitalWrite(A2, HIGH); // set Analog_1 to HIGH

//brightness
  //pinMode(A1, INPUT); // set Analog_2 to INPUT


  /***************************************************************************************
    Encoder Setup
  ***************************************************************************************/
  //pinMode(pinA, INPUT_PULLUP); // set pinA as an input, pulled HIGH to the logic voltage (5V or 3.3V for most cases)
  //pinMode(pinB, INPUT_PULLUP); // set pinB as an input, pulled HIGH to the logic voltage (5V or 3.3V for most cases)
  //attachInterrupt(0,PinA,RISING); // set an interrupt on PinA, looking for a rising edge signal and executing the "PinA" Interrupt Service Routine (below)
  //attachInterrupt(1,PinB,RISING); // set an interrupt on PinB, looking for a rising edge signal and executing the "PinB" Interrupt Service Routine (below)
  /***************************************************************************************
    Other Setup
  ***************************************************************************************/
  // Start up the LED strip
  strip.begin();
  // Update the strip, to start they are all 'off'
  strip.show();

  //read last pattern setting from EEPROM 
  lastSavedEncoderPosition = EEPROM.read(128);
  encoderPos = lastSavedEncoderPosition;
}

/***************************************************************************************
  Main Loop
***************************************************************************************/
void loop() {
  
  //Read Potentiometer & Encoder
  //GetBrightness();
    
  //Get encoder button value
  //GetEncoderButtonValue();

  //keep encoder knob within upper && lower limits
  if (encoderPos > upperLimit){
     encoderPos = lowerLimit;
  } else if (encoderPos < lowerLimit) {
     encoderPos = upperLimit;
  }

  //currBrightness knob reads 0-1024,
  //divide by 4 to get a number between 0-255
  currBrightness = currBrightness / 4;  
  
  //testCode();

  //callColorFunction();


  counter++;
  if (counter > 10){
    counter = 0;
  }
  //Adjust Frame Rate
  //delay(100); 
  //if (oldEncPos != encoderPos){
 //   StorePattern();
 // }
  
  //oldEncPos = encoderPos;

  switch (encoderPos){
    case 1:           //Single Color (1-6)
      White();
      break;
    case 2:
      Amber();
      break;
    case 3:
      Red();
      break;
    case 4:
      Green();
      break;
    case 5:
      Blue();
      //Purple();
      break;
    case 6:           
      Teal();
      break;
    case 7:             //Rainbow Colors (7-11)
      RainbowOneYoffset();
      break;
    case 8:
      RainbowTwoYoffset();
      break;
    case 9:
      RainbowThreeXoffset();
      break;
    case 10:
      RainbowFlowSlow();
      break;
    case 11:
      RainbowFlow();
      break;
    case 12:            //Two Colors (12-15)
      AmberWhite();
      break;
    case 13:
      RedGreen();
      break;
    case 14:
      PurpleBlue();
      break;
    case 15:
      BlueWhite();
      break;
    case 16:            //Rainbow Flow Colors (16-20)
      RainbowHsvSlow();
      break;
    case 17:
      RainbowHsvFast();
      break;
    case 18:
      RainbowFlowSlow();
      break;
    case 19:   
      DualColorFlow();
      break;
    case 20:
      RainbowFive();
      break;
    case 21:
      RainbowNoFlow();
      break;
    case 22:
      GreenBlue();
      break;
}

void testCode(){
/*  Serial.print(counter);
  Serial.print(h);
  Serial.print("   Encoder Position:  ");
  Serial.print(encoderPos);
  Serial.print("   Encoder Button:  ");
  Serial.print(encoderButton);
  Serial.print("   Brightness >> ");
  Serial.print(currBrightness);
  Serial.print("   Xoff   ");
  Serial.print(xoffset);
  Serial.print("   Yoff   ");
  Serial.println(yoffset);
}
*/
void callColorFunction(){
    switch (encoderPos){
    case 1:           //Single Color (1-6)
      White();
      break;
    case 2:
      Amber();
      break;
    case 3:
      Red();
      break;
    case 4:
      Green();
      break;
    case 5:
      Blue();
      //Purple();
      break;
    case 6:           
      Teal();
      break;
    case 7:             //Rainbow Colors (7-11)
      RainbowOneYoffset();
      break;
    case 8:
      RainbowTwoYoffset();
      break;
    case 9:
      RainbowThreeXoffset();
      break;
    case 10:
      RainbowFlowSlow();
      break;
    case 11:
      RainbowFlow();
      break;
    case 12:            //Two Colors (12-15)
      AmberWhite();
      break;
    case 13:
      RedGreen();
      break;
    case 14:
      PurpleBlue();
      break;
    case 15:
      BlueWhite();
      break;
    case 16:            //Rainbow Flow Colors (16-20)
      RainbowHsvSlow();
      break;
    case 17:
      RainbowHsvFast();
      break;
    case 18:
      RainbowFlowSlow();
      break;
    case 19:   
      DualColorFlow();
      break;
    case 20:
      RainbowFive();
      break;
    case 21:
      RainbowNoFlow();
      break;
    case 22:
      GreenBlue();
      break;
  }
}

