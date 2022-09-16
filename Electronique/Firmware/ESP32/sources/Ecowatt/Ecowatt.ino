
#include "credentials.h"

/***** Wifi ******/

#include <WiFi.h>
#include <HTTPClient.h>
#define HEADER_SIZE 200


/****** LED *****/

#include <Adafruit_NeoPixel.h>

#define PIN        15
#define NUMPIXELS  24
Adafruit_NeoPixel  pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ400);

byte colorsMap[4][3] =  // 4 niveaux possibles, couleur RGB
{
  { 0, 50,  0}, // 0 = vert
  { 0,  0, 50}, // 1 = bleu
  {50, 25,  0}, // 2 = orange
  {50,  0,  0}  // 3 = rouge
};


///***** Misc *****////

#include <Arduino.h>
#include <ArduinoJson.h>

int previsions[4][24] = {0};


void setup() {

  Serial.begin(115200);
  Serial.println("Hello");
  delay(2000);

  initLED();

  Serial.print("Connecting to ");
  Serial.println(wifiSSID);
  WiFi.begin(wifiSSID, wifiPASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    waitLedAnimation();
    //delay(500);
    //Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected at IP address:");
  Serial.println(WiFi.localIP());


  if (WiFi.status() == WL_CONNECTED) {

    // "https://digital.iservices.rte-france.com/token/oauth";
    // "https://nodered.creatronic.fr/ecowatt";

    char token[HEADER_SIZE] = "";
    int result = getAccessToken(api_key, "https://digital.iservices.rte-france.com/token/oauth", token);
    //int result = getAccessToken(api_key, "https://nodered.creatronic.fr/ecowatt", token);

    // "https://digital.iservices.rte-france.com/open_api/ecowatt/v4/signals";
    // "https://digital.iservices.rte-france.com/open_api/ecowatt/v4/sandbox/signals";

    if (result == 200) result = getPrevisions(token, "https://digital.iservices.rte-france.com/open_api/ecowatt/v4/sandbox/signals", previsions);
    else error();
    if (result != 200) error();
  } else error();

}

void loop() {
  
  for (int i = 0; i < 4; i++) {
    displayPrevisionDay(previsions[i]);
    delay(5000);
  }
  
}
