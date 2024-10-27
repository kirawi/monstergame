#include "Dragon.hpp"
#include <stdexcept>

/**
    Default constructor.
    Default-initializes all private members. 
    Default Category: MYSTICAL
    Default element: NONE
    Default number of head(s): 1
    Booleans are default-initialized to False. 
*/
Dragon::Dragon() : Creature() {
    setCategory(Category::MYSTICAL);
    heads_ = 1;
    type_ = Element::NONE;
    can_fly_ = false;
}

/**
    Parameterized constructor.
    @param      : The name of the Dragon (a reference to string)
    @param      : The category of the Dragon (a Category enum) with default value MYSTICAL
    @param      : The Dragon's hitpoints (an integer), with default value 1 if not provided, or if the value provided is 0 or negative
    @param      : The Dragon's level (an integer), with default value 1 if not provided, or if the value provided is 0 or negative
    @param      : A flag indicating whether the Dragon is tame, with default value False
    @param      : The element (an Element enum), with default value NONE if not provided
    @param      : The number of heads (an integer), with default value 1 if not provided, or if the value provided is 0 or negative
    @param      : A flag indicating whether the Dragon can fly, with default value False
    @post       : The private members are set to the values of the corresponding parameters.
    Hint: Notice the default arguments in the parameterized constructor.
*/
Dragon::Dragon(const std::string& name, Category c, int hp, int lvl, bool is_tame, Element element, int heads, bool fly) : Creature(name, c, hp, lvl, is_tame), type_(element), can_fly_(fly) {
    if (!setNumberOfHeads(heads)) {
        heads_ = 1;
    }
}

/**
    Getter for the element.
    @return     : The element (a string representation of the Element enum)
*/
std::string Dragon::getElement() const {
    switch (type_) {
        case NONE:
            return "NONE";
        case FIRE:
            return "FIRE";
        case WATER:
            return "WATER";
        case EARTH:
            return "EARTH";
        case AIR:
            return "AIR";
    }
}

/**
    Setter for the element.
    @param      : A reference to the element (an Element enum)
    @post       : The element is set to the value of the parameter.
*/
bool Dragon::setElement(const Element& e) {
    type_ = e;
    return true;
}

/**
    Getter for the number of heads.
    @return     : The number of heads (an integer)
*/
int Dragon::getNumberOfHeads() const {
    return heads_;
}

/**
    Setter for the number of heads.
    @param      : A reference to the number of heads (an integer)
    @pre        : The number of heads is > 0. Do nothing for invalid values.
    @post       : The number of heads is set to the value of the parameter.
    @return     : True if the number of heads is set, false otherwise.
*/
bool Dragon::setNumberOfHeads(const int& heads) {
    if (heads > 0) {
        heads_ = heads;
        return true;
    }
    return false;
}

/**
    Getter for the flight flag.
    @return     : The flight flag (a boolean)
*/
bool Dragon::getFlight() const {
    return can_fly_;
}

/**
    Setter for the flight flag.
    @param      : A reference to the flight flag (a boolean)
    @post       : The flight flag is set to the value of the parameter.
*/
bool Dragon::setFlight(const bool& fly) {
    can_fly_ = fly;
    return true;
}

 /**
    @post     : displays Dragon data in the form:
    "NAME: [NAME]\n
    CATEGORY: [CATEGORY]\n
    HP: [Hitpoints]\n
    LVL: [LEVEL]\n
    TAME: [TRUE/FALSE]
    ELEMENT: [ELEMENT]\n
    HEADS: [NUMBER OF HEADS]\n
    FLIGHT: [FLIGHT]\n"
*/
void Dragon::display() const {
    std::cout << "NAME: " << getName() << std::endl;
    std::cout << "CATEGORY: " << getCategory() << std::endl;
    std::cout << "HP: " << getHitpoints() << std::endl;
    std::cout << "LVL: " << getLevel() << std::endl;
    std::cout << "TAME: " << (isTame() ? "TRUE" : "FALSE") << std::endl;
    std::cout << "ELEMENT: " << getElement() << std::endl;
    std::cout << "HEADS: " << heads_ << std::endl;
    std::cout << "FLIGHT: " << (can_fly_ ? "TRUE" : "FALSE") << std::endl;
}


/**
    @post   : If the creature is UNDEAD, it becomes tame if not already, as it appreciates the gesture, even though as an UNDEAD it does not really eat. 
              It gains 1 hitpoint from the mysterious powers it receives by wearing the mushroom as a hat. Nothing else happens.
              If the creature is an ALIEN, it consumes the mushroom and gains 1 additional hitpoint. Nothing else happens.
              If the creature is MYSTICAL, it consumes the mushroom and gains 1 additional hitpoint if it has FIRE or EARTH affinity (Either by cooking the mushroom first, or by being fungi-tolerant). Nothing else happens.
              But if it is MYSTICAL and has WATER, AIR, or no affinity, if it only has 1 hitpoint left, it doesn't want to risk it and leaves the Cavern. If it has more than 1 hitpoint, it loses 1 hitpoint and becomes untamed if it was tame. Nothing else happens.
    @return : true if the creature leaves the Cavern, false otherwise
*/
bool Dragon::eatMycoMorsel() {
    if (getCategory() == "UNDEAD") {
        setTame(true);
        setHitpoints(getHitpoints() + 1);
    } else if (getCategory() == "ALIEN") {
        setHitpoints(getHitpoints() + 1);
    } else if (getCategory() == "MYSTICAL") {
        if (getElement() == "FIRE" || getElement() == "EARTH") {
            setHitpoints(getHitpoints() + 1);
        } else if (getHitpoints() == 1) {
            return true;
        } else {
            setHitpoints(getHitpoints() - 1);
            setTame(false);
        }
    }
    return false;
}

