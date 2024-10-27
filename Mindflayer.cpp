#include "Mindflayer.hpp"
#include <algorithm>

/**
    Default constructor.
    Default-initializes all private members. 
    Default Category: ALIEN
    Default summoning: False
*/
Mindflayer::Mindflayer() : Creature() {
    setCategory(Category::ALIEN);
    summoning_ = false;
}

/**
    Parameterized constructor.
    @param      : A reference to the name of the Mindflayer (a string)
    @param      : The category of the Mindflayer (a Category enum) with default value ALIEN
    @param      : The Mindflayer's hitpoints (an integer), with default value 1 if not provided, or if the value provided is 0 or negative
    @param      : The Mindflayer's level (an integer), with default value 1 if not provided, or if the value provided is 0 or negative
    @param      : A flag indicating whether the Mindflayer is tame, with default value False
    @param      : The projectiles (a vector of Projectile structs), with default value an empty vector if not provided
    @param      : A flag indicating whether the Mindflayer can summon, with default value False
    @param      : The affinities (a vector of Variant enums), with default value an empty vector if not provided
    @post       : The private members are set to the values of the corresponding parameters.
    Hint: Notice the default arguments in the parameterized constructor.
*/
Mindflayer::Mindflayer(const std::string& name, Category c, int hp, int lvl, bool is_tame, std::vector<Projectile> projectiles, bool can_summon, std::vector<Variant> affinities) : Creature(name, c, hp, lvl, is_tame), summoning_(can_summon) {
    setProjectiles(projectiles);
    setAffinities(affinities);
}

/**
    Getter for the projectiles.
    @return     : The projectiles (a vector of Projectile structs)
*/
std::vector<Mindflayer::Projectile> Mindflayer::getProjectiles() const {
    return projectiles_;
}

/**
    Setter for the projectiles.
    @param      : A reference to the projectiles (a vector of Projectile structs)
    @post       : The projectiles are set to the value of the parameter. There should not be any duplicate projectiles in Mindflayer's projectiles vector.
    : For example, if the vector in the given parameter contains the following Projectiles: {{PSIONIC, 2}, {TELEPATHIC, 1}, {PSIONIC, 1}, {ILLUSIONARY, 3}}, 
    : the projectiles vector should be set to contain the following Projectiles: {{PSIONIC, 3}, {TELEPATHIC, 1}, {ILLUSIONARY, 3}}.
    : If the quantity of a projectile is 0 or negative, it should not be added to the projectiles vector. 
    : Note the order of the projectiles in the vector.
*/
bool Mindflayer::setProjectiles(const std::vector<Projectile>& projectiles) {
    std::vector<Projectile> res = getProjectiles();
    for (uint i = 0; i < projectiles.size(); i++) {
        if (projectiles[i].quantity_ <= 0) {
            continue;
        }
        bool add_element = true;

        // Exclude projectiles with dupe variants
        for (uint v = 0; v < res.size(); v++) {
            if (projectiles[i].type_ == res[v].type_) {
                res[v].quantity_ += projectiles[i].quantity_;
                add_element = false;
                break;
            }
        }

        if (add_element) {
            res.push_back(projectiles[i]);
        }
    }

    projectiles_ = res;
    return true;
}

/**
    Getter for the summoning.
    @return     : The summoning (a boolean)
*/
bool Mindflayer::getSummoning() const {
    return summoning_;
}

/**
    Setter for the summoning.
    @param      : A reference to the summoning (a boolean)
    @post       : The summoning is set to the value of the parameter.
*/
bool Mindflayer::setSummoning(const bool& summoning) {
    summoning_ = summoning;
    return true;
}

/**
    Getter for the affinities.
    @return     : The affinities (a vector of Variant enums)
*/
std::vector<Mindflayer::Variant> Mindflayer::getAffinities() const {
    return affinities_;
}

/**
    Setter for the affinities.
    @param      : A reference to the affinities (a vector of Variant enums)
    @post       : The affinities are set to the value of the parameter.
    : There should not be any duplicate affinities in Mindflayer's affinities vector. 
    : For example, if the vector in the given parameter contains the following affinities: {PSIONIC, TELEPATHIC, PSIONIC, ILLUSIONARY}, 
    : the affinities vector should be set to contain the following affinities: {PSIONIC, TELEPATHIC, ILLUSIONARY}.
    : Note the order of the affinities in the vector.
*/
bool Mindflayer::setAffinities(const std::vector<Variant>& affinities) {
    std::vector<Variant> res = getAffinities();
    for (uint i = 0; i < affinities.size(); i++) {
        bool add_element = true;

        // Exclude dupes
        for (uint v = 0; v < res.size(); v++) {
            if (affinities[i] == res[v]) {
                add_element = false;
                break;
            }
        }

        if (add_element) {
            res.push_back(affinities[i]);
        }
    }

    affinities_ = res;
    return true;
}

