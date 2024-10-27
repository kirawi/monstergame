#ifndef CREATURE_HPP_
#define CREATURE_HPP_
#include <iostream>
#include <queue>
#include <string>
#include <cctype>

struct Attack {
    std::string name_;
    std::vector<std::string> type_;
    std::vector<int> damage_;
};

class Creature : public std::queue<Attack>
{
    public:
        enum Category {UNKNOWN, UNDEAD, MYSTICAL, ALIEN};
        /**
            Default constructor.
            Default-initializes all private members. 
            Default creature name: "NAMELESS". 
            Booleans are default-initialized to False. 
            Default enum value: UNKNOWN 
            Default Hitpoints and Level: 1.
        */
        Creature();

        /**
            Parameterized constructor.
            @param      : The name of the creature (a string)
            @param      : The category of the creature (a Category enum) with default value UNKNOWN
            @param      : The creature's hitpoints (an integer), with default value 1 if not provided, or if the value provided is 0 or negative
            @param      : The creature's level (an integer), with default value 1 if not provided, or if the value provided is 0 or negative
            @param      : A flag indicating whether the creature is tame, with default value False
            @post       : The private members are set to the values of the corresponding parameters.
            Hint: Notice the default arguments in the parameterized constructor.
        */
        Creature(const std::string& name, Category category = UNKNOWN, int hitpoints = 1, int level = 1, bool tame = false); 

        /**
             @param : the name of the Creature, a string
             @post  : sets the Creature's name to the value of the parameter in UPPERCASE (convert any lowercase character to upppercase
                      Only alphabetical characters are allowed. 
                    : If the input contains non-alphabetic characters, do nothing.
            @return : true if the name was set, false otherwise
        */
        bool setName(const std::string& name);

        /**
             @return : the name of the Creature
        */
        std::string getName() const;


        /**
            @param  : the category of the Creature (an enum)
            @post   : sets the Creature's category to the value of the parameter
        */
        void setCategory(const Category& category);


        /**
             @return : the race of the Creature (in string form)
        */
        std::string getCategory() const;

        /*
            @return : the race of the Creature
        */
        Category getEnumCategory() const;

        /**
            @param  : an integer that represents the creature's hitpoints
            @pre    : hitpoints > 0 : Creatures cannot have 0 or negative hitpoints (do nothing for invalid input)
            @post   : sets the hitpoints private member to the value of the parameter
            @return : true if the hitpoints were set, false otherwise
        */
        bool setHitpoints(const int& hitpoints);


        /**
             @return : the value stored in hitpoints_
        */
        int getHitpoints() const;

        /**
            @param  : an integer level
            @pre    : level > 0 : Creatures cannot have 0 or negative levels (do nothing for invalid input)
            @post   : sets the level private member to the value of the parameter 
            @return : true if the level was set, false otherwise
        */
        bool setLevel(const int& level);


        /**
             @return : the value stored in level_
        */
        int getLevel() const;


        /**
            @param  : a boolean value
            @post   : sets the tame flag to the value of the parameter
        */
        void setTame(const bool& tame);


        /**
            @return true if the Creature is tame, false otherwise
            Note: this is an accessor function and must follow the same convention as all accessor functions even if it is not called getTame
        */
        bool isTame() const;

         /**
            @post     : displays Creature data in the form:
            "[NAME]\n
            Category: [CATEGORY]\n
            Level: [LEVEL]\n
            Hitpoints: [Hitpoints]\n
            Tame: [TRUE/FALSE]"   
        */
        virtual void display() const = 0;


        /**
         @param     	: A const reference to the right hand side of the == operator.
        @return     : Returns true if the right hand side creature is "equal", false otherwise.
                                    Two creatures are equal if they have the same name, same category, same level, and if they're tame or not
                                        NOTE: By this definition, only the aforementioned subset of the creature's attributes must be equal for two creatures to be deemed "equal".

        Example: In order for creature1 to be == to creature2 we only need:
        - The same name
        - The same category
        - The same level
        - They must either be both tame or not
        */
        bool operator==(const Creature& rhs) const;

        /**
         @param      : A const reference to the right hand side of the != operator.
        @return     : Returns true if the right hand side creature is NOT "equal" (!=), false 				
                                        otherwise. Two creatures are NOT equal if any of their name, category or level are
                                    not equal, or if one is tame and the other is not.
                                    NOTE: By this definition, one or more of the aforementioned subset of the 											creature's attributes only must be different for two creatures to be 
                                    deemed "NOT equal".
        */
        bool operator!=(const Creature& rhs) const;
        

         /**
            @post     : Modifies the creature's private member variables (the exact modifications will be subclass specific)
            @return   : true if the creature leaves the Cavern, false otherwise
        */
        virtual bool eatMycoMorsel() = 0;

        /**
          * @return a copy of the attackQueue
        */
        std::queue<Attack> getAttackQueue() const;

        /**
          * @param: A const reference to int indicating the attack to be added to the queue.
          * Pure virtual function to be implemented by the derived classes
          */
        virtual void addAttack(const int& kind) = 0;

        /**
          * @param: A const reference to attack to be added to the queue. 
          * @post: The attack is added to the queue
          */
        void addAttack(const Attack& attack);

        /**
          * @post: the attackQueue is emptied
        */
        void clearAttackQueue();

        /**
          * @post: Displays the options for the attacks
          * Pure virtual function to be implemented by the derived classes
          */
        virtual void displayAttacks() const = 0; 

    private:
        // The name of the creature (a string in UPPERCASE)
        std::string name_;
        // The category of the creature (an enum)
        Category category_;
        // The creature's hitpoints (a non-zero, non-negative integer)
        int hitpoints_;
        // The creature's level (a non-zero, non-negative integer)
        int level_;
        // A flag indicating whether the creature is tame
        bool tame_;

};

#endif