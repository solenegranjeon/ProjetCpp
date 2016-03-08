

#ifndef POPULATION_H__
#define POPULATION_H__
// ===========================================================================
//                                  Includes
// ===========================================================================

#include <cstdio>
#include <cstdlib>
#include <string>

using namespace std;

class Population {
	
	friend class Simulation;
	
	public :
		// =========================================================================
		//                               Constructors
		// =========================================================================
		
		Population() = delete;
		Population(const Population&) = delete;
		Population& operator=(const Population&) = delete;
		Population(double, double, double, double, double, double, double, int,int,int,int);
		
		// =========================================================================
		//                                Destructor
		// =========================================================================
		
		~Population(); 

		// =========================================================================
		//                                  Getters
		// =========================================================================
		
		bool get_Status(int,int);
		
		// =========================================================================
		//                                  Setters
		// =========================================================================

		
		// =========================================================================
		//                                 Operators
		// =========================================================================

		// =========================================================================
		//                              Public Methods
		// =========================================================================
		void mutation_all(void);
		void death_all(void);
		void fitness_all(void);
	protected :
		// =========================================================================
		//                             Protected Methods
		// =========================================================================

		// =========================================================================
		//                                Attributes
		// =========================================================================
		
		//Matrix containing pointers to Bacterias at the right position
		Bacteria*** pop;
		
		//Attributes of the population
		int pop_A;
		int pop_B;
		int pop_Dead;
		
		int W;
		int H;
		
		//Attributes needed to create bacterias
		double Raa;
		double Rbb;
		double Rab;
		double Rbc;
		double Pmut;
		double Pdeath;
		double Wmin;
		
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

