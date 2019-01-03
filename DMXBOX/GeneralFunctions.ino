void StorePattern(){
  if (lastSavedEncoderPosition >= lowerLimit && lastSavedEncoderPosition <= upperLimit){
    // if lastSavedEncoderPosition is a valid pattern
    // && lastSavedEncoderPosition is not the same as current encoder
    if (lastSavedEncoderPosition != encoderPos){
      EEPROM.write(128, encoderPos);
    } 
  }
}
/***************************************************************************************
  Brightness
***************************************************************************************/
void GetBrightness(){
  
  brightnessRead = analogRead(A1); // read analog pin 2
  
  //Catch-All for Off and Noise Filter
  NoiseFilter(brightnessRead);
}

void NoiseFilter(int brightness){
    //Catch-All for Off and Noise Filter
  brightnessRead -= 10;

  if (brightnessRead < 12){
    brightnessRead = 0;
  }
  if (brightnessRead <= 12){
    currBrightness = 0;
  } else if (abs(brightnessRead - currBrightness) > 12){
    currBrightness = brightnessRead;
  }
}

/***************************************************************************************
  Encoder
***************************************************************************************/
void GetEncoderButtonValue(){
  encoderButton = digitalRead(4); // read digital pin 4
  
  // if encoder button is pressed, set encoder position = 1 (1st pattern)
  if (encoderButton == 0){
    encoderPos = 2;
  }
}

void PinA(){
  cli(); //stop interrupts happening before we read pin values
  reading = PIND & 0xC; // read all eight pin values then strip away all but pinA and pinB's values
  if(reading == B00001100 && aFlag) { //check that we have both pins at detent (HIGH) and that we are expecting detent on this pin's rising edge
    encoderPos --; //decrement the encoder's position count
    bFlag = 0; //reset flags for the next turn
    aFlag = 0; //reset flags for the next turn
    EEPROM.write(128, encoderPos);
  }
  else if (reading == B00000100) bFlag = 1; //signal that we're expecting pinB to signal the transition to detent from free rotation
  sei(); //restart interrupts
}

void PinB(){

  cli(); //stop interrupts happening before we read pin values
  reading = PIND & 0xC; //read all eight pin values then strip away all but pinA and pinB's values
  if (reading == B00001100 && bFlag) { //check that we have both pins at detent (HIGH) and that we are expecting detent on this pin's rising edge
    encoderPos ++; //increment the encoder's position count
    bFlag = 0; //reset flags for the next turn
    aFlag = 0; //reset flags for the next turn
    EEPROM.write(128, encoderPos);
  }
  else if (reading == B00001000) aFlag = 1; //signal that we're expecting pinA to signal the transition to detent from free rotation
  sei(); //restart interrupts
}

int fastfloor(float n) {
  return n > 0 ? (int) n : (int) n - 1;
}
float k_fn(int a) {
  s = (A[0] + A[1] + A[2]) * onesixth;
  float x = u - A[0] + s;
  float y = v - A[1] + s;
  float z = w - A[2] + s;
  float t = 0.6f - x * x - y * y - z * z;
  int h = shuffle(i + A[0], j + A[1], k + A[2]);
  A[a]++;
  if (t < 0) return 0;
  int b5 = h >> 5 & 1;
  int b4 = h >> 4 & 1;
  int b3 = h >> 3 & 1;
  int b2 = h >> 2 & 1;
  int b = h & 3;
  float p = b == 1 ? x : b == 2 ? y : z;
  float q = b == 1 ? y : b == 2 ? z : x;
  float r = b == 1 ? z : b == 2 ? x : y;
  p = b5 == b3 ? -p : p;
  q = b5 == b4 ? -q: q;
  r = b5 != (b4^b3) ? -r : r;
  t *= t;
  return 8 * t * t * (p + (b == 0 ? q + r : b2 == 0 ? q : r));
}
int shuffle(int i, int j, int k) {
  return b(i, j, k, 0) + b(j, k, i, 1) + b(k, i, j, 2) + b(i, j, k, 3) + b(j, k, i, 4) + b(k, i, j, 5) + b(i, j, k, 6) + b(j, k, i, 7);
}
int b(int i, int j, int k, int B) {
  return T[b(i, B) << 2 | b(j, B) << 1 | b(k, B)];
}
int b(int N, int B) {
  return N >> B & 1;
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


/*****************************************************************************/
// Simplex noise code:
// From an original algorythm by Ken Perlin.
// Returns a value in the range of about [-0.347 .. 0.347]
float SimplexNoise(float x, float y, float z) {
  // Skew input space to relative coordinate in simplex cell
  s = (x + y + z) * onethird;
  i = fastfloor(x+s);
  j = fastfloor(y+s);
  k = fastfloor(z+s);
   
  // Unskew cell origin back to (x, y , z) space
  s = (i + j + k) * onesixth;
  u = x - i + s;
  v = y - j + s;
  w = z - k + s;;
   
  A[0] = A[1] = A[2] = 0;
   
  // For 3D case, the simplex shape is a slightly irregular tetrahedron.
  // Determine which simplex we're in
  int hi = u >= w ? u >= v ? 0 : 1 : v >= w ? 1 : 2;
  int lo = u < w ? u < v ? 0 : 1 : v < w ? 1 : 2;
   
  return k_fn(hi) + k_fn(3 - hi - lo) + k_fn(lo) + k_fn(0);
}


