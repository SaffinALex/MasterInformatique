#include <stdio.h>
#include <iostream>
#include <fstream>
#include "image_ppm.h"

using namespace std;


int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille;
  int histo[256];
  for(int i = 0; i<256;i++) histo[i] = 0;
  
  if (argc != 3) 
     {
       printf("Usage: ImageIn.pgm ImageOut \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);


   OCTET *ImgIn, *ImgOut;
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille);

   for(int i = 0; i < nH; i++){
    for(int j = 0; j < nW; j++){
      int n = ImgIn[i*nW+j];
      histo[n]++;
    } 
   }

   int min = 0;
   int max = 0
   ;
   for(int i = 0; i<256; i++){
    if(histo[i] > 0){
      min = i;
      break;
    }
   }
   for(int i = 255; i>=0; i--){
    if(histo[i] > 0){
      max = i;
      break;
    }
   }
  for (int i=0; i < nTaille;i++){
     {
       ImgOut[i]=round(255.0 * (ImgIn[i] - min)/(max-min) );
     }
   }

   ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn);
}

