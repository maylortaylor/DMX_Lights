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
    
}
void Red(){
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(currBrightness,0,0));//Red  
  }
  
}
void Blue(){ 
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0,0,currBrightness));//Blue 
  }
  
}
void White(){
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(currBrightness/2, currBrightness/2,currBrightness/2)); //White  
  }
  
}
void Amber(){
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(currBrightness, currBrightness/3,0)); //Amber 
  }
  
}
void Teal(){
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0,currBrightness/2,currBrightness/2));//Green & Blue
  }
  
}
void Purple(){
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(currBrightness/2,0,currBrightness/2));//Red & Blue
  }
  
}

/***************************************************************************************
  Rainbow Colors 
  1) spaceinc = space between colors, increment to have a greater gap
  2) timeinc = time between each color, increment for faster color transitions
***************************************************************************************/
void RainbowOneYoffset(){
  spaceinc = 0.03;
  timeinc = (0.0001 * currSpeed);
  yoffset += timeinc; 
  //xoffset += timeinc;
  SimplexNoisePatternInterpolated(spaceinc, timeinc, yoffset, xoffset);    
}
void RainbowTwoYoffset(){
  spaceinc = 0.06;
  timeinc = (0.0001 * currSpeed);
  yoffset += timeinc; ; 
  //xoffset += timeinc;
  SimplexNoisePatternInterpolated(spaceinc, timeinc, yoffset, xoffset);    
}
void RainbowThreeXoffset(){
  spaceinc = 0.05;
  timeinc = (0.0001 * currSpeed);
  //yoffset += timeinc; 
  xoffset += timeinc;
  SimplexNoisePatternInterpolated(spaceinc, timeinc, yoffset, xoffset);    
}
void RainbowFourXoffset(){
  spaceinc = 0.03;
  timeinc = (0.0001 * currSpeed);
  //yoffset += timeinc; 
  xoffset += timeinc;
  SimplexNoisePatternInterpolated(spaceinc, timeinc, yoffset, xoffset);    
}
void RainbowFive(){
    h += .0001 * currSpeed; //increment to make faster
    if (h > 1){
      h -= 1;
    }
    if (h < 0){
      h += 1;
    }

    float hTemp = h;

    hTemp = h + .025; //space between colors
    
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
    
}

/***************************************************************************************
  TWO Colors
***************************************************************************************/
void RedGreen(){
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    if ((i % 2) == 0){
      strip.setPixelColor(i, strip.Color(0,currBrightness,0));// Green
    } else {
      strip.setPixelColor(i, strip.Color(currBrightness,currBrightness/2,0));// Red
    }
  } 
    
}
void PurpleBlue(){
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    if ((i % 2) == 0){
      strip.setPixelColor(i, strip.Color(0,0,currBrightness));// Blue
    } else {
      strip.setPixelColor(i, strip.Color(currBrightness/2,0,currBrightness/2));// Purple
    }  
  }
  
}
void BlueWhite(){
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    if ((i % 2) == 0){
      strip.setPixelColor(i, strip.Color(currBrightness/2,currBrightness/2,currBrightness/2));// White
    } else {
      strip.setPixelColor(i, strip.Color(0,0,currBrightness));// Blue
    }
  }
    
}
void AmberWhite(){
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    if ((i % 2) == 0){
      strip.setPixelColor(i, strip.Color(currBrightness/2,currBrightness/2,currBrightness/2));// White
    } else {
      strip.setPixelColor(i, strip.Color(currBrightness, currBrightness/3,0)); //Amber
    } 
  }
   
}
void GreenBlue(){
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    if ((i % 2) == 0){
      strip.setPixelColor(i, strip.Color(0,currBrightness,0));// Green
    } else {
      strip.setPixelColor(i, strip.Color(0,0,currBrightness)); //Blue
    } 
  }
   
}

/***************************************************************************************
  Rainbow Flow Colors
***************************************************************************************/
void RainbowFlow(){
	h = h + (currSpeed * .0001);
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
	
}
void DualColorFlow(){
    h = h + (currSpeed * .0001);//increment to make faster
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
     
}
void RainbowHsvSlow(){
  h = h + (currSpeed * .0001); //increment to make faster
  
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
  
}
void RainbowHsvFast(){
  h = h + (currSpeed * .0001); //increment to make faster
  
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
   
}

