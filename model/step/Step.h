#ifndef SO2_PROJ_STEP_H
#define SO2_PROJ_STEP_H
#include "EquipmentType.h"
class Step {
    EquipmentType type;
    int durationInSeconds;
public:
    EquipmentType getType() const;

    int getDurationInSeconds() const;

public:
    Step(EquipmentType type, int durationInSeconds);
};


#endif //SO2_PROJ_STEP_H