/**
    @param       : A reference to the Variant 
    @return      : The string representation of the variant
*/
std::string Mindflayer::variantToString(const Variant& var) const {
    switch (var) {
        case PSIONIC:
            return "PSIONIC";
        case TELEPATHIC:
            return "TELEPATHIC";
        case ILLUSIONARY:
            return "ILLUSIONARY";
    }
}

 /**
    @post     : displays Mindflayer data in the form:
    "NAME: [NAME]\n
    CATEGORY: [CATEGORY]\n
    HP: [Hitpoints]\n
    LVL: [LEVEL]\n
    TAME: [TRUE/FALSE]\n   
    SUMMONING: [SUMMONING]\n
    [Projectile 1]: [QUANTITY]\n
    Affinities: \n
    [Affinity 1]\n"
*/
void Mindflayer::display() const {
    std::cout << "NAME: " << getName() << std::endl;
    std::cout << "CATEGORY: " << getCategory() << std::endl;
    std::cout << "HP: " << getHitpoints() << std::endl;
    std::cout << "LVL: " << getLevel() << std::endl;
    std::cout << "TAME: " << (isTame() ? "TRUE" : "FALSE") << std::endl;
    std::cout << "SUMMONING: " << (getSummoning() ? "TRUE" : "FALSE") << std::endl;
    for (uint i = 0; i < getProjectiles().size(); i++) {
        std::cout << variantToString(getProjectiles()[i].type_) << ": " << std::to_string(getProjectiles()[i].quantity_) << std::endl;
    }
    if (getAffinities().size() != 0) {
        std::cout << "AFFINITIES: " << std::endl;
        for (uint i = 0; i < getAffinities().size(); i++) {
            std::cout << variantToString(getAffinities()[i]) << std::endl;
        }
    }
}


/**
    @param    : A reference to the variant to be searched for
    @return   : True if a match was found in the Mindflayer's affinities; else false
*/
bool Mindflayer::hasAffinity(const Variant& v) const {
    for (size_t i = 0; i < getAffinities().size(); i++) {
        if (getAffinities()[i] == v) {
            return true;
        }
    }
    return false;
}

