
// ===========================================================================
//                                  Includes
// ===========================================================================

#include "Bacteria.h"
#include "Population.h"

// ===========================================================================
//                       Definition of static attributes
// ===========================================================================


// ===========================================================================
//                                Constructors
// ===========================================================================

//Constructor with params
Population::Population(double Raa, double Rbb, double Rab, double Rbc, 
double Pmut, double Pdeath, double Wmin, int W, int H, int A, int B){

	this->Raa = Raa;
	this->Rbb = Rbb;
	this->Rab = Rab;
	this->Rbc = Rbc;
	this->Pmut = Pmut;
	this->Pdeath = Pdeath;
	this->Wmin = Wmin;

	pop_A = 0;
	pop_B = 0;
	pop_Dead = 0;
	x_max = W;
	y_max = H;

	int index = 0;
	
	pop = new Bacteria*[W*H];
	for(int i = 0; i<x_max; i++){
		for(int j = 0; j<y_max; j++){
			int random = rand()%2;
			//if random=0 -> A else B
			if(random==0){
				if(pop_A < A){
					//Create bacteria A
					pop[index] = new Bacteria(Raa,Rbb,Rab,Rbc,Pmut,Pdeath,Wmin,i,j,1);
					pop_A ++;
				}
				else{
					//Create B
					pop[index] = new Bacteria(Raa,Rbb,Rab,Rbc,Pmut,Pdeath,Wmin,i,j,2);
					pop_B ++;
				}
			}
			if(random==1){
				if(pop_B < B){
					//Create B
					pop[index] = new Bacteria(Raa,Rbb,Rab,Rbc,Pmut,Pdeath,Wmin,i,j,2);
					pop_B ++;
				}
				else{
					//Create A
					pop[index] = new Bacteria(Raa,Rbb,Rab,Rbc,Pmut,Pdeath,Wmin,i,j,1);
					pop_A ++;
				}
			}
			index++;
		}
	}

}

// ===========================================================================
//                                 Destructor
// ===========================================================================

Population::~Population() {
	
	for(int i = 0; i<x_max*y_max; i++){
		if(pop[i] != nullptr){
			delete pop[i];
		}
	}
	delete[] pop;
	pop = nullptr;
	
}

// ===========================================================================
//                               Public Methods
// ===========================================================================
void Population::mutation_all(void){
	
	for(int i = 0; i<x_max*y_max; i++){
		if( pop[i] != nullptr){
			int state1 = pop[i]->Geno();
			pop[i]->Mutation();
			if(state1 != pop[i]->Geno()){
				if(state1 == 1){
					pop_A --;
					pop_B ++;
				}
				else{
					pop_A ++;
					pop_B --;
				}
			}
		}
	}
	
}

void Population::death_all(void){

	for(int i = 0; i<x_max*y_max; i++){
		if(pop[i] != nullptr){
			pop[i]->Death();
			if(pop[i]->Alive() == false){
				pop_Dead ++;
				if(pop[i]->Geno() == 1){
					pop_A --;
				}
				else{
					pop_B --;
				}
			}
		}
	}

}

void Population::fitness_all(void){

	for(int i = 0; i<x_max*y_max; i++){
		if(pop[i] != nullptr){
			pop[i]->Fitness();
		}
	}

}


//Getter

bool Population::get_Status(int i){
	return pop[i]->Alive();
}

// ===========================================================================
//                              Protected Methods
// ===========================================================================

// ===========================================================================
//                              External Methods
// ===========================================================================


