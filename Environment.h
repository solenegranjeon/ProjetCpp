

#ifndef ENVIRONMENT_H__
#define ENVIRONMENT_H__
// ===========================================================================
//                                  Includes
// ===========================================================================

#include <cstdio>
#include <cstdlib>

class Environment {
	
	friend class Simulation;
	
	public :
		// =========================================================================
		//                               Constructors
		// =========================================================================
		
		Environment() = delete;
		Environment(const Environment&) = delete;
		Environment& operator=(const Environment&) = delete;
		Environment(int, int, double, double);
		
		// =========================================================================
		//                                Destructor
		// =========================================================================
		
		~Environment(); 

		// =========================================================================
		//                                  Getters
		// =========================================================================

		double get_A(int,int);
		double get_B(int,int);
		double get_C(int,int);

		// =========================================================================
		//                                  Setters
		// =========================================================================
		void set_A(int, int, double);
		void set_B(int, int, double);
		void set_C(int, int, double);
		
		// =========================================================================
		//                                 Operators
		// =========================================================================

		// =========================================================================
		//                              Public Methods
		// =========================================================================
		
		void diffuse(int,int);
		void diffuse_all(void);
		void reinit();

	protected :
		// =========================================================================
		//                             Protected Methods
		// =========================================================================

		// =========================================================================
		//                                Attributes
		// =========================================================================

		int W;
		int H;
		double D;
		
		double A_init;
		
		double** A_out;
		double** B_out;
		double** C_out;
		
		double** A_out_next;
		double** B_out_next;
		double** C_out_next;
		
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


