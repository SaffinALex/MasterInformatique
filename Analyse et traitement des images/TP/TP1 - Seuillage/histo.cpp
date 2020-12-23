#include <stdio.h>
#include <iostream>
#include <fstream>
#include "image_ppm.h"

using namespace std;


int main(int argc, char* argv[])
{

  char cNomImgLue[250];
  int nH, nW, nTaille;
  int histo[256];
  
  if (argc != 2) 
     {
       printf("Usage: ImageIn.pgm \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   for(int i = 0; i< 256; i++)
 		histo[i] = 0;


   OCTET *ImgIn;
   OCTET  *ImgOut;
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille);

   fstream fs;
   fs.open("histo.dat", fstream::out);
   for(int i = 0; i < nH; i++){
   	for(int j = 0; j < nW; j++){
   		int n = ImgIn[i*nW+j];
   		histo[n]++;
   	} 
   }

   	for(int i = 0; i < 256; i++)
   		fs<<i<<" "<<histo[i]<<endl;
   fs.close();
}

