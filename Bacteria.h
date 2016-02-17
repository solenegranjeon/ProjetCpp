

#ifndef BACTERIA_H__
#define BACTERIA_H__
// ===========================================================================
//                                  Includes
// ===========================================================================

#include <cstdio>
#include <cstdlib>
#include <random>
#include <chrono>

class Bacteria {
	
	public :
		// =========================================================================
		//                               Constructors
		// =========================================================================
		
		Bacteria() = delete;
		Bacteria(const Bacteria&);
		//~ Bacteria(double, double, double, double, double, double, int, int);
		
		// =========================================================================
		//                                Destructor
		// =========================================================================
		
		~Bacteria(); 

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

		void Mutation(void);

	protected :
		// =========================================================================
		//                             Protected Methods
		// =========================================================================

		// =========================================================================
		//                                Attributes
		// =========================================================================

	// Simulation parameters
	double Raa;
	double Rbb;
	double Rab;
	double Rbc;
	double Pmut;
	double Pdeath;
	
	// Parameters specific to the bacteria
	int* pos; //[x,y]
	bool alive;
	bool can_divide;
	double* phenotype; //[A,B,C]
	int genotype; //1:Ga 2:Gb
	double fitness;

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
