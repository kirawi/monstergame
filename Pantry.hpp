#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <iostream>

#include "LinkedList.hpp"

struct Ingredient {
    std::string name_;
    std::string description_;
    int quantity_;
    int price_;
    std::vector<Ingredient*> recipe_;

    /**
            Default Constructor
            @post: Creates a new Ingredient object with default values. String defaults to empty string. 
                    Default quantity is 0, default price is 1.
    */
    Ingredient() : quantity_(0), price_(1) {}
    
    /**
          Parameterized Constructor
          @param: A string representing a ingredient name
          @param: A string representing ingredient description
          @param: An int representing the ingredient's quantity
          @param: An int representing the ingredient's price
          @param: A vector holding Ingredient pointers representing the ingredient's recipe
          @post: Creates a new Ingredient object with the given parameters
    */
    Ingredient(const std::string& name, const std::string& description, int quantity, int price, std::vector<Ingredient*> recipe) 
        : name_(name), description_(description), quantity_(quantity), price_(price), recipe_(recipe) {}
};

class Pantry : public LinkedList<Ingredient*> {
    private:
        /*
            @param A pointer to the ingredient
            @post Will output in the format of 
                [Ingredient Name0](C)
                [Ingredient Name1](C) <- [Ingredient Name2](3)
                [Ingredient Name3](C) <- [Ingredient Name4](C) <- [Ingredient Name5] (3)
            @note Similar to ingredientQuery but will not report uncraftable ingredients (hence why it's private)
        */
        void recipeIngredientQuery(Ingredient* i) const;
        
    public:
        /**
           Default Constructor
        */
        Pantry();

        /**
            @param: the name of an input file
            @pre: Formatting of the csv file is as follows:
                Name: A string
                Description: A string
                Quantity: A non negative integer
                Price: A non negative integer
                Recipe: A list of Ingredient titles of the form [NAME1] [NAME2];
                For example, to make this ingredient, you need (Ingredient 1 AND Ingredient 2)
                The value may be NONE.
            Notes:
                - The first line of the input file is a header and should be ignored.
                - The recipe are separated by a semicolon and may be NONE.
                - The recipe may be in any order.
                - If any of the recipe are not in the list, they should be created as new ingredients with the following information:
                    - Title: The name of the ingredient
                    - Description: "UNKNOWN"
                    - Quantity: 0
                    - Price: 0
                    - Recipe: An empty vector
                - However, if you eventually encounter a ingredient that matches one of the "UNKNOWN" ingredients while parsing the file, you should update all the ingredient details.

                For example, given a row in the file:
                Inferno_Espresso,An energizing elixir brewed with mystical flames providing resistance to caffeine crashes for a limited time.,1,50,Fiery_Bean Ember_Spice

                The order of the ingredients in the list:
                Fiery_Bean, Ember_Spice, Inferno_Espresso
                Hint: update as needed using addIngredient()

            @post: Each line of the input file corresponds to a ingredient to be added to the list. No duplicates are allowed.
            Hint: use std::ifstream and getline()
        */
        Pantry(const std::string& path);

         /**
                Destructor
                @post: Explicitly deletes every dynamically allocated Ingredient object
        */
        ~Pantry();

        /**
            @param: A const string reference to a ingredient name
            @return: The integer position of the given ingredient if it is in the Pantry, -1 if not found. REMEMBER, indexing starts at 0.
        */
        int getPosOf(const std::string& ingredient) const;

        /**
            @param: A const string reference to a ingredient name
            @return: True if the ingredient information is already in the Pantry
        */
        bool contains(const std::string& ingredient) const;

        /**
            @param:  A pointer to an Ingredient object
            @post:  Inserts the given ingredient pointer into the Pantry, unless an ingredient of the same name is already in the pantry. 
                    Each of its Ingredients in its recipe are also added to the Pantry IF not already in the list.
            @return: True if the ingredient was added successfully, false otherwise.
        */
        bool addIngredient(Ingredient* ingredient);

        /**
            @param: A const string reference representing a ingredient name
            @param: A const string reference representing ingredient description
            @param: A const int reference representing the ingredient's quantity
            @param: A const int reference representing the ingredient's price
            @param: A const reference to a vector holding Ingredient pointers representing the ingredient's recipe
            @post:   Creates a new Ingredient object and inserts a pointer to it into the Pantry. 
                    Each of its Ingredients in its recipe are also added to the Pantry IF not already in the list.
            @return: True if the ingredient was added successfully
        */
        bool addIngredient(const std::string& name, const std::string& description, const int& quantity, const int& price, const std::vector<Ingredient*>& recipe);

