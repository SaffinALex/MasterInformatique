#include <stdio.h>
#include <iostream>
#include <fstream>
#include "image_ppm.h"

using namespace std;


int main(int argc, char* argv[])
{
  char cNomImgLue[250],cNomImgLue2[250], cNomImgEcrite[250];
  int nH, nW, nTaille;
  
  if (argc != 4) 
     {
       printf("Usage: mask.pgm ImgIn.pgm ImageOut.pgm \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue);
   sscanf (argv[2],"%s",cNomImgLue2);
   sscanf (argv[3],"%s",cNomImgEcrite);

   OCTET *ImgIn, *ImgIn2, *ImgOut;
   

   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);

   allocation_tableau(ImgIn2, OCTET, nTaille);
   lire_image_pgm(cNomImgLue2, ImgIn2, nH * nW);

   allocation_tableau(ImgOut, OCTET, nTaille);
  
for(int u = 0; u < 10000; u++){
  if(u >=1){
  for (int i=0; i < nH; i++){
   for (int j=0; j < nW; j++)
     {
      ImgIn2[i*nW+j] = ImgOut[i*nW+j];
     }
   }
 }
 for (int i=1; i < nH-1; i++){
   for (int j=1; j < nW-1; j++)
     {
        if ( ImgIn[i*nW+j] == 0){
          float moy = 0;
          int cpt = 0;
          if(ImgIn[(i+1)*nW+j] != 0){
            cpt++;
            moy+=ImgIn2[(i+1)*nW+j];
          }
          else if(ImgIn[(i-1)*nW+j] != 0){
            cpt++;
            moy+=ImgIn2[(i-1)*nW+j];
          }
          else if(ImgIn[(i+1)*nW+(j+1)] != 0){
            cpt++;
            moy+=ImgIn2[(i+1)*nW+(j+1)];
          }
          else if(ImgIn[(i-1)*nW+(j+1)]!= 0){
            cpt++;
            moy+=ImgIn2[(i-1)*nW+(j+1)];
          }
          else if(ImgIn[(i+1)*nW+(j-1)]!= 0){
            cpt++;
            moy+=ImgIn2[(i+1)*nW+(j-1)];
          }
          else if(ImgIn[(i-1)*nW+(j-1)]!= 0){
            cpt++;
            moy+=ImgIn2[(i-1)*nW+(j-1)];
          }
          else if(ImgIn[i*nW+(j+1)]!= 0){
            cpt++;
            moy+=ImgIn2[i*nW+(j+1)];
          }
          else if(ImgIn[i*nW+(j-1)]!= 0){
            cpt++;
            moy+=ImgIn2[i*nW+(j-1)];
          }
          if(cpt > 0){
            ImgOut[i*nW+j] = moy/cpt;
            if(ImgOut[i*nW+j] > 100)
              ImgIn[i*nW+j] = 255;
          }
          else
            ImgOut[i*nW+j] = 0;

          
        }
        else{
          ImgOut[i*nW+j] = ImgIn2[i*nW+j];
        }
     }
   }
 }
  

   ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn);
   return 1;

}
