#ifndef TELEMETRY_H
#define TELEMETRY_H

#include "sensors/sht40-sensor.h"

String buildTelemetryJson(SHTReading sht40);

#endif