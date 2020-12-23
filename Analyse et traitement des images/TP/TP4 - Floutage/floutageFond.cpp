
#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgLue[250],cNomImgLue2[250], cNomImgEcrite[250];
  int nH, nW, nTaille, nR, nG, nB;
  
  if (argc != 4) 
     {
       printf("Usage: ImageIn.ppm ImageIn2.ppm ImageOut.ppm  \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgLue2) ;
   sscanf (argv[3],"%s",cNomImgEcrite);


   OCTET *ImgIn,*ImgIn2, *ImgOut;
   
   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   int nTaille3 = nTaille * 3;
   allocation_tableau(ImgIn, OCTET, nTaille3);
   lire_image_ppm(cNomImgLue, ImgIn, nH * nW);

   allocation_tableau(ImgOut, OCTET, nTaille3);

  lire_nb_lignes_colonnes_image_pgm(cNomImgLue2, &nH, &nW);
  allocation_tableau(ImgIn2, OCTET, nTaille);
   
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
      if(ImgIn2[i*nW+j] == 255){
        ImgOut[posR] = (ImgIn[posR] + ImgIn[posR+nW*3] + ImgIn[posR-nW*3] + ImgIn[posR+nW*3+3] + ImgIn[posR+nW*3-3] + ImgIn[posR-nW*3+3] + ImgIn[posR-nW*3+3] + ImgIn[posR + 3] + ImgIn[posR - 3])/9;
        ImgOut[posG] = (ImgIn[posG] + ImgIn[posG+nW*3] + ImgIn[posG-nW*3] + ImgIn[posG-nW*3+3] + ImgIn[posG+nW*3+3] + ImgIn[posG+nW*3-3] + ImgIn[posG-nW*3-3] + ImgIn[posG + 3] + ImgIn[posG - 3])/9;
        ImgOut[posB] = (ImgIn[posB] + ImgIn[posB+nW*3] + ImgIn[posB-nW*3] + ImgIn[posB-nW*3+3] + ImgIn[posB+nW*3+3] + ImgIn[posB+nW*3-3] + ImgIn[posB-nW*3-3] + ImgIn[posB + 3] + ImgIn[posB - 3])/9;
      }
      else{
        ImgOut[posR] = ImgIn[posR];
        ImgOut[posG] = ImgIn[posG];
        ImgOut[posB] = ImgIn[posB];
      }
   }
  }
      

   ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
 }