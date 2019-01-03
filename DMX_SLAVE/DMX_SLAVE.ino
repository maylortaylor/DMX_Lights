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
int currProgram = 2;

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PWM_MaxPixels, PIN, NEO_RGB + NEO_KHZ800);

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


/***************************************************************************************
  Setup
***************************************************************************************/
void setup() {
  /***************************************************************************************
    General Setup
  ***************************************************************************************/
 DMXSerial.init(DMXProbe);
 DMXSerial.maxChannel(3);
 /***************************************************************************************
    Other Setup
  ***************************************************************************************/
  // Start up the LED strip
  strip.begin();
  // Update the strip, to start they are all 'off'
  strip.show();
}

/***************************************************************************************
  Main Loop
***************************************************************************************/
void loop() {
  
  GetDMX();
   

  callColorFunction();

}

void callColorFunction(){
    switch (currProgram){
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

