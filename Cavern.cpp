#include "Cavern.hpp"
#include <algorithm>
#include <optional>
#include <stdexcept>


/**
    Default constructor.
    Default-initializes all private members. 
*/
Cavern::Cavern() : level_sum_(0), tame_count_(0), ArrayBag<Creature>() {}
 /** 
  * @param   :   A reference to a Creature entering the Cavern
  * @post    :   If the given Creature is not already in the Cavern, add Creature to the Cavern and updates the level sum and the tame Creature count if the creature is tame.
  * @return  :   returns true if a Creature was successfully added to the Cavern, false otherwise
            :   Hint: Use the above definition of equality will help determine if a Creature is already in the Cavern
**/
bool Cavern::enterCavern(const Creature& c) {
    if (!ArrayBag<Creature>::contains(c) && ArrayBag<Creature>::add(c)) {
        level_sum_ += c.getLevel();
        tame_count_ += c.isTame();
        return true;
    } else {
        return false;
    }
}

/** 
  * @param   :   A  reference to a Creature leaving the Cavern
  * @return  :  returns true if a creature was successfully removed from the Cavern (i.e. items_), false otherwise
  * @post    :    removes the creature from the Cavern and updates the level sum. 
                  If the Creature is tame it also updates the tame count.
**/
bool Cavern::exitCavern(const Creature& c) {
    if (ArrayBag<Creature>::remove(c)) {
        level_sum_ -= c.getLevel();
        tame_count_ -= c.isTame();
        return true;
    } else {
        return false;
    }
}

 /** 
  * @return   :  The integer level count of all the creatures currently in the Cavern
  **/
int Cavern::getLevelSum() const {
    return level_sum_;
}

/**
  * @return   :  The average level (int) of all the creatures in the Cavern
  * @post     :  Computes the average level (double) of the Cavern rounded to the NEAREST integer.
  **/
int Cavern::calculateAvgLevel() const {
    return level_sum_ / std::max(1, ArrayBag<Creature>::getCurrentSize());
}

/**
  * @return   :  The integer count of tame Creatures in the Cavern
  **/
int Cavern::getTameCount() const {
    return tame_count_;
}

/**
  * @return   :  The percentage (double) of all the tame creatures in the Cavern
  * @post     :   Computes the percentage of tame creatures in the Cavern rounded up to 2 decimal places.
  **/
double Cavern::calculateTamePercentage() const {
    double n = 10000 * static_cast<double>(tame_count_) / std::max(1, ArrayBag<Creature>::getCurrentSize());
    return std::ceil(n) / 100;
}

/**
  * @param  :   A reference to a string representing a creature Category with value in ["UNKNOWN", "UNDEAD", "MYSTICAL", "ALIEN"]
  * @return  :  An integer tally of the number of creatures in the Cavern of the given category. 
              If the argument string does not match one of the expected category values, the tally is zero. 
              NOTE: no pre-processing of the input string necessary, only uppercase input will match.
**/
int Cavern::tallyCategory(const std::string& s) const {
    size_t sum = 0;
    for (size_t i = 0; i < ArrayBag<Creature>::getCurrentSize(); i++) {
        if (ArrayBag<Creature>::items_[i].getCategory() == s) {
            sum++;
        }
    }
    return sum;
}

/**
    @param  :   An integer representing the level threshold of the creatures to be removed from the Cavern, with default value 0
    @post   :   Removes all creatures from the Cavern whose level is less than the given level. If no level is given, removes all creatures from the Cavern. Ignore negative input.
    @return :   The number of creatures removed from the Cavern
*/
int Cavern::releaseCreaturesBelowLevel(int n) {
    n = std::max(n, 0);

    size_t removed = 0;
    for (size_t i = 0; i < ArrayBag<Creature>::getCurrentSize();) {
        if (ArrayBag<Creature>::items_[i].getLevel() < n) {
            removed += ArrayBag<Creature>::remove(ArrayBag<Creature>::items_[i]);
        } else {
            i++;
        }
    }
    return removed;
}

