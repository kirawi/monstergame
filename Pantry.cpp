#include "Pantry.hpp"
#include <algorithm>

/*
    @param A const string reference to be parsed
    @param A char to be split upon
    @return A vector of split substrings without the delimiter
*/
std::vector<std::string> split(const std::string& s, char delim){
    std::vector<std::string> result;
    std::stringstream ss(s);
    std::string buf;
    while (std::getline(ss, buf, delim)) {
        result.push_back(buf);
    }
    return result;
}

/*
    @param A string to be trimmed
    @post Trims whitespace from param
    @note Taken from https://stackoverflow.com/a/217605
*/
inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

/**
   Default Constructor
*/
Pantry::Pantry() : LinkedList<Ingredient*>() {}

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
Pantry::Pantry(const std::string& path) {
    std::ifstream f { path };
    if (!f.is_open()) {
        throw std::runtime_error("Failed to open file: " + path);
    }

    std::string line;
    std::getline(f, line);

    // Add a new ingredient per each line
    while (std::getline(f, line)) {
        // INFO: Needed to pass gradescope (maybe line ending but necessary either way)
        rtrim(line);
        // Get cells in that CSV row without the semicolon
        std::vector<std::string> cells = split(split(line, ';')[0], ',');

        std::string name = cells[0];
        std::string desc = cells[1];
        int quantity = std::stoi(cells[2]);
        int price = std::stoi(cells[3]);
        std::vector<Ingredient*> recipe;

        // Handle `NONE` cell
        if (cells[4].substr(0, 4) != "NONE") {
            std::vector<std::string> recipe_ingredients = split(cells[4], ' ');
            for (size_t i = 0; i < recipe_ingredients.size(); i++) {
                Ingredient* ingredient = getIngredient(recipe_ingredients[i]);

                // SAFETY: Handle nullptr if it doesn't exist!
                if (ingredient) {
                    recipe.push_back(ingredient);
                }
            }
        }

        // Can be checked for existence in subsequent loops
        // HAXX: Assumes no duplicates (woiuld need to sum quantities and add fast path)
        addIngredient(name, desc, quantity, price, recipe);
    }
}

 /**
        Destructor
        @post: Explicitly deletes every dynamically allocated Ingredient object
*/
Pantry::~Pantry() {
    LinkedList::clear();
}

/**
    @param: A const string reference to a ingredient name
    @return: The integer position of the given ingredient if it is in the Pantry, -1 if not found. REMEMBER, indexing starts at 0.
*/
int Pantry::getPosOf(const std::string& ingredient) const {
    Node<Ingredient*>* head_ptr = LinkedList::getHeadNode();
    size_t pos = 0;

    // Return first instance of ingredient
    while (head_ptr) {
        if (head_ptr->getItem()->name_ == ingredient) {
            return pos;
        }
        head_ptr = head_ptr->getNext();
        pos++;
    }

    // Not found
    return -1;
}

/**
    @param: A const string reference to a ingredient name
    @return: True if the ingredient information is already in the Pantry
*/
bool Pantry::contains(const std::string& ingredient) const {
    // `getPosOf` returns -1 if it doesn't exist
    return getPosOf(ingredient) != -1;
}

/**
    @param:  A pointer to an Ingredient object
    @post:  Inserts the given ingredient pointer into the Pantry, unless an ingredient of the same name is already in the pantry. 
            Each of its Ingredients in its recipe are also added to the Pantry IF not already in the list.
    @return: True if the ingredient was added successfully, false otherwise.
*/
bool Pantry::addIngredient(Ingredient* ingredient) {
    // Handle nullptr
    if (!ingredient) {
        return false;
    }

    if (!contains(ingredient->name_)) {

        return LinkedList::insert(LinkedList::getLength(), ingredient);
    }
    return false;
}

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
bool Pantry::addIngredient(const std::string& name, const std::string& description, const int& quantity, const int& price, const std::vector<Ingredient*>& recipe) {
    // SAFETY: Required by LinkedList since it doesn't copy
    Ingredient* i = new Ingredient { name, description, quantity, price, recipe };
    return addIngredient(i);
}

/*
    @param A const string reference reresenting an ingredient name
    @return A reference to the Ingredient if the ingredient is in the pantry.
*/
Ingredient* Pantry::getIngredient(const std::string& name) const {
    size_t pos = getPosOf(name);
    if (pos == -1) {
        return nullptr;
    }
    Ingredient* res = LinkedList::getEntry(pos);

    // SAFETY: Already checked if it exists in `getPosOf`
    return res;
}

