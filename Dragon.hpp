#ifndef DRAGON_HPP
#define DRAGON_HPP

#include "Creature.hpp"



class Dragon : public Creature
{

    public:

        enum Element {NONE, FIRE, WATER, EARTH, AIR};
        
        /**
            Default constructor.
            Default-initializes all private members. 
            Default Category: MYSTICAL
            Default element: NONE
            Default number of head(s): 1
            Booleans are default-initialized to False. 
        */
        Dragon();

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
        Dragon(const std::string& name, Category category = MYSTICAL, int hitpoints = 1, int level = 1, bool tame = false, Element element = NONE, int number_of_heads = 1, bool flight = false);

         /**
            Getter for the element.
            @return     : The element (a string representation of the Element enum)
        */
        std::string getElement() const;

        /**
            Setter for the element.
            @param      : A reference to the element (an Element enum)
            @post       : The element is set to the value of the parameter.
        */
        void setElement(const Element& element);

        /**
            Getter for the number of heads.
            @return     : The number of heads (an integer)
        */
        int getNumberOfHeads() const;

        /**
            Setter for the number of heads.
            @param      : A reference to the number of heads (an integer)
            @pre        : The number of heads is > 0. Do nothing for invalid values.
            @post       : The number of heads is set to the value of the parameter.
            @return     : True if the number of heads is set, false otherwise.
        */
        bool setNumberOfHeads(const int& number_of_heads);

        /**
            Getter for the flight_ flag.
            @return     : The flight_ flag (a boolean)
        */
        bool getFlight() const;

        /**
            Setter for the flight_ flag.
            @param      : A reference to the flight flag (a boolean)
            @post       : The flight_ flag is set to the value of the parameter.
        */
        void setFlight(const bool& flight);



        // override the Creature display function
        /**
            @post     : displays Dragon data in the form:
            "DRAGON - [NAME]\n
            CATEGORY: [CATEGORY]\n
            HP: [HITPOINTS]\n
            LVL: [LEVEL]\n
            TAME: [TAME]\n
            ELEMENT: [ELEMENT]\n
            HEADS: [NUMBER OF HEADS]\n
            IT [CAN/CANNOT] FLY\n"
            
            Example:
            
        */
        void display() const override;

        /**
            @post   : If the creature is UNDEAD, it becomes tame if not already, as it appreciates the gesture, even though as an UNDEAD it does not really eat. 
                    It gains 1 hitpoint from the mysterious powers it receives by wearing the mushroom as a hat. Nothing else happens.
                    If the creature is an ALIEN, it consumes the mushroom and gains 1 additional hitpoint. Nothing else happens.
                    If the creature is MYSTICAL, it consumes the mushroom and gains 1 additional hitpoint if it has FIRE or EARTH affinity (Either by cooking the mushroom first, or by being fungi-tolerant). Nothing else happens.
                    But if it is MYSTICAL and has WATER, AIR, or no affinity, if it only has 1 hitpoint left, it doesn't want to risk it and leaves the Cavern. If it has more than 1 hitpoint, it loses 1 hitpoint and becomes untamed if it was tame. Nothing else happens.
            @return : true if the creature leaves the Cavern, false otherwise
        */
        bool eatMycoMorsel() override;

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
        void addAttack(const int& kind) override;

        /**
          * @post:  displays the attacks of the Dragon in the form:
          *        [DRAGON] Choose an attack (1-3):\n1: BITE\t\t2: STOMP\t\t3: ELEMENTAL BREATH\n
          */
        void displayAttacks() const override;

    private:
        Element element_;
        int number_of_heads_;
        bool flight_;     

};

#endif // DRAGON_HPP