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

#include "Bacteria.h"
#include "Population.h"
#include "Environment.h"
#include "Simulation.h"

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
  double D = 0.1;
  
  double Pmut = 0;
  double Pdeath = 0.02;
  
  double T = 500;
	double Ainit = 50;
	
	double t_simulation = 10000;
  
  
  
  return 0;
}
