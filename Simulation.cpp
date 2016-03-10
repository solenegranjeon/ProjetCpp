// ===========================================================================
//                                  Includes
// ===========================================================================

#include "Simulation.h"

// ===========================================================================
//                       Definition of static attributes
// ===========================================================================


// ===========================================================================
//                                Constructors
// ===========================================================================

Simulation::Simulation(double Raa, double Rbb, double Rab, double Rbc, 
double Pmut, double Pdeath, double Wmin, int W, int H, double D, 
double A_init, int A, int B, int T, int t_max) {
	
	this->Raa = Raa;
	this->Rbb = Rbb;
	this->Rab = Rab;
	this->Rbc = Rbc;
	this->Pmut = Pmut;
	this->Pdeath = Pdeath;
	this->Wmin = Wmin;
	
	this->Ga_init = A;
	this->Gb_init = B;
		
	this->W = W;
	this->H = H;
	this->D = D;
	this->A_init = A_init;
	
	this->t_max = t_max;
	this->T = T;
	this->t_cur = 1;
	
	population = new Population(Raa, Rbb, Rab, Rbc, Pmut, Pdeath, Wmin, W, H, A, B);
	envir = new Environment(W, H, D, A_init);
	
	Bacterias = new int*[W];
	for(int rows = 0; rows < H; rows ++){
		Bacterias[rows] = new int[H];
		for(int col = 0; col < W; col ++){
			if(population->pop[rows][col]->genotype == 1){
				Bacterias[rows][col] = 1;
			}
			else{
				Bacterias[rows][col] = 2;
			}
		}
	}
	
}




// ===========================================================================
//                                 Destructor
// ===========================================================================

Simulation::~Simulation() {
	delete population;
	delete envir;
	for( int row = 0; row < H; row ++){
		delete[] Bacterias[row];
		Bacterias[row] = nullptr;
	}
	delete[] Bacterias;
	Bacterias = nullptr;
}

// ===========================================================================
//                               Public Methods
// ===========================================================================

void Simulation::Algo_evol(void){
	
	step_Metabolique();
	population->fitness_all();
	
	while(t_cur<=t_max){
			
		// Every T, reinitialization of the environment
		if(t_cur % T == 0){
			envir->reinit();
		}
	
		//Diffusion of A,B,C in the environment
		envir->diffuse_all();
		
		//Bacterias die randomly and diffuse their content in the environment
		step_Death();
		
		//Step mutation
		population->mutation_all();
		
		//Step division
		step_Division();
		
		//Step Metabolique
		step_Metabolique();
		
		//Step living and adjusting the fitness
		population->fitness_all();
		
		//Maj bool of Bacterias
		step_Maj_Bool();
		
		//Maj Bacterias
		step_Maj_Bacterias();
		
		t_cur ++;
		
	}
	
}


void Simulation::step_Metabolique(void){
	
	for(int row = 0; row < W; row++){
		for(int col = 0; col < H; col ++){
		
			if(population->pop[row][col]->can_metabo == true){
			
				if(population->pop[row][col]->genotype == 1){
					
					float A_out = envir->A_out[row][col];
					float A = population->pop[row][col]->phenotype[0];
					
					float new_A_out = envir->A_out[row][col];
					float new_A = population->pop[row][col]->phenotype[0];
					float new_B = population->pop[row][col]->phenotype[1];
					
					for(int index = 0; index < 10; index ++){
						new_A_out -= (new_A_out * Raa) * 0.1 ;
					}
					
					for(int index = 0; index < 10; index ++){
						new_A += (A_out * Raa - A * Rab) * 0.1 ;
					}
					
					for(int index = 0; index < 10; index ++){
						new_B += (A * Rab) * 0.1;
					}
					
					//Modifies A_out in envir, A and B in the Bacteria
					envir->set_A(row,col,new_A_out);
					population->pop[row][col]->set_A(new_A);
					population->pop[row][col]->set_B(new_B);
										
				}
				
				else{
					
					float B_out = envir->B_out[row][col];
					float B = population->pop[row][col]->phenotype[1];
					
					float new_B_out = envir->B_out[row][col];
					float new_B = population->pop[row][col]->phenotype[1];
					float new_C = population->pop[row][col]->phenotype[2];
					
					for(int index = 0; index < 10; index ++){
						new_B_out -= (new_B_out * Rbb) * 0.1;
					}
					
					for(int index = 0; index < 10; index ++){
						new_B += (B_out * Rbb - new_B * Rbc) * 0.1;
					}
					
					for(int index = 0; index < 10; index ++){
						new_C += (B * Rbc) * 0.1;
					}
					
					//Modifies B_out in envir, B and C in the Bacteria
					envir->set_B(row,col,new_B_out);
					population->pop[row][col]->set_B(new_B);
					population->pop[row][col]->set_C(new_C);
					
				}
			
			}
		
		}
	}
	
}

