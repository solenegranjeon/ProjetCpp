
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
	this->W = W;
	this->H = H;
	
	pop = new Bacteria**[W];
	for(int i = 0; i< W; i++){
		pop[i] = new Bacteria*[H];
		for(int j = 0; j<H; j++){
			int random = rand()%2;
			//if random=0 -> A else B
			if(random==0){
				if(pop_A < A){
					//Create bacteria A
					pop[i][j] = new Bacteria(Raa,Rbb,Rab,Rbc,Pmut,Pdeath,Wmin,i,j,1);
					pop_A ++;
				}
				else{
					//Create B
					pop[i][j] = new Bacteria(Raa,Rbb,Rab,Rbc,Pmut,Pdeath,Wmin,i,j,2);
					pop_B ++;
				}
			}
			if(random==1){
				if(pop_B < B){
					//Create B
					pop[i][j] = new Bacteria(Raa,Rbb,Rab,Rbc,Pmut,Pdeath,Wmin,i,j,2);
					pop_B ++;
				}
				else{
					//Create A
					pop[i][j] = new Bacteria(Raa,Rbb,Rab,Rbc,Pmut,Pdeath,Wmin,i,j,1);
					pop_A ++;
				}
			}
		}
	}

}

// ===========================================================================
//                                 Destructor
// ===========================================================================

Population::~Population() {
	
	for(int i = 0; i<W; i++){
		for( int j = 0; j < H; j++){
			if(pop[i][j] != nullptr){
				delete pop[i][j];
			}
		}
		delete[] pop[i];
	}
	
	delete[] pop;
	pop = nullptr;
	
}

// ===========================================================================
//                               Public Methods
// ===========================================================================
void Population::mutation_all(void){
	
	for(int i = 0; i < W; i++){
		for(int j = 0; j < H; j++){
			
			if( pop[i][j]->alive == 	true){
				int state1 = pop[i][j]->genotype;
				pop[i][j]->Mutation();
				if(state1 != pop[i][j]->genotype){
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
	
}

void Population::death_all(void){

	for(int i = 0; i<W; i++){
		for(int j = 0; j < H; j++){
			
			if(pop[i][j]->alive == true){
				
				pop[i][j]->Death();
				if(pop[i][j]->just_died == true){
					pop_Dead ++;
					if(pop[i][j]->just_died == 1){
						pop_A --;
					}
					else{
						pop_B --;
					}
				}
				
			}
			
		}
	}

}

void Population::fitness_all(void){

	for(int i = 0; i<W; i++){
		for(int j = 0; j<H; j++){
			
			if(pop[i][j]->alive == true){
				pop[i][j]->Fitness();
			}
			
		}
	}

}


// ===========================================================================
//                              Protected Methods
// ===========================================================================

// ===========================================================================
//                              External Methods
// ===========================================================================


