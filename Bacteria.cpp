
// ===========================================================================
//                                  Includes
// ===========================================================================

#include <fstream>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include "Bacteria.h"

using namespace std;

// ===========================================================================
//                       Definition of static attributes
// ===========================================================================


// ===========================================================================
//                                Constructors
// ===========================================================================


// Copy constructor
Bacteria::Bacteria(const Bacteria& bac){
	
	this->Raa = bac.Raa;
	this->Rbb = bac.Rbb;
	this->Rab = bac.Rab;
	this->Rbc = bac.Rbc;
	this->Pmut = bac.Pmut;
	this->Pdeath = bac.Pdeath;
	this->Wmin = bac.Wmin;
	
	// Parameters specific to the bacteria
	pos = new int[2];
	memcpy(pos, bac.pos, sizeof(int)*2);
	
	phenotype = new double[3];
	memcpy(phenotype, bac.phenotype, sizeof(double)*3);
	
	this->alive = bac.alive;
	this->can_divide = bac.can_divide;
	this->genotype = bac.genotype; //1:Ga 2:Gb
	this->fitness = bac.fitness;
	
}

//Constructor giving parameters
Bacteria::Bacteria(double Raa, double Rbb, double Rab, double Rbc, 
double Pmut, double Pdeath, double Wmin, int x, int y, int geno){

	this->Raa = Raa;
	this->Rbb = Rbb;
	this->Rab = Rab;
	this->Rbc = Rbc;
	this->Pmut = Pmut;
	this->Pdeath = Pdeath;
	this->Wmin = Wmin;
	
	// Parameters specific to the bacteria
	pos = new int[2];
	pos[0] = x;
	pos[1] = y;
	
	phenotype = new double[3];
	phenotype[0] = 0;
	phenotype[1] = 0;
	phenotype[2] = 0;
	
	this->alive = true;
	this->can_divide = false;
	this->genotype = geno;
	this->fitness = 0;

}

// ===========================================================================
//                                 Destructor
// ===========================================================================

Bacteria::~Bacteria() {

	delete[] pos;
	delete[] phenotype;
	
}

// ===========================================================================
//                               Public Methods
// ===========================================================================

void Bacteria::Mutation(void){
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  default_random_engine generator (seed);
	uniform_real_distribution <double> distribution (0.0,1.0);
	double prob = distribution(generator);
	if(prob < this->Pmut){
		if(genotype == 1){
			genotype = 2;
		}
		else{
			genotype = 1;
		}
	}
}

void Bacteria::Death(void){
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  default_random_engine generator (seed);
	uniform_real_distribution <double> distribution (0.0,1.0);
	double prob = distribution(generator);
	if(prob<this->Pdeath){
		alive = false;
	}
}

void Bacteria::Fitness(void){
	if(genotype == 1){
		fitness = phenotype[1];
	}
	else{
		fitness = phenotype[2];
	}
	if(fitness < Wmin){
		fitness = 0;
	}
}

void Bacteria::Divide(void){
	phenotype[0] /= 2;
	phenotype[1] /= 2;
	phenotype[2] /= 2;
}


//Getters

int Bacteria::Geno(void){
	return genotype;
}

int Bacteria::pos_x(void){
	return pos[0];
}

int Bacteria::pos_y(void){
	return pos[1];
}

double Bacteria::A_in(void){
	return phenotype[0];
}

double Bacteria::B_in(void){
	return phenotype[1];
}

double Bacteria::C_in(void){
	return phenotype[2];
}

double Bacteria::Fit(void){
	return fitness;
}

bool Bacteria::Alive(void){
	return alive;
}

bool Bacteria::Can_Divide(void){
	return can_divide;
}

//Setter
void Bacteria::set_x(int x){
	pos[0] = x;
}

void Bacteria::set_y(int y){
	pos[1] = y;
}

// ===========================================================================
//                              Protected Methods
// ===========================================================================

// ===========================================================================
//                              External Methods
// ===========================================================================

