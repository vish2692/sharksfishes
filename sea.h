#ifndef SEA_H
#define SEA_H

#include "QVector"

class Animal;

class Sea
{
private:

    Animal *** grid;
    QVector<Animal *> garbage;
    unsigned int width;
    unsigned int height;
    unsigned int simulation_turns;
    unsigned int starting_fishes;
    unsigned int starting_sharks;
    unsigned int turns_left;

    void Clean();

public:
    Sea();
    Sea(unsigned int width, unsigned int height, unsigned int simulation_turns, unsigned int starting_fishes, unsigned int starting_sharks);

    void Init();
    void Configure(unsigned int width, unsigned int height, unsigned int simulation_turns, unsigned int starting_fishes, unsigned int starting_sharks);
    void Populate();

    Animal * Get(int x, int y);
    inline void Set(int x, int y, Animal * animal) {this->grid[x][y] = animal;}
    inline unsigned int getWidth() {return width;}
    inline unsigned int getHeight() {return height;}
    void Move(Animal * animal, int x, int y);
    void Delete(Animal * animal);

    inline unsigned int getSimulationTurns(){ return this->simulation_turns ; }
};

#endif // SEA_H
