
int getAccessToken(char apiKey[], char url[], char token[])
{

  char header[HEADER_SIZE] = "";

  strcat(header, "Basic ");
  strcat(header, apiKey);

  HTTPClient http;

  http.begin(url);
  http.addHeader("Authorization", header);
  Serial.println(header);

  String empty = "";
  int httpResponseCode = http.POST(empty);

  if ( httpResponseCode == 200 ) {

    String payload = http.getString();
    Serial.println(payload);
    DynamicJsonDocument payloadObject(200);
    deserializeJson(payloadObject, payload);
    const char* access_token_temp = payloadObject["access_token"];
    strcpy(token, access_token_temp);
    Serial.println(token);

  } else {

    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }

  http.end();

  return httpResponseCode;

}

int getPrevisions(char token[], char url[], int previsions[4][24]) {

  HTTPClient http;
  http.begin(url);

  char header[HEADER_SIZE] = "";
  strcat(header, "Bearer ");
  strcat(header, token);
  http.addHeader("Authorization", header);

  int httpResponseCode = http.GET();

  if ( httpResponseCode == 200 ) {

    String payload = http.getString();
    //Serial.println(payload);

    DynamicJsonDocument payloadObject(6144);
    deserializeJson(payloadObject, payload);

    for (int day = 0; day < 4; day++)
    {
      JsonObject dayObject = payloadObject["signals"][day];

      Serial.print("Day = "); Serial.println(dayObject["jour"].as<const char*>());

      for (int pas = 0; pas < 24; pas++)
      {
        JsonObject pasObject = dayObject["values"][pas];
        previsions[day][pas] = pasObject["hvalue"];
        Serial.print("Day #"); Serial.print(day); Serial.print(" pas #"); Serial.print(pas); Serial.print(" = ");   Serial.println(previsions[day][pas]);
      }
    }

  } else {

    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }

  return httpResponseCode;

}
