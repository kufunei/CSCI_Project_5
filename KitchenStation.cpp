/**
 * @file KitchenStation.cpp
 * @brief This file contains the implementation of the KitchenStation class, which represents a kitchen station in a virtual bistro simulation.
 * 
 * The KitchenStation class includes methods to manage and present the details of a dish, including station name, dishes, and ingredients stock.
 * It also includes an implementation of the the default, paramerized constructor, destructor, and accessor and mutator functions for KitchenStation.
 * The implementation ensures that the dish name is validated and correctly formatted.
 * 
 * @date November 3, 2024
 * @author Kun Feng Wei
 */

#include "KitchenStation.hpp"
#include "Dish.hpp"
#include "LinkedList.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <iomanip> // For std::fixed and std::setprecision
#include <cctype>  // For std::isalpha, std::isspace

/**
 * Default Constructor
 * @post: Initializes an empty kitchen station with default values.
 */
KitchenStation::KitchenStation() : station_name_("UNKNOWN"), dishes_({}), ingredients_stock_({}) {}

/**
 * Parameterized Constructor
 * @param station_name A string representing the station's name.
 * @post: Initializes a kitchen station with the given name.
 */
KitchenStation::KitchenStation(const std::string& station_name) : station_name_(station_name), dishes_({}), ingredients_stock_({}) {}

/**
 * Destructor
 * @post: Deallocates all dynamically allocated dishes in the
station. */
KitchenStation::~KitchenStation()
{
    std::vector<Dish*> dishes = KitchenStation::getDishes();
    for (size_t i = 0; i < dishes.size(); i++)
    {
        delete dishes[i];
        dishes[i] = nullptr;
    }
}

/**
 * Retrieves the name of the kitchen station.
 * @return: The name of the station.
 */
std::string KitchenStation::getName() const
{
    return station_name_;
}

/**
 * Sets the name of the kitchen station.
 * @param name A string representing the new station name.
 * @post: Updates the station's name.
 */
void KitchenStation::setName(const std::string& name)
{
    station_name_ = name;
}

/**
 * Retrieves the list of dishes assigned to the kitchen station.
 * @return A vector of pointers to Dish objects assigned to the station.
 */
std::vector<Dish*> KitchenStation::getDishes() const
{
    return dishes_;
}

/**
 * Retrieves the ingredient stock available at the kitchen station.
* @return A vector of Ingredient objects representing the station's
ingredient stock.
*/
std::vector<Ingredient> KitchenStation::getIngredientsStock() const
{
    return ingredients_stock_;
}

/**
 * Assigns a dish to the station.
 * @param dish A pointer to a Dish object.
 * @post: Adds the dish to the station's list of dishes if not
already present.
 * @return: True if the dish was added successfully; false
otherwise.
 */
bool KitchenStation::assignDishToStation(Dish* dish)
{
    for (size_t i = 0; i < dishes_.size(); i++)
    {
        if (dishes_[i] == dish)
        {
            return false;
        }
    }    
    dishes_.push_back(dish);
    return true;
}

/**
 * Replenishes the station's ingredient stock.
 * @param ingredient An Ingredient object.
 * @post: Adds the ingredient to the station's stock or updates the
quantity if it already exists.
 */
void KitchenStation::replenishStationIngredients(const Ingredient& ingredient)
{
    for (size_t i = 0; i < ingredients_stock_.size(); i++)
    {
        if (ingredients_stock_[i].name == ingredient.name)
        {
            ingredients_stock_[i].quantity = ingredients_stock_[i].quantity + ingredient.quantity;
        }
    }
    ingredients_stock_.push_back(ingredient);
}

// struct Ingredient
// {
//     std::string name;
//     int quantity;           // Quantity in stock
//     int required_quantity;  // Quantity required for the dish
//     double price;           // Price per unit

//     //Constructors
//     Ingredient();
//     Ingredient(const std::string& name, int quantity, int required_quantity, double price);
// };

/**
 * Checks if the station can complete an order for a specific dish.
 * @param dish_name A string representing the name of the dish.
 * @return: True if the station has the dish assigned and all
required ingredients are in stock; false otherwise.
 */
bool KitchenStation::canCompleteOrder(const std::string& dish_name)
{
    for (size_t i = 0; i < dishes_.size(); i++)
    {
        if (dishes_[i]->getName() == dish_name)
        {
            for (size_t j = 0; j < dishes_[i]->getIngredients().size(); j++)
            {
                bool ready = false;
                for (size_t k = 0; k < ingredients_stock_.size(); k++)
                {
                    if (ingredients_stock_[k].name == dishes_[i]->getIngredients()[j].name && ingredients_stock_[k].quantity >= dishes_[i]->getIngredients()[j].required_quantity)
                    {
                        ready = true;
                    }
                }
                if (ready == false)
                {
                    return false;
                }
            }
            return true;
        }
    }
    return false;
}

/*
 * Prepares a dish if possible.
 * @param dish_name A string representing the name of the dish.
 * @post: If the dish can be prepared, reduce the quantities of the
used ingredients accordingly. If the stock ingredient is depleted to
0, remove the ingredient from the Kitchen Station.
* @return: True if the dish was prepared successfully; false
 otherwise.
 */
bool KitchenStation::prepareDish(const std::string& dish_name)
{
    if (canCompleteOrder(dish_name) == true)
    {
        for (size_t i = 0; i < dishes_.size(); i++)
        {
            if (dishes_[i]->getName() == dish_name)
            {
                for (size_t j = 0; j < dishes_[i]->getIngredients().size(); j++)
                {
                    for (size_t k = 0; k < ingredients_stock_.size(); k++)
                    {
                        if (ingredients_stock_[k].name == dishes_[i]->getIngredients()[j].name)
                        {
                            ingredients_stock_[k].quantity = ingredients_stock_[k].quantity - dishes_[i]->getIngredients()[j].required_quantity;
                            if (ingredients_stock_[k].quantity <= 0)
                            {
                                ingredients_stock_.erase(ingredients_stock_.begin() + k);
                                k--;
                            }
                        }
                    }
                }
                return true;
            }
        }
    }
    return false;
}