/**
    @param  : A reference to a string representing a creature Category with a value in ["UNKNOWN", "UNDEAD", "MYSTICAL", "ALIEN"], or default value "ALL" if no category is given
    @post   : Removes all creatures from the Cavern whose category matches the given category. If no category is given, removes all creatures from the Cavern.
    @return : The number of creatures removed from the Cavern
              NOTE: no pre-processing of the input string necessary, only uppercase input will match. If the input string does not match one of the expected category values, do not remove any creatures.
*/
int Cavern::releaseCreaturesOfCategory(const std::string& s) {
    if (s == "ALL") {
        int n = ArrayBag<Creature>::getCurrentSize();
        ArrayBag<Creature>::clear();
        return n;
    }

    size_t removed = 0;
    for (size_t i = 0; i < ArrayBag<Creature>::getCurrentSize();) {
        if (ArrayBag<Creature>::items_[i].getCategory() == s) {
            removed += ArrayBag<Creature>::remove(ArrayBag<Creature>::items_[i]);
        } else {
            i++;
        }
    }
    return removed;
    
}

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
void Cavern::cavernReport() const {
    std::cout << "UNKNOWN: " << tallyCategory("UNKNOWN")
                << "\nUNDEAD: " << tallyCategory("UNDEAD")
                << "\nMYSTICAL: " << tallyCategory("MYSTICAL")
                << "\nALIEN: " << tallyCategory("ALIEN")
                << "\n\nAverage LEVEL: " << calculateAvgLevel()
                << "\nTAME: " << calculateTamePercentage()
                << "%\n";
}


/**
@post: For every creature in the cavern, displays each creature's information
*/
void Cavern::displayCreatures() const {
    for (size_t i = 0; i < getCurrentSize(); i++) {
        items_[i]->display();
    }
}

/**
@param: a string reference to a category
@post: For every creature in the cavern of the given category (only exact matches to the input string), displays each creature's information

*/
void Cavern::displayCategory(const std::string& category) const {
    for (size_t i = 0; i < getCurrentSize(); i++) {
        if (items_[i]->getCategory() == category) {
            items_[i]->display();
        }
    }
}

/**
@post: Every creature in the cavern eats a MycoMorsel.
*/
void Cavern::mycoMorselFeast() {
    for (size_t i = 0; i < getCurrentSize(); i++) {
        items_[i]->eatMycoMorsel();
    }
}
/*
    @param The category of creature to initialize the stack of
    @post Stores the `kind` Creatures of highest level in the cavern's corresponding stack, in the order in which they appear in the Cavern (i.e. starting from index 0 in items_, thus, if the highest level is 5 and there are 3 `kind` creatures with level 5, the one with lowest index in items_ is at the bottom of the stack and the one with the highest index in item_ is at the top of the stack with a total of 3 `kind` creatures on the stack)
        : Empties the stack before beginning
*/
void Cavern::initializeStack(Creature::Category kind) {
    // Get the highest level for that creature
    int max_level = 0;
    for (int i = 0; i < ArrayBag::item_count_; i++) {
        Creature* c = ArrayBag::items_[i];
        if (c->getEnumCategory() == kind && c->getLevel() > max_level) {
            max_level = c->getLevel();
        }
    }

    // Only push the highest level creatures to the corresponding stack
    std::stack<Creature*> s;
    for (int i = 0; i < ArrayBag::item_count_; i++) {
        Creature* c = ArrayBag::items_[i];
        if (c->getEnumCategory() == kind && c->getLevel() == max_level) {
            s.push(c);
        }
    }

    // Empty stack and update
    switch (kind) {
        case Creature::Category::UNKNOWN: {
            unknown_stack.swap(s);
            break;
        }
        case Creature::Category::UNDEAD: {
            undead_stack.swap(s);
            break;
        }
        case Creature::Category::MYSTICAL: {
            mystical_stack.swap(s);
            break;
        }
        case Creature::Category::ALIEN: {
            alien_stack.swap(s);
            break;
        }
    }
}

/**
  * @post: Stores the ALIEN Creatures of highest level in the cavern's alien stack, in the order in which they appear in the Cavern (i.e., starting from index 0 in items_, thus, if the highest level is 5 and there are 3 ALIEN creatures with level 5, the one with lowest index in items_ is at the bottom of the stack and the one with highest index in item_ is at the top of the stack, with a total of 3 ALIEN Creatures on the stack)

  *      : Empty the stack before beginning.
  */
void Cavern::initializeAlienStack() {
    initializeStack(Creature::Category::ALIEN);
}

/**
  * @post: Stores the UNDEAD Creatures of highest level in the cavern's undead stack, in the order in which they appear in the Cavern (i.e., starting from index 0 in items_, thus, if the highest level is 5 and there are 3 UNDEAD creatures with level 5, the one with lowest index in items_ is at the bottom of the stack and the one with highest index in item_ is at the top of the stack, with a total of 3 UNDEAD Creatures on the stack)
        : Empty the stack before beginning.
  */
