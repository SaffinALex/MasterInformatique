#include <stdio.h>
#include <iostream>
#include <fstream>
#include "image_ppm.h"

using namespace std;


int main(int argc, char* argv[])
{

  char cNomImgLue[250];
  int nH, nW, nTaille, indice;
  bool isLigne;
  
  if (argc != 4) 
     {
       printf("Usage: ImageIn.pgm ligne/colonne indice\n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[3],"%d",&indice);
   isLigne = atoi(argv[2]);

   OCTET *ImgIn;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
   fstream fs;
   fs.open("profile.dat", fstream::out);
   if(isLigne){
   	for(int j = 0; j < nH; j++){
   		int n = ImgIn[indice*nW+j];
   		fs<<j<<" "<<n<<endl;
   	} 
   }
   else{
	for(int i = 0; i < nW; i++){
   		int n = ImgIn[i*nW+indice];
   		fs<<i<<" "<<n<<endl;
   	} 
   }
   fs.close();
}

