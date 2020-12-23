// test_couleur.cpp : Seuille une image couleur 

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille, nR, nG, nB;
  
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
	 
   int position = 0;
   int posR = 0;
   int posG = 0;
   int posB = 0;

   for (int i=1; i < nH-1; i++){
    for(int j =1; j < nW -1; j++){
      position = i*nW*3 + j*3;
      posR = position;
      posG = position+1;
      posB = position+2;
      ImgOut[posR] = (ImgIn[posR] + ImgIn[posR+nW*3] + ImgIn[posR-nW*3] + ImgIn[posR+nW*3+3] + ImgIn[posR+nW*3-3] + ImgIn[posR-nW*3+3] + ImgIn[posR-nW*3+3] + ImgIn[posR + 3] + ImgIn[posR - 3])/9;
      ImgOut[posG] = (ImgIn[posG] + ImgIn[posG+nW*3] + ImgIn[posG-nW*3] + ImgIn[posG-nW*3+3] + ImgIn[posG+nW*3+3] + ImgIn[posG+nW*3-3] + ImgIn[posG-nW*3-3] + ImgIn[posG + 3] + ImgIn[posG - 3])/9;
      ImgOut[posB] = (ImgIn[posB] + ImgIn[posB+nW*3] + ImgIn[posB-nW*3] + ImgIn[posB-nW*3+3] + ImgIn[posB+nW*3+3] + ImgIn[posB+nW*3-3] + ImgIn[posB-nW*3-3] + ImgIn[posB + 3] + ImgIn[posB - 3])/9;
    }
  }
      

   ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn);
   return 1;
   }

//b 