#include <iostream>
#include "Dish.hpp"
#include "LinkedList.hpp"
#include "KitchenStation.hpp"
#include "StationManager.hpp"
#include <string>
#include <vector>
#include <iomanip> // For std::fixed and std::setprecision
#include <cctype>  // For std::isalpha, std::isspace

int main()
{
    //Ingredient(const std::string& name, int quantity, int required_quantity, double price);
    Ingredient i1("flour", 10, 5, 6.99);
    Ingredient i2("sugar", 20, 10, 3.99);
    Ingredient i3("eggs", 12, 2, 4.99);
    Ingredient i4("butter", 6, 3, 4.99);

    //Dish(const std::string& name, const std::vector<Ingredient>& ingredients = {}, int prep_time = 0, double price = 0.0, CuisineType cuisine_type = CuisineType::OTHER);
    Dish* d1 = new Dish("Cake", std::vector<Ingredient>{i1, i2, i3, i4}, 30, 20.99, Dish::CuisineType::AMERICAN);
    Dish* d2 = new Dish("Pasta", std::vector<Ingredient>{i1, i2, i3, i4}, 20, 15.99, Dish::CuisineType::ITALIAN);

    StationManager station_manager;
    KitchenStation* station1 = new KitchenStation("Station 1");
    KitchenStation* station2 = new KitchenStation("Station 2");

    station_manager.addStation(station1);
    station_manager.addStation(station2);

    station_manager.assignDishToStation("Station 1", d1);
    station_manager.assignDishToStation("Station 2", d2);

    station_manager.replenishIngredientAtStation("Station 1", i1);
    station_manager.replenishIngredientAtStation("Station 1", i2);
    station_manager.replenishIngredientAtStation("Station 1", i3);
    station_manager.replenishIngredientAtStation("Station 1", i4);

    if (station_manager.canCompleteOrder("Cake"))
    {
        station_manager.prepareDishAtStation("Station 1", "Cake");
        std::cout << "Dish Made" << std::endl;
    }
    else
    {
        std::cout << "Dish Not Made" << std::endl;
    }

    // delete d1;
    // delete d2;
    // delete station1;
    // delete station2;

    return 0;
}