
// ===========================================================================
//                                  Includes
// ===========================================================================

#include "Bacteria.h"
#include "Population.h"
#include "Environment.h"

#include <fstream>
#include <cstring>
#include <iostream>

// ===========================================================================
//                       Definition of static attributes
// ===========================================================================


// ===========================================================================
//                                Constructors
// ===========================================================================

// Constructor
Environment::Environment(int W, int H, double D, double A_init) {
	this->W = W;
	this->H = H;
	this->D = D;
	
	A_out = new double*[W];
	
	for(int i = 0; i<W; i++){
		A_out[i] = new double[H];
		for(int j = 0; j<H; j++){
			A_out[i][j] = A_init;
		}
	}
	
	B_out = new double*[W];
	
	for(int i = 0; i<W; i++){
		B_out[i] = new double[H];
		for(int j = 0; j<H; j++){
			B_out[i][j] = 0;
		}
	}
	
	C_out = new double*[W];
	
	for(int i = 0; i<W; i++){
		C_out[i] = new double[H];
		for(int j = 0; j<H; j++){
			C_out[i][j] = 0;
		}
	}
	
	A_out_next = new double*[W];
	
	for(int i = 0; i<W; i++){
		A_out_next[i] = new double[H];
		memcpy(A_out_next[i], A_out[i], sizeof(double)*H);
	}
	
	B_out_next = new double*[W];
	
	for(int i = 0; i<W; i++){
		B_out_next[i] = new double[H];
		memcpy(B_out_next[i], B_out[i], sizeof(double)*H);
	}
	
	C_out_next = new double*[W];
	
	for(int i = 0; i<W; i++){
		C_out[i] = new double[H];
		memcpy(C_out_next[i], C_out[i], sizeof(double)*H);
	}
	
}


// ===========================================================================
//                                 Destructor
// ===========================================================================

Environment::~Environment() {
	
	for(int i = 0; i<W; i++){
		delete[] A_out[i];
		delete[] B_out[i];
		delete[] C_out[i];
		delete[] A_out_next[i];
		delete[] B_out_next[i];
		delete[] C_out_next[i];
	}
	delete[] A_out;
	delete[] B_out;
	delete[] C_out;
	delete[] A_out_next;
	delete[] B_out_next;
	delete[] C_out_next;
}

// ===========================================================================
//                               Public Methods
// ===========================================================================

void Environment::diffuse(int x, int y){
	
	double A_next = A_out[x][y];
	double B_next = B_out[x][y];
	double C_next = C_out[x][y];
	for(int i = -1; i <= 1; i++){
		for(int j = -1; j<= 1; j++){
			A_next += D*A_out[(x+i+W)%W][(y+j+H)%H];
			B_next += D*B_out[(x+i+W)%W][(y+j+H)%H];
			C_next += D*C_out[(x+i+W)%W][(y+j+H)%H];
		}
	}
	A_next -= 9*D*A_out[x][y];
	B_next -= 9*D*B_out[x][y];
	C_next -= 9*D*C_out[x][y];
	
	A_out_next[x][y] = A_next;
	B_out_next[x][y] = B_next;
	C_out_next[x][y] = C_next;
	
}

void Environment::diffuse_all(void){
	for(int i = 0; i<W; i++){
		for(int j = 0; j<H; j++){
			this->diffuse(i,j);
		}
	}
	for(int i = 0; i<W; i++){
		memcpy(A_out[i], A_out_next[i], sizeof(double)*H);
		memcpy(B_out[i], B_out_next[i], sizeof(double)*H);
		memcpy(C_out[i], C_out_next[i], sizeof(double)*H);
	}
}

// ===========================================================================
//                              Protected Methods
// ===========================================================================

// ===========================================================================
//                              External Methods
// ===========================================================================


