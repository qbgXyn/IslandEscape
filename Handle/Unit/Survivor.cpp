#include "Survivor.h"
#include "../Decoration/Item_Handle.h"
#include "../../Map/Map.h"

#include "../../Item/Item_data.h"

#include <iostream>

//#include <bits/stdc++.h>
const float Survivor::base_collision_radius = 64.0;
const double Survivor::base_max_speed = 10.0;
const int Survivor::base_attackInterval = 1; 
const float Survivor::base_attack_radius = 96.0; 
const double Survivor::base_attack_sector_angle = 60.0; // set base index for survivor
const int Survivor::base_max_health = 10.0;

Survivor::Survivor(Map *map, double x, double y) : Unit(map, x, y) { //constructor
    type = Handle::Type::SURVIVOR;
    pathable += Terrain::Type::GRASS;
    pathable += Terrain::Type::STONE;
    pathable += Terrain::Type::SHOAL; //player can walk through grass, stone and shoal ground but not ocean

    visible_size = base_visible_size;
    health = base_max_health;
    damage = base_damage;
    armor = base_armor; //initalize value

    Inventory[0] = new Item_inventory {Item::ID::SWORD}; //by default give a sword to the player at the beginning in the first left item bar and hold it
    Inventory[1] = new Item_inventory {Item::ID::TORCH_LIT}; //by deafult give a torch to the player
    // 2-4 for testing only
    Inventory[2] = new Item_inventory {Item::ID::REGEN_INSTANT_POTION};
    Inventory[3] = new Item_inventory {Item::ID::REGEN_INSTANT_POTION};
    Inventory[4] = new Item_inventory {Item::ID::SPEED_POTION};
    visible_size += Inventory[1]->item->getData(); //add visibility given by torch (lit) given
}


void Survivor::update() {

    Handle::update();

    // attack interval section
    if (attackInterval > 0) {
        --attackInterval;
    }

    // sword section
    {
        int index = getItemIndex(Item::ID::SWORD_COOLDOWN);
        if (index != ITEM_NOT_EXIST) { // sword in cooldown
            int durability = Inventory[index]->item->getDurability();
            --durability;
            Inventory[index]->item->setDurability(durability);
            if (durability % sword::duration == 0) { // cooldown finished
                if (durability == 0) { // run out of durability
                    deleteItem(index);
                }else {
                    itemSwitchState(Item::ID::SWORD_COOLDOWN, Item::ID::SWORD);
                }
            }
        }
    }

    // effect section
    {
        vector<Effect*>::const_iterator it_end = EffectList.end();
        int duration;
        Effect *e;
        for(vector<Effect*>::const_iterator it = EffectList.begin(); it != it_end; ++it) { // iterate all effect
            e = *it;
            cout << e << endl;
            duration = (*it)->getDuration();
            --duration;
            if (duration > 0) {
                e->setDuration(duration);
            }else {
                removeEffect(e);
            }
        }
    }

    // campfire section
    vector<Handle*> nearbyList = map->getHandleGroup(location[0], location[1], 2*base_collision_radius);
    vector<Handle*>::const_iterator it_end = nearbyList.end();
    bool isNearCampfire = false;
    for(vector<Handle*>::const_iterator it = nearbyList.begin(); it != it_end; ++it) { // search for campfire
        if ((*it)->getType() == Handle::Type::CAMPFIRE) {
            isNearCampfire = true;
            break;
        }
    }

    if (!isNearCampfire && invulerableByCampfire) { // not near a campfire but invulerable by campfire
        invulerableByCampfire = false;
        setInvulnerable(false);
    }

    if (isNearCampfire) { // if near a campfire
        if (!invulerableByCampfire) { // near a campfire but not invulerable by campfire
            invulerableByCampfire = true;
            setInvulnerable(true);
        }

        //gain torchtime 
        Item::ID id;
        for (int index = 0; index < maxSlotOfInventory; ++index) {
            if (Inventory[index] != nullptr) {
                id = Inventory[index]->item->getID();
                if (id == Item::ID::TORCH_LIT || id == Item::ID::TORCH) {
                    Inventory[index]->item->setDurability(Inventory[index]->item->getDurability() + 2);
                    break;
                }
            }
        }
    }
}

double Survivor::getDirection() const {
    return direction;
}

void Survivor::setMoveDirection(bool move, double direction) {
    if (!move) {
        setVelocityX(0);
        setVelocityY(0);
        return;
    }
    this->direction = direction;
    if (direction == 0 || direction == 180) {
        setVelocityX(0);
        setVelocityY((direction-90)*base_max_speed/90);
    }
    if (direction == -90 || direction == 90) {
        setVelocityX((direction)*base_max_speed/90);
        setVelocityY(0);
    }
    if (direction == 45) {
        setVelocityX(sqrt(base_max_speed*base_max_speed/2));
        setVelocityY(-sqrt(base_max_speed*base_max_speed/2));
    }
    if (direction == 135) {
        setVelocityX(sqrt(base_max_speed*base_max_speed/2));
        setVelocityY(sqrt(base_max_speed*base_max_speed/2));
    }
    if (direction == -135) {
        setVelocityX(-sqrt(base_max_speed*base_max_speed/2));
        setVelocityY(sqrt(base_max_speed*base_max_speed/2));
    }
    if (direction == -45) {
        setVelocityX(-sqrt(base_max_speed*base_max_speed/2));
        setVelocityY(-sqrt(base_max_speed*base_max_speed/2));
    }
}

