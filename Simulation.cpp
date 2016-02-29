
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
	this->t_cur = 0;
	
	population = new Population(Raa, Rbb, Rab, Rbc, Pmut, Pdeath, Wmin, W, H, A, B);
	envir = new Environment(W, H, D, A_init);
}




// ===========================================================================
//                                 Destructor
// ===========================================================================

Simulation::~Simulation() {
	delete population;
	delete envir;
}

// ===========================================================================
//                               Public Methods
// ===========================================================================

void Simulation::Algo_evol(void){
	
	while(t_cur<t_max){
		
		if(t_cur%T == 0){
			// Reinitialization of the environment
			envir->reinit();
		}
	
		//Diffusion of A,B,C in the environment
		envir->diffuse_all();
		
		//Bacterias die randomly and diffuse their content in the environment
		step_Death();
		
		//Step mutation
		population->mutation_all();
		
		//Step division
		
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
				
				delete population->pop[i];
				population->pop[i] = nullptr;
				
			}
		}
	}
}

//~ string Simulation::Stat(void){
	//~ string res = int(population->pop_A) + " " + int(population->pop_B) + " " +
	//~ int(population->pop_Dead) + "\n";
	//~ return res;
//~ }

// ===========================================================================
//                              Protected Methods
// ===========================================================================

// ===========================================================================
//                              External Methods
// ===========================================================================



