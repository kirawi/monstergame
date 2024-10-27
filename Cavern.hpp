#pragma once

#include "ArrayBag.hpp"
#include "Creature.hpp"
#include "Dragon.hpp"
#include "Ghoul.hpp"
#include "Mindflayer.hpp"

#include <stack>
#include <vector>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>

class Cavern : public ArrayBag<Creature*>{
    public: 
      /**
          Default constructor.
          Default-initializes all private members. 
      */
      Cavern();
       /** 
        * @param   :   A reference to a Creature entering the Cavern
        * @post    :   If the given Creature is not already in the Cavern, add Creature to the Cavern and updates the level sum and the tame Creature count if the creature is tame.
        * @return  :   returns true if a Creature was successfully added to the Cavern, false otherwise
                  :   Hint: Use the above definition of equality will help determine if a Creature is already in the Cavern
      **/
      bool enterCavern(const Creature& c);

      /** 
        * @param   :   A  reference to a Creature leaving the Cavern
        * @return  :  returns true if a creature was successfully removed from the Cavern (i.e. items_), false otherwise
        * @post    :    removes the creature from the Cavern and updates the level sum. 
                        If the Creature is tame it also updates the tame count.
      **/
      bool exitCavern(const Creature& c);

       /** 
        * @return   :  The integer level count of all the creatures currently in the Cavern
        **/
      int getLevelSum() const;

      /**
        * @return   :  The average level (int) of all the creatures in the Cavern
        * @post     :  Computes the average level (double) of the Cavern rounded to the NEAREST integer.
        **/
      int calculateAvgLevel() const;

      /**
        * @return   :  The integer count of tame Creatures in the Cavern
        **/
      int getTameCount() const;

      /**
        * @return   :  The percentage (double) of all the tame creatures in the Cavern
        * @post     :   Computes the percentage of tame creatures in the Cavern rounded up to 2 decimal places.
        **/
      double calculateTamePercentage() const;

      /**
        * @param  :   A reference to a string representing a creature Category with value in ["UNKNOWN", "UNDEAD", "MYSTICAL", "ALIEN"]
        * @return  :  An integer tally of the number of creatures in the Cavern of the given category. 
                    If the argument string does not match one of the expected category values, the tally is zero. 
                    NOTE: no pre-processing of the input string necessary, only uppercase input will match.
      **/
      int tallyCategory(const std::string& s) const;

      /**
          @param  :   An integer representing the level threshold of the creatures to be removed from the Cavern, with default value 0
          @post   :   Removes all creatures from the Cavern whose level is less than the given level. If no level is given, removes all creatures from the Cavern. Ignore negative input.
          @return :   The number of creatures removed from the Cavern
      */
      int releaseCreaturesBelowLevel(int n = 0);

      /**
          @param  : A reference to a string representing a creature Category with a value in ["UNKNOWN", "UNDEAD", "MYSTICAL", "ALIEN"], or default value "ALL" if no category is given
          @post   : Removes all creatures from the Cavern whose category matches the given category. If no category is given, removes all creatures from the Cavern.
          @return : The number of creatures removed from the Cavern
                    NOTE: no pre-processing of the input string necessary, only uppercase input will match. If the input string does not match one of the expected category values, do not remove any creatures.
      */
      int releaseCreaturesOfCategory(const std::string& s = "ALL");

      /**
        * @post    : Outputs a report of the creatures currently in the Cavern in the form:
                    "UNKNOWN: [x]\nUNDEAD: [x]\nMYSTICAL: [x]\nALIEN: [x]\n\nAVERAGE LEVEL: [x]\nTAME:[x]%\n"
                    Note that the average level should be rounded to the NEAREST integer, and the percentage of tame creatures in the Cavern should be rounded to 2 decimal places.

                    Example output: 
                    UNKNOWN: 1
                    UNDEAD: 3
                    MYSTICAL: 2
                    ALIEN: 1

                    AVERAGE LEVEL: 5
                    TAME: 85.72%
      */
      void cavernReport() const;

    /**
        @post: For every creature in the cavern, displays each creature's information
    */
    void displayCreatures() const;

    /**
        @param: a string reference to a category
        @post: For every creature in the cavern of the given category (only exact matches to the input string), displays each creature's information

    */
    void displayCategory(const std::string& category) const;

    /**
        @post: Every creature in the cavern eats a MycoMorsel.
    */
    void mycoMorselFeast();


    /**
      * @post: Stores the ALIEN Creatures of highest level in the cavern's alien stack, in the order in which they appear in the Cavern (i.e., starting from index 0 in items_, thus, if the highest level is 5 and there are 3 ALIEN creatures with level 5, the one with lowest index in items_ is at the bottom of the stack and the one with highest index in item_ is at the top of the stack, with a total of 3 ALIEN Creatures on the stack)

      *      : Empty the stack before beginning.
      */
    void initializeAlienStack();

