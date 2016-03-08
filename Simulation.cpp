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
	
	this->Gaps = new int*[W];
	for (int rows = 0; rows < H; rows++){
		Gaps[rows] = new int[H];
		for( int col = 0; col <W; col++){
			Gaps[rows][col] = 1;
		}
	}
	
	population = new Population(Raa, Rbb, Rab, Rbc, Pmut, Pdeath, Wmin, W, H, A, B);
	envir = new Environment(W, H, D, A_init);
}




// ===========================================================================
//                                 Destructor
// ===========================================================================

Simulation::~Simulation() {
	delete population;
	delete envir;
	for( int row = 0; row < H; row ++){
		delete[] Gaps[row];
		Gaps[row] = nullptr;
	}
	delete[] Gaps;
	Gaps = nullptr;
}

// ===========================================================================
//                               Public Methods
// ===========================================================================

void Simulation::Algo_evol(void){
	

	
	while(t_cur<=t_max){
		
		printf("Iteration %d :\n",t_cur);
		
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
		
		//Step living and adjusting the fitness
		population->fitness_all();
		
		t_cur ++;
	}
	
}

void Simulation::step_Death(void){
	//Bacterias die randomly
	population->death_all();
	
	//The dead bacterias diffuse their content in the environment
	for(int i = 0; i < W; i++){
		for(int j = 0; j < H; j++){
					
			if(population->pop[i][j] != nullptr){
				
				if(population->get_Status(i,j) == false){ // Bacteria is dead
					
					int x = i;
					int y = j;
					
					double new_A = envir->get_A(x,y) + population->pop[i][j]->A_in();
					double new_B = envir->get_B(x,y) + population->pop[i][j]->B_in();
					double new_C = envir->get_C(x,y) + population->pop[i][j]->C_in();
					
					envir->set_A(x,y,new_A);
					envir->set_B(x,y,new_B);
					envir->set_C(x,y,new_C);
					
					Gaps[x][y] = 0;
					
					delete population->pop[i][j];
					population->pop[i][j] = nullptr;
					
				}
			}
			
		}
	}
	
}

