/*\
JSON EX

{
  "deviceId": "plant-monitor-01",
  "timestamp": "2026-05-14T20:00:00Z",
  "sensors": {
    "soilRaw": 312,
    "soilState": "MOIST",
    "lightRaw": 940,
    "temperature": 22.4,
    "humidity": 55.2
  },
  "actuators": {
    "pumpRunning": false,
    "growLightOn": true
  },
  "system": {
    "insideLightWindow": true,
    "wateringCooldownOver": false
  }
}
*/

#include <Arduino.h>
#include "telemetry.h"
#include <ArduinoJson.h>
#include "RTC.h"

JsonDocument root;
RTCTime currentTime;

String buildTelemetryJson(SHTReading sht40) {

  JsonDocument doc;

  doc["deviceId"] = "plant-monitor-01";
  // add a function to convert currentTime to standardized format
  // Should currentTime be an arg of this function? or come from #include RTC.h?
  doc["timestamp"] = "8am";

  JsonObject sensors = doc["sensors"].to<JsonObject>();

  sensors["temperature"] = sht40.SHTTemp;
  sensors["humidity"] = sht40.SHTHum;

  String jsonOutput;
  serializeJson(doc, jsonOutput);

  return jsonOutput;
}