void Simulation::step_Death(void){
	//Bacterias die randomly
	population->death_all();
	
	//The just dead bacterias diffuse their content in the environment.
	for(int i = 0; i < W; i++){
		for(int j = 0; j < H; j++){
					
			if(population->pop[i][j]->just_died == true){ //The Bacteria just died
				
				int x = i;
				int y = j;
				
				double new_A = envir->get_A(x,y) + population->pop[i][j]->A_in();
				double new_B = envir->get_B(x,y) + population->pop[i][j]->B_in();
				double new_C = envir->get_C(x,y) + population->pop[i][j]->C_in();
					
				envir->set_A(x,y,new_A);
				envir->set_B(x,y,new_B);
				envir->set_C(x,y,new_C);
					
				population->pop[i][j]->just_died = false;
					
			}
			
		}
	}
	
}

void Simulation::step_Division(void){
	
	//1)We find the gaps and order them randomly
	//a.The number of gaps is the number of dead bacterias
	int nb_gaps = population->pop_Dead;
	
	if(nb_gaps > 0){

		//b.We gather their position
		int** pos_gaps = new int*[nb_gaps];
		int index_gap = 0;
		for(int r = 0; r < H; r++){
			for(int c = 0; c < W; c++){
				if(population->pop[r][c]->alive == false){
					pos_gaps[index_gap] = new int[2];
					pos_gaps[index_gap][0] = r;
					pos_gaps[index_gap][1] = c;
					index_gap ++;
				}
			}
		}
		
		//c.Order them randomly
		//http://www.cplusplus.com/reference/algorithm/random_shuffle/
		random_shuffle(&pos_gaps[0],&pos_gaps[nb_gaps-1]);
		
		//2)For each gap, we find the bacteria next to it with the highest fitness

		for( int index_gap = 0; index_gap < nb_gaps; index_gap++){ //For each gap
			
			//Coordinates of the Gap
			int x_gap = pos_gaps[index_gap][0];
			int y_gap = pos_gaps[index_gap][1];
			
			//Find the number of neigbors
			int nb_neighb = count_Neighb(x_gap, y_gap);
						
			if( nb_neighb > 0){ //If there are any,
				
				double max_fitness = 0;

				//Find the best fitness from the fitness of all neighbors
				for(int up_down = 0; up_down < 3; up_down ++){ //up and down neighbs
					
					if(population->pop[(x_gap-1+up_down+W)%W][(y_gap+1+H)%H]->can_divide == true){ //up;
						
						if(population->pop[(x_gap-1+up_down+W)%W][(y_gap+1+H)%H]->fitness > max_fitness){
							max_fitness = population->pop[(x_gap-1+up_down+W)%W][(y_gap+1+H)%H]->fitness;
						}
					}
					
					if(population->pop[(x_gap-1+up_down+W)%W][(y_gap-1+H)%H]->can_divide == true){ // down
						if(population->pop[(x_gap-1+up_down+W)%W][(y_gap-1+H)%H]->fitness > max_fitness){
							max_fitness = population->pop[(x_gap-1+up_down+W)%W][(y_gap-1+H)%H]->fitness;
						}
					}
					
				}
				
				if(population->pop[(x_gap-1+W)%W][(y_gap+H)%H]->can_divide == true){ // left neighb
					if(population->pop[(x_gap-1+W)%W][(y_gap+H)%H]->fitness > max_fitness){
						max_fitness = population->pop[(x_gap-1+W)%W][(y_gap+H)%H]->fitness;
					}
				}
				
				if(population->pop[(x_gap+1+W)%W][(y_gap+H)%H]->can_divide == true){ // right neighb
					if(population->pop[(x_gap+1+W)%W][(y_gap+H)%H]->fitness > max_fitness){
						max_fitness = population->pop[(x_gap+1+W)%W][(y_gap+H)%H]->fitness;
					}
				}
				
				//Find the bacterias with this fitness
				vector<int> x_best = {};
				vector<int> y_best = {};
				
				for(int up_down = 0; up_down < 3; up_down ++){ //up and down neighbs
					
					if(population->pop[(x_gap-1+up_down+W)%W][(y_gap+1+H)%H]->can_divide == true){ //up;
						if(population->pop[(x_gap-1+up_down+W)%W][(y_gap+1+H)%H]->fitness == max_fitness){
							x_best.push_back((x_gap-1+up_down+W)%W);
							y_best.push_back((y_gap+1+H)%H);
						}
					}
					
					if(population->pop[(x_gap-1+up_down+W)%W][(y_gap-1+H)%H]->can_divide == true){ // down
						if(population->pop[(x_gap-1+up_down+W)%W][(y_gap-1+H)%H]->fitness == max_fitness){
							x_best.push_back((x_gap-1+up_down+W)%W);
							y_best.push_back((y_gap-1+H)%H);
						}
					}
					
				}
				
				if(population->pop[(x_gap-1+W)%W][(y_gap+H)%H]->can_divide == true){ // left neighb
					if(population->pop[(x_gap-1+W)%W][(y_gap+H)%H]->fitness == max_fitness){
						x_best.push_back((x_gap-1+W)%W);
						y_best.push_back((y_gap+H)%H);
					}
				}
				
				if(population->pop[(x_gap+1+W)%W][(y_gap+H)%H]->can_divide == true){ // right neighb
					if(population->pop[(x_gap+1+W)%W][(y_gap+H)%H]->fitness == max_fitness){
						x_best.push_back((x_gap+1+W)%W);
						y_best.push_back((y_gap+H)%H);
					}
				}
				
				//Randomly chose one of them
				int index = 0;
				if(x_best.size()>1){
					index = rand()%x_best.size();
				}
								
				//3)This bacteria divides itself into 2:
				//a.We split its concentration of A,B,C into 2
				population->pop[x_best[index]][y_best[index]]->Divide();
				 
				//b.Modifie the bacteria at the position
				double ph_A = population->pop[x_best[index]][y_best[index]]->phenotype[0];
				double ph_B = population->pop[x_best[index]][y_best[index]]->phenotype[1];
				double ph_C = population->pop[x_best[index]][y_best[index]]->phenotype[2];
				int geno = population->pop[x_best[index]][y_best[index]]->genotype;
	
				population->pop[x_gap][y_gap]->Relive(ph_A,ph_B,ph_C,geno);
				
				//c. Change stats of population
				population->pop_Dead --;
				if(population->pop[x_gap][y_gap]->genotype == 1){
					population->pop_A ++;
				}
				else{
					population->pop_B ++;
				}
				
			}

		}
			
		//4) Delete pos_gaps
		for(int i = 0; i< nb_gaps; i++){
			delete[] pos_gaps[i];
			pos_gaps[i] = nullptr;
		}
		delete[] pos_gaps;
		pos_gaps = nullptr;
		
	}
	
}

