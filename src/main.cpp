long currenttime = 0;

// ****************************** JLED *************************************
#include <jled.h>
// breathe LED for 5 times, LED is connected to pin 9 (PWM capable) gpio
auto led_on = JLed(LED_BUILTIN).Breathe(3000).Forever();
auto led_off = JLed(LED_BUILTIN).LowActive().Off();
// *************************************************************************


// Include the libraries we need
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into port 0 on the Arduino
#define ONE_WIRE_BUS 0
#define TEMPERATURE_PRECISION 10

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

// arrays to hold device addresses when getting them by index
// DeviceAddress insideThermometer, outsideThermometer, electricalThermometer;

// assign them manually
DeviceAddress insideThermometer = {0x28, 0x34, 0x11, 0x79, 0x97, 0x13, 0x03, 0xAC};
DeviceAddress outsideThermometer = {0x28, 0x67, 0x45, 0xA6, 0x56, 0x23, 0x0B, 0xDD};
DeviceAddress electricalThermometer = {0x28, 0x7D, 0x9F, 0x69, 0x0B, 0x00, 0x00, 0xD6};

float insideTemp, outsideTemp, electricalTemp;


#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "network.h"
#include "RemoteXY_functions.h"
#include "RemoteXY_callbacks.h"
#include "OTA.h"
#include "functions.h"



void setup()
{
  // Debug console
  Serial.begin(115200);
  led_off.Update();

  pinMode(LED_BUILTIN, OUTPUT);

  ConnectWifi();

  OTA_Functions();

  setupSensors();
}

long send_timer = 0;
long send_interval = 1000;

void loop()
{
  currenttime = millis();
  manageBlynkConnection2();
  led_on.Update();
  ArduinoOTA.poll();

  if (currenttime - send_timer >= send_interval) {
    send_timer = currenttime;
    readTemps();
  }
}






