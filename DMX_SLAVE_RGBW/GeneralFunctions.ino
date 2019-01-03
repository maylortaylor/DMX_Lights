/***************************************************************************************
  Brightness
***************************************************************************************/
void GetDMX(){
  
   if (DMXSerial.receive())
   {
		//Read DMX channels to variables
		Red = DMXSerial.read(1);
		Green = DMXSerial.read(2);
		Blue = DMXSerial.read(3);
		White = DMXSerial.read(4);
		
		//Set PWM Pins to new Duty Cycle
		analogWrite(3, Red);	//R
		analogWrite(5, Green);	//G
		analogWrite(6, Blue);	//B
		analogWrite(9, White);	//W
   }

}


/***********************************************************
  hsv2rgb
  Function: Calculate RGB values for colors represented
    in Hue, Saturation, and Value (brightness).
***********************************************************/
void hsv2rgb(float H, float S, float V, int& R, int& G, int& B)
{
  int var_i;
  float var_1, var_2, var_3, var_h, var_r, var_g, var_b;
  if ( S == 0 )                       //HSV values = 0 ÷ 1
  {
    R = V * 255;
    G = V * 255;
    B = V * 255;
  }
  else
  {
    var_h = H * 6;
    if ( var_h == 6 ) var_h = 0;      //H must be < 1
    var_i = int( var_h ) ;            //Or ... var_i = floor( var_h )
    var_1 = V * ( 1 - S );
    var_2 = V * ( 1 - S * ( var_h - var_i ) );
    var_3 = V * ( 1 - S * ( 1 - ( var_h - var_i ) ) );

    if ( var_i == 0 ) {
    var_r = V     ;
    var_g = var_3 ;
    var_b = var_1 ;
    }
    else if ( var_i == 1 ) {
    var_r = var_2 ;
    var_g = V     ;
    var_b = var_1 ;
    }
    else if ( var_i == 2 ) {
    var_r = var_1 ;
    var_g = V     ;
    var_b = var_3 ;
    }
    else if ( var_i == 3 ) {
    var_r = var_1 ;
    var_g = var_2 ;
    var_b = V     ;
    }
    else if ( var_i == 4 ) {
    var_r = var_3 ;
    var_g = var_1 ;
    var_b = V     ;
    }
    else                   {
    var_r = V     ;
    var_g = var_1 ;
    var_b = var_2 ;
    }

    //RGB results = 0 ÷ 255 (Production)
    R = (var_r) * 255;
    G = (var_g) * 255;
    B = (var_b) * 255;
  }
}


