#include <stdio.h>
#include "image_ppm.h"
#include <time.h>   
#include <iostream>

float calculEntropie(OCTET *ImgInt, int nTaille ){
  float p[256]={0};

  //Probabilité
 
  for (int i=0; i < nTaille; i++){
    p[ImgInt[i]]++; 
  }

  for(int i = 0; i< 256; i++){
    p[i] = p[i]/(float)nTaille;
  }

  float H = 0;
  //Entropie calcul
  for(int i = 0; i<256; i++){
    if(p[i]>0){
      H+=p[i]*log2(p[i]);
    }
  }
  
  return -H;
}
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
   OCTET* ImgInt;
   allocation_tableau(ImgInt, OCTET, nTaille);
   
   int seed = 0;
   float Hmin = 10000;

   for(int i = 0; i<100; i++){
    //Xor brute force
    srand(i);
    for (int j=0; j < nTaille; j++){
      ImgInt[j] = ImgIn[j]^(rand()% 256 + 0); 
    }
    
    //Entropie image déchiffré
    float H = calculEntropie(ImgInt, nTaille);
    std::cout<<" "<<i<< " "<<H<<std::endl;
    if(Hmin >= H){
      Hmin = H;
      
      seed = i;
    }
    //Si Entropie de l'image déchiffré s'éloigne de l'entropie maximal alors c'est la bonne seed.
  }
  srand(seed);
  for (int j=0; j < nTaille; j++){
    ImgInt[j] = ImgIn[j]^(rand()% 256 + 0); 
  }
  ecrire_image_pgm(cNomImgEcrite, ImgInt,  nH, nW);
  std::cout<<"La seed utilisé pour chiffrer cette image était : "<<seed<<std::endl;
      
  free(ImgInt);
  free(ImgIn);
  return 1;
}