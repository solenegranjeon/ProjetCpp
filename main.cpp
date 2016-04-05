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

	srand(time(NULL));

  //Parameters:
  double Raa = 0.1;
  double Rbb = 0.1;
  double Rab = 0.1;
  double Rbc = 0.1;
  
  int W = 32;
  int H = 32;
  int pop_A = 512;
  int pop_B = 512;
  //BONUS: Faire varier D entre 0 et 0.1
  double D = 0;
  
  //Pmut soit 0 soit 0.001
  double Pmut = 0;
  double Pdeath = 0.02;
  double Wmin = 0.001;
  
  int t_simulation = 10000;
  
  //~ double Ainit = 25;
  //~ int T = 250;
	
	//Finding statistics for various parameters
	ofstream output("D0v2.txt", ios::out | ios::app);
	output << "T A_init L S Dead Code \n" ;
	
	//Faire varier T entre 1 et 1500 de 10 en 10
  //Faire varier Ainit entre 0 et 50 de 2 en 2
  
	for(int A = 0; A <= 1; A++){
		
		for(int t = 1; t <= 17; t ++){ // 700 à 860
			
			//~ double Ainit = A*2.5;
			//~ int T = (Ainit + 134) * 6 + 20*t;
			
			double Ainit = 48 + 2*A;
			int T = 680 + 10*t;
			
			Simulation* sim = new Simulation(Raa,Rbb,Rab,Rbc,Pmut,Pdeath,Wmin,W,H,
			D,Ainit,pop_A,pop_B,T,t_simulation);
			
			sim->Algo_evol();
			
			cout << sim->Stat();
			
			output << sim->Stat();

			//~ ImagePPM* miracle = new ImagePPM(32,sim->Bacterias);
			//~ string name_im = "T" + to_string(T) + "Ainit" + to_string(Ainit) + ".ppm";
			//~ miracle->save(name_im);
				
			//~ delete miracle;
			delete sim;
		
		}

	}
	
	output.close();
	
	//~ system(Rscript nomdufichier);
	
  return 0;
}
