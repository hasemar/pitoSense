float senseStrm()
{
  float avgRead;  // average sensor reading
  const int rho = 1000; // kg/m3   density of water
  const int maxRange =  103421; // pascals  (max sensor range)
  const int zero = 530;     // zero analog
  const int span = 1023;  // analog span
  int scaledPress = 0;  // pascals
  float velocity = 0.0;     // mm/s velocity
  const int num = 30; // number of samples to average over
  int samples[num]; // array for averaging sensor reading
  pitotVal = 0; // start from zero
  
  for(int i = 0; i<num; i++) //gather 30 samples and sum them up
  {
    samples[i] = analogRead(SnsrPin);
    delay(5);
    pitotVal += samples[i];
  }
  
  avgRead = pitotVal/num; // take average
  scaledPress = map(avgRead, zero, span, 0, maxRange);   // scale average analog value to pascals
  Serial.println(rho);
  Serial.println(velocity);
  Serial.println(scaledPress);
  velocity = sqrt(2*-scaledPress/rho); // apply velocity equation (outputs m/s)
  pitotVal = analogRead(SnsrPin);  // for logging
  Serial.println(velocity);
  
  return velocity;  // should return the velocity of the water based on the equation v=sqrt(2*dp/rho)
}