/**
  * @param: A const reference to int corresponding to the attack to be added to the attack queue.
  * @post: Adds an attack to the attack queue based on the int parameter.
  * Here are the attacks for the Dragon:

* 1: Attack name: BITE
*      if ALIEN: 4 PHYSICAL
*      if MYSTICAL: 2 PHYSICAL, and additional damage of 1 [FIRE/WATER/EARTH/AIR] if the Dragon has an elemental affinity of FIRE, WATER, EARTH, or AIR)
*      if UNDEAD: 2 PHYSICAL, 1 POISON
*      if UNKNOWN: 2 PHYSICAL

* 2: Attack name: STOMP
*      if ALIEN: 2 PHYSICAL
*      if MYSTICAL: 1 PHYSICAL, and additional damage of 1 [FIRE/WATER/EARTH/AIR] if the Dragon has an elemental affinity of FIRE, WATER, EARTH, or AIR)
*      if UNDEAD: 1 PHYSICAL, 1 POISON
*      if UNKNOWN: 1 PHYSICAL

* 3: Attack name: [ELEMENTAL BREATH/BAD BREATH], where the name is ELEMENTAL BREATH if the Dragon has an elemental affinity, otherwise it is BAD BREATH
*      if ALIEN: 6 [POISON/FIRE/WATER/EARTH/AIR], where the damage type is the Dragon's elemental affinity if it has one, otherwise it is POISON
*      if MYSTICAL: 3 [POISON/FIRE/WATER/EARTH/AIR], where the damage type is the Dragon's elemental affinity if it has one, otherwise it is POISON
*      if UNDEAD: 3 [POISON/FIRE/WATER/EARTH/AIR], 1 POISON. The damage types and amount are added to the vector as two separate entries, even if both entries are POISON type.
*      if UNKNOWN: 3 [POISON/FIRE/WATER/EARTH/AIR] where the damage type is the Dragon's elemental affinity if it has one, otherwise it is POISON  
*/
void Dragon::addAttack(const int& kind) {
    // Nested switch: first switch is for category of attack, while the second switch is for the attack based
    // on some characteristic
    Attack a;
    switch (kind) {
        // Attack "BITE"
        case 1: {
            a.name_ = "BITE";

            // Per category attacks
            switch (getEnumCategory()) {
                case ALIEN: {
                    a.type_ = { "PHYSICAL" };
                    a.damage_ = { 4 };
                    break;
                }
                case MYSTICAL: {
                    a.type_ = { "PHYSICAL"};
                    a.damage_ = { 2 };

                    // Extra elemental damage
                    if (element_ != Element::NONE) {
                        a.type_.push_back(getElement());
                        a.damage_.push_back(1);
                    }
                    break;
                }
                case UNDEAD: {
                    a.type_ = {"PHYSICAL", "POISON"};
                    a.damage_ = {2, 1};
                    break;
                }
                case UNKNOWN: {
                    a.type_ = {"PHYSICAL"};
                    a.damage_ = {2};
                    break;
                }
            }
            break;
        }
        // STOMP
        case 2: {
            a.name_ = "STOMP";

            // Per category attacks
            switch (getEnumCategory()) {
                case ALIEN: {
                    a.type_ = { "PHYSICAL" };
                    a.damage_ = { 2};
                    break;
                }
                case MYSTICAL: {
                    a.type_ = { "PHYSICAL"};
                    a.damage_ = { 1 };

                    // Extra elemental damage
                    if (element_ != Element::NONE) {
                        a.type_.push_back(getElement());
                        a.damage_.push_back(1);
                    }
                    break;
                }
                case UNDEAD: {
                    a.type_ = {"PHYSICAL", "POISON"};
                    a.damage_ = {1, 1};
                    break;
                }
                case UNKNOWN: {
                    a.type_ = {"PHYSICAL"};
                    a.damage_ = {1};
                    break;
                }
            }
            break;
        }
        // `element_` BREATH
        case 3: {
            if (element_ == Element::NONE) {
                a.name_ = "BAD BREATH";
                // Poison by default
                a.type_ = { "POISON" };
            } else {
                a.name_ = "ELEMENTAL BREATH";
                a.type_ = { getElement() };
            }

            // Per category attacks
            switch (getEnumCategory()) {
                case ALIEN: 
                    a.damage_ = { 6 };
                    break;
                case MYSTICAL: 
                    a.damage_ = { 3 };
                    break;
                case UNDEAD: {
                    a.type_.push_back("POISON");
                    a.damage_ = { 3, 1 };
                    break;
                }
                case UNKNOWN: 
                    a.damage_ = { 3 };
                    break;
            }
            break;
        }
        default: {
            // Invalid attack!
            throw std::invalid_argument("Invalid attack kind!: {" + std::to_string(kind) + "}");
        }
    }
    Creature::addAttack(a);
}

/**
  * @post:  displays the attacks of the Dragon in the form:
  *        [DRAGON] Choose an attack (1-3):\n1: BITE\t\t2: STOMP\t\t3: ELEMENTAL BREATH\n
  */
void Dragon::displayAttacks() const {
    std::cout << "[DRAGON] Choose an attack (1-3):\n1: BITE\t\t2: STOMP\t\t3: ELEMENTAL BREATH\n";
}
