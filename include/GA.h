#ifndef GA_H
#define GA_H
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <ctime>
#include <cmath>
#include "Game.h"

using namespace std;
using namespace Game;

typedef struct individ { //informações do individuo
    GameState chromossome;
    int fitness_value;
    double probability_of_selection;
    void set_probability(int sumOfFitness_value);
    void set_fitness_value();
} individuals;
extern GameState* test;
typedef vector<individuals> Tpopulation;

void setFitnessValue_forAll(Tpopulation& population);

void copyMatrix(int* dest, int* source);

Tpopulation generatePopulation(const int amountOfIndividuals);

void mutation(individuals& individ);

individuals selectIndividual(Tpopulation population);

void applyMovements(GameState& gs);

Tpopulation crossover(Tpopulation population);


bool sortPopulation(individuals a, individuals b);

bool sortNatSel(individuals a, individuals b);

void naturalSelection(Tpopulation& population);
#endif