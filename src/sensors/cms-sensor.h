#ifndef CMS_SENSOR_H
#define CMS_SENSOR_H

enum SoilState {
    DRY,
    MOIST,
    WET,
    INVALID
};

void initCMS();
SoilState determineSoilState();

#endif