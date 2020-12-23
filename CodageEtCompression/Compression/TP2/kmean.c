
#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille;
  float  nR1, nR2, nG1, nG2, nB1, nB2;
  
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
   int niteration = 10;
   allocation_tableau(ImgIn, OCTET, nTaille3);
   lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille3);

   nR1 = 59;
   nG1 = 77;
   nB1 = 33;

   nR2 = 222;
   nG2 = 59;
   nB2 = 54;

   float  cpt1, cpt2;
   cpt1=0;
   cpt2=0;

   float cR1 = nR1;
   float cG1 = nG1;
   float cB1 = nB1;
   float cR2 = nR2;
   float cG2 = nG2;
   float cB2 = nB2;


   for(int j=0; j<10; j++){
    cpt1 = 0;
    cpt2 = 0;
     for (int i=0; i < nTaille3; i+=3)
       {

         float v1 = sqrt(pow(ImgIn[i]-nR1,2) + pow(ImgIn[i+1]-nG1,2) + pow(ImgIn[i+2]-nB1,2) );
         float v2 = sqrt(pow(ImgIn[i]-nR2,2) + pow(ImgIn[i+1]-nG2,2) + pow(ImgIn[i+2]-nB2,2) );

         if(v1 < v2){
            cR1+=ImgIn[i];
            cG1+=ImgIn[i+1];
            cB1+=ImgIn[i+2];
            cpt1++;
          }
          else{
            cR2+=ImgIn[i];
            cG2+=ImgIn[i+1];
            cB2+=ImgIn[i+2];
            cpt2++;
          }
    }
    nR1 = cR1/cpt1;
    nG1 = cG1/cpt1;
    nB1 = cB1/cpt1;

    nR2 = cR2/cpt2;
    nG2 = cG2/cpt2;
    nB2 = cB2/cpt2;

   cR1 = nR1;
   cG1 = nG1;
   cB1 = nB1;
   cR2 = nR2;
   cG2 = nG2;
   cB2 = nB2;

  }
    for (int i=0; i < nTaille3; i+=3)
       {
         int nR = ImgIn[i];
         int nG = ImgIn[i+1];
         int nB = ImgIn[i+2];
         float v1 = sqrt(pow(nR-nR1,2) + pow(nG-nG1,2) + pow(nB-nB1,2) );
         float v2 = sqrt(pow(nR-nR2,2) + pow(nG-nG2,2) + pow(nB-nB2,2) );
         if(v1 < v2){
          ImgOut[i] = nR1;
          ImgOut[i+1] = nG1;
          ImgOut[i+2] = nB1;
         }
         else{
          ImgOut[i] = nR2;
          ImgOut[i+1] = nG2;
          ImgOut[i+2] = nB2;
         }
       }
   ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn);
   return 1;
 }