        /*
            @param A const string reference reresenting an ingredient name
            @return A pointer to the Ingredient if the ingredient is in the pantry. nullptr if not
        */
        Ingredient* getIngredient(const std::string& name) const;

        /**
            @param:  A Ingredient pointer
            @return: A boolean indicating if all the given ingredient can be created (all of the ingredients in its recipe can be created, or if you have enough of each ingredient in its recipe to create it)
        */
        bool canCreate(Ingredient* ingredient) const;

        /**
            @param: A Ingredient pointer
            @post: Prints the ingredient name, quantity, and description.
            The output should be of the form:
            [Ingredient Name]: [Quantity]\n
            [Ingredient Description]\n
            Price: [Price]\n
            Recipe:\n
            [Ingredient0] [Ingredient1]\n

            If the ingredient has no recipe, print "Recipe:\nNONE\n\n" after the price.
        */
        void printIngredient(Ingredient* ingredient) const;

        /**
            @param: A const string reference to a ingredient name
            @post:  Prints a list of ingredients that must be created before the given ingredient can be created (missing ingredients for its recipe, where you have 0 of the needed ingredient).
                    If the ingredient is already in the pantry, print "In the pantry([quantity])\n"
                    If there are no instances of the ingredient, if it cannot be crafted because of insufficient ingredients, print "[Ingredient Name](0)\nMISSING INGREDIENTS"
                    If it can be crafted, recursively print the ingredients that need to be used (if there are instances of them) or created (if there are no instances of them) in the order that the ingredients appear in the recipe, joined by "<-".
                    If the ingredient has no recipe, print "UNCRAFTABLE\n" at the end of the function.

                    Below are some of the expected forms. "Scenario: [scenario] is not part of the output. It is just to help you understand the expected output.":

                    Scenario: The Ingredient does not exist in the list
                    Query: [Ingredient Name]
                    No such ingredient

                    Scenario: The Ingredient exists in the list, and there are >0 instances of it
                    Query: [Ingredient Name]
                    In the pantry ([Quantity])

                    Scenario: The Ingredient exists in the list, and there are 0 instances of it, and it is craftable by using an ingredient that is already in the pantry
                    Query: [Ingredient Name0]
                    [Ingredient Name0](C)
                    [Ingredient Name1](1)

                    Scenario: The Ingredient exists in the list, and there are 0 instances of it, and it is craftable by using an ingredient that has to be crafted
                    Query: [Ingredient Name0]
                    [Ingredient Name0](C)
                    [Ingredient Name1](C) <- [Ingredient Name2](3)

                    Scenario: The Ingredient exists in the list, and there are 0 instances of it, and there are multiple ingredients that have to be crafted (each row represents a different ingredient inå the original recipe)
                    Query: [Ingredient Name0]
                    [Ingredient Name0](C)
                    [Ingredient Name1](C) <- [Ingredient Name2](3)
                    [Ingredient Name3](C) <- [Ingredient Name4](C) <- [Ingredient Name5] (3)

                    Scenario: The Ingredient exists in the list, and there are 0 instances of it, and it is not craftable (it has no recipe)
                    Query: [Ingredient Name0]
                    UNCRAFTABLE

                    Scenario: The Ingredient exists in the list, and there are 0 instances of it, and it has a recipe, but you do not have enough of the ingredients to craft it
                    Query: [Ingredient Name0]
                    [Ingredient Name0](0)
                    MISSING INGREDIENTS

            HINT: Use canCreate() to determine if the ingredient can be created.
        */
        void ingredientQuery(const std::string& name) const;

        /**
            @return: An integer sum of the price of all the ingredients currently in the list.
            Note: This should only include price values from ingredients that you have 1 or more of. Do not consider ingredients that you have 0 of, even if you have the ingredients to make them.
        */
        int calculatePantryValue() const;

        /**
            @param: A const string reference to a filter with a default value of "NONE".
            @post: With default filter "NONE": Print out every ingredient in the list.
                With filter "CONTAINS":   Only print out the ingredients with >0 instances in the list.
                With filter "MISSING": Only print out the ingredients with 0 instances in the list.
                With filter "CRAFTABLE":  Only print out the ingredients where you have all the ingredients to craft them.
                If an invalid filter is passed, print "INVALID FILTER\n"
                Printing ingredients should be of the form:

                [Ingredient name]: [Quantity]
                [Ingredient description]\n
                Price: [price]\n
                Recipe:\n
                [Ingredient0] [Ingredient1]\n\n

                If the ingredient has no recipe, print "Recipe:\nNONE\n\n" after the price.
        */
        void pantryList(const std::string& filter = "NONE") const;

};
