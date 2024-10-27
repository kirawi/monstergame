#ifndef MINDFLAYER_HPP
#define MINDFLAYER_HPP

#include "Creature.hpp"
#include <vector>



class Mindflayer : public Creature{
    public:

        enum Variant {PSIONIC, TELEPATHIC, ILLUSIONARY};
    
struct Projectile{
    Variant type_;
    int quantity_;
};
        /**
            Default constructor.
            Default-initializes all private members. 
            Default Category: ALIEN
            Default summoning: False
        */
        Mindflayer();

        /**
            Parameterized constructor.
            @param      : A reference to the name of the Mindflayer (a string)
            @param      : The category of the Mindflayer (a Category enum) with default value ALIEN
            @param      : The Mindflayer's hitpoints (an integer), with default value 1 if not provided, or if the value provided is 0 or negative
            @param      : The Mindflayer's level (an integer), with default value 1 if not provided, or if the value provided is 0 or negative
            @param      : A flag indicating whether the Mindflayer is tame, with default value False
            @param      : The projectiles (a vector of Projectile structs), with default value an empty vector if not provided
            @param      : A flag indicating whether the Mindflayer can summon a Thoughtspawn, with default value False
            @param      : The affinities (a vector of Variant enums), with default value an empty vector if not provided
            @post       : The private members are set to the values of the corresponding parameters.
            Hint: Notice the default arguments in the parameterized constructor.
        */
        Mindflayer(const std::string& name, Category category = ALIEN, int hitpoints = 1, int level = 1, bool tame = false, std::vector<Projectile> projectiles = {}, bool summoning = false, std::vector<Variant> affinities = {});

        /**
            Getter for the projectiles.
            @return     : The projectiles (a vector of Projectile structs)
        */
        std::vector<Projectile> getProjectiles() const;

        /**
            Setter for the projectiles.
            @param      : A reference to the projectiles (a vector of Projectile structs)
            @post       : The projectiles are set to the value of the parameter. There should not be any duplicate projectiles in Mindflayer's projectiles vector.
                        : For example, if the vector in the given parameter contains the following Projectiles: {{PSIONIC, 2}, {TELEPATHIC, 1}, {PSIONIC, 1}, {ILLUSIONARY, 3}}, 
                        : the projectiles vector should be set to contain the following Projectiles: {{PSIONIC, 3}, {TELEPATHIC, 1}, {ILLUSIONARY, 3}}. 
                        : If the quantity of a projectile is 0 or negative, it should not be added to the projectiles vector.
                        : Note the order of the projectiles in the vector.
        */
        void setProjectiles(const std::vector<Projectile>& projectiles);

        /**
            Getter for the summoning.
            @return     : The summoning (a boolean)
        */
        bool getSummoning() const;

        /**
            Setter for the summoning.
            @param      : A reference to the summoning (a boolean)
            @post       : The summoning is set to the value of the parameter.
        */
        void setSummoning(const bool& summoning);

        /**
            Getter for the affinities.
            @return     : The affinities (a vector of Variant enums)
        */
        std::vector<Variant> getAffinities() const;

        /**
            Setter for the affinities.
            @param      : A reference to the affinities (a vector of Variant enums)
            @post       : The affinities are set to the value of the parameter.
                        : There should not be any duplicate affinities in Mindflayer's affinities vector. 
                        : For example, if the vector in the given parameter contains the following affinities: {PSIONIC, TELEPATHIC, PSIONIC, ILLUSIONARY}, 
                        : the affinities vector should be set to contain the following affinities: {PSIONIC, TELEPATHIC, ILLUSIONARY}.
                        : Note the order of the affinities in the vector.
        */
        void setAffinities(const std::vector<Variant>& affinities);

        /**
            @param       : A reference to the Variant 
            @return      : The string representation of the variant
        */
        std::string variantToString(const Variant& variant) const;



                /**
            @post     : displays Mindflayer data in the form:
            "MINDFLAYER - [NAME]\n
            CATEGORY: [CATEGORY]\n
            HP: [HITPOINTS]\n
            LVL: [LEVEL]\n
            TAME: [TAME]\n
            SUMMONING: [SUMMONING]\n
            [PROJECTILE TYPE 1]: [QUANTITY 1]\n
            [PROJECTILE TYPE 2]: [QUANTITY 2]\n
            AFFINITIES: \n
            [AFFINITY 1]\n
            [AFFINITY 2]\n"

            NOTE: For the Projectiles, print out the type and quantity of each projectile in the format: 
            [TYPE]: [QUANTITY] for each projectile in the vector, where the type is the string equivalent of the Variant (eg. "PSIONIC"/"TELEPATHIC"/"ILLUSIONARY"). If there are no projectiles, don't print anything. 

            For the Affinities, print out each affinity in the format: [AFFINITY 1]\n[AFFINITY 2]\n for each Affinity in the vector, where the Affinity is the string equivalent of the Variant (eg. "PSIONIC"/"TELEPATHIC"/"ILLUSIONARY"). If there are no affinities, don't print anything, including the label "AFFINITIES:". 
            
            Example:

        */
        void display() const override;

        /**
            @post   : If the creature is UNDEAD, it becomes tame if not already, as it appreciates the gesture, even though as an UNDEAD it does not really eat. It gains 1 hitpoint from the mysterious powers it receives by wearing the mushroom as a hat. Nothing else happens.
                      If the creature is MYSTICAL, if it can summon a Thoughtspawn, it gives the mushroom to the Thoughtspawn instead. If it cannot summon a Thoughtspawn and is tame, it eats the mushroom to be polite. If it only had 1 hitpoint left, it remains at 1 hitpoint and becomes untame, else it loses 1 hitpoint. If it cannot summon a Thoughtspawn and is untame, it decides it doesn't have to deal with this and it leaves the Cavern. Nothing else happens.
                      If the creature is an ALIEN, if it has Telepathic affinity, it convinces Selfa Ensert to eat the mushroom instead, and gains 1 hitpoint from laughing at their resulting illness (as laughter is the best medicine).
                      If it is an ALIEN and does not have Telepathic affinity, but has a Telepathic projectile, it uses one of such projectile to achieve the same effect. (Remember to remove the projectile from the vector if it only had 1 left)
                      If it is an ALIEN and does not have Telepathic affinity or a Telepathic projectile, it eats the mushroom and gains 2 hitpoints. As it turns out, the mushroom was good for it. It becomes tame if it was not already. Nothing else happens.
            @return   : true if the creature leaves the Cavern, false otherwise
        */
        bool eatMycoMorsel() override;

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
        void addAttack(const int& kind) override;

        /**
          @post     : displays the attacks of the Mindflayer in the form:
          [MINDFLAYER] Choose an attack (1-3):\n1: PSIONIC BOLT\t\t2: TELEPATHIC BOLT\t\t3: ILLUSIONARY BOLT\n
        */
        void displayAttacks() const override;

       

    private:
        std::vector<Projectile> projectiles_;
        bool summoning_;
        std::vector<Variant> affinities_;

};
#endif // MINDFLAYER_HPP