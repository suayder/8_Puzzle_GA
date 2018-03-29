#include "main.h"
using namespace Game;


int main(int argc, char **argv) {
    srand(time(NULL));

    FILE* initial_matrix;
    FILE* objective_matrix;
    if(argc == 3) {
        initial_matrix = fopen(argv[1], "r");
        objective_matrix = fopen(argv[2], "r");
    }


    for(int i = 0; i < 9; i++)
    {
        fscanf(initial_matrix, "%d", &(GameState::initial[i]));
        fscanf(objective_matrix, "%d", &(GameState::objetivo[i]));
    }
    cout << "Matriz inicial: " << endl;
    print_state(GameState::initial);
    cout << "Matriz Objetivo: " << endl;
    print_state(GameState::objetivo);
    //fclose(initial_matrix);
    //fclose(objective_matrix);

    test = new GameState;
    init_man = manhattan(GameState::initial, GameState::objetivo);
    printf("GameState IsSolvable(initial): %d\nGameState isSolvable(objetivo): %d\n", isSolvable(GameState::initial),  isSolvable(GameState::objetivo));
    if(isSolvable(GameState::initial)%2 == isSolvable(GameState::objetivo)%2) printf("Matriz Checada! Solução Possível!!!\n");
    else
    {
        printf("Matriz não resolvivel, trocando GameState::objetivo para: 1 2 3 4 5 6 8 7 0!!!\n");
        swapInt(&GameState::objetivo[6], &GameState::objetivo[7]);
    }

    Tpopulation population;
    int size_of_population;
    cout<<"Type the population size: ";
    cin >> size_of_population;
    population = generatePopulation(size_of_population);
    sort(population.begin(), population.end(), sortPopulation);
    int countInd = 1;
    for(auto p:population) {

        printf("Individuo %d: \n", countInd++);
        print_state(p.chromossome.tabuleiro);
        printf("\nFitness: %d\n\n", p.fitness_value);
    }

    int numberOfGeneration = 0, generations;
    Tpopulation newPopulation;
    //cout<<"Type number of generation you want: "<<endl;
    //cin>>generations;applyMove
    //while(numberOfGeneration<generations){
    while(true) {
        newPopulation = crossover(population);
#ifdef DBG
        printf("Passou Cross\n");
#endif // DBG
        if(test->moves.size() != 0 && test->moves.size() < 99999)
        {
            cout << "GameState::objetivo Atingido: " << endl;
            print_state(test->tabuleiro);
            cout << "\nMovimentos: " << test->moves.size() << endl;
            exit(0);
            test->resetState();
            print_state(test->tabuleiro);
            printf("\n");
            for(auto& mov:test->moves)
            {
                switch (mov)
                {
                case UP:
                    printf("UP:\n");
                    test->applyMove(UP);
                    print_state(test->tabuleiro);
                    break;
                case DOWN:
                    printf("DOWN:\n");
                    test->applyMove(DOWN);
                    print_state(test->tabuleiro);
                    break;
                case LEFT:
                    printf("LEFT:\n");
                    test->applyMove(LEFT);
                    print_state(test->tabuleiro);
                    break;
                case RIGHT:
                    printf("RIGHT:\n");
                    test->applyMove(RIGHT);
                    print_state(test->tabuleiro);
                    break;

                default:
                    break;
                }
            }
            break;
        }
        naturalSelection(newPopulation);
        population = newPopulation;
        numberOfGeneration++;
        //if(population[0].chromossome.moves.size() > 0) cout << population[0].chromossome.moves.size() << endl;
        if(numberOfGeneration%100 == 0) {
            cout << "geração: "<<numberOfGeneration<< " Fitness: " << population[0].fitness_value -
                 population[0].chromossome.moves.size() << " Chromossome Size: " <<
                 population[0].chromossome.moves.size() << endl;
            individuals ind = population[rand()%population.size()];
            print_state(ind.chromossome.tabuleiro);
            cout << ind.fitness_value << " " << ind.chromossome.moves.size() << endl;
        }

    }

    //ofstream result("result.dat");
    cout<<"Result: "<<endl;
    countInd = 1;
    for(auto p:population) {
        printf("Individuo %d: \n", countInd++);
        print_state(p.chromossome.tabuleiro);
        printf("\nFitness: %d\n\n", p.fitness_value*-1);
        exit(0);
    }
    //result.close();
    //system("gnuplot -p chart.gnu");
    return 0;
}
