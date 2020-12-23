#include <stdio.h>
#include <iostream>   
#include <fstream>
#include "image_ppm.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[])
{
    char cNomImgEcrite[250], cNomImgC[250];

    if (argc != 3)
    {
        printf("Usage: ImgIn ImageOut.pgm  \n");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgC);
    sscanf(argv[2], "%s", cNomImgEcrite);

    OCTET * ImgOut;


  FILE* fichier = NULL;

  int hauteur, largeur, nbPixels, l, a, b;
  fichier = fopen(cNomImgC, "r");
  int n;
  int posx, posy;
  double cpt = 0;
  double cptbis = 0;
  if (fichier != NULL)
  {
      fscanf(fichier, "%d %d",&hauteur, &largeur);
      int nTaille3 = hauteur * largeur * 3;
      allocation_tableau(ImgOut, OCTET, nTaille3);

      while (cptbis < (hauteur) * (largeur) ) {
          fscanf(fichier, "%d %d %d %d", &nbPixels, &l, &a, &b);

          while (cpt < nbPixels) {
              fgetc(fichier); // sauter
              n = fgetc(fichier); //NbrPixelLignex
              posx = fgetc(fichier); //posx
              cpt += n;
              
              for (int i = 0; i < n; i++) {
                  
                  posy = fgetc(fichier); // On lit le caractère
                  ImgOut[posx * largeur * 3 + posy * 3] = l;
                  ImgOut[posx * largeur * 3 + posy * 3 + 1] = a;
                  ImgOut[posx * largeur * 3 + posy * 3 + 2] = b;
              }
          }
          cptbis += nbPixels;
         // cout << nbPixels <<" "<<cptbis<<" "<< hauteur*(largeur)<< endl;
          cpt = 0;
      }

      fclose(fichier);
  }
  
   ecrire_image_ppm(cNomImgEcrite, ImgOut,  hauteur, largeur);
  
   return 1;
}