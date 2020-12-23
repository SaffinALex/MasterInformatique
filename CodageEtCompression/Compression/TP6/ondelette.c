
#include <stdio.h>
#include "image_ppm.h"
#include <iostream>

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille;
  
  if (argc != 3) 
     {
       printf("Usage: ImageIn.ppm ImageOut.ppm \n"); 
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

   //Composante choisir R et G
   //réduction

  /* for(int i = 0; i<nTaille3; i+=3){
    if(i%nTaille!=0 && i!=0 && i < (nTaille3 - nTaille)){
      int Ay = ImgIn[i+1];
      int Acr = ImgIn[i];
      int Acb = ImgIn[i+2];
      int By = ImgIn[(i+3)+1];
      int Bcr = ImgIn[(i+3)];
      int Bcb = ImgIn[(i+3)+2];
      int Cy = ImgIn[(i+nTaille)+1];
      int Ccr = ImgIn[(i+nTaille)];
      int Ccb = ImgIn[(i+nTaille)+2];
      int Dy = ImgIn[(i+nTaille+3)+1];
      int Dcr = ImgIn[(i+nTaille+3)];
      int Dcb = ImgIn[(i+nTaille+3)+2];
      ImgOut[i] = floor((Acr+Bcr+Ccr+Dcr)/4.0);
      ImgOut[i+1] = floor((Ay+By+Cy+Dy)/4.0);
      ImgOut[i+2] = floor((Acb+Bcb+Ccb+Dcb)/4.0);

      ImgOut[i+3] = floor(((Acr+Bcr) - (Ccr+Dcr))/2.0);
      ImgOut[i+4] = floor(((Ay+By) - (Cy+Dy))/2.0);
      ImgOut[i+5] = floor(((Acb+Bcb) - (Ccb+Dcb))/2.0);

      ImgOut[(i+nTaille)] = floor(((Acr-Bcr) + (Ccr-Dcr))/2.0);
      ImgOut[(i+nTaille)+1] = floor(((Ay-By) + (Cy-Dy))/2.0);
      ImgOut[(i+nTaille)+2] = floor(((Acb-Bcb) + (Ccb-Dcb))/2.0);

      ImgOut[(i+nTaille+3)] = floor((Acr-Bcr) - (Ccr-Dcr));
      ImgOut[(i+nTaille+3)+1] = floor((Ay-By) - (Cy-Dy));
      ImgOut[(i+nTaille+3)+2] = floor((Acb-Bcb) - (Ccb-Dcb));
    }
    else{
      ImgOut[i] = ImgIn[i];
      ImgOut[i+1] = ImgIn[i+1];
      ImgOut[i+2] = ImgIn[i+2];
    }

   }*/
   for(int i = 0; i< nTaille; i++){
    for(int j = 0; j< nTaille; j++){
      
    }
   }
   ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn);
   return 1;
 }