    /**
      * @post: Stores the UNDEAD Creatures of highest level in the cavern's undead stack, in the order in which they appear in the Cavern (i.e., starting from index 0 in items_, thus, if the highest level is 5 and there are 3 UNDEAD creatures with level 5, the one with lowest index in items_ is at the bottom of the stack and the one with highest index in item_ is at the top of the stack, with a total of 3 UNDEAD Creatures on the stack)
            : Empty the stack before beginning.
      */
    void initializeUndeadStack();

    /**
      * @post: Stores the MYSTICAL Creatures of highest level in the cavern's mystical stack, in the order in which they appear in the Cavern (i.e., starting from index 0 in items_, thus, if the highest level is 5 and there are 3 MYSTICAL creatures with level 5, the one with lowest index in items_ is at the bottom of the stack and the one with highest index in item_ is at the top of the stack, with a total of 3 MYSTICAL Creatures on the stack)
      *      : Empty the stack before beginning.
      */
    void initializeMysticalStack();

    /**
      * @post: Stores the UNKNOWN Creatures of highest level in the cavern's unknown stack, in the order in which they appear in the Cavern (i.e., starting from index 0 in items_, thus, if the highest level is 5 and there are 3 UNKNOWN creatures with level 5, the one with lowest index in items_ is at the bottom of the stack and the one with highest index in item_ is at the top of the stack, with a total of 3 UNKNOWN Creatures on the stack)
      *      : Empty the stack before beginning.
      */
    void initializeUnknownStack();

    /**
      * @return: A copy of the stack of highest level Aliens in the cavern
      */ 
    std::stack<Creature*> getAlienStack() const;

    /**
      * @return: A copy of the stack of highest level Undeads in the cavern
      */
    std::stack<Creature*> getUndeadStack() const;

    /**
      * @return: A copy of the stack of highest level Mysticals in the cavern
      */
    std::stack<Creature*> getMysticalStack() const;

    /**
      * @return: A copy of the stack of highest level Unknowns in the cavern
      */
    std::stack<Creature*> getUnknownStack() const;

    /**
      * @post: clears the stack of highest level Aliens in the cavern
      */ 
    void clearAlienStack();

    /**
      * @post: clears the stack of highest level Undeads in the cavern
      */
    void clearUndeadStack();

    /**
      * @post: clears the stack of highest level Mysticals in the cavern
      */
    void clearMysticalStack();

    /**
      * @post: clears the stack of highest level Unknowns in the cavern 
      */
    void clearUnknownStack();

    /**
      * @param: A stack of creature pointers 
      * @pre:   All the creature on the input stack are of same category and same (highest) level
      * @post:  For each creature in the stack, rebuild the Cavern's appropriate stack. (For example, if the creatures given are of category ALIEN, this function should build the Cavern's Alien stack.)
      *        Clear the Cavern's stack of the given category before adding the creatures to the stack.
      *        Before adding each creature to the Cavern's stack, prompt the user to select 2 attacks for the creature.
      *        Preserve the order of the creatures in the stack given. (E.g. The creature at the top of the given stack should also become the creature at the top of the Cavern's stack)
      *        If the input is invalid (valid inputs will be 1,2 or 3 only), keep prompting for a non-negative number that is within range, by printing "INVALID INPUT. TRY AGAIN.\n" and prompt for input again.
      *        When a valid action is read, it is passed to the creature's addAttack function to add the corresponding attack to the creature's attack queue.
      *        Prompting for attacks should be done in the following form (hint: use the creature's displayAttacks function):
      *        SELECT 2 ATTACKS FOR [CREATURE NAME] 
               [[CREATURE TYPE]] Choose an attack (1-3):
      *        1: [ATTACK 1 NAME]\t\t2: [ATTACK 2 NAME]\t\t3: [ATTACK 3 NAME]
               [user input]
      *        [[CREATURE TYPE]] Choose an attack (1-3):
      *        1: [ATTACK 1 NAME]\t\t2: [ATTACK 2 NAME]\t\t3: [ATTACK 3 NAME]
    */
    void setAttacks(std::stack<Creature*> s);


  private:
    // An integer sum of the levels of all the creatures currently in the Cavern
    int level_sum_;
    // An integer count of all the creatures currently in the Cavern that are tame
    int tame_count_;
    std::stack<Creature*> alien_stack;
    std::stack<Creature*> undead_stack;
    std::stack<Creature*> mystical_stack;
    std::stack<Creature*> unknown_stack;

    /*
        @param The type of creature to initialize the stack of
        @post Stores the `kind` Creatures of highest level in the cavern's corresponding stack, in the order in which they appear in the Cavern (i.e. starting from index 0 in items_, thus, if the highest level is 5 and there are 3 `kind` creatures with level 5, the one with lowest index in items_ is at the bottom of the stack and the one with the highest index in item_ is at the top of the stack with a total of 3 `kind` creatures on the stack)
            : Empties the stack before beginning
    */
    void initializeStack(Creature::Category kind);

};
#endif
