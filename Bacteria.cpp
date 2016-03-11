
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
	this->just_died = false;
	this->can_metabo = true;
	
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
	if(prob < this->Pdeath){
		alive = false;
		just_died = true;
		can_divide = false;
		can_metabo = false;
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
		can_divide = false;
	}
	else{
		can_divide = true;
	}
}

void Bacteria::Divide(void){
	phenotype[0] /= 2;
	phenotype[1] /= 2;
	phenotype[2] /= 2;
	can_divide = false;
	can_metabo = false;
}

void Bacteria::Relive(double A, double B, double C, int geno){
	
	phenotype[0] = A;
	phenotype[1] = B;
	phenotype[2] = C;
	genotype = geno;
	Fitness();
	
	alive = true;
	just_died = false;
	can_divide = false;
	can_metabo = false;
	
}

//Getters


double Bacteria::A_in(void){
	return phenotype[0];
}

double Bacteria::B_in(void){
	return phenotype[1];
}

double Bacteria::C_in(void){
	return phenotype[2];
}


//Setter
void Bacteria::set_x(int x){
	pos[0] = x;
}

void Bacteria::set_y(int y){
	pos[1] = y;
}

void Bacteria::set_A(double new_A){
	phenotype[0] = new_A;
}

void Bacteria::set_B(double new_B){
	phenotype[1] = new_B;
}

void Bacteria::set_C(double new_C){
	phenotype[2] = new_C;
}

// ===========================================================================
//                              Protected Methods
// ===========================================================================

// ===========================================================================
//                              External Methods
// ===========================================================================

