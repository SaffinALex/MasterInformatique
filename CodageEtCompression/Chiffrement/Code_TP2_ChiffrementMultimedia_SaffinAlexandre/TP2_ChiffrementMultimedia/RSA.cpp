#include <stdio.h>
#include "image_ppm.h"
#include <time.h>   
#include <iostream>
#include<vector>

bool estPremier(int a){
  for(int i = 2; i < a; i++){
    if(a%i == 0) return false;
  }
  return true;
}
int calculPGCD(int a, int b){
  int r=0;
  int tmp;
  if(a<b){
    tmp = b;
    b = a;
    a = tmp;
  }
  while(true)
  {
    r = a % b;
    if(r == 0)
    {
      return b; //Dernier r non nul
    }
    //std::cout<<r<<std::endl;
    a = b;
    b = r;
  }
  return 0;
}

bool sontPremier(int a, int b){
  return calculPGCD(a,b) == 1;
}


std::vector<int> getAllExposant(int p, int q){
  int n = (p-1)*(q-1);
  std::vector<int> v;
  for(int i = 2; i<n; i++){
    if(sontPremier(i,n)) v.push_back(i);
  }
  return v;
  
}

int euclideEtendu (int a, int b){
  int r1 = a;
  int r2 = b;
  int v1 = 0;
  int v2 = 1;
  int q,r3,v3;
  while(r2 != 0){
    q = r1/r2;
    r3 = r1;
    v3 = v1;
    r1 = r2;
    v1 = v2;
    r2 = r3 - q*r2;
    v2 = v3 - q*v2;
  }
  return v1;
}

int inverseMod(int e, int n){
  int v = euclideEtendu(n, e);
  return v;
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
  


  int q = 11;
  int p = 23;
  std::vector<int> v;
  if(q != p && sontPremier(q,p)){
    v = getAllExposant(p,q);
  }

  int e = 17;
  double n = p*q;
  double s;

  for(int i=0; i<nTaille; i++){
    s= ImgIn[i];
    for(int j = 0; j < e-1; j++){
      s = s*ImgIn[i];
      s = std::fmod(s,n);
    }

    ImgOut[i] = s;
   
  }


  ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
  free(ImgIn); 
  
  return 1;
}