void RainbowHsvTight(){
  h = h + ((currSpeed / 3) * .001); //increment to make faster
  
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
    hTemp += .1; //decrease to space out the colors

    if (hTemp > 1){
      hTemp -= 1;
    }
    if (hTemp < 0){
      hTemp += 1;
    }
  }

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
    //Convert to 24 bit output for WS2811
    strip.setPixelColor(i, strip.Color(r, g , b));
  }
        
  if (yoffset >= 16000)
  {
    yoffset = -26000;
  }

  if (yoffset <= -26000)
  {
    yoffset = 16000;
  }

  if (xoffset >= 16000)
  {
    xoffset = -16000;
  }

  if (xoffset <= -16000)
  {
    xoffset = 16000;
  }

}

//NEW SHIT

void GlowingAmber(){
  hTemp = random(maxPixels);

  if (currBrightness > 0)
  {
    strip.setPixelColor(hTemp, strip.Color(currBrightness, currBrightness / 3, 0));
  }

  for (int i = 0; i < maxPixels; i++)
  {
      red = (strip.getPixelColor(i) >> 16 & 0xff);
      green = ((strip.getPixelColor(i) >> 8) & 0xff);
      blue = (strip.getPixelColor(i) & 0xff);

      if (red >= 1)
      {
          red--;
      }
      if (blue >= 1)
      {
          blue--;
      }

      if (green >= 1)
      {
          green--;
      }

      strip.setPixelColor(i, strip.Color(red, green, blue));
  }

}

void sparkleRasta(){
    //find lucky pixel
    hTemp = random(maxPixels);
    
    //determine which color to turn it
    tempStep += 1;
    if (tempStep > 2)
    {
      tempStep = 0;
    }

    if (currBrightness > 0)
    {
      switch(tempStep)
      {
        case 0:
          strip.setPixelColor(hTemp, strip.Color(currBrightness, 0, 0));
          break;
        case 1:
          strip.setPixelColor(hTemp, strip.Color(0, currBrightness, 0));
          break;
        case 2:
          strip.setPixelColor(hTemp, strip.Color(currBrightness, currBrightness / 1.5, 0));
      }
    }
    
    for (int i = 0; i < maxPixels; i++)
    {
        red = (strip.getPixelColor(i) >> 16 & 0xff);
        green = ((strip.getPixelColor(i) >> 8) & 0xff);
        blue = (strip.getPixelColor(i) & 0xff);

        if (red >= 1)
        {
            red--;
        }
        if (blue >= 1)
        {
            blue--;
        }

        if (green >= 1)
        {
            green--;
        }

        strip.setPixelColor(i, strip.Color(red, green, blue));
    }

}

void GlowingAmberWhite(){
    //find lucky pixel
    hTemp = random(maxPixels);
    
    //determine which color to turn it
    tempStep += 1;
    if (tempStep > 1)
    {
      tempStep = 0;
    }

    if (currBrightness > 0)
    {
      switch(tempStep)
      {
        case 0:
          strip.setPixelColor(hTemp, strip.Color(currBrightness, currBrightness / 3, 0));
          break;
        case 1:
          strip.setPixelColor(hTemp, strip.Color(currBrightness / 2, currBrightness / 2, currBrightness / 2));
          break;
      }
    }
    
    for (int i = 0; i < maxPixels; i++)
    {
        red = (strip.getPixelColor(i) >> 16 & 0xff);
        green = ((strip.getPixelColor(i) >> 8) & 0xff);
        blue = (strip.getPixelColor(i) & 0xff);

        if (red >= 1)
        {
            red--;
        }
        if (blue >= 1)
        {
            blue--;
        }

        if (green >= 1)
        {
            green--;
        }

        strip.setPixelColor(i, strip.Color(red, green, blue));
    }

}

void PurpleGold(){
    //find lucky pixel
    hTemp = random(maxPixels);
    
    //determine which color to turn it
    tempStep += 1;
    if (tempStep > 1)
    {
      tempStep = 0;
    }

    if (currBrightness > 0)
    {
      if (tempStep == 0)
      {
        strip.setPixelColor(hTemp, strip.Color(currBrightness / 1.5, 0, currBrightness / 2));
      }else{
        strip.setPixelColor(hTemp, strip.Color(currBrightness, currBrightness / 3, 0));
      }
    }
    
    for (int i = 0; i < maxPixels; i++)
    {
        red = (strip.getPixelColor(i) >> 16 & 0xff);
        green = ((strip.getPixelColor(i) >> 8) & 0xff);
        blue = (strip.getPixelColor(i) & 0xff);

        if (red >= 1)
        {
            red--;
        }
        if (blue >= 1)
        {
            blue--;
        }

        if (green >= 1)
        {
            green--;
        }

        strip.setPixelColor(i, strip.Color(red, green, blue));
    }

}

