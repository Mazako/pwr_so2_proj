#include "Step.h"

Step::Step(EquipmentType type, int durationInSeconds) : type(type), durationInSeconds(durationInSeconds) {}

EquipmentType Step::getType() const {
    return type;
}

int Step::getDurationInSeconds() const {
    return durationInSeconds;
}
