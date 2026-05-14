#ifndef WP_ACTUATOR_H
#define WP_ACTUATOR_H

extern bool waterCooldownOver;
extern bool currentPumpStatus;

void initWP();
void waterPumpON();
void waterPumpOFF();

#endif