void SparkleBlueGreen(){
    //find lucky pixel
    hTemp = random(maxPixels);
    
    //determine which color to turn it
    tempStep += 1;
    if (tempStep > 1)
    {
      tempStep = 0;
    }

    red = (strip.getPixelColor(hTemp) >> 16 & 0xff);
    green = ((strip.getPixelColor(hTemp) >> 8) & 0xff);
    blue = (strip.getPixelColor(hTemp) & 0xff);

    if (currBrightness > 0)
    {
      if (tempStep == 0)
      {
        strip.setPixelColor(hTemp, strip.Color(red, currBrightness, blue));
      }else{
        strip.setPixelColor(hTemp, strip.Color(red, green, currBrightness));
      }
    }
    
    for (int i = 0; i < maxPixels; i++)
    {
        red = (strip.getPixelColor(i) >> 16 & 0xff);
        green = ((strip.getPixelColor(i) >> 8) & 0xff);
        blue = (strip.getPixelColor(i) & 0xff);

        if (red >= 1)
        {
            red--;
        }
        if (blue >= 1)
        {
            blue--;
        }

        if (green >= 1)
        {
            green--;
        }

        strip.setPixelColor(i, strip.Color(red, green, blue));
    }

}

void colorWipe(){
  tempStep += 1;
  if (tempStep > maxPixels)
  {
    tempStep = 0;
    hTemp = h;
    h = random(1000) / 1000.0;
  }

  hsv2rgb(float(h), 1, (float(currBrightness)/255.0), red, green, blue);

  for(uint16_t i=0; i<tempStep; i++) {
    strip.setPixelColor(i, strip.Color(red,green,blue));
  }
  
  hsv2rgb(float(hTemp), 1, (float(currBrightness)/255.0), red, green, blue);
  
  for(uint16_t i=tempStep; i<maxPixels; i++) {
    strip.setPixelColor(i, strip.Color(red,green,blue));
  }

  delay((100 - currSpeed) * 6);

}

void DualColorFlowGreenFast()
{
    float hHigh = .7;
    float hLow = .3;
    float hHigh2 = .85;
    float hLow2 = .6;

    if (h > hHigh)
    {
        h = hHigh;
        fadeDirection = 0;
    }
    if (h < hLow)
    {
        h = hLow;
        fadeDirection = 1;
    }

    if (fadeDirection == 1)
    {
        h += .0001 * currSpeed; // increment to make faster
    }
    if (fadeDirection == 0)
    {
        h -= .0001 * currSpeed; // decrement to make faster
    }

    float hTemp = h;

    hTemp = h - .1; // space between colors

    hsv2rgb(float(h), 1, (float(currBrightness) / 255.0), red, green, blue);

    hsv2rgb(float(hTemp), 1, (float(currBrightness) / 255.0), red2, green2, blue2);

    for (uint16_t i = 0; i < maxPixels; i = i + 2)
    {

        strip.setPixelColor(i, strip.Color(red, green, blue));
        strip.setPixelColor(i + 1, strip.Color(red2, green2, blue2));
    }
    strip.show();
}

void DualColorFlowRedFast()
{
    float hHigh = .15;
    float hLow = .05;

    if (h > hHigh)
    {
        h = hHigh;
        fadeDirection = 0;
    }
    if (h < hLow)
    {
        h = hLow;
        fadeDirection = 1;
    }

    if (fadeDirection == 1)
    {
        h += .00005 * currSpeed; // increment to make faster
    }
    if (fadeDirection == 0)
    {
        h -= .00005 * currSpeed; // decrement to make faster
    }

    float hTemp = h;

    hTemp = h - .1; // space between colors

    if (h > 1)
    {
        h -= 1;
    }
    if (h < 0)
    {
        h += 1;
    }

    if (hTemp > 1)
    {
        hTemp -= 1;
    }
    if (hTemp < 0)
    {
        hTemp += 1;
    }
    hsv2rgb(float(h), 1, (float(currBrightness) / 255.0), red, green, blue);

    hsv2rgb(float(hTemp), 1, (float(currBrightness) / 255.0), red2, green2, blue2);

    for (uint16_t i = 0; i < maxPixels; i = i + 2)
    {

        strip.setPixelColor(i, strip.Color(red, green, blue));
        strip.setPixelColor(i + 1, strip.Color(red2, green2, blue2));
    }
}

