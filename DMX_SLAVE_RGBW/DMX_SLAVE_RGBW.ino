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
    
  DMX:
	DE/RE -> GND
	RO -> RX
	VCC -> VCC
	GND -> GND
  
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
#include <DMXSerial.h>

/***************************************************************************************
  General Variables
***************************************************************************************/

int Red = 0;
int Green = 0;
int Blue = 0;
int White = 0;

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
	DMXSerial.maxChannel(4);
 
	/***************************************************************************************
    Other Setup
	***************************************************************************************/
	
	pinMode(3, OUTPUT);
	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);
	pinMode(9, OUTPUT);
	
	analogWrite(3, 0); //R
	analogWrite(5, 0); //G
	analogWrite(6, 0); //B
	analogWrite(9, 0); //W
  
  
}

/***************************************************************************************
  Main Loop
***************************************************************************************/
void loop() {
  
  GetDMX();

}
