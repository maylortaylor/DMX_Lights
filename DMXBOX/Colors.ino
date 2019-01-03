/***************************************************************************************
  COLOR Functions strip.Color(GREEN, RED, BLUE);
***************************************************************************************/

/***************************************************************************************
  Single Colors
***************************************************************************************/
void Green(){
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0,currBrightness,0));//Green
  }
  strip.show();  
}
void Red(){
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(currBrightness,0,0));//Red  
  }
  strip.show();
}
void Blue(){ 
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0,0,currBrightness));//Blue 
  }
  strip.show();
}
void White(){
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(currBrightness, currBrightness,currBrightness)); //White  
  }
  strip.show();
}
void Amber(){
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(currBrightness, currBrightness/3,0)); //Amber 
  }
  strip.show();
}
void Teal(){
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0,currBrightness,currBrightness));//Green & Blue
  }
  strip.show();
}
void Purple(){
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(currBrightness,0,currBrightness));//Red & Blue
  }
  strip.show();
}

/***************************************************************************************
  Rainbow Colors 
  1) spaceinc = space between colors, increment to have a greater gap
  2) timeinc = time between each color, increment for faster color transitions
***************************************************************************************/
void RainbowOneYoffset(){
  spaceinc = 0.03;
  timeinc = 0.0009;
  yoffset += timeinc; 
  //xoffset += timeinc;
  SimplexNoisePatternInterpolated(spaceinc, timeinc, yoffset, xoffset);    
}
void RainbowTwoYoffset(){
  spaceinc = 0.05;
  timeinc = 0.0003;
  yoffset += timeinc; ; 
  //xoffset += timeinc;
  SimplexNoisePatternInterpolated(spaceinc, timeinc, yoffset, xoffset);    
}
void RainbowThreeXoffset(){
  spaceinc = 0.05;
  timeinc = 0.0005;
  //yoffset += timeinc; 
  xoffset += timeinc;
  SimplexNoisePatternInterpolated(spaceinc, timeinc, yoffset, xoffset);    
}
void RainbowFourXoffset(){
  spaceinc = 0.03;
  timeinc = 0.0009;
  //yoffset += timeinc; 
  xoffset += timeinc;
  SimplexNoisePatternInterpolated(spaceinc, timeinc, yoffset, xoffset);    
}
void RainbowFive(){
    h += .0004; //increment to make faster
    if (h > 1){
      h -= 1;
    }
    if (h < 0){
      h += 1;
    }

    float hTemp = h;

    hTemp = h + .1; //space between colors
    
    if (hTemp > 1){
      hTemp -= 1;
    }
    if (hTemp < 0){
      hTemp += 1;
    }

    hsv2rgb(float(h), 1, (float(currBrightness)/255.0), red, green, blue);

    hsv2rgb(float(hTemp), 1, (float(currBrightness)/255.0), red2, green2, blue2);
  
    for(uint16_t i=0; i<strip.numPixels(); i=i+2) {
      strip.setPixelColor(i, strip.Color(red,green,blue));
      strip.setPixelColor(i+1, strip.Color(red2,green2,blue2));    
    }
    strip.show();
}
/***************************************************************************************
  TWO Colors
***************************************************************************************/
void RedGreen(){
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    if ((i % 2) == 0){
      strip.setPixelColor(i, strip.Color(0,currBrightness,0));// Green
    } else {
      strip.setPixelColor(i, strip.Color(currBrightness,0,0));// Red
    }
  } 
  strip.show();  
}
void PurpleBlue(){
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    if ((i % 2) == 0){
      strip.setPixelColor(i, strip.Color(0,0,currBrightness));// Blue
    } else {
      strip.setPixelColor(i, strip.Color(currBrightness,0,currBrightness));// Purple
    }  
  }
  strip.show();
}
void BlueWhite(){
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    if ((i % 2) == 0){
      strip.setPixelColor(i, strip.Color(currBrightness,currBrightness,currBrightness));// White
    } else {
      strip.setPixelColor(i, strip.Color(0,0,currBrightness));// Blue
    }
  }
  strip.show();  
}
void AmberWhite(){
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    if ((i % 2) == 0){
      strip.setPixelColor(i, strip.Color(currBrightness/2,currBrightness/2,currBrightness/2));// White
    } else {
      strip.setPixelColor(i, strip.Color(currBrightness, currBrightness/3,0)); //Amber
    } 
  }
  strip.show(); 
}
void GreenBlue(){
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    if ((i % 2) == 0){
      strip.setPixelColor(i, strip.Color(currBrightness,currBrightness/3,currBrightness/2));// Green
    } else {
      strip.setPixelColor(i, strip.Color(currBrightness,0,currBrightness)); //Blue
    } 
  }
  strip.show(); 
}
/***************************************************************************************
  Rainbow Flow Colors
***************************************************************************************/
void RainbowFlow(){
  h += .0005; //increment to make faster
  if (h > 1){
    h -= 1;
  }
  if (h < 0){
    h += 1;
  }

  float hTemp = h;
  
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    hsv2rgb(float(hTemp), 1, (float(currBrightness)/255.0), red, green, blue);
    strip.setPixelColor(i, strip.Color(red,green,blue));

    //slowly increment 'h' by small increments to make color flow
    hTemp += .05; //decrease to space out the colors

    if (hTemp > 1){
      hTemp -= 1;
    }
    if (hTemp < 0){
      hTemp += 1;
    }
  }
  strip.show();
}
void RainbowFlowSlow(){
  h += .0001; //increment to make faster
  if (h > 1){
    h -= 1;
  }
  if (h < 0){
    h += 1;
  }

  float hTemp = h;
  
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    hsv2rgb(float(hTemp), 1, (float(currBrightness)/255.0), red, green, blue);
    strip.setPixelColor(i, strip.Color(red,green,blue));

    //slowly increment 'h' by small increments to make color flow
    hTemp += .0045; //decrease to space out the colors

    if (hTemp > 1){
      hTemp -= 1;
    }
    if (hTemp < 0){
      hTemp += 1;
    }  
  } 
  strip.show();
}

