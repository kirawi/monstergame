#include "Creature.hpp"

Creature::Creature() : Creature { "NAMELESS" } {}

Creature::Creature(const std::string& name, Creature::Category category, int hp, int level, bool is_tame) : category_(category), is_tame_(is_tame) {
    if (!setName(name)) {
        this->name_ = "NAMELESS";
    }

    this->hitpoints_= std::max(1, hp);
    this->level_ = std::max(1, level);
}

bool Creature::setName(const std::string& name) {
    std::string buf;

    for (ulong i = 0; i < name.length(); i++) {
        if (!isalpha(name[i])) {
            return false;
        } else if (!isupper(name[i])) {
            buf.push_back(toupper(name[i]));
        } else {
            buf.push_back(name[i]);
        }
    }
    this->name_ = buf;
    return true;
}

std::string Creature::getName() const {
    return this->name_;
}

bool Creature::setCategory(const Creature::Category& category) {
    if (category < 0 || category > 3) {
        this->category_ = Creature::Category::UNKNOWN;
    } else {
        this->category_ = category;
    }
    return true;
}

std::string Creature::getCategory() const {
    switch (this->category_) {
        case Creature::UNDEAD:
            return "UNDEAD";
        case Creature::MYSTICAL:
            return "MYSTICAL";
        case Creature::ALIEN:
            return "ALIEN";
        default:
            return "UNKNOWN";
    }
}

bool Creature::setHitpoints(const int& n) {
    if (n < 0) {
        return false;
    }
    this->hitpoints_ = n;
    return true;
}

int Creature::getHitpoints() const {
    return this->hitpoints_;
}

bool Creature::setLevel(const int& n) {
    if (n < 0) {
        return false;
    }
    this->level_ = n;
    return true;
}

int Creature::getLevel() const {
    return this->level_;
}

bool Creature::setTame(const bool& is_tame) {
    this->is_tame_ = is_tame;
    return true;
}

bool Creature::isTame() const {
    return this->is_tame_;
}

std::string boolToString(const bool& b) {
    if (b) {
        return "TRUE";
    } else {
        return "FALSE";
    }
}

/**
    @post     : displays Creature data in the form:
    "[NAME]\n
    Category: [CATEGORY]\n
    Level: [LEVEL]\n
    Hitpoints: [Hitpoints]\n
    Tame: [TRUE/FALSE]"   
*/
void Creature::display() const
{
    std::cout << name_ << std::endl;
    std::cout << "Category: " << getCategory() << std::endl;
    std::cout << "Level: " << level_ << std::endl;
    std::cout << "Hitpoints: " << hitpoints_ << std::endl;
    std::cout << "Tame: " << (tame_ ? "TRUE" : "FALSE") << std::endl;
}

/**
    @param      : a const reference to the right hand side of the == operator.
    @return     : Returns true if the right hand side creature is "equal", false otherwise.
                Two creatures are equal if they have the same name, same category, same level, and if they're either both tame or both not
                NOTE: By this definition, only the aforementioned subset of the creature's attributes must be equal for two creatures to be deemed "equal".

    Example: In order for creature1 to be == to creature2 we only need:
    - The same name
    - The same category
    - The same level
    - They must either be both tame or both not
*/
bool Creature::operator==(const Creature& rhs) const {
    return name_ == rhs.name_
            && category_ == rhs.category_
            && level_ == rhs.level_
            && tame_ == rhs.tame_;
}


/**
    @param      : a const reference to the right hand side of the != operator.
    @return     : Returns true if the right hand side creature is NOT "equal" (!=), false         
                otherwise. Two creatures are NOT equal if any of their name, category or level are not equal, or if one is tame and the other is not.
                NOTE: By this definition, one or more of the aforementioned subset of the creature's attributes only must be different for two creatures to be deemed "NOT equal".
*/
bool Creature::operator!=(const Creature& rhs) const {
    return !(*this == rhs);
}
/**
  * @return a copy of the attackQueue
*/
std::queue<Attack> Creature::getAttackQueue() const {
    return *this;
}

/**
  * @param: A const reference to attack to be added to the queue. 
  * @post: The attack is added to the queue
  */
void Creature::addAttack(const Attack& attack) {
    std::queue<Attack>::push(attack);
}

/**
  * @post: the attackQueue is emptied
*/
void Creature::clearAttackQueue() {
    std::queue<Attack>().swap(*this);
}

/*
    @return : the race of the Creature
*/
Creature::Category Creature::getEnumCategory() const {
    return category_;
}
