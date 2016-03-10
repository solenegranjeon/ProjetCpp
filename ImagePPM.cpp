
// ===========================================================================
//                                  Includes
// ===========================================================================

#include "ImagePPM.h"

// ===========================================================================
//                       Definition of static attributes
// ===========================================================================

// ===========================================================================
//                                Constructors
// ===========================================================================
ImagePPM::ImagePPM(){
	W=0;
	H=0;
	MaxVal=0;
	tab=nullptr;
}

ImagePPM::ImagePPM(const ImagePPM& im){
	W=im.W;
	H=im.H;
	MaxVal=im.MaxVal;
	tab = new unsigned char[3*W*H];
	memcpy(tab, im.tab, sizeof(unsigned char)*W*H*3);
}

ImagePPM::ImagePPM(string name){
	string input;
	ifstream f;
	f.open(name.c_str(), ios::in);
	f >> input;
	f >> W;
	f >> H;
	f >> MaxVal;
	tab = new unsigned char[3*W*H];
	f.read((char*)tab, sizeof(char)*3*W*H);
	f.close();
}

ImagePPM::ImagePPM(int size, int** data){
	W=size;
	H=size;
	MaxVal=255;
	tab = new unsigned char[3*W*H];
	int index = 0;
	for(int x = 0; x< size; x++){
		for(int y = 0; y< size; y++){
			if(data[x][y]==1){
				tab[index]=(unsigned char)255;
				index++;
				tab[index]=(unsigned char)0;
				index++;
				tab[index]=(unsigned char)102;
				index++;
			}
			else if(data[x][y] == 2){
				tab[index]=(unsigned char)153;
				index++;
				tab[index]=(unsigned char)255;
				index++;
				tab[index]=(unsigned char)255;
				index++;
			}
			else{
				tab[index]=(unsigned char)0;
				index++;
				tab[index]=(unsigned char)0;
				index++;
				tab[index]=(unsigned char)0;
				index++;
			
			}
		}
	}
}


// ===========================================================================
//                                 Destructor
// ===========================================================================
ImagePPM::~ImagePPM() {
	delete[] tab;
	tab = nullptr;
}

// ===========================================================================
//                               Public Methods
// ===========================================================================
void ImagePPM::save( string file ){
  ofstream f(file.c_str(), ios::out | ios::trunc | ios::binary);
  f << "P6\n" << W<< " " << H << "\n" << MaxVal << "\n";
  f.write((char*)tab, sizeof(char)*W*H*3);
  f.close();
}

void ImagePPM::desaturate( void ){
	for(int x = 0; x<W; x++){
		for(int y = 0; y<H; y++){
			double r = (double)tab[(x* H +y)*3];
			double g = (double)tab[(x* H +y)*3+1];
			double b = (double)tab[(x* H +y)*3+2];
			double m = 0.21*r+0.71*g+0.07*b;
			if(m<0.0){
				m=0.0;
			}
			if(m>MaxVal){
				m= (double)MaxVal;
			}
			tab[(x* H +y)*3] = (unsigned char)m;
			tab[(x* H +y)*3+1] = (unsigned char)m;
			tab[(x* H +y)*3+2] = (unsigned char)m;
		}
	}
}

void ImagePPM::gaussian_blur( double* matrix ){
	unsigned char* newtab = new unsigned char[W*H*3];
	
  for (int x = 0; x < W; x++){
		
    for (int y = 0; y < H; y++){
			
      for(int c = 0; c < 3; c++){
				
        double s   = 0.0;
        double sum = 0.0;
        
        for (int i = -1; i < 2; i++){
					
          for(int j = -1; j < 2; j++){
						  
						  if (x+i < W && x+i >= 0 && y+j < H && y+j >= 0){

              s   += (double)tab[((x+i)* H +(y+j))*3+c]*matrix[(i+1)+3*(j+1)];
              sum += matrix[(i+1)+3*(j+1)];
            }
            
          }
          
        }
        
        s /= sum;
        if (s > 255.0){
					s = 255.0;
				}
				if (s < 0.0){
					s = 0.0;
				}
				
				newtab[((x)*H +(y))*3+c] = (unsigned char)s;
			}
		}
	}
	memcpy(tab, newtab, sizeof(unsigned char)*W*H*3);
  delete[] newtab;
  newtab = nullptr;
}


// ===========================================================================
//                              Protected Methods
// ===========================================================================

// ===========================================================================
//                              External Methods
// ===========================================================================

