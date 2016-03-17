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
  double D = 0.1;
  
  double Pmut = 0;
  double Pdeath = 0.02;
  double Wmin = 0.001;
  
  //Faire varier T entre 1 et 500
  int T = 750;
  //Faire varier Ainit entre 0 et 50
	double Ainit = 1;
	
	int t_simulation = 10000;
	
	//Finding statistics for various parameters
	ofstream output("Run_5000.txt", ios::out | ios::trunc);
	output << "T A_init L S Dead \n" ;
	
	ofstream output2("Run_5000.txt", ios::out | ios::trunc);
	output2 << "T A_init Code \n" ;
	
	//~ for(int t = 1; t <= 28; t ++){
		//~ 
		//~ for(int A = 0; A <= 5; A++){
			
			//~ int T = t*25;
			//~ double Ainit = A*10;
		
			Simulation* sim = new Simulation(Raa,Rbb,Rab,Rbc,Pmut,Pdeath,Wmin,W,H,
			D,Ainit,pop_A,pop_B,T,t_simulation);
			
			sim->Algo_evol();
			cout << sim->Stat() << endl;
			cout << sim->Graph_Vals() << endl;
			output << sim->Stat();
			output2 << sim->Graph_Vals();

			ImagePPM* miracle = new ImagePPM(32,sim->Bacterias);
			string name_im = "T" + to_string(T) + "Ainit" + to_string(Ainit) + ".ppm";
			miracle->save(name_im);
				
			delete miracle;
			delete sim;
		
		//~ }
		
	//~ }
	
	output.close();
	output2.close();
	
  return 0;
}