void Simulation::step_Maj_Bool(void){
	
	for(int row = 0; row < W; row ++){
		for(int col = 0; col < H; col ++){
		
			if(population->pop[row][col]->alive == true){
			
				population->pop[row][col]->can_divide = true;
				population->pop[row][col]->can_metabo = true;
				population->pop[row][col]->just_died = false;
			
			}
		
		}
	}
	
}

string Simulation::Stat(void){
	string res = "" + to_string(T) + " " + to_string(A_init) + " " + to_string(population->pop_A) + " " + 
	to_string(population->pop_B) + " " + to_string(population->pop_Dead) 
	+ "\n" ;
	return res;
}

int Simulation::count_Neighb(int x_gap, int y_gap){
	
	int res = 0;
	
	for(int up_down = 0; up_down < 3; up_down ++){ //up and down neighs
		if(population->pop[(x_gap-1+up_down+W)%W][(y_gap+1+H)%H]->can_divide == true){ //up
			res ++;
		}
		if(population->pop[(x_gap-1+up_down+W)%W][(y_gap-1+H)%H]->can_divide == true){ // down
			res ++;
		}
	}
	if(population->pop[(x_gap-1+W)%W][(y_gap+H)%H]->can_divide == true){ // left neighb
		res ++;
	}
	if(population->pop[(x_gap+1+W)%W][(y_gap+H)%H]->can_divide == true){ // right neighb
		res ++;
	}
	
	return res;
}

void Simulation::step_Maj_Bacterias(void){
	
	for(int rows = 0; rows < H; rows ++){
		for(int col = 0; col < W; col ++){
			if(population->pop[rows][col]->alive == false){
				Bacterias[rows][col] = 0;
			}
			else if(population->pop[rows][col]->genotype == 1){
				Bacterias[rows][col] = 1;
			}
			else{
				Bacterias[rows][col] = 2;
			}
		}
	}
	
}



// ===========================================================================
//                              Protected Methods
// ===========================================================================

// ===========================================================================
//                              External Methods
// ===========================================================================


