#include <stdio.h>
#include "image_ppm.h"
#include <time.h>   
#include <iostream>
#include<vector>

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille;
  
  if (argc != 3) 
     {
       printf("Usage: ImageIn.pgm ImageOut.pgm \n"); 
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
  
   for(int i = 0; i<nTaille; i++){
    if(ImgIn[i]>127) ImgOut[i] = 0;
    else ImgOut[i] = 255;
   }
  
  ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
  free(ImgIn); 
  
  return 1;
}