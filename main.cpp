//http://liris.cnrs.fr/~crocaber/3Bim/

// ===========================================================================
//                                  Includes
// ===========================================================================

#include <stdlib.h>
#include <stdio.h>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <ctime>
#include <string>
#include <algorithm>
#include <random>

#include "Bacteria.h"
#include "Population.h"
#include "Environment.h"
#include "Simulation.h"
#include "ImagePPM.h"

using namespace std;

// ===========================================================================
//                            Function declarations
// ===========================================================================


// ===========================================================================
//                                    MAIN
// ===========================================================================
int main(int argc,char* argv[]) {

  //Parameters:
  double Raa = 0.1;
  double Rbb = 0.1;
  double Rab = 0.1;
  double Rbc = 0.1;
  
  int W = 32;
  int H = 32;
  int A = W*H/2;
  int B = W*H/2;
  double D = 0.1;
  
  double Pmut = 0;
  double Pdeath = 0.02;
  double Wmin = 0.001;
  
  //Faire varier T entre 1 et 500
  double T = 250;
  //Faire varier Ainit entre 0 et 50
	double Ainit = 25;
	
	//10000 normalement
	double t_simulation = 10000;
   
  Bacteria* bact = new Bacteria(Raa,Rbb,Rab,Rbc,Pmut,Pdeath,Wmin,0,0,1);  
   
  Population* pop = new Population(Raa,Rbb,Rab,Rbc,Pmut,Pdeath,Wmin,W,H,W*H/2,W*H/2);
  
  Environment* envir = new Environment(W,H,D,Ainit);
  envir->diffuse_all();
  
  Simulation* sim = new Simulation(Raa,Rbb,Rab,Rbc,Pmut,Pdeath,Wmin,W,H,
  D,Ainit,A,B,T,t_simulation);
  
  sim->Algo_evol();
  cout << sim->Stat() << endl;

	ImagePPM* miracle = new ImagePPM(32,sim->Bacterias);
	miracle->save("BacteriesT250A25.ppm");
		
	delete miracle;

	delete bact;
  delete envir;
	delete pop;
	delete sim;
  
  return 0;
}