void RainbowNoFlow(){
  h = 0; 

  float hTemp = h;
  
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    hsv2rgb(float(hTemp), 1, (float(currBrightness)/255.0), red, green, blue);
    strip.setPixelColor(i, strip.Color(red,green,blue));

    //slowly increment 'h' by small increments to make color flow
    hTemp += .042; //decrease to space out the colors

    if (hTemp > 1){
      hTemp -= 1;
    }
    if (hTemp < 0){
      hTemp += 1;
    }  
  } 
  strip.show();
}

void DualColorFlow(){
    h += .0003; //increment to make faster
    if (h > 1){
      h -= 1;
    }
    if (h < 0){
      h += 1;
    }

    float hTemp = h;

    hTemp = h + .5; //space between colors
    
    if (hTemp > 1){
      hTemp -= 1;
    }
    if (hTemp < 0){
      hTemp += 1;
    }

    hsv2rgb(float(h), 1, (float(currBrightness)/255.0), red, green, blue);

    hsv2rgb(float(hTemp), 1, (float(currBrightness)/255.0), red2, green2, blue2);
  
    for(uint16_t i=0; i<strip.numPixels(); i=i+2) {
      
      strip.setPixelColor(i, strip.Color(red,green,blue));
      strip.setPixelColor(i+1, strip.Color(red2,green2,blue2));     
    }
    strip.show(); 
}
void RainbowHsvSlow(){
  h += .0002; //increment to make faster
  
  if (h > 1){
    h -= 1;
  }
  
  if (h < 0){
    h += 1;
  }
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    hsv2rgb(float(h), 1, (float(currBrightness)/255.0), red, green, blue);
    strip.setPixelColor(i, strip.Color(red,green,blue));// Red 
  }
  strip.show();
}
void RainbowHsvFast(){
  h += .0007; //increment to make faster
  
  if (h > 1){
    h -= 1;
  }
  
  if (h < 0){
    h += 1;
  }
  hsv2rgb(float(h), 1, (float(currBrightness)/255.0), red, green, blue);
  
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(red,green,blue));// Red 
  }
  strip.show(); 
}


/***********************************************************
  Simplex Noise Pattern (Rainbow Cloud Generator)
***********************************************************/
void SimplexNoisePatternInterpolated(float spaceinc, float timeinc, float yoffset, float xoffset) {

  // Simplex noise for whole strip of LEDs.
  // (Well, it's simplex noise for set number of LEDs and cubic interpolation between those nodes.)
  
    // Calculate simplex noise for LEDs that are nodes:
    // Store raw values from simplex function (-0.347 to 0.347)
    //float xoffset = 0.0;
  float xoffset_holder =  xoffset;
  
    for (int i=0; i<=LEDs_in_strip; i=i+node_spacing) {
      xoffset += spaceinc;
      LED_array_red[i] = SimplexNoise(xoffset,yoffset,0);
      LED_array_green[i] = SimplexNoise(xoffset,yoffset,1);
      LED_array_blue[i] = SimplexNoise(xoffset,yoffset,2);
    }

  xoffset = xoffset_holder;
  
    // Interpolate values for LEDs between nodes
    for (int i=0; i<LEDs_in_strip; i++) {
      int position_between_nodes = i % node_spacing;
      int last_node, next_node;

      // If at node, skip
      if ( position_between_nodes == 0 ) {
        // At node for simplex noise, do nothing but update which nodes we are between
        last_node = i;
        next_node = last_node + node_spacing;
      }
      // Else between two nodes, so identify those nodes
      else {
        // And interpolate between the values at those nodes for red, green, and blue
        float t = float(position_between_nodes) / float(node_spacing);
        float t_squaredx3 = 3*t*t;
        float t_cubedx2 = 2*t*t*t;
        LED_array_red[i] = LED_array_red[last_node] * ( t_cubedx2 - t_squaredx3 + 1.0 ) + LED_array_red[next_node] * ( -t_cubedx2 + t_squaredx3 );
        LED_array_green[i] = LED_array_green[last_node] * ( t_cubedx2 - t_squaredx3 + 1.0 ) + LED_array_green[next_node] * ( -t_cubedx2 + t_squaredx3 );
        LED_array_blue[i] = LED_array_blue[last_node] * ( t_cubedx2 - t_squaredx3 + 1.0 ) + LED_array_blue[next_node] * ( -t_cubedx2 + t_squaredx3 );
      }
    }
  
    // Convert values from raw noise to scaled r,g,b and feed to strip
    for (int i=0; i<LEDs_in_strip; i++) {
    int r = currBrightness*((LED_array_red[i]*734 + 16)/255);
    int g = currBrightness*((LED_array_green[i]*734 + 16)/255);
    int b = currBrightness*((LED_array_blue[i]*734 + 16)/255);
      
    if ( r>255 ) { r=255; }
    else if ( r<0 ) { r=0; }  // Adds no time at all. Conclusion: constrain() sucks.
  
    if ( g>255 ) { g=255; }
    else if ( g<0 ) { g=0; }
  
    if ( b>255 ) { b=255; }
    else if ( b<0 ) { b=0; }  
    
    //Convert to 24 bit output for WS2801
    strip.setPixelColor(i, strip.Color(r, g , b));
    }

    // Update strip  
    strip.show();
}


