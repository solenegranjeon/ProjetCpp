

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
	
	friend class Simulation;
	friend class Population;
	
	public :
		// =========================================================================
		//                               Constructors
		// =========================================================================
		
		Bacteria() = delete;
		Bacteria(const Bacteria&) = delete;
		Bacteria(double, double, double, double, double, double, double, int, int, int);
		
		// =========================================================================
		//                                Destructor
		// =========================================================================
		
		~Bacteria(); 

		// =========================================================================
		//                                  Getters
		// =========================================================================
		
		double A_in(void);
		double B_in(void);
		double C_in(void);
		
		// =========================================================================
		//                                  Setters
		// =========================================================================
		void set_x(int);
		void set_y(int);
		void set_A(double);
		void set_B(double);
		void set_C(double);
		
		// =========================================================================
		//                                 Operators
		// =========================================================================

		// =========================================================================
		//                              Public Methods
		// =========================================================================

		void Mutation(void);
		void Death(void);
		void Fitness(void);
		void Divide(void);
		void Relive(double,double,double,int);


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
	double Wmin;
	
	// Parameters specific to the bacteria
	int* pos; //[x,y]
	double* phenotype; //[A,B,C]
	int genotype; //1:Ga 2:Gb
	double fitness;
	
	bool alive;
	bool just_died;
	bool can_divide;
	bool can_metabo;

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
