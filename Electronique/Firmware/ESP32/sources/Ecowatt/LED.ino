void initLED()
{

  FastLED.addLeds<NEOPIXEL, PIN_PIXEL>(leds, NUMPIXELS);
  FastLED.setBrightness(50);
  
  /* pixels.begin();
    pixels.clear();

    for (int i = 0; i < 24; i++) {
     pixels.setPixelColor(i, 0, 0, 0);
    }

    pixels.show();*/

  FastLED.show();
}

void displayPrevisionDay(int toDisplay[24])
{

  //pixels.clear();

  for (int i = 0; i < 24; i++) {
    //  pixels.setPixelColor(i, colorsMap[toDisplay[i]][0], colorsMap[toDisplay[i]][1], colorsMap[toDisplay[i]][2]);
   leds[i] = CRGB ( colorsMap[toDisplay[i]][0], colorsMap[toDisplay[i]][1], colorsMap[toDisplay[i]][2]);
    Serial.print(toDisplay[i]);
    Serial.print(" ");
    /*Serial.print("LED #");
      Serial.print(i);
      Serial.print(" hvalue = ");
      Serial.print(toDisplay[i]);
      Serial.print(" R");
      Serial.print(colorsMap[toDisplay[i]][0]);
      Serial.print("G");
      Serial.print(colorsMap[toDisplay[i]][1]);
      Serial.print("B");
      Serial.println(colorsMap[toDisplay[i]][2]);*/
  }
  Serial.println("");
  // pixels.show();
  FastLED.show();

}

void waitLedAnimation()
{
  /* static unsigned long startTime = millis();
    static int j = 0;
    if (millis() > (startTime + 10)) {
     startTime = millis();
     for (int i = 0; i < 24; i++) {
       pixels.setPixelColor(i, Wheel((i + j) & 255));
     }
     pixels.show();
     j++;
    }*/

        static uint8_t hue;
    
  for(int i = 0; i < NUMPIXELS/2; i++) {   
    leds.fadeToBlackBy(40);
    leds[i] = CHSV(hue++,255,255);
    leds(NUMPIXELS/2,NUMPIXELS-1) = leds(NUMPIXELS/2 - 1 ,0);
    FastLED.delay(33);
  }
}

void error() {

  while (1)
  {
    for (int i = 0; i < 24; i++) {
      // pixels.setPixelColor(i, 50, 0, 0);
      leds[i] = CRGB::Red;
    }
    //pixels.show();
    FastLED.show();
    delay(500);
    //pixels.clear();
        for (int i = 0; i < 24; i++) {
      // pixels.setPixelColor(i, 50, 0, 0);
      leds[i] = CRGB::Black;
    }
    FastLED.show();
    // pixels.show();
    delay(500);
  }
}

/*uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }*/
