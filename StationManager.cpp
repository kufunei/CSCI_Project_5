/**
 * @file StationManager.cpp
 * @brief This file contains the implementation of the StationManager class that is a subclass of LinkedList that stores KitchenStation* objects, which represents a station manager in a virtual bistro simulation.
 * 
 * The StationManager class includes a default constructor, destructor, and methods to manage and present the details of the station manager. 
 * 
 * @date November 3, 2024
 * @author Kun Feng Wei
 */

#include "KitchenStation.hpp"
#include "StationManager.hpp"
#include "LinkedList.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <iomanip> // For std::fixed and std::setprecision
#include <cctype>  // For std::isalpha, std::isspace

/**
 * Default Constructor
 * @post: Initializes an empty station manager.
 */
StationManager::StationManager() : LinkedList<KitchenStation*>() {}

/**
 * Destructor
 * @post: Deallocates all kitchen stations and clears the list.
 */
StationManager::~StationManager()
{
    for (size_t i = 0; i < getLength(); i++)
    {
        KitchenStation* station = getEntry(i);
        delete station;
        station = nullptr;
    }
    clear();
}

/**
 * Adds a new station to the station manager.
 * @param station A pointer to a KitchenStation object.
 * @post: Inserts the station into the linked list.
 * @return: True if the station was successfully added; false
otherwise.
 */
bool StationManager::addStation(KitchenStation* station)
{
    for (size_t i = 0; i < getLength(); i++)
    {
        if (getEntry(i)->getName() == station->getName())
        {
            return false;
        }
    }
    return insert(getLength(), station);
}

/**
 * Removes a station from the station manager by name.
* @param station_name A string representing the station's name.
 * @post: Removes the station from the list and deallocates it.
 * @return: True if the station was found and removed; false
otherwise.
 */
bool StationManager::removeStation(const std::string& station_name)
{
    for (size_t i = 0; i < getLength(); i++)
    {
        if (getEntry(i)->getName() == station_name)
        {
            delete getEntry(i);
            remove(i);
            return true;
        }
    }
    return false;
}

/**
 * Finds a station in the station manager by name.
 * @param station_name A string representing the station's name.
 * @return: A pointer to the KitchenStation if found; nullptr
otherwise.
 */
KitchenStation* StationManager::findStation(const std::string& station_name) const
{
    for (size_t i = 0; i < getLength(); i++)
    {
        if (getEntry(i)->getName() == station_name)
        {
            return getEntry(i);
        }
    }
    return nullptr;
}

/**
 * Moves a specified station to the front of the station manager
list.
 * @param station_name A string representing the station's name.
 * @post: The station is moved to the front of the list if it
exists.
 * @return: True if the station was found and moved; false
otherwise.
 */
bool StationManager::moveStationToFront(const std::string& station_name)
{
    KitchenStation* station = findStation(station_name);
    if (station)
    {
        for (size_t i = 0; i < getLength(); i++)
        {
            if (getEntry(i)->getName() == station_name)
            {
                remove(i);
            }
        }
        insert(0, station);
        return true;
    }
    return false;
}

/**
 * Merges the dishes and ingredients of two specified stations.
 * @param station_name1 The name of the first station.
 * @param station_name2 The name of the second station.
 * @post: The second station is removed from the list, and its
contents are added to the first station.
 * @return: True if both stations were found and merged; false
otherwise.
 */
bool StationManager::mergeStations(const std::string& station_name1, const std::string& station_name2)
{
    KitchenStation* station1 = findStation(station_name1);
    KitchenStation* station2 = findStation(station_name2);

    if (station1 && station2)
    {
        for (size_t i = 0; i < station2->getDishes().size(); i++)
        {
            station1->getDishes().push_back(station2->getDishes()[i]);
        }

        for (size_t i = 0; i < station2->getIngredientsStock().size(); i++)
        {
            station1->getIngredientsStock().push_back(station2->getIngredientsStock()[i]);
        }
        removeStation(station_name2);
        return true;
    }
    return false;
}

 /**
 * Assigns a dish to a specific station.
* @param station_name A string representing the station's name.
 * @param dish A pointer to a Dish object.
 * @post: Assigns the dish to the specified station.
 * @return: True if the station was found and the dish was assigned;
false otherwise.
 */
bool StationManager::assignDishToStation(const std::string& station_name, Dish* dish)
{
    KitchenStation* station = findStation(station_name);
    if (station)
    {
        station->assignDishToStation(dish);
        return true;
    }
    return false;
}

/**
 * Replenishes an ingredient at a specific station.
 * @param station_name A string representing the station's name.
 * @param ingredient An Ingredient object.
 * @post: Replenishes the ingredient stock at the specified station.
 * @return: True if the station was found and the ingredient was
replenished; false otherwise.
 */
bool StationManager::replenishIngredientAtStation(const std::string& station_name, const Ingredient& ingredient)
{
    KitchenStation* station = findStation(station_name);
    if (station)
    {
        station->replenishStationIngredients(ingredient);
        return true;
    }
    return false;
}

/**
 * Checks if any station in the station manager can complete an
order for a specific dish.
 * @param dish_name A string representing the name of the dish.
 * @return: True if any station can complete the order; false
otherwise.
 */
bool StationManager::canCompleteOrder(const std::string& dish_name) const
{
    for (size_t i = 0; i < getLength(); i++)
    {
        if (getEntry(i)->canCompleteOrder(dish_name))
        {
            return true;
        }
    }
    return false;
}

/**
 * Prepares a dish at a specific station if possible.
 * @param station_name A string representing the station's name.
 * @param dish_name A string representing the name of the dish.
 * @post: If the dish can be prepared, reduces the quantities of the
used ingredients at the station.
 * @return: True if the dish was prepared successfully; false
otherwise.
 */
bool StationManager::prepareDishAtStation(const std::string& station_name, const std::string& dish_name)
{
    KitchenStation* station = findStation(station_name);
    if (station)
    {
        station->prepareDish(dish_name);
        return true;
    }
    return false;
}