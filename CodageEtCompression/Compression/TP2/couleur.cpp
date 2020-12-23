#include <stdio.h>
#include "image_ppm.h"
#include <iostream>
#include <fstream>

using namespace std;

double EQM(OCTET *left, OCTET *right, int nTaille3){
  double eqm_r = 0;
  double eqm_g = 0;
  double eqm_b = 0;

  for (int px = 0 ; px < nTaille3; px++)
  {
    eqm_r += pow(left[px] - right[px], 2);
    eqm_g += pow(left[px+1] - right[px+1], 2);
    eqm_b += pow(left[px+2] - right[px+2], 2);
  }

  return (eqm_r + eqm_g + eqm_b) / (nTaille3 * 3);
}

double PSNR(OCTET *left, OCTET *right, int nTaille3){
  return 10 * log10(pow(255, 2) / EQM(left, right, nTaille3));
}

int main(int argc, char* argv[]){
  char cNomImgLue[250], cNomImgEcrite[250], cNomImgEcrite2[250];
  int nH, nW, nTaille, nTaille_2;

  if (argc != 4) 
  {
  printf("Usage: ImageIn.ppm ImageOut.ppm ImageOut2.ppm \n"); 
  exit (1) ;
  }

  sscanf (argv[1],"%s",cNomImgLue);
  sscanf (argv[2],"%s",cNomImgEcrite);
  sscanf (argv[3],"%s",cNomImgEcrite2);

  OCTET *ImgIn, *ImgOut, *ImgOut2;

  lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
  nTaille = nH * nW;
  // nTaille_2 = nH/2 * nW/2;
  // printf("nH : %d\n", nH);
  // printf("nH/2 : %d\n", nH/2);
  // printf("nTaille : %d\n", nTaille);
  // printf("nTaille_2 : %d\n", nTaille_2);

  int nTaille3 = nTaille * 3;
  // int nTaille3_2 = nTaille_2 * 3;
  int nTaille3_2 = nH/2 * nW/2 * 3;
  allocation_tableau(ImgIn, OCTET, nTaille3);
  lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
  allocation_tableau(ImgOut, OCTET, nTaille3_2);
  allocation_tableau(ImgOut2, OCTET, nTaille3);


  for (int i=0; i < nTaille3; i+=12){
    ImgOut[i/4] = ImgIn[i];
    ImgOut[i/4+1] = ImgIn[i+1];
    ImgOut[i/4+2] = ImgIn[i+2];
  }

  for (int i=0; i < nTaille3; i+=12){
    ImgOut2[i] = ImgOut[i/4];
    ImgOut2[i+3] = ImgOut[i/4];
    ImgOut2[i+6] = ImgOut[i/4];
    ImgOut2[i+9] = ImgOut[i/4];
    ImgOut2[i+2] = ImgOut[(i/4+2)];
    ImgOut2[i+2+3] = ImgOut[(i/4+2)];
    ImgOut2[i+2+6] = ImgOut[(i/4+2)];
    ImgOut2[i+2+9] = ImgOut[(i/4+2)];
  }

  for (int i = 0; i < nTaille3 ; i+=3)
  {
    ImgOut2[i+1] = ImgIn[i+1];
  }


  //ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH/2, nW/2);
  ecrire_image_ppm(cNomImgEcrite2, ImgOut2,  nH, nW);
  free(ImgIn);
}