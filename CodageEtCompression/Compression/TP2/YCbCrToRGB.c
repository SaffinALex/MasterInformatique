
#include <stdio.h>
#include "image_ppm.h"

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

   for(int i = 0; i<nTaille3; i+=3){
       float Y = ImgIn[i+1];
   float Cb= ImgIn[i+2];
   float Cr= ImgIn[i];
    ImgOut[i] = 1.164 * (Y - 16) + 1.596 * (Cr - 128);
    ImgOut[i+1] = 1.164 * (Y-16) - 0.813 * (Cr-128) - 0.392 * (Cb-128);
    ImgOut[i+2] = 1.164 * (Y-16) + 2.017 * (Cb-128);
    if(ImgOut[i]>255 || ImgOut[i+1]>255 || ImgOut[i+2]>255){
      printf("coucou");
    }
    if(ImgOut[i]<0 || ImgOut[i+1]<0 || ImgOut[i+2]<0){
      printf("coucou");
    }
   }
   ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn);
   return 1;
 }