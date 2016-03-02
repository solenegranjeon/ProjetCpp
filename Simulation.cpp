
// ===========================================================================
//                                  Includes
// ===========================================================================

#include "Simulation.h"

// ===========================================================================
//                       Definition of static attributes
// ===========================================================================


// ===========================================================================
//                                Constructors
// ===========================================================================

Simulation::Simulation(double Raa, double Rbb, double Rab, double Rbc, 
double Pmut, double Pdeath, double Wmin, int W, int H, double D, 
double A_init, int A, int B, int T, int t_max) {
	
	this->Raa = Raa;
	this->Rbb = Rbb;
	this->Rab = Rab;
	this->Rbc = Rbc;
	this->Pmut = Pmut;
	this->Pdeath = Pdeath;
	this->Wmin = Wmin;
	
	this->Ga_init = A;
	this->Gb_init = B;
		
	this->W = W;
	this->H = H;
	this->D = D;
	this->A_init = A_init;
	
	this->t_max = t_max;
	this->T = T;
	this->t_cur = 1;
	
	this->Gaps = new int*[W];
	for (int rows = 0; rows < H; rows++){
		Gaps[rows] = new int[H];
		for( int col = 0; col <W; col++){
			Gaps[rows][col] = 1;
		}
	}
	
	population = new Population(Raa, Rbb, Rab, Rbc, Pmut, Pdeath, Wmin, W, H, A, B);
	envir = new Environment(W, H, D, A_init);
}




// ===========================================================================
//                                 Destructor
// ===========================================================================

Simulation::~Simulation() {
	delete population;
	delete envir;
	for( int row = 0; row < H; row ++){
		delete[] Gaps[row];
		Gaps[row] = nullptr;
	}
	delete[] Gaps;
	Gaps = nullptr;
}

// ===========================================================================
//                               Public Methods
// ===========================================================================

void Simulation::Algo_evol(void){
	

	
	while(t_cur<=t_max){
		
			printf("Iteration %d :\n",t_cur);
		
		// Every T, reinitialization of the environment
		if(t_cur % T == 0){
			envir->reinit();
		}
	
		//Diffusion of A,B,C in the environment
		envir->diffuse_all();
		
		//Bacterias die randomly and diffuse their content in the environment
		step_Death();
		
		//Step mutation
		population->mutation_all();
		
		//Step division
		step_Division();
		
		//Step living and adjusting the fitness
		population->fitness_all();
		
		t_cur ++;
	}
	
}

void Simulation::step_Death(void){
	//Bacterias die randomly
	population->death_all();
	//The dead bacterias diffuse their content in the environment
	for(int i = 0; i<W*H; i++){
		
		if(population->pop[i] != nullptr){
			
			if(population->get_Status(i) == false){ // Bacteria is dead
				
				int x = population->pop[i]->pos_x();
				int y = population->pop[i]->pos_y();
				
				double new_A = envir->get_A(x,y) + population->pop[i]->A_in();
				double new_B = envir->get_B(x,y) + population->pop[i]->B_in();
				double new_C = envir->get_C(x,y) + population->pop[i]->C_in();
				
				envir->set_A(x,y,new_A);
				envir->set_B(x,y,new_B);
				envir->set_C(x,y,new_C);
				
				Gaps[x][y] = 0;
				
				delete population->pop[i];
				population->pop[i] = nullptr;
				
			}
		}
	}
}

void Simulation::step_Division(void){
	
	//1)We find the gaps and order them randomly
	//a.We count the gaps
	int nb_gaps = 0;
		
	for(int r = 0; r < H; r++){
		for(int c = 0; c < W; c++){
			if(Gaps[r][c] == 0){
				nb_gaps ++;
			}
		}
	}
	
	//!!!!!!!!!!!!!!!!!!!!
	printf("Nb of holes: %d.\n\n",nb_gaps);
	
	//b.We gather their position
	int** pos_gaps = new int*[nb_gaps];
	int i = 0;
	for(int r = 0; r < H; r++){
		for(int c = 0; c < W; c++){
			if(Gaps[r][c] == 0){
				pos_gaps[i] = new int[2];
				pos_gaps[i][0] = r;
				pos_gaps[i][1] = c;
				i++;
			}
		}
	}
	//c.Order them randomly
	//http://www.cplusplus.com/reference/algorithm/random_shuffle/
	random_shuffle(&pos_gaps[0],&pos_gaps[nb_gaps-1]);
	
	//2)For each gap, we find the bacteria next to it with the highest fitness
	//~ for( int i = 0; i < nb_gaps; i++){
		//~ int max_fitness = 0;
		//~ //Coordinates of the Gap
		//~ int x = Gaps[i][0];
		//~ int y = Gaps[i][1];
		//~ //Find the coordinates of the neigbors:
		//~ for(int i = 0; i < 3; i++){
			//~ if(
		//~ }	
	//~ }
	
	//3)This bacteria divides itself into 2:
	//a.We split its concentration of A,B,C into 2 and 
	//b.create a copy of this bacteria at the position of the gap.
	
	//4) Delete pos_gaps
	for(int i = 0; i< nb_gaps; i++){
		delete[] pos_gaps[i];
		pos_gaps[i] = nullptr;
	}
	delete[] pos_gaps;
	pos_gaps = nullptr;
	
}

string Simulation::Stat(void){
	string res = "" + to_string(population->pop_A) + " " + 
	to_string(population->pop_B) + " " + to_string(population->pop_Dead) 
	+ "\n" ;
	return res;
}

// ===========================================================================
//                              Protected Methods
// ===========================================================================

// ===========================================================================
//                              External Methods
// ===========================================================================



