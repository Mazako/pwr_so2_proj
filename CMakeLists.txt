cmake_minimum_required(VERSION 3.27)
project(so2_proj)

set(CMAKE_CXX_STANDARD 23)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})


include_directories(model/kitchen_equipment
        model/meal
        model/step
        model/kitchen
        model/order
        model/cook
        model/waiter
        model/menu)

add_executable(so2_proj main.cpp
        model/meal/Meal.cpp
        model/meal/Meal.h
        model/step/Step.cpp
        model/step/Step.h
        model/kitchen_equipment/EquipmentType.h
        model/kitchen_equipment/KitchenEquipment.cpp
        model/kitchen/Kitchen.cpp
        model/kitchen/Kitchen.h
        model/order/Order.cpp
        model/order/Order.h
        model/order/OrderStatus.h
        model/cook/Cook.cpp
        model/cook/Cook.h
        model/waiter/Waiter.cpp
        model/waiter/Waiter.h
        model/client/Client.cpp
        model/client/Client.h
        model/menu/Menu.cpp
        model/menu/Menu.h)

target_link_libraries(so2_proj ${CURSES_LIBRARIES})
