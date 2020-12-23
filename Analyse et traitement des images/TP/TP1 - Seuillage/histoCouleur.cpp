#include <stdio.h>
#include <iostream>
#include <fstream>
#include "image_ppm.h"

using namespace std;


int main(int argc, char* argv[])
{

  char cNomImgLue[250];
  int nH, nW, nTaille;
  int histoR[256];
  int histoG[256];
  int histoB[256];
  if (argc != 2) 
     {
       printf("Usage: ImageIn.pgm \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
	   for(int i = 0; i< 256; i++){
	 		histoR[i] = 0;
      histoG[i] = 0;
      histoB[i] = 0;
	}


   OCTET *ImgIn;
   
   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;

   int nTaille3 = nTaille * 3;
   allocation_tableau(ImgIn, OCTET, nTaille3);
   lire_image_ppm(cNomImgLue, ImgIn, nH * nW);

   fstream fs;
   fs.open("histoCouleur.dat", fstream::out);
	 for(int i = 0; i < nTaille3; i+=3){
		  int R = ImgIn[i];
      int G = ImgIn[i+1];
      int B = ImgIn[i+2];
		  histoR[R]++;
      histoG[G]++;
      histoB[B]++;
	}

	for(int i = 0; i< 256; i++){
	 	fs<<i<<" "<<histoR[i]<<" "<<histoG[i]<<" "<<histoB[i]<<endl;
	}
   fs.close();
}