void Survivor::gainAttributeFromEffect(Effect *e) { //gain effect
    cout << "gain effect" << endl;
    Effect::Type type = e->getType();
    switch(type) {
        case Effect::Type::REGEN_INSTANT:
            health += e->getData();
            health = min(base_max_health, health);
            break;
        case Effect::Type::SPEED:
            max_speed += e->getData();
            break;
        case Effect::Type::INVULNERABLE:
            setInvulnerable(true);
            break;
        case Effect::Type::INVISIBLE:
            setInvisible(true);
            break;
    }
     cout << "gain effect done" << endl;
}

void Survivor::addEffect(Effect *e) { //add effect into the vector list
    cout << "add effect" << endl;
    gainAttributeFromEffect(e);
    if (e->getDuration() > 0) {// if duration > 0, add it to list and set-up timer
        cout << "add effect to list" << endl;
        EffectList.push_back(e);
    }
    cout << "add effect done" << endl;
}

void Survivor::removeAttributeFromEffect(Effect *e) {
    cout << "remove attribute effect" << endl;
    Effect::Type type = e->getType();
    switch(type) {
        case Effect::Type::SPEED:
            max_speed -= e->getData();
            break;
        case Effect::Type::INVULNERABLE:
            setInvulnerable(false);
            break;
        case Effect::Type::INVISIBLE:
            setInvisible(false);
            break;
        default:
            break;
    }
    cout << "remove attribute effect done" << endl;
}
void Survivor::removeEffect(Effect *e) {
    cout << "remove effect" << endl;
    removeAttributeFromEffect(e);
    vector<Effect*>::const_iterator it_end = EffectList.end();
    for(vector<Effect*>::const_iterator it = EffectList.begin(); it != it_end; ++it) { //search and remove the Effect
        if ((*it) == e) {
            delete e;
            EffectList.erase(it);
            cout << "remove effect return" << endl;
            return; //assuming Effect is unique
        }
    }
    cout << "remove effect done" << endl;
}

bool Survivor::isInventoryFull() const { //check if the "bag" is full
    int counter = 0;
    for (int i = 0; i < maxSlotOfInventory; ++i) {
        if (Inventory[i] != nullptr) {
            ++counter;
        }
    }
    return counter >= maxSlotOfInventory;
}

void Survivor::useItem(Item_inventory *i) { //use the holding item
    if (i == nullptr) return; //check if holding an item
    Item *item = i->item;
    Item::ID id = item->getID();
    int durability = item->getDurability();
    double data = item->getData();
    int duration = item->getDuration(); //get the private data of item
    switch(id) {
        case Item::ID::KEY:
            turnOnBoat();
            return; // no need to reduce durability
        case Item::ID::TORCH:
        case Item::ID::TORCH_LIT:
            switchTorchState();
            return; // no need to reduce durability
        case Item::ID::ROCK:
            // further information needed for implementation
            break;
        case Item::ID::BELL:
            // further information needed for implementation
            break;
        case Item::ID::SPEED_POTION: {
            Effect *e = new Effect(Effect::Type::SPEED, data, duration);
            addEffect(e);
            break;
        }
        case Item::ID::REGEN_INSTANT_POTION: {
            Effect *e = new Effect(Effect::Type::REGEN_INSTANT, data, duration);
            addEffect(e);
            cout << "add regen potion" << endl;
            break;
        }
        case Item::ID::SWORD: // if sword is not in cooldown
            if (attackInterval > 0) return; // if survivor itself is in attack cooldown, so as to support multiple weapon
            setDamage(item->getData());
            attack(base_attack_radius, base_attack_sector_angle);
            attackInterval = base_attackInterval;
            itemSwitchState(Item::ID::SWORD, Item::ID::SWORD_COOLDOWN);
            return;
        case Item::ID::SWORD_COOLDOWN:
            return; // no need to reduce durability
        default:
            break;
    }
    cout << "durability testing" << endl;
    if (durability > 0) {
        --durability;
        if (durability == 0) {
            deleteItem(selectedItemIndex);
        }else {
            item->setDurability(durability);
        }
    }
}