void TwinkleRainbow()
{
    hTemp = random(maxPixels);
    h += .0001 * currSpeed;
    if (h > 1)
    {
        h = 0;
    }
    if (h < 0)
    {
        h = 1;
    }
    hsv2rgb(float(h), 1, (float(currBrightness) / 255.0), red, green, blue);

    strip.setPixelColor(hTemp, strip.Color(red, green, blue));


    for (int i = 0; i < maxPixels; i++)
    {
        red = (strip.getPixelColor(i) >> 16 & 0xff);
        green = ((strip.getPixelColor(i) >> 8) & 0xff);
        blue = (strip.getPixelColor(i) & 0xff);

        if (red >= 1)
        {
            red--;
        }
        if (blue >= 1)
        {
            blue--;
        }
        if (green >= 1)
        {
            green--;
        }

        strip.setPixelColor(i, strip.Color(red, green, blue));
    }
}


void rastaFlag()
{
  for(uint16_t i=0; i<strip.numPixels(); i+=9) {
    strip.setPixelColor(i, strip.Color(currBrightness,0,0));
    strip.setPixelColor(i+1, strip.Color(currBrightness,0,0));
    strip.setPixelColor(i+2, strip.Color(currBrightness,0,0));
    strip.setPixelColor(i+3, strip.Color(currBrightness,currBrightness/1.5,0));
    strip.setPixelColor(i+4, strip.Color(currBrightness,currBrightness/1.5,0));
    strip.setPixelColor(i+5, strip.Color(currBrightness,currBrightness/1.5,0));
    strip.setPixelColor(i+6, strip.Color(0,currBrightness,0));
    strip.setPixelColor(i+7, strip.Color(0,currBrightness,0));
    strip.setPixelColor(i+8, strip.Color(0,currBrightness,0));
  }
}

void triFlag()
{
  h = h + (currSpeed * .00001); //increment to make faster
  
  if (h > 1){
    h -= 1;
  }
  
  if (h < 0){
    h += 1;
  }

  float hTemp = h;
  
  hsv2rgb(float(hTemp), 1, (float(currBrightness)/255.0), red, green, blue);

  //slowly increment 'h' by small increments to make color flow
  hTemp += .166; //decrease to space out the colors
  if (hTemp > 1){
    hTemp -= 1;
  }
  if (hTemp < 0){
    hTemp += 1;
  }

  hsv2rgb(float(hTemp), 1, (float(currBrightness)/255.0), red2, green2, blue2);

  hTemp += .166; 
  if (hTemp > 1){
    hTemp -= 1;
  }
  if (hTemp < 0){
    hTemp += 1;
  }

  hsv2rgb(float(hTemp), 1, (float(currBrightness)/255.0), red3, green3, blue3);

  for(uint16_t i=0; i<strip.numPixels(); i+=9) {
    strip.setPixelColor(i, strip.Color(red,green,blue));
    strip.setPixelColor(i+1, strip.Color(red,green,blue));
    strip.setPixelColor(i+2, strip.Color(red,green,blue));
    strip.setPixelColor(i+3, strip.Color(red3,green3,blue3));
    strip.setPixelColor(i+4, strip.Color(red3,green3,blue3));
    strip.setPixelColor(i+5, strip.Color(red3,green3,blue3));
    strip.setPixelColor(i+6, strip.Color(red2,green2,blue2));
    strip.setPixelColor(i+7, strip.Color(red2,green2,blue2));
    strip.setPixelColor(i+8, strip.Color(red2,green2,blue2));
  }
}

void waterFlag()
{
  for(uint16_t i=0; i<strip.numPixels(); i+=9) {
    strip.setPixelColor(i, strip.Color(0,0,currBrightness));
    strip.setPixelColor(i+1, strip.Color(0,0,currBrightness));
    strip.setPixelColor(i+2, strip.Color(0,0,currBrightness));
    strip.setPixelColor(i+3, strip.Color(0,currBrightness,0));
    strip.setPixelColor(i+4, strip.Color(0,currBrightness,0));
    strip.setPixelColor(i+5, strip.Color(0,currBrightness,0));
    strip.setPixelColor(i+6, strip.Color(currBrightness,0,currBrightness / 2));
    strip.setPixelColor(i+7, strip.Color(currBrightness,0,currBrightness / 2));
    strip.setPixelColor(i+8, strip.Color(currBrightness,0,currBrightness / 2));
  }
}