void Simulation::step_Division(void){
	
	//1)We find the gaps and order them randomly
	//a.The number of gaps is the number of dead bacterias
	int nb_gaps = population->pop_Dead;
	
	if(nb_gaps > 0){

		printf("Nb of holes: %d.\n\n",nb_gaps);
		
		//b.We gather their position
		int** pos_gaps = new int*[nb_gaps];
		int index_gap = 0;
		for(int r = 0; r < H; r++){
			for(int c = 0; c < W; c++){
				if(Gaps[r][c] == 0){
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
			
				if( nb_neighb > 0){
				
				int max_fitness = 0;
				int index_best_bact_x = -1;
				int index_best_bact_y = -1;	
				
				// And Gather the neighbors:
				//~ 
				//~ int neighb [nb_neighb];
				//~ 
				//~ int index_tab = 0;
		//~ 
				//~ for(int up_down = 0; up_down < 3; up_down ++){ //up and down neighbs
					//~ 
					//~ if(Gaps[(x_gap-1+up_down+W)%W][(y_gap+1+H)%H] != 0){ //up
						//~ for(int index_bact = 0; index_bact < W*H; index_bact ++){
							//~ if(population->pop[index_bact] != nullptr){
								//~ if(population->pop[index_bact]->pos[0] == (x_gap-1+up_down+W)%W && population->pop[index_bact]->pos[1] == (y_gap+1+H)%H){
									//~ neighb[index_tab] = index_bact;
								//~ }
							//~ }
						//~ }
						//~ index_tab ++;
					//~ }
					//~ 
					//~ if(Gaps[(x_gap-1+up_down+W)%W][(y_gap-1+H)%H] != 0){ // down
						//~ for(int index_bact = 0; index_bact < W*H; index_bact ++){
							//~ if(population->pop[index_bact] != nullptr){
								//~ if(population->pop[index_bact]->pos[0] == (x_gap-1+up_down+W)%W && population->pop[index_bact]->pos[1] == (y_gap-1+H)%H){
									//~ neighb[index_tab] = index_bact;
								//~ }
							//~ }
						//~ }
						//~ index_tab ++;
					//~ }
					//~ 
				//~ }
				//~ 
				//~ if(Gaps[(x_gap-1+W)%W][(y_gap+H)%H] != 0){ // left neighb
					//~ for(int index_bact = 0; index_bact < W*H; index_bact ++){
						//~ if(population->pop[index_bact] != nullptr){
							//~ if(population->pop[index_bact]->pos[0] ==(x_gap-1+W)%W && population->pop[index_bact]->pos[1] == (y_gap+H)%H){
								//~ neighb[index_tab] = index_bact;
							//~ }
						//~ }
					//~ }
					//~ index_tab ++;
				//~ }
				//~ 
				//~ if(Gaps[(x_gap+1+W)%W][(y_gap+H)%H] != 0){ // right neighb
					//~ for(int index_bact = 0; index_bact < W*H; index_bact ++){
						//~ if(population->pop[index_bact] != nullptr){
							//~ if(population->pop[index_bact]->pos[0] ==(x_gap+1+W)%W && population->pop[index_bact]->pos[1] == (y_gap+H)%H){
								//~ neighb[index_tab] = index_bact;
							//~ }
						//~ }
					//~ }
					//~ index_tab ++;
				//~ }
				
				//To check:
				//~ printf("Gap %d, %d neighbors. Index of neighb: ",index_gap,nb_neighb);
				//~ for(int i=0; i<8; i++){
					//~ printf("%d,",neighb[i]);
				//~ }
				//~ printf("\n");
				
				//Shuffle neighbors
				//~ random_shuffle(&neighb[0],&neighb[nb_neighb-1]);

				//Find best fitness and corresponding bacteria
				//~ if(nb_neighb != 0){
					//~ for(int index_n = 0; index_n < nb_neighb; index_n ++){
						//~ if(population->pop[neighb[index_n]]->fitness > max_fitness && neighb[index_n] != -1 ){
							//~ index_best_bact = neighb[index_n];
							//~ max_fitness = population->pop[neighb[index_n]]->fitness;
						//~ }
					//~ }
				//~ }		
				
				//3)This bacteria divides itself into 2:
				//a.We split its concentration of A,B,C into 2
				//~ printf("index best bact %d \n",index_best_bact);
				//~ population->pop[index_best_bact]->Divide();
				 
				//b.create a copy of this bacteria at the position of the gap.
				
				//~ Bacteria* newBact = new Bacteria(*(population->pop[index_best_bact]));
				//~ newBact->set_x(x_gap);
				//~ newBact->set_y(y_gap);
				
				//c. add it to the population
				//~ population->pop[x_gap][y_gap] = newBact;
				
				//d. put a 1 at the position of the new bacteria in Gaps
				//~ Gaps[x_gap][y_gap] = 1;
				
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

string Simulation::Stat(void){
	string res = "" + to_string(population->pop_A) + " " + 
	to_string(population->pop_B) + " " + to_string(population->pop_Dead) 
	+ "\n" ;
	return res;
}

int Simulation::count_Neighb(int x_gap, int y_gap){
	int res = 0;
	for(int up_down = 0; up_down < 3; up_down ++){ //up and down neighs
		if(Gaps[(x_gap-1+up_down+W)%W][(y_gap+1+H)%H] != 0){ //up
			res ++;
		}
		if(Gaps[(x_gap-1+up_down+W)%W][(y_gap-1+H)%H] != 0){ // down
			res ++;
		}
	}
	if(Gaps[(x_gap-1+W)%W][(y_gap+H)%H] != 0){ // left neighb
		res ++;
	}
	if(Gaps[(x_gap+1+W)%W][(y_gap+H)%H] != 0){ // right neighb
		res ++;
	}
	return res;
}


// ===========================================================================
//                              Protected Methods
// ===========================================================================

// ===========================================================================
//                              External Methods
// ===========================================================================


