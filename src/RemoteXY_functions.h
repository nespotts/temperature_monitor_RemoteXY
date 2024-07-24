
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>



String mainURL ="http://192.168.8.148";
JsonDocument doc;


long get_data_timer = 0;
long get_data_interval = 500; // ms

long send_data_timer = 0;
long send_data_interval = 1000; // ms


// convert float to char array
String floatToCharArray(float val, int decimal_places=3) {
  char temp[32];
  dtostrf(val, 0, decimal_places, temp);
  return String(temp);
}



void set_value(String key, String value) {
  WiFiClient client;
  HTTPClient http;

  // Serial.print("[HTTP] begin...");

  if (http.begin(client, mainURL + "/set_value/" + key + "/" + value)) {  // HTTP
    // Serial.print("[HTTP] GET...");
    // start connection and send HTTP header
    int httpCode = http.GET();

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET code: %d", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        String payload = http.getString();
        // deserializeJson(doc, payload);
        // Serial.println(payload);
      }
    } else {
      Serial.printf("[HTTP] GET failed, error: %s", http.errorToString(httpCode).c_str());
    }

    http.end();
  } else {
    Serial.printf("[HTTP} Unable to connect");
  }
}

void set_temps(float inside_temp, float outside_temp, float electrical_temp) {
  WiFiClient client;
  HTTPClient http;

  // Serial.print("[HTTP] begin...");

  if (http.begin(client, mainURL + "/set_temps/" + floatToCharArray(inside_temp) + "/" + floatToCharArray(outside_temp) + "/" + floatToCharArray(electrical_temp))) {  // HTTP
    // Serial.print("[HTTP] GET...");
    // start connection and send HTTP header
    int httpCode = http.GET();

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET code: %d", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        String payload = http.getString();
        // deserializeJson(doc, payload);
        // Serial.println(payload);
      }
    } else {
      Serial.printf("[HTTP] GET failed, error: %s", http.errorToString(httpCode).c_str());
    }

    http.end();
  } else {
    Serial.printf("[HTTP} Unable to connect");
  }
}




