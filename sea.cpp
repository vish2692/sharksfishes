#include "sea.h"
#include "animal.h"

Sea::Sea() {
    width = 100;
    height = 100;
    simulation_turns = 10000;
    starting_fishes = 10;
    starting_sharks = 10;
    this->garbage = QVector<Animal *>();
}

Sea::Sea(unsigned int width, unsigned int height, unsigned int simulation_turns, unsigned int starting_fishes, unsigned int starting_sharks) {
    this->width = width;
    this->height = height;
    this->simulation_turns = simulation_turns;
    this->turns_left = simulation_turns;
    this->starting_fishes = starting_fishes;
    this->starting_sharks = starting_sharks;
}

void Sea::Delete(Animal *animal) {
    this->Set(animal->getX(), animal->getY(), NULL);
    this->garbage.push_back(animal);
}

void Sea::Clean() {
    Animal * current = this->garbage.first();
    while(current != NULL) {
        this->garbage.pop_front();
        delete current;
        current = this->garbage.first();
    }
}