/**
    @param:  A Ingredient pointer
    @return: A boolean indicating if all the given ingredient can be created (all of the ingredients in its recipe can be created, or if you have enough of each ingredient in its recipe to create it)
*/
bool Pantry::canCreate(Ingredient* ingredient) const  {
    // SAFETY: Handle nullptr
    if (!ingredient) {
        throw std::invalid_argument("Passed nullptr");
    }

    // Has no recipe
    if (ingredient->recipe_.size() == 0) {
        return false;
    }

    for (size_t i = 0; i < ingredient->recipe_.size(); i++) {
        Ingredient* req_ingredient = ingredient->recipe_[i];

        // Return early if the pantry doesn't have it or if the ingredients can't be created
        if (contains(req_ingredient->name_)) {
            // Can't make more of ingredient
            if (req_ingredient->quantity_ == 0 && !canCreate(req_ingredient)) {
                return false;
            }
        } else {
            // Does not have ingredient in pantry
            return false;
        }
    }
    return true;
}

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
void Pantry::printIngredient(Ingredient* ingredient) const {
    // SAFETY: Handle nullptr
    if (!ingredient) {
        throw std::invalid_argument("Passed nullptr");
    }

    std::cout << ingredient->name_ + ": " + std::to_string(ingredient->quantity_)
                    + "\n" + ingredient->description_
                    + "\nPrice: " + std::to_string(ingredient->price_)
                    + "\nRecipe:\n";
    if (ingredient->recipe_.size() == 0) {
        std::cout << "NONE\n\n";
    } else {
        // Print the ingredients in the recipe
        for (size_t i = 0; i < ingredient->recipe_.size(); i++) {
            std::cout << ingredient->recipe_[i]->name_;

            // Don't add extra space between ingredient names if it's the last one
            if (!(i + 1 == ingredient->recipe_.size())) {
                std::cout << " ";
            }
        }
        std::cout << "\n\n";
    }
}

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
void Pantry::ingredientQuery(const std::string& name) const {
    Ingredient* i = getIngredient(name);
    std::cout << "Query: " + name + "\n";

    // Fast path
    if (!i) {
        std::cout << "No such ingredient\n\n";
        return;
    }

    // Order of if statements chosen based on post format
    if (i->quantity_ > 0) {
        std::cout << "In the pantry (" << i->quantity_ << ")\n";
    } 

    if (i->recipe_.size() == 0) {
        std::cout << "UNCRAFTABLE\n\n";
        return;
    } 
    
    // Needs to be crafted
    if (i->quantity_ == 0){
        if (canCreate(i)) {
            std::cout << name + "(C)\n";
            for (size_t x = 0; x < i->recipe_.size(); x++) {
                recipeIngredientQuery(i->recipe_[x]);
            }
            std::cout << "\n";
        } else {
            // Recipe is not possible to follow
            std::cout << i->name_ + "(" << i->quantity_ << ")\nMISSING INGREDIENTS\n\n";
        }
    }
}

/*
    @param A const reference to the ingredient
    @post Will output in the format of 
        [Ingredient Name0](C)
        [Ingredient Name1](C) <- [Ingredient Name2](3)
        [Ingredient Name3](C) <- [Ingredient Name4](C) <- [Ingredient Name5] (3)
*/
void Pantry::recipeIngredientQuery(Ingredient* i) const {
    // // SAFETY: handle nullptr!
    if (!i) {
        throw std::invalid_argument("Passed nullptr");
    }

    if (i->quantity_ > 0) {
        std::cout << i->name_ + "(" << i->quantity_ << ")\n";
    } else {
        std::cout << i->name_ + "(C) <- ";
        // Iterate over each individual recipe ingredient
        for (size_t x = 0; x < i->recipe_.size(); x++) {
            recipeIngredientQuery(i->recipe_[x]);
        }
    }
}
   

/**
    @return: An integer sum of the price of all the ingredients currently in the list.
    Note: This should only include price values from ingredients that you have 1 or more of. Do not consider ingredients that you have 0 of, even if you have the ingredients to make them.
*/
int Pantry::calculatePantryValue() const {
    Node<Ingredient*>* head_ptr = LinkedList::getHeadNode();
    size_t sum = 0;
    while (head_ptr) {
        Ingredient* i = head_ptr->getItem();
        if (i->quantity_ != 0) {
            sum += i->quantity_ * i->price_;
        }

        // Iterate
        head_ptr = head_ptr->getNext();
    }
    return sum;
}

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
void Pantry::pantryList(const std::string& filter) const {
    if (filter == "NONE") {
        Node<Ingredient*>* head_ptr = LinkedList::getHeadNode();
        while (head_ptr) {
            Ingredient* i = head_ptr->getItem();
            printIngredient(i);

            // Iterate
            head_ptr = head_ptr->getNext();
        }
    } else if (filter == "CONTAINS") {
        Node<Ingredient*>* head_ptr = LinkedList::getHeadNode();
        while (head_ptr) {
            Ingredient* i = head_ptr->getItem();
            if (i->quantity_ > 0) {
                printIngredient(i);
            }

            // Iterate
            head_ptr = head_ptr->getNext();
        }
    } else if (filter == "MISSING") {
        Node<Ingredient*>* head_ptr = LinkedList::getHeadNode();
        while (head_ptr) {
            Ingredient* i = head_ptr->getItem();

            if (i->quantity_ == 0) {
                printIngredient(i);
            }

            // Iterate
            head_ptr = head_ptr->getNext();
        }
    } else if (filter == "CRAFTABLE") {
        Node<Ingredient*>* head_ptr = LinkedList::getHeadNode();
        while (head_ptr) {
            Ingredient* i = head_ptr->getItem();
            if (canCreate(i)) {
                printIngredient(i);
            }

            // Iterate
            head_ptr = head_ptr->getNext();
        }
    } else {
        std::cout << "INVALID FILTER\n";
    }
}

