#ifndef SO2_PROJ_COOK_H
#define SO2_PROJ_COOK_H
#include <memory>
#include "Order.h"
#include "Kitchen.h"
#include "MakeMove.h"


class Cook : public MakeMove{
    static int ID;
    void threadFunction(const std::shared_ptr<Kitchen> &kitchen);
    long id;
    std::shared_ptr<Order> order = nullptr;
    std::thread thread;
    EquipmentType currentEq;

    const char *equipmentTypeToString(EquipmentType type) {
        switch (type) {
            case EquipmentType::OVEN:
                return "Oven";
            case EquipmentType::MIXER:
                return "Mixer";
            case EquipmentType::COOKER:
                return "Cooker";
            case EquipmentType::PAN:
                return "Pan";
            case EquipmentType::MICROVAVE:
                return "Microwave";
            case EquipmentType::TABLE:
                return "Table";
            default:
                return "Unknown";
        }
    }


public:
    Cook(const std::shared_ptr<Kitchen> &kitchen, int x1, int y1, std::string letter);
    void start();
    const std::string getOrderInfo();

    void setCurrentEq(EquipmentType currentEq);
};


#endif