#include <iostream>
void Survivor::pickupItem() { //pick up a item nearby on the ground]
    vector<Handle*> list = map->getHandleGroup(location[0], location[1], 2*base_collision_radius); // get all surrounding handles
    cout << "pickup()" << endl;

    Handle* h;
    Item_Handle* ih;

    vector<Handle*>::const_iterator it_end = list.end(); // check if it collide with existing handle
    for(vector<Handle*>::const_iterator it = list.begin(); it != it_end; ++it) { // iterate all handle
        cout << "iterating handle" << endl;
        if (isInventoryFull()) { // no need to search more if inventory is full
            cout << "inventory full" << endl;
            return;
        }
        h = *it;
        cout << h << endl;
        if (h->getType() == Handle::Type::ITEM) { // if it's item
            cout << "get an item_handle" << endl;
            for(int index = 0; index < maxSlotOfInventory; ++index) { // iterate all slot in inventory
                cout << "searching for empty slot" << endl;
                if (Inventory[index] == nullptr) {                  // find an empty slot of inventory
                    cout << "find a empty slot: " << index << endl;
                    ih = reinterpret_cast<Item_Handle*> (h);
                    cout << "creating new item inventory" << endl;
                    Inventory[index] = new Item_inventory {*ih->item};
                    cout << "name: " << Inventory[index]->item->getName() << endl;
                    cout << "new item inventory created" << endl;
                    map->removeHandle(h);
                    cout << "item_handle removed" << endl;
                    break; // back to iterating handle
                }
            }
        }
    }
    cout << "pickup() finished" << endl;
}


void Survivor::dropItem() {
    Item_inventory *Item = Inventory[selectedItemIndex];
    if (Item != nullptr) { //check if holding an item
        Item::ID id = Item->item->getID();
        if (id == Item::ID::TORCH_LIT || id == Item::ID::SWORD_COOLDOWN) // drop torch lit and sword cooldown is not allowed
            return;

        map->createItem_Handle(id, location[0], location[1]);
        delete Item; //when drop the item, remove it from the array but will not move other item positon in the array
        Inventory[selectedItemIndex] = nullptr;
        return;
    }
    return;
}

void Survivor::switchTorchState() { //switch between torch and set a new durability
    if (Inventory[selectedItemIndex] == nullptr) return; //check if not holding any item 

    int durability;
    Item::ID id = Inventory[selectedItemIndex]->item->getID();

    if (id == Item::ID::TORCH || id == Item::ID::TORCH_LIT) { // if used item is torch
        durability = Inventory[selectedItemIndex]->item->getDurability();

        if (id == Item::ID::TORCH) { // only able to switch to lit state when durability > 0
            if (durability > 0) {
                delete Inventory[selectedItemIndex]; //remove the old one
                Inventory[selectedItemIndex] = new Item_inventory {Item::ID::TORCH_LIT};
                setVisibleSize(getVisibleSize() + Inventory[selectedItemIndex]->item->getData()); //add visible size
            }
        }
        else {
            delete Inventory[selectedItemIndex]; //remove the old one
            Inventory[selectedItemIndex] = new Item_inventory {Item::ID::TORCH};
            setVisibleSize(getVisibleSize() - Inventory[selectedItemIndex]->item->getData()); // shrink visible size
        }
        Inventory[selectedItemIndex]->item->setDurability(durability);
    }
}

void Survivor::itemSwitchState(Item::ID oldID, Item::ID newID) { //item is run out of time, switch it from old item to new item
    Item_inventory *ih = nullptr;
    int i;
    for (i = 0; i < maxSlotOfInventory; ++i) {
        if (Inventory[i] != nullptr && Inventory[i]->item->getID() == oldID) { //search item
            ih = Inventory[i];
            break;
        }
    }
    if (ih == nullptr) return; // if item is not present

    int durability = ih->item->getDurability();
    deleteItem(i);
    if (newID != Item::ID::EMPTY) { // check if no need to create new item
        ih = new Item_inventory {newID};
        ih->item->setDurability(durability);
        Inventory[i] = ih; // put the item back to the inventory

        if (newID == Item::ID::TORCH) { // in the case of torch
            setVisibleSize(getVisibleSize() - ih->item->getData()); // shrink visible size
        }
    }

}


void Survivor::deleteItem(int index) {
    delete Inventory[index];
    Inventory[index] = nullptr;
}


int Survivor::getTorchTime() const{ //return the torch durability
    Item::ID id;
    for (int i = 0; i < maxSlotOfInventory; ++i) {
        if (Inventory[i] != nullptr) { //check if holding a item
            id = Inventory[i]->item->getID();
            if (id == Item::ID::TORCH || id == Item::ID::TORCH_LIT) {
                return Inventory[i]->item->getDurability();
            }
        }

    }
    return 0;
}

bool Survivor::turnOnBoat() const { //if can turnon the boat, end the game
    vector<Handle*> list = map->getHandleGroup(location[0], location[1], 2*base_collision_radius); // get all surrounding handle

    vector<Handle*>::const_iterator it_end = list.end(); // check if it collide with existing handle
    for(vector<Handle*>::const_iterator it = list.begin(); it != it_end; ++it) {
        if ((*it)->getType() == Handle::Type::BOAT) {
            map->end_game(); // game win!
            return true;
        }
    }
    return false;
}

int Survivor::getItemIndex(Item::ID id) const { //loop through the item array to check the item
    for (int i = 0; i < maxSlotOfInventory; ++i) {
        if (Inventory[i] != nullptr && Inventory[i]->item->getID() == id) { //search item name
            return i;
        }
    }
    return ITEM_NOT_EXIST;
}

void Survivor::Switch_selectedItem_Index(int index) //change the index item so that it refer to different item in the item array
{
    selectedItemIndex = index;
}
