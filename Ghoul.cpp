#include "Ghoul.hpp"

/**
  Default constructor.
  Default-initializes all private members. 
  Default Category: UNDEAD
  Default decay: 0
  Default faction: NONE
  Booleans are default-initialized to False.         */
Ghoul::Ghoul() : Creature() {
    setCategory(Category::UNDEAD);
    decay_ = 0;
    faction_ = Faction::NONE;
}

/**
    Parameterized constructor.
    @param      : The name of the Ghoul (a reference to string)
    @param      : The category of the Ghoul (a Category enum) with default value UNDEAD
    @param      : The Ghoul's hitpoints (an integer), with default value 1 if not provided, or if the value provided is 0 or negative
    @param      : The Ghoul's level (an integer), with default value 1 if not provided, or if the value provided is 0 or negative
    @param      : A flag indicating whether the Ghoul is tame, with default value False
    @param      : The level of decay (an integer), with default value 0 if not provided, or if the value provided is negative
    @param      : The faction (a Faction enum), with default value NONE if not provided
    @param      : A flag indicating whether the Ghoul can transform, with default value False
    @post       : The private members are set to the values of the corresponding parameters.
    Hint: Notice the default arguments in the parameterized constructor.
*/
Ghoul::Ghoul(const std::string& name, Category c, int hp, int lvl, bool is_tame, int decay, Faction faction, bool transform) : Creature(name, c, hp, lvl, is_tame), faction_(faction), can_transform_(transform) {
    if (!setDecay(decay)) {
        decay_ = 0;
    }
}

/**
    Getter for the faction.
    @return     : The faction (a string representation of the Faction enum)
*/
std::string Ghoul::getFaction() const {
    switch (faction_) {
        case NONE:
            return "NONE";
        case FLESHGORGER:
            return "FLESHGORGER";
        case SHADOWSTALKER:
            return "SHADOWSTALKER";
        case PLAGUEWEAVER:
            return "PLAGUEWEAVER";
    }
}

/**
    Setter for the faction.
    @param      : A reference to the faction (an Faction enum)
    @post       : The faction is set to the value of the parameter.
*/
bool Ghoul::setFaction(const Faction& f) {
    faction_ = f;
    return true;
}

/**
    Getter for the level of decay.
    @return     : The level of decay (an integer)
*/
int Ghoul::getDecay() const {
    return decay_;
}

/**
    Setter for the level of decay.
    @param      : A reference to the level of decay (an integer)
    @pre        : The level of decay must be >= 0 (do nothing otherwise)
    @post       : The level of decay is set to the value of the parameter.
    @return     : True if the number of decay is set, false otherwise.
*/
bool Ghoul::setDecay(const int& decay) {
    if (decay >= 0) {
        decay_ = decay;
        return true;
    }
    return false;
}

/**
    Getter for the transformation.
    @return     : The transformation (a boolean)
*/
bool Ghoul::getTransformation() const {
    return can_transform_;
}

/**
    Setter for the transformation.
    @param      : A reference to the tranfsormation (a boolean)
    @post       : The transformation is set to the value of the parameter.
*/
bool Ghoul::setTransformation(const bool& transform) {
    can_transform_ = transform;
    return true;
}

 /**
    @post     : displays Ghoul data in the form:
    "NAME: [NAME]\n
    CATEGORY: [CATEGORY]\n
    HP: [Hitpoints]\n
    LVL: [LEVEL]\n
    TAME: [TRUE/FALSE]"   
    DECAY: [DECAY]\n
    FACTION: [FACTION]\n
    TRANSFORM: [TRANSFORM]\n
*/
void Ghoul::display() const {
    std::cout << "NAME: " << getName() << std::endl;
    std::cout << "CATEGORY: " << getCategory() << std::endl;
    std::cout << "HP: " << getHitpoints() << std::endl;
    std::cout << "LVL: " << getLevel() << std::endl;
    std::cout << "TAME: " << (isTame() ? "TRUE" : "FALSE") << std::endl;
    std::cout << "DECAY: " << decay_ << std::endl;
    std::cout << "FACTION: " << getFaction() << std::endl;
    std::cout << "TRANSFORM: " << (can_transform_ ? "TRUE" : "FALSE") << std::endl;
}

