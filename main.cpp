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
  //~ int T = 1;
  //Faire varier Ainit entre 0 et 50
	//~ double Ainit = 50;
	
	int t_simulation = 10000;
	
	//Finding statistics for various parameters
	ofstream output("Run_7.txt", ios::out | ios::trunc);
	output << "T A_init L S Dead \n" ;
	
	for(int t = 1; t <= 10; t ++){
		
		for(int A = 0; A <= 5; A++){
			
			int T = t*50;
			double Ainit = A*10;
		
			Simulation* sim = new Simulation(Raa,Rbb,Rab,Rbc,Pmut,Pdeath,Wmin,W,H,
			D,Ainit,A,B,T,t_simulation);
			
			sim->Algo_evol();
			cout << sim->Stat() << endl;
			output << sim->Stat();

			ImagePPM* miracle = new ImagePPM(32,sim->Bacterias);
			string name_im = "T" + to_string(T) + "Ainit" + to_string(Ainit) + ".ppm";
			miracle->save(name_im);
				
			delete miracle;
			delete sim;
		
		}
		
	}
	
	output.close();
	
  return 0;
}
