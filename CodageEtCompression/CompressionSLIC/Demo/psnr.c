
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
   allocation_tableau(ImgOut, OCTET, nTaille3);
   lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
   lire_image_ppm(cNomImgEcrite, ImgOut, nH * nW);

    double eqm_r = 0;
    double eqm_g = 0;
    double eqm_b = 0;

    for (int i=0; i<nTaille3; i++)
    {
      eqm_r += pow(ImgIn[i] - ImgOut[i], 2);
      eqm_g += pow(ImgIn[i+1] - ImgOut[i+1], 2);
      eqm_b += pow(ImgIn[i+2] - ImgOut[i+2], 2);
    }
    double eqm = (eqm_r + eqm_g + eqm_b)/nTaille3;
    float PSNR = 10 * log10(pow(255, 2)/eqm);
    std::cout<<PSNR<<std::endl;
    return 0;
}
 
   
