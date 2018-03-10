#include "GA.h"


using namespace std;
using namespace Game;
auto f=[](int* x)
{
    return (manhattan(x, GameState::objetivo));/*usando manhattan como fitness GA*/;
};


void individuals::set_probability(int sumOfFitness_value)
{
    probability_of_selection = 100*fitness_value/(double)sumOfFitness_value;
}
void individuals::set_fitness_value()
{
    fitness_value = 4*f(chromossome.tabuleiro) + chromossome.moves.size();
}




void setFitnessValue_forAll(Tpopulation& population) {
    long double sumOfFitness_value = 0.0;

    for(auto& ind:population) {
        ind.set_fitness_value();
        sumOfFitness_value += ind.fitness_value;
    }

    for (auto& p:population)
        p.set_probability(sumOfFitness_value);

}

void copyMatrix(int* dest, int* source)
{
    for(int i = 0; i < 9; i++) dest[i] = source[i];
}

Tpopulation generatePopulation(const int amountOfIndividuals) {
    Tpopulation population(amountOfIndividuals);
    int sumOfFitness_value = 0;
    int genesAmount = ceil(log(amountOfIndividuals)/log(4));
    int cont = 0;

    for(auto& p:population) {
        copyMatrix(p.chromossome.tabuleiro,GameState::initial);
        printf("Individuo %d done!\n", cont++);


        for(int i = 0; i<(genesAmount); i++) {

            while(!p.chromossome.applyMove((movimentos)(rand()%4)));

        }

    }
    for(auto& p:population) {
        p.set_fitness_value();
        sumOfFitness_value += p.fitness_value;
    }

    for (auto& p:population)
        p.set_probability(sumOfFitness_value);

    return population;
}

void mutation(individuals& individ) {
    
    int genesToAdd = rand()%4;
    if(genesToAdd/2 == 0){
        for(int i = 0; i < genesToAdd/2; i++)
        {
            individ.chromossome.applyMove((movimentos)(rand()%4));
        }
    }
    else
    {
        for(int i = 0; i < individ.chromossome.moves.size();i++)
        {
            if(rand()%4>1) individ.chromossome.applyMove((movimentos)(rand()%4));
            else individ.chromossome.moves.erase(individ.chromossome.moves.begin()+rand()%individ.chromossome.moves.size());
        }

    }
}
//Roulette wheel method using the probability
individuals selectIndividual(Tpopulation population) { //select to crossover (natural selection)
    double sum = 0.0;
    for(auto& p:population)
        sum += p.probability_of_selection;

    double  selectedValue = rand()%(int)sum;
    double aux = 0.0;

    for(auto& p:population)
    {
        aux += p.probability_of_selection;
        if(aux>=selectedValue) return p;
    }

}


//Method: Mult Point Crossover
Tpopulation crossover(Tpopulation population) {
    int numberOfCrosses = population.size()/2;
    while (numberOfCrosses--)
    {
        individuals ind1 = selectIndividual(population);
        individuals ind2 = selectIndividual(population);

#ifdef DBG
        cout << "Passou selection!" << endl;
#endif // DBG
        int size = (ind1.chromossome.moves.size() < ind2.chromossome.moves.size()) ? ind1.chromossome.moves.size() : ind2.chromossome.moves.size();
        /* int position1 = rand()%((int)ind1.chromossome.moves.size() + 1);
        int position2 = rand()%((int)ind2.chromossome.moves.size() + 1);

        if(position1>position2)
            swapInt(&position1,&position2); */
#ifdef DBG
        cout << "Passou swapInt\n";
#endif // DEBUG

        individuals child1 = ind1, child2 = ind2;

#ifdef DBG
        cout << "Passou resize vector\n";
#endif // DEBUG
        //for(int i = position1; i<=position2; i++)
        for(int i = 0; i < size; i++)
        {
            /* if(child1.chromossome.moves.size() > i && ind2.chromossome.moves.size() > i) {
                child1.chromossome.moves[i] = ind2.chromossome.moves[i];
#ifdef DBG
                cout << "Modificou child1!\n";
#endif // !DBG
            }

            if(child2.chromossome.moves.size() > i && ind1.chromossome.moves.size() > i) {
                child2.chromossome.moves[i] = ind1.chromossome.moves[i];
#ifdef DEBUG
                cout << "Modificou child2!\n";
#endif // DEBUG
            } */
            if(i%2) child1.chromossome.moves[i] = ind2.chromossome.moves[i];
            else child2.chromossome.moves[i] = ind1.chromossome.moves[i];
        }

#ifdef DBG
        cout << "Passou moves\n";
#endif // DEBUG

        applyMovements(child1.chromossome);
#ifdef DBG
        cout << "Passou apply child1\n";
#endif // DBG
        applyMovements(child2.chromossome);
#ifdef DBG
        cout << "Passou apply child2\n";
#endif // DBG --
        mutation(child1);
        mutation(child2);
        population.push_back(child1);
        population.push_back(child2);
    }
    return population;
}



void applyMovements(GameState& gs)
{
    gs.resetState();
    for(auto& move : gs.moves)
    {
        if(isGoal(gs.tabuleiro,GameState::objetivo))
        {
            if(test->moves.size() > 0)
            {
                if(test->moves.size() > gs.moves.size()) *test = gs;
            }
            else *test = gs;
        }
        if(!gs.applyMove(move))
        {
            while(!gs.applyMove((movimentos)(rand()%4))) {
#ifdef DBG
                printf("É aqui negão %d!\n", (movimentos)(rand()%4));
#endif // DBG
                if(isGoal(gs.tabuleiro,GameState::objetivo))
                {
                    if(test->moves.size() > 0)
                    {
                        if(test->moves.size() > gs.moves.size()) *test = gs;
                    }
                    else *test = gs;
                }


            }

        }
    }
}


bool sortPopulation(individuals a, individuals b) {
    return (a.fitness_value < b.fitness_value);
}

bool sortNatSel(individuals a, individuals b)
{
    return (a.fitness_value < b.fitness_value);
}

void naturalSelection(Tpopulation& population) {

    int sumOfFitness_value = 0;
    setFitnessValue_forAll(population);


    sort(population.begin(), population.end(), sortNatSel);

    int numberOfKills = population.size()/2;
    while(numberOfKills>0) {
        numberOfKills--;
        population.pop_back();
    }

}
