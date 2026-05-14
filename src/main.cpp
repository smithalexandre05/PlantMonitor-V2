#include <Arduino.h>
#include "config.h"
#include "sensors/sht40-sensor.h"
#include "sensors/ldr-sensor.h"
#include "sensors/cms-sensor.h"
#include "actuators/gl-actuator.h"
#include "actuators/wp-actuator.h"
#include "wifi-manager.h"
#include "time-manager.h"

SHTReading currentSHTReading;
unsigned long lastSHTReadTime = 0;
unsigned long lastLDRReadTime = 0;
unsigned long lastWPRunTime = 0;
unsigned long lastCoolDownTime = 0;

void setup() {

  Serial.begin(9600);

  initSHT40();
  initLDR();
  initGL();
  initCMS();
  initWP();
  connectWiFi();
  if (isWiFiConnected() == true) {
    initTime();
  }
}

void loop() {

  unsigned long currentTime = millis();

  if (currentTime - lastSHTReadTime >= SHTReadInterval) {
    currentSHTReading = readSHT40();
    lastSHTReadTime = currentTime;
  }

  if (isInsideLightWindow()) {
    if (currentTime - lastLDRReadTime >= LDRReadInterval) {
      if (determineLightState() == true) {
        turnGrowLightON();
      } else {
        turnGrowLightOFF();
      }
      lastLDRReadTime = currentTime;
    }
  }

  if (waterCooldownOver) {
    if(determineSoilState() == DRY) {
      waterPumpON();
      currentPumpStatus = true;
      waterCooldownOver = false;
      lastWPRunTime = currentTime;
    }
  }
  if ((currentPumpStatus) && (currentTime - lastWPRunTime >= WPRunTime)) {
    waterPumpOFF();
    currentPumpStatus = false;
    lastCoolDownTime = currentTime;
  }
  if ((!waterCooldownOver) && (!currentPumpStatus) && (currentTime - lastCoolDownTime >= WPCooldownPeriod)) {
    waterCooldownOver = true;
  }
}