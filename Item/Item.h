#include <string>
class Item {
    public:
        enum class Category{
            POTION = 1,
            WEAPON = 2,
            EQUIPMENT = 3,
            SPECIAL = 4 // including key
        };
        enum class Type{
            KEY = 1
        };
    private:
        Category category;
        Type type; // the ID of an item


};