void Cavern::initializeUndeadStack() {
    initializeStack(Creature::Category::UNDEAD);
    
}

/**
  * @post: Stores the MYSTICAL Creatures of highest level in the cavern's mystical stack, in the order in which they appear in the Cavern (i.e., starting from index 0 in items_, thus, if the highest level is 5 and there are 3 MYSTICAL creatures with level 5, the one with lowest index in items_ is at the bottom of the stack and the one with highest index in item_ is at the top of the stack, with a total of 3 MYSTICAL Creatures on the stack)
  *      : Empty the stack before beginning.
  */
void Cavern::initializeMysticalStack() {
    initializeStack(Creature::Category::MYSTICAL);
    
}

/**
  * @post: Stores the UNKNOWN Creatures of highest level in the cavern's unknown stack, in the order in which they appear in the Cavern (i.e., starting from index 0 in items_, thus, if the highest level is 5 and there are 3 UNKNOWN creatures with level 5, the one with lowest index in items_ is at the bottom of the stack and the one with highest index in item_ is at the top of the stack, with a total of 3 UNKNOWN Creatures on the stack)
  *      : Empty the stack before beginning.
  */
void Cavern::initializeUnknownStack() {
    initializeStack(Creature::Category::UNKNOWN);
    
}

/**
  * @return: A copy of the stack of highest level Aliens in the cavern
  */ 
std::stack<Creature*> Cavern::getAlienStack() const {
    return alien_stack;
}

/**
  * @return: A copy of the stack of highest level Undeads in the cavern
  */
std::stack<Creature*> Cavern::getUndeadStack() const {
    return undead_stack;
}

/**
  * @return: A copy of the stack of highest level Mysticals in the cavern
  */
std::stack<Creature*> Cavern::getMysticalStack() const {
    return mystical_stack;
}

/**
  * @return: A copy of the stack of highest level Unknowns in the cavern
  */
std::stack<Creature*> Cavern::getUnknownStack() const {
    return unknown_stack;
}

/**
  * @post: clears the stack of highest level Aliens in the cavern
  */ 
void Cavern::clearAlienStack() {
    std::stack<Creature*>().swap(alien_stack);
}

/**
  * @post: clears the stack of highest level Undeads in the cavern
  */
void Cavern::clearUndeadStack() {
    std::stack<Creature*>().swap(undead_stack);
}

/**
  * @post: clears the stack of highest level Mysticals in the cavern
  */
void Cavern::clearMysticalStack() {
    std::stack<Creature*>().swap(mystical_stack);
}

/**
  * @post: clears the stack of highest level Unknowns in the cavern 
  */
void Cavern::clearUnknownStack() {
    std::stack<Creature*>().swap(unknown_stack);
}

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
void Cavern::setAttacks(std::stack<Creature*> in) {
    // No valid resolution for this case
    if (in.empty()) {
        return;
    }

    // To preserve the order of the stack, we need to push to a vec first and then push those 
    // elements back->front to the result stack
    std::vector<Creature*> temp;
    Creature::Category category = in.top()->getEnumCategory();
    while (!in.empty()) {
        Creature* c = in.top();
        std::cout << "SELECT 2 ATTACKS FOR " + c->getName() + "\n";

        // Get 2 attacks
        for (size_t i = 0; i < 2; i++) {
            int choice = -1;
            c->displayAttacks();
            std::cin >> choice;

            // Handle invalid input
            while (!(1 <= choice && choice <= 3)) {
                std::cout << "INVALID INPUT. TRY AGAIN.\n";
                std::cin >> choice;
            }
            c->addAttack(choice);
        }

        // SAFETY: `c`'s data is cloned
        temp.push_back(c);
        in.pop();
    }

    std::stack<Creature*> res;
    while (!temp.empty()) {
        // SAFETY: element is cloned
        res.push(temp.back());
        temp.pop_back();
    }

    // Set stacks of corresponding stacks
    switch (category) {
        case Creature::UNKNOWN: 
            unknown_stack.swap(res);
            break;
        case Creature::UNDEAD: 
            undead_stack.swap(res);
            break;
        case Creature::MYSTICAL: 
            mystical_stack.swap(res);
            break;
        case Creature::ALIEN: 
            alien_stack.swap(res);
            break;
    }
}
