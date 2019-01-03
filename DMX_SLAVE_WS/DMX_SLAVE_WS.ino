/***************************************************************************************
****************************************************************************************

Project: DMX WS2811 Lights

Description: Controls a WS2811 based strands of LEDs via DMX input

    
Connections:

  VCC = 5v
  
  WS2811:
    GND -> GND
    VCC -> VCC
    DAT -> Digital 6
    
  RS485 IC:
	DE/RE -> GND
	RO -> RX
	VCC -> VCC
	GND -> GND
	
	
	
Change log: 

Version 1.1
  9/1/18 - Matt/Brian - More better functions

Version 1.0
  9/1/18 - Brian - Converted to DMX

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
// #include <Colors.ino>

/***************************************************************************************
  !!!! >>>>> LOOK HERE <<<<<< !!!! ------ S   E   T    U   P
***************************************************************************************/
#define maxPixels 50 // number of lights being used
#define PIN 6
#define DMX_Channel 1
//#define RGBW true
#define INVERTED 1      //Define keyword

/***************************************************************************************
  General Variables
***************************************************************************************/
//const PROGMEM  dataType  variableName[] = {};

int currBrightness = 0;
int currSpeed = 0;
int currProgram = 2;
int currFade = 0;
int currFadeStep = 0;
unsigned long antiSpam = 0;
int tempProgram = 0;
#define maxProgram 32

int fadeDirection = 0; // 1 or 0, positive or negative
int fadeDirection2 = 0; // 1 or 0, positive or negative
int fadeDirectionHTemp = 0; // 1 or 0, positive or negative

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(maxPixels, PIN, NEO_RGB + NEO_KHZ800);

/***********************************************************
  Simplex Noise Variable Declaration
***********************************************************/
//Define simplex noise node for each LED
const int LEDs_in_strip = maxPixels;
const int LEDs_for_simplex = 6;

// Extra fake LED at the end, to avoid fencepost problem.
// It is used by simplex node and interpolation code.
float LED_array_red[LEDs_in_strip+1];
float LED_array_green[LEDs_in_strip+1];
float LED_array_blue[LEDs_in_strip+1];
int node_spacing = LEDs_in_strip / LEDs_for_simplex;

// Math variables
int i, j, k, A[] = {0, 0, 0};
float x1,y1,x2,y2;
float u, v, w, s, h, hTemp;
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
int red3, green3, blue3;
int tempStep = 0;

/***************************************************************************************
  Other Variables
***************************************************************************************/


/***************************************************************************************
  Setup
***************************************************************************************/
void setup()
{
  /***************************************************************************************
    General Setup
  ***************************************************************************************/
	DMXSerial.init(DMXProbe);
	DMXSerial.maxChannel(4);

	//Create a random seed by reading nearby electric noise on the disconnected analog ports
  randomSeed(analogRead(A1) + analogRead(A2) + analogRead(A3) + analogRead(A4) + analogRead (A5));
 	//Randomish x and y offset for simplex noise
 	yoffset = analogRead(A1) + analogRead (A5);
 	xoffset = analogRead(A2) + analogRead(A3);

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
void loop()
{
	//Read DMX values from Serial buffer
  GetDMX();

	// display appropriate pattern
  callColorFunction();

	// read and alter color/currBrightness
	effectFunction();
	
	// make the led strip show color
	strip.show();
}

void callColorFunction()
{
	// select color
  switch (currProgram) {
		case 0:
			GlowingAmberWhite();
			break;
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
			break;
		case 6:           
			Teal();
			break;
		case 7:
			Purple();
			break;
		case 8:
			GlowingAmber();
			break;
		case 9:
			SparkleBlueGreen();
			break;
		case 10:
			RainbowTwoYoffset();
			break;
		case 11:
			RainbowThreeXoffset();
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
			GreenBlue();
			break;
		case 17:
			RainbowHsvFast();
			break;
		case 18:
			RainbowFlow();
			break;
		case 19:   
			DualColorFlow();
			break;
		case 20:
			RainbowFive();
			break;
		case 21:
			RainbowHsvSlow();
			break;
		case 22:
			colorWipe();
			break;
		case 23:
			DualColorFlowGreenFast();
			break;
		case 24:
			DualColorFlowRedFast();
			break;
		case 25:
			TwinkleRainbow();
			break;
		case 26:
			rastaFlag();
			break;
		case 27:
			RainbowHsvTight();
			break;
		case 28:
			PurpleGold();
			break;
		case 29:
			sparkleRasta();
			break;
		case 30:
			triFlag();
			break;
		case 31:
			waterFlag();
			break;
		case 32:
			Amber();
			break;
	}
}

