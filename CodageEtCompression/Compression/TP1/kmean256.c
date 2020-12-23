
#include <stdio.h>
 #include <iostream>
#include "image_ppm.h"
#include <time.h>

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


   float tabR[256];
   float tabG[256];
   float tabB[256];

   int cpt [256] ={1};
   float dist [256];

   srand (time(NULL));
   for(int i = 0; i<256; i++){
    tabR[i] = rand() % 255 + 1;
    tabG[i] = rand() % 255 + 1;
    tabB[i] = rand() % 255 + 1;
   }




  for(int j=0; j<2; j++){
    for(int i=0; i<256; i++) cpt[i] = 1;
     for (int i=0; i < nTaille3; i+=3)
       {

         for(int u = 0; u<256; u++) dist[u] = sqrt(pow(ImgIn[i]-tabR[u],2) + pow(ImgIn[i+1]-tabG[u],2) + pow(ImgIn[i+2]-tabB[u],2) );

         float dmin = dist[0];
         int index = 0;

         for(int u = 1; u<256; u++){
          if (dist[u] < dmin){
            dmin = dist[u];
            index = u;
         }
        }
        tabR[index]+=ImgIn[i];
        tabG[index]+=ImgIn[i+1];
        tabB[index]+=ImgIn[i+2];
        cpt[index]+=1;
    }
    for(int i=0; i<256; i++){
      tabR[i] = tabR[i]/cpt[i];
      tabG[i] = tabG[i]/cpt[i];
      tabB[i] = tabB[i]/cpt[i];
    }
  }

  
    for (int i=0; i < nTaille3; i+=3)
       {

         for(int u = 0; u<256; u++) dist[u] = sqrt(pow(ImgIn[i]-tabR[u],2) + pow(ImgIn[i+1]-tabG[u],2) + pow(ImgIn[i+2]-tabB[u],2) );
         float dmin = dist[0];
         int index = 0;
         for(int u = 1; u<256; u++){
          if (dist[u] < dmin){
            dmin = dist[u];
            index = u;
         }
        }
        ImgOut[i] = tabR[index];
        ImgOut[i+1] = tabG[index];
        ImgOut[i+2] = tabB[index];
       }

   ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn);
   return 1;
 }