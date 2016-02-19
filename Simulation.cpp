
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
	
	pop = new Population(Raa, Rbb, Rab, Rbc, Pmut, Pdeath, Wmin, W, H, A, B);
	envir = new Environment(W, H, D, A_init);
}




// ===========================================================================
//                                 Destructor
// ===========================================================================

Simulation::~Simulation() {
	delete pop;
	delete envir;
}

// ===========================================================================
//                               Public Methods
// ===========================================================================

void Simulation::Algo_evol(void){
	
	while(t_cur<t_max){
	
		//Diffusion of A,B,C in the environment
		envir->diffuse_all();
		
		//Bacterias die randomly and diffuse their content in the environment
		step_Death();
		
		//Step division
		
		//Step living
		
		
		t_cur ++;
	}
}

void Simulation::step_Death(void){
	
}

// ===========================================================================
//                              Protected Methods
// ===========================================================================

// ===========================================================================
//                              External Methods
// ===========================================================================



