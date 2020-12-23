
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
   int tabR[nTaille/2];
   int tabG[nTaille/2];
   int tabR2[nTaille];
   int tabG2[nTaille];

   //Composante choisir R et G
   //réduction
   for(int i = 0; i<nTaille/2; i++){
      tabR[i] =  ImgIn[(i*2)];
      tabG[i] = ImgIn[(i*2)+1];
   }
   //Rezise
   for(int i = 0; i<nTaille; i++){
    tabR2[i] = tabR[i/6];
    tabG2[i] = tabG[i/6];
   }

   for(int i = 0; i<nTaille3; i+=3){
    ImgOut[i] = tabR2[i/3];
    ImgOut[i+1] = tabG2[(i+1)/3];
    ImgOut[i+2] = ImgIn[i+2];
   }
   ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn);
   return 1;
 }