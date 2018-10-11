#include "Ruletka.h"

Ruletka::Ruletka(std::default_random_engine& engine)
{
    myEngine = engine;
}

Ruletka::~Ruletka() {}

Uczciwa::Uczciwa(std::default_random_engine& engine): Ruletka(engine) {}

Europejska::Europejska(std::default_random_engine& engine): Ruletka(engine) {}

Amerykanska::Amerykanska(std::default_random_engine& engine): Ruletka(engine) {}

int Uczciwa::zakrec()
{
    std::uniform_int_distribution<int> dist(1, 36);
    int randomElement = dist(myEngine);
    return randomElement;
}

int Europejska::zakrec()
{
    std::uniform_int_distribution<int> dist(0, 36);
    int randomElement = dist(myEngine);
    return randomElement;
}

int Amerykanska::zakrec()
{
    std::uniform_int_distribution<int> dist(0, 37);
    int randomElement = dist(myEngine);
    if(randomElement == 37)
        randomElement = 0;
    return randomElement;
}



