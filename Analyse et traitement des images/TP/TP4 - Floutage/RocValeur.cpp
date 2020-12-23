#include <stdio.h>
#include <iostream>
#include <fstream>
#include "image_ppm.h"

using namespace std;

int main(int argc, char* argv[])
{
  char cNomImgLue[250],cNomImgLue2[250], cNomImgEcrite[250];
  int nH, nW, nTaille;
  int tab[256][4];
  
  if (argc != 4) 
     {
       printf("Usage: ImageIn.pgm ImageIn2.pgm ImageOut.pgm \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgLue2) ;
   sscanf (argv[3],"%s",cNomImgEcrite);

   OCTET *ImgIn, *ImgIn2, *ImgOut;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);

   allocation_tableau(ImgIn2, OCTET, nTaille);
   lire_image_pgm(cNomImgLue2, ImgIn2, nH * nW);

   allocation_tableau(ImgOut, OCTET, nTaille);

  
   //   for (int i=0; i < nTaille; i++)
   // {
   //  if ( ImgIn[i] < S) ImgOut[i]=0; else ImgOut[i]=255;
   //  }
int FP = 0;
int VP = 0;
int FN = 0;
int VN = 0;
for(int S = 0; S < 256; S++){
  FN = 0;
  FP = 0;
  VN = 0;
  VP = 0;
 for (int i=0; i < nH; i++){
   for (int j=0; j < nW; j++)
     {
       if ( ImgIn[i*nW+j] < S) ImgOut[i*nW+j]=0; else ImgOut[i*nW+j]=255;
       if(ImgOut[i*nW+j] == 0 && ImgIn2[i*nW+j] == 0){
        VP++;
       }
       else if(ImgOut[i*nW+j] == 0 && ImgIn2[i*nW+j] != 0){
        FP++;
       }
       else if(ImgOut[i*nW+j] == 255 && ImgIn2[i*nW+j] != 255){
        FN++;
       }
       else if(ImgOut[i*nW+j] == 255 && ImgIn2[i*nW+j] == 255){
        VN++;
       }
     }
   }

   tab[S][0] = VP;
   tab[S][1] = FP;
   tab[S][2] = VN;
   tab[S][3] = FN;
  }
   free(ImgIn);
   fstream fs;
   fs.open("rocValeur.dat", fstream::out);
   for(int i = 0; i < 256; i++)
      fs<<i<<" "<<tab[i][0]<<" "<<tab[i][1]<<" "<<tab[i][2]<<" "<<tab[i][3]<<" "<<(double)tab[i][0]/((double)tab[i][0]+(double)tab[i][3])<<" "<<((double)tab[i][2]/((double)tab[i][2]+(double)tab[i][1]))<<endl;
   fs.close();
   return 1;
}