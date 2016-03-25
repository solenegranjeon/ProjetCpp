

#ifndef SIMULATION_H__
#define SIMULATION_H__
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

using namespace std;

class Simulation {
	
	public :
		//To display bacterias
		int** Bacterias;
	
		// =========================================================================
		//                               Constructors
		// =========================================================================
		
		Simulation() = delete;
		Simulation(const Simulation&) = delete;
		Simulation& operator=(const Simulation&) = delete;
		Simulation(double, double, double, double, double, double, double, 
		int, int, double, double, int, int, int, int);
		
		// =========================================================================
		//                                Destructor
		// =========================================================================
		
		~Simulation(); 

		// =========================================================================
		//                                  Getters
		// =========================================================================

		// =========================================================================
		//                                  Setters
		// =========================================================================

		
		// =========================================================================
		//                                 Operators
		// =========================================================================

		// =========================================================================
		//                              Public Methods
		// =========================================================================
		void step_Death(void);
		void step_Division(void);
		void step_Metabolique(void);
		void step_Maj_Bool(void);
		void step_Maj_Pop(void);
		void step_Maj_Bacterias(void);
		
		int count_Neighb(int,int);
		
		void Algo_evol(void);
		
		string Stat(void);
		string Graph_Vals(void);
		
		//To test 
		void set_Concentrations(void);

	protected :
		// =========================================================================
		//                             Protected Methods
		// =========================================================================

		// =========================================================================
		//                                Attributes
		// =========================================================================
		
		//Parameters of the model
		//for the Bacterias
		double Raa;
		double Rbb;
		double Rab;
		double Rbc;
		double Pmut;
		double Pdeath;
		double Wmin;
		
		//for the Environment
		int W;
		int H;
		double D;
		double A_init;
		
		//for the Population
		int Ga_init;
		int Gb_init;
		
		//for the Simulation
		int t_cur;
		int T;
		int t_max;
		Population* population;
		Environment* envir;
		
		int nb_gaps;
		
		//To test program
		double A_total;
		double B_total;
		double C_total;
		double Total;
		
	// ===========================================================================
	//                            Getters' definitions
	// ===========================================================================


	// ===========================================================================
	//                            Setters' definitions
	// ===========================================================================

	// ===========================================================================
	//                           Operators' definitions
	// ===========================================================================

	// ===========================================================================
	//                        Inline functions' definition
	// ===========================================================================
	
};
#endif