/**
    @post: 
        If the creature is UNDEAD, it becomes tame if not already, as it appreciates the gesture, even though as an UNDEAD it does not really eat. It gains 1 hitpoint from the mysterious powers it receives by wearing the mushroom as a hat. Nothing else happens.
        If the creature is MYSTICAL, if it can summon a Thoughtspawn, it gives the mushroom to the Thoughtspawn instead. If it cannot summon a Thoughtspawn and is tame, it eats the mushroom to be polite. If it only had 1 hitpoint left, it remains at 1 hitpoint and becomes untame, else it loses 1 hitpoint. If it cannot summon a Thoughtspawn and is untame, it decides it doesn't have to deal with this and it leaves the Cavern. Nothing else happens.
        If the creature is an ALIEN, if it has Telepathic affinity, it convinces Selfa Ensert to eat the mushroom instead, and gains 1 hitpoint from laughing at their resulting illness (as laughter is the best medicine).
        If it is an ALIEN and does not have Telepathic affinity, but has a Telepathic projectile, it uses one of such projectile to achieve the same effect. (Remember to remove the projectile from the vector if it only had 1 left)
        If it is an ALIEN and does not have Telepathic affinity or a Telepathic projectile, it eats the mushroom and gains 2 hitpoints. As it turns out, the mushroom was good for it. It becomes tame if it was not already. Nothing else happens.
    @return   : true if the creature leaves the Cavern, false otherwise
*/
bool Mindflayer::eatMycoMorsel() {
    if (getCategory() == "UNDEAD") {
        setTame(true);
        setHitpoints(getHitpoints() + 1);
    } else if (getCategory() == "MYSTICAL" && !getSummoning()) {
        if (isTame()) {
            if (getHitpoints() == 1) {
                setTame(false);
            } else {
                setHitpoints(getHitpoints() - 1);
            }
        } else {
            return true;
        }
    } else if (getCategory() == "ALIEN") {
        if (hasAffinity(Variant::TELEPATHIC)) {
            setHitpoints(getHitpoints() + 1);
        } else {
            // Check if it has a telepathic projectile to fire
            for (size_t i = 0; i < projectiles_.size(); i++) {
                if (projectiles_[i].type_ == Variant::TELEPATHIC) {
                    setHitpoints(getHitpoints() + 1);

                    // Fire projectile; remove from list if it was the last one
                    if (projectiles_[i].quantity_ == 1) {
                        projectiles_.erase(projectiles_.begin() + i);
                    }  else {
                        projectiles_[i].quantity_ -= 1;
                    }
                    return false;
                } 
            }

            // Has no telepathic projectile nor affinity
            setHitpoints(getHitpoints() + 2);
            setTame(true);
        }
    }
    return false;
}
/**
* @param: A const reference to int corresponding to the attack to be added to the attack queue.
* @post: Adds an attack to the attack queue based on the int parameter.
* Here are the attacks for the Mindflayer:
*
* 1: PSIONIC BOLT/TENTACLE SLAP
*  If the Mindflayer has a PSIONIC projectile:
*      Attack name: PSIONIC BOLT
*      If the Mindflayer has a PSIONIC affinity:
*          Damage: 3 PSIONIC
*      Else:
*          Damage: 2 PSIONIC
* If the Mindflayer does not have a PSIONIC projectile:
*     Attack name: TENTACLE SLAP
*     Damage: 1 PHYSICAL, 1 EMOTIONAL
*
* 2: TELEPATHIC BOLT/TENTACLE SLAP
* If the Mindflayer has a TELEPATHIC projectile:
*      Attack name: TELEPATHIC BOLT
*      If the Mindflayer has a TELEPATHIC affinity:
*      Damage: 3 TELEPATHIC
*      Else:
*          Damage: 2 TELEPATHIC
* If the Mindflayer does not have a TELEPATHIC projectile:
*      Attack name: TENTACLE SLAP
*      Damage: 1 PHYSICAL, 1 EMOTIONAL
*
* 3: ILLUSIONARY BOLT/TENTACLE SLAP
* If the Mindflayer has an ILLUSIONARY projectile:
*      Attack name: ILLUSIONARY BOLT
*      If the Mindflayer has an ILLUSIONARY affinity:
*          Damage: 3 ILLUSIONARY
*      Else:
*          Damage: 2 ILLUSIONARY
* If the Mindflayer does not have an ILLUSIONARY projectile:
*      Attack name: TENTACLE SLAP
*      Damage: 1 PHYSICAL, 1 EMOTIONAL
* 
*/
void Mindflayer::addAttack(const int& kind) {
    // Nested: first switch is for category of attack, while the second `if` statements are for the attack based
    // on some characteristic
    Attack a;
    switch (kind) {
        // Psionic bolt
        case 1: {
            // Check if it has a psionic projectile
            const auto projectiles = getProjectiles();
            const bool has_psionic_proj = std::any_of(projectiles.begin(), projectiles.end(), [&](Projectile i) { return i.type_ == PSIONIC; });

            if (has_psionic_proj) {
                a.name_ = "PSIONIC BOLT";
                a.type_ = { "PSIONIC" };

                // Check if it has a psionic affinity
                const auto affinities = getAffinities();
                const bool has_psionic_aff = std::any_of(affinities.begin(), affinities.end(), [&](Variant i) { return i == PSIONIC; });
                if (has_psionic_aff) {
                    a.damage_ = { 3 };
                } else {
                    a.damage_ = { 2 };
                }
            } else {
                a.name_ = "TENTACLE SLAP";
                a.type_ = { "PHYSICAL", "EMOTIONAL" };
                a.damage_ = { 1, 1 };
            }
            break;
        }
        // Telepathic
        case 2: {
            // Check if it has a telepathic projectile
            const auto projectiles = getProjectiles();
            const bool has_tele_proj = std::any_of(projectiles.begin(), projectiles.end(), [&](Projectile i) { return i.type_ == TELEPATHIC; });

            if (has_tele_proj) {
                a.name_ = "TELEPATHIC BOLT";
                a.type_ = { "TELEPATHIC" };

                // Check if it has a telepathic affinity
                const auto affinities = getAffinities();
                const bool has_tele_aff = std::any_of(affinities.begin(), affinities.end(), [&](Variant i) { return i == TELEPATHIC; }); 
                if (has_tele_aff) {
                    a.damage_ = { 3 };
                } else {
                    a.damage_ = { 2 };
                }
            } else {
                a.name_ = "TENTACLE SLAP";
                a.type_ = { "PHYSICAL", "EMOTIONAL" };
                a.damage_ = { 1, 1 };
            }
            break;
        }
        // Illusoinary
        case 3: {
            // Check if it has a illusionary projectile
            const auto projectiles = getProjectiles();
            const bool has_illus_proj = std::any_of(projectiles.begin(), projectiles.end(), [&](Projectile i) { return i.type_ == ILLUSIONARY; });

            if (has_illus_proj) {
                a.name_ = "ILLUSIONARY BOLT";
                a.type_ = { "ILLUSIONARY" };

                // Check if it has a illusionary affinity
                const auto affinities = getAffinities();
                const bool has_illus_aff = std::any_of(affinities.begin(), affinities.end(), [&](Variant i) { return i == ILLUSIONARY; });
                if (has_illus_aff) {
                    a.damage_ = { 3 };
                } else {
                    a.damage_ = { 2 };
                }
            } else {
                a.name_ = "TENTACLE SLAP";
                a.type_ = { "PHYSICAL", "EMOTIONAL" };
                a.damage_ = { 1, 1 };
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
  @post     : displays the attacks of the Mindflayer in the form:
  [MINDFLAYER] Choose an attack (1-3):\n1: PSIONIC BOLT\t\t2: TELEPATHIC BOLT\t\t3: ILLUSIONARY BOLT\n
*/
void Mindflayer::displayAttacks() const {
    std::cout << "[MINDFLAYER] Choose an attack (1-3):\n1: PSIONIC BOLT\t\t2: TELEPATHIC BOLT\t\t3: ILLUSIONARY BOLT\n";
}
