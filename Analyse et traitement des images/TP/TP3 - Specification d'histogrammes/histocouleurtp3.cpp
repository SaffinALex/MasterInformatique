// test_couleur.cpp : Seuille une image couleur 

#include <stdio.h>
#include "image_ppm.h"
#include <iostream>

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille, nR, nG, nB, S;
  int histoR[256];
  int histoG[256];
  int histoB[256];
  
  if (argc != 3) 
     {
       printf("Usage: ImageIn.ppm ImageOut.ppm  \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);

   OCTET *ImgIn, *ImgOut;
   
   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   int nTaille3 = nTaille * 3;
   allocation_tableau(ImgIn, OCTET, nTaille3);
   lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille3);
	   for(int i = 0; i< 256; i++){
      histoR[i] = 0;
      histoG[i] = 0;
      histoB[i] = 0;
  }
   for(int i = 0; i < nTaille3; i+=3){
      int R = ImgIn[i];
      int G = ImgIn[i+1];
      int B = ImgIn[i+2];
      histoR[R]++;
      histoG[G]++;
      histoB[B]++;
  }

     int minR = 0;
   int maxR = 0;
   int minG = 0;
   int maxG = 0;
   int minB = 0;
   int maxB = 0;

   for(int i = 0; i<256; i++){
    if(histoR[i] > 0){
      minR = i;
      break;
    }
   }
   for(int i = 255; i>=0; i--){
    if(histoR[i] > 0){
      maxR = i;
      break;
    }
   }
   for(int i = 0; i<256; i++){
    if(histoG[i] > 0){
      minR = i;
      break;
    }
   }
   for(int i = 255; i>=0; i--){
    if(histoG[i] > 0){
      maxR = i;
      break;
    }
   }
   for(int i = 0; i<256; i++){
    if(histoB[i] > 0){
      minR = i;
      break;
    }
   }
   for(int i = 255; i>=0; i--){
    if(histoB[i] > 0){
      maxR = i;
      break;
    }
   }
   
  for (int i=0; i < nTaille3; i+=3)
     {
       ImgOut[i] = round(255.0 * (ImgIn[i] - minR)/(maxR-minR) );
       ImgOut[i+1] = round(255.0 * (ImgIn[i+1]) - minG/(maxG-minG)  );
       ImgOut[i+2] = round(255.0 * (ImgIn[i+2]) - minB/(maxB-minB)  );
     }
std::cout<<"oooo"<<std::endl;
   ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn);
   return 1;
}
