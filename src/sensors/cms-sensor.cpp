#include "config.h"
#include "cms-sensor.h"
#include <Arduino.h>

float currentSoilState;

void initCMS() {
    pinMode(CMS_PIN, INPUT);
}

float retrieveCMSReading() {
    return analogRead(CMS_PIN);
}

SoilState determineSoilState() {
    currentSoilState = retrieveCMSReading();
    if (currentSoilState > CMS_DRY_Min) {
        return DRY;
    } else if (currentSoilState > CMS_MOIST_Min) {
        return MOIST;
    } else {
        return WET;
    }
}