/**
 * @file KitchenStation.hpp
 * @brief This file contains the declaration of the KitchenStation class, which represents a kitchen station in a virtual bistro simulation.
 * 
 * The KitchenStation class includes attributes such as station name, dishes, and ingredients stock.
 * It provides constructors, destructor, accessor and mutator functions.
 * 
 * @date November 3, 2024
 * @author Kun Feng Wei
 */

#ifndef KITCHENSTATION_HPP
#define KITCHENSTATION_HPP

#include "Dish.hpp"
#include "LinkedList.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <iomanip> // For std::fixed and std::setprecision
#include <cctype>  // For std::isalpha, std::isspace

class KitchenStation
{
public:
/**
 * Default Constructor
 * @post: Initializes an empty kitchen station with default values.
 */ 
    KitchenStation();

/**
 * Parameterized Constructor
 * @param station_name A string representing the station's name.
 * @post: Initializes a kitchen station with the given name.
 */
    KitchenStation(const std::string& station_name);

/**
 * Destructor
 * @post: Deallocates all dynamically allocated dishes in the
station. */
    ~KitchenStation();

/**
 * Retrieves the name of the kitchen station.
 * @return: The name of the station.
 */
    std::string getName() const;

/**
 * Sets the name of the kitchen station.
 * @param name A string representing the new station name.
 * @post: Updates the station's name.
 */
    void setName(const std::string& name);

/**
 * Retrieves the list of dishes assigned to the kitchen station.
 * @return A vector of pointers to Dish objects assigned to the station.
 */
    std::vector<Dish*> getDishes() const;

/**
 * Retrieves the ingredient stock available at the kitchen station.
* @return A vector of Ingredient objects representing the station's
ingredient stock.
*/
    std::vector<Ingredient> getIngredientsStock() const;

/**
 * Assigns a dish to the station.
 * @param dish A pointer to a Dish object.
 * @post: Adds the dish to the station's list of dishes if not
already present.
 * @return: True if the dish was added successfully; false
otherwise.
 */
    bool assignDishToStation(Dish* dish);

/**
 * Replenishes the station's ingredient stock.
 * @param ingredient An Ingredient object.
 * @post: Adds the ingredient to the station's stock or updates the
quantity if it already exists.
 */
    void replenishStationIngredients(const Ingredient& ingredient);

/**
 * Checks if the station can complete an order for a specific dish.
 * @param dish_name A string representing the name of the dish.
 * @return: True if the station has the dish assigned and all
required ingredients are in stock; false otherwise.
 */
    bool canCompleteOrder(const std::string& dish_name);

/**
 * Prepares a dish if possible.
 * @param dish_name A string representing the name of the dish.
 * @post: If the dish can be prepared, reduce the quantities of the
used ingredients accordingly. If the stock ingredient is depleted to
0, remove the ingredient from the Kitchen Station.
* @return: True if the dish was prepared successfully; false
 otherwise.
 */
    bool prepareDish(const std::string& dish_name);

private:
    std::string station_name_;
    std::vector<Dish*> dishes_;
    std::vector<Ingredient> ingredients_stock_;
};

#endif // KITCHENSTATION_HPP
