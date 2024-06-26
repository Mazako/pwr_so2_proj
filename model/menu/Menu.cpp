#include <random>
#include "Menu.h"

Menu::Menu() {
    meals = std::vector<Meal>{
        Meal("Pizza", std::deque<Step>{
            Step(EquipmentType::MIXER, 2),
            Step(EquipmentType::TABLE, 4),
            Step(EquipmentType::OVEN, 3)
        }),

        Meal("Spaghetti", std::deque<Step>{
            Step(EquipmentType::COOKER, 1),
            Step(EquipmentType::PAN, 4)
        })
    };
}

std::shared_ptr<Order> Menu::createRandomOrder() const {
    std::random_device device;
    std::mt19937 rng(device());
    std::uniform_int_distribution<> distribution(0, meals.size() - 1);
    return std::make_shared<Order>(meals[distribution(rng)]);
}
