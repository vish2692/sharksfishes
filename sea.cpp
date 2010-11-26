#include "sea.h"
#include "animal.h"
#include "fish.h"
#include "shark.h"
#include <QDebug>

Sea::Sea() {
    this->Configure(100, 100, 1000, 10, 10);
    this->garbage = QVector<Animal *>();

    this->grid = new Animal**[this->width];
    for(int i=0; i<this->width ;i++)
    {
        this->grid[i] = new Animal*[this->height];
        for(int j=0 ; j<this->height ; j++)
            this->grid[i][j] = NULL ;
    }
}

Sea::Sea(unsigned int width, unsigned int height, unsigned int simulation_turns, unsigned int starting_fishes, unsigned int starting_sharks) {
    this->Configure(width, height, simulation_turns, starting_fishes, starting_sharks);
    this->garbage = QVector<Animal *>();

    this->grid = new Animal**[this->width];
    for(int i=0; i<this->width ;i++)
    {
        this->grid[i] = new Animal*[this->height];
        for(int j=0 ; j<this->height ; j++)
            this->grid[i][j] = NULL ;
    }
}

void Sea::Init() {
    Animal::setSea(this);
}

void Sea::Configure(unsigned int width, unsigned int height, unsigned int simulation_turns, unsigned int starting_fishes, unsigned int starting_sharks) {
    this->width = width;
    this->height = height;
    this->simulation_turns = simulation_turns;
    this->turns_left = simulation_turns;
    this->starting_fishes = starting_fishes;
    this->starting_sharks = starting_sharks;
}

void Sea::Populate() {
    unsigned int i;
    qDebug() << "Start - Populate Sea" ;
    for(i = 0; i < this->starting_fishes; i++)
        new Fish();
    for(i = 0; i < this->starting_sharks; i++)
        new Shark();
    qDebug() << "End - Populate Sea" ;
}

Animal * Sea::Get(int x, int y) {
    // if x < 0, we get the position from the other side of the grid.
    // same for y
    //qDebug() << x <<  " " << this->width << " " << this->height << " x : " << (x < 0 ? this->width - x : (x >= this->width ? x % this->width : x)) << " y : "<<(y < 0 ? this->height - y : (y >= this->height ? y % this->height: y));
    return this->grid[(x < 0 ? this->width + x : (x >= this->width ? x % this->width : x))][(y < 0 ? this->height + y : (y >= this->height ? y % this->height: y))];
}

void Sea::Delete(Animal *animal) {
    this->Set(animal->getX(), animal->getY(), NULL);
    this->garbage.push_back(animal);
    qDebug() << "Delete animal" ;
}

void Sea::Clean() {
    Animal * current = this->garbage.first();
    while(current != NULL) {
        this->garbage.pop_front();
        delete current;
        current = this->garbage.first();
    }
}

void Sea::Move(Animal *animal, int x, int y) {
    this->Set(animal->getX(), animal->getY(), NULL);
    int posX = (x < 0 ? this->width + x : (x >= this->width ? x % this->width : x));
    int posY = (y < 0 ? this->height + y : (y >= this->height ? y % this->height: y));
    this->Set(posX, posY, animal);
    animal->setX(posX);
    animal->setY(posY);
}