/**
    @post   : If the creature is UNDEAD, it becomes tame if not already, as it appreciates the gesture, even though as an UNDEAD it does not really eat. It gains 1 hitpoint from the mysterious powers it receives by wearing the mushroom as a hat. Nothing else happens.
              If the creature is of Faction FLESHGORGER, it becomes so offended by being offered a mushroom that it becomes untamed if it was tame. If it was already untamed, it leaves the Cavern. Nothing else happens.
              If the creature was of Faction SHADOWSTALKER, if it was untame, it hides from the mushroom and nothing happens. If it was tame, it eats the mushroom and loses 1 hitpoint, unless it only had 1 hitpoint left in which case it stays at 1 hitpoint but becomes untame. Nothing else happens.
    @return   : true if the creature leaves the Cavern, false otherwise
*/
bool Ghoul::eatMycoMorsel() {
    // Order of if statements follows post
    if (getCategory() == "UNDEAD") {
        setTame(true);
        setHitpoints(getHitpoints() + 1);
        return false;
    }

    if (getFaction() == "FLESHGORGER") {
        // Leave if not already tamed
        if (!isTame()) {
            return true;
        }
        setTame(false);
    } else if (getFaction() == "SHADOWSTALKER" && isTame()) {
        if (getHitpoints() == 1) {
            setTame(false);
        } else {
            setHitpoints(getHitpoints() - 1);
        }
    }
    return false;
}
:w
/**
* @param: A const reference to int corresponding to the attack to be added to the attack queue.
* @post: Adds an attack to the attack queue based on the int parameter.
* Here are the attacks for the Ghoul:
* 
* 1: Attack name: BITE
*   if ALIEN: 4 PHYSICAL
*   if MYSTICAL: 
*      if FLESHGORGER: 2 PHYSICAL
*      if SHADOWSTALKER: 2 PHYSICAL, 1 VOID
*      if PLAGUEWEAVER: 2 PHYSICAL, 1 POISON
*      if NONE: 2 PHYSICAL
*  if UNDEAD: 2 PHYSICAL, 1 POISON
*  if UNKNOWN: 2 PHYSICAL
* 
* 2: 
*  if FLESHGORGER/NONE: 
*      Attack name: CLAW
*      2 PHYSICAL
*  if SHADOWSTALKER:
*     Attack name: SLASH
*     2 PHYSICAL, 1 VOID
* if PLAGUEWEAVER:
*    Attack name: INFECT
*    2 PHYSICAL, 1 POISON
* 
* 3:
*  if FLESHGORGER/NONE:
*     Attack name: FLY SWARM
*     3 PHYSICAL
* if SHADOWSTALKER:
*     Attack name: SHROUD OF DARKNESS
*     2 PHYSICAL, 1 VOID
* if PLAGUEWEAVER:
*     Attack name: PLAGUE CLOUD
*     2 PHYSICAL, 1 POISON
*  
*/
void Ghoul::addAttack(const int& kind) {
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
                    a.type_ = { "PHYSICAL" };
                    a.damage_ = { 2 };

                    // Extra faction damage
                    switch (faction_) {
                        case SHADOWSTALKER: {
                            a.type_.push_back("VOID");
                            a.damage_.push_back(1);
                            break;
                        }
                        case PLAGUEWEAVER: {
                            a.type_.push_back("POISON");
                            a.damage_.push_back(1);
                            break;
                        }
                        default: break;
                    }
                    break;
                }
                case UNDEAD: {
                    a.type_ = { "PHYSICAL", "POISON" };
                    a.damage_ = { 2, 1 };
                    break;
                }
                case UNKNOWN: {
                    a.type_ = { "PHYSICAL" };
                    a.damage_ = { 2 };
                    break;
                }
            }
            break;
        }
        // CLAW
        case 2: {
            switch (faction_) {
                case SHADOWSTALKER : {
                    a.name_ = "SLASH";
                    a.type_ = { "PHYSICAL", "VOID" };
                    a.damage_ = { 2, 1 };
                    break;
                }
                case PLAGUEWEAVER: {
                    a.name_ = "INFECT";
                    a.type_ = { "PHYSICAL", "POISON" };
                    a.damage_ = { 2, 1 };
                    break;
                }
                default: {
                    a.name_ = "CLAW";
                    a.type_ = { "PHYSICAL" };
                    a.damage_ = { 2};
                    break;
                }
            }
            break;
        }
        // Cloud
        case 3: {
            switch (faction_) {
                case SHADOWSTALKER : {
                    a.name_ = "SHROUD OF DARKNESS";
                    a.type_ = { "PHYSICAL", "VOID" };
                    a.damage_ = { 2, 1 };
                    break;
                }
                case PLAGUEWEAVER: {
                    a.name_ = "PLAGUE CLOUD";
                    a.type_ = { "PHYSICAL", "POISON" };
                    a.damage_ = { 2, 1 };
                    break;
                }
                default: {
                    a.name_ = "FLY SWARM";
                    a.type_ = { "PHYSICAL" };
                    a.damage_ = { 3 };
                    break;
                }
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
  @post     : displays the attacks of the Ghoul in the form:
  [GHOUL] Choose an attack (1-3):\n1: BITE\t\t2: CLAW\t\t3: CLOUD OF DOOM\n
*/
void Ghoul::displayAttacks() const {
    std::cout << "[GHOUL] Choose an attack (1-3):\n1: BITE\t\t2: CLAW\t\t3: CLOUD OF DOOM\n";
}
