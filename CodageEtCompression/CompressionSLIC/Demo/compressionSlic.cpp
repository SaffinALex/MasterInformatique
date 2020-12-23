#include <stdio.h>
#include <iostream>   
#include <fstream>
#include "image_ppm.h"
#include <vector>
using namespace std;
struct Pixel {
    float l;
    float a;
    float b;
    int x;
    int y;
};

struct SuperPixel {
    float l;
    float a;
    float b;
    std::vector<Pixel> pixels;
    int x;
    int y;
};



int main(int argc, char* argv[])
{
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille, taux;

    if (argc != 4)
    {
        printf("Usage: ImageIn.pgm ImageOut.pgm paramSP \n");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgEcrite);
    taux = atoi(argv[3]) ;
   // cout << taux << endl;

    OCTET* ImgIn, * ImgOut;

    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    int nTaille3 = nTaille * 3;
    allocation_tableau(ImgIn, OCTET, nTaille3);
    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);

    allocation_tableau(ImgOut, OCTET, nTaille3);
    
    std::vector<vector<SuperPixel> > grid;
    while (nW % taux > 0) taux += 1;
    cout << taux << endl;
    grid.resize(taux);
    /*for (int i = 0; i < nTaille3; i++) {
        ImgOut[i] = ImgIn[i];
    }*/
    //cout << nW / taux << endl;
    for (unsigned int i = 0; i < grid.size(); i++)
        grid[i].resize(taux);

    for (unsigned int i = 0; i < grid.size(); i++) {
        for (unsigned int j = 0; j < grid[i].size(); j++) {
            grid[i][j].x = 0;
            grid[i][j].y = 0;
            grid[i][j].l = 0;
            grid[i][j].a = 0;
            grid[i][j].b = 0;
       
            for (unsigned int y = 0; y < nW/grid.size(); y++) {

                for (unsigned int w = 0; w < nW/grid.size(); w++) {
                    Pixel p;
                    p.x = y + i * nW/grid.size() ;
                    p.y = w + j * nH/grid.size();
                  //  if (p.x > 256 || p.y > 256) cout << p.x <<" "<<p.y<<" "<< nW / grid.size()<< endl;
                    p.l = ImgIn[p.x * nW * 3 + p.y * 3];
                    p.a = ImgIn[p.x * nW * 3 + p.y * 3 + 1];
                    p.b = ImgIn[p.x * nW * 3 + p.y * 3 + 2];

                    grid[i][j].pixels.push_back(p);
                    grid[i][j].x += p.x;
                    grid[i][j].y += p.y;
                    grid[i][j].l += p.l;
                    grid[i][j].a += p.a;
                    grid[i][j].b += p.b;
                }
            }
            grid[i][j].x /= grid[i][j].pixels.size();
            grid[i][j].y /= grid[i][j].pixels.size();
            grid[i][j].l /= grid[i][j].pixels.size();
            grid[i][j].a /= grid[i][j].pixels.size();
            grid[i][j].b /= grid[i][j].pixels.size();
          
           // std::cout << grid[i][j].x << "," << grid[i][j].y << std::endl;
        }
    }
    int compteur = 0;
    for (unsigned int i = 0; i < grid.size(); i++) {
        for (unsigned int j = 0; j < grid[i].size(); j++) {
            compteur += grid[i][j].pixels.size();
        }
    }
    //cout << compteur << " " << nW * nH << endl;
    for (int g = 0; g < 10; g++) {
        for (unsigned int i = 0; i < grid.size(); i++) {
            for (unsigned int j = 0; j < grid[i].size(); j++) {
                for (unsigned int w = 0; w < grid[i][j].pixels.size(); w++) {
                    // grid[i][j].pixels[w].l = grid[i][j].l;
                    Pixel pixel = grid[i][j].pixels[w];
                    float d1 = 100000;
                    float d2 = 100000;
                    float d3 = 100000;
                    float d4 = 100000;
                    float d5 = 100000;

                    d1 = sqrt(pow(pixel.l - grid[i][j].l, 2) + pow(pixel.a - grid[i][j].a, 2) + pow(pixel.b - grid[i][j].b, 2)) + sqrt(pow(pixel.x - grid[i][j].x, 2) + pow(pixel.y - grid[i][j].y, 2));
                    if (i < grid.size() - 1)
                        d2 = sqrt(pow(pixel.l - grid[i + 1][j].l, 2) + pow(pixel.a - grid[i + 1][j].a, 2) + pow(pixel.b - grid[i + 1][j].b, 2)) + sqrt(pow(pixel.x - grid[i + 1][j].x, 2) + pow(pixel.y - grid[i + 1][j].y, 2));
                    if (j < grid.size() - 1)
                        d3 = sqrt(pow(pixel.l - grid[i][j + 1].l, 2) + pow(pixel.a - grid[i][j + 1].a, 2) + pow(pixel.b - grid[i][j + 1].b, 2)) + sqrt(pow(pixel.x - grid[i][j + 1].x, 2) + pow(pixel.y - grid[i][j + 1].y, 2));
                    if (i > 0)
                        d4 = sqrt(pow(pixel.l - grid[i - 1][j].l, 2) + pow(pixel.a - grid[i - 1][j].a, 2) + pow(pixel.b - grid[i - 1][j].b, 2)) + sqrt(pow(pixel.x - grid[i - 1][j].x, 2) + pow(pixel.y - grid[i - 1][j].y, 2));
                    if (j > 0)
                        d5 = sqrt(pow(pixel.l - grid[i][j - 1].l, 2) + pow(pixel.a - grid[i][j - 1].a, 2) + pow(pixel.b - grid[i][j - 1].b, 2)) + sqrt(pow(pixel.x - grid[i][j - 1].x, 2) + pow(pixel.y - grid[i][j - 1].y, 2));
                    float d[5] = { d1,d2,d3,d4,d5 };
                    float min = d1;
                    //distance minimum
                    for (int u = 0; u < 5; u++) {
                        if (d[u] < d1) min = d[u];
                    }
                    if (min == d2) {
                        grid[i + 1][j].pixels.push_back(pixel);
                        grid[i][j].pixels.erase(grid[i][j].pixels.begin() + w);
                        w--;
                    }
                    else if (min == d3) {
                        grid[i][j + 1].pixels.push_back(pixel);
                        grid[i][j].pixels.erase(grid[i][j].pixels.begin() + w);
                        w--;
                    }
                    else if (min == d4) {
                        grid[i - 1][j].pixels.push_back(pixel);
                        grid[i][j].pixels.erase(grid[i][j].pixels.begin() + w);
                        w--;
                    }
                    else if (min == d5) {
                        grid[i][j - 1].pixels.push_back(pixel);
                        grid[i][j].pixels.erase(grid[i][j].pixels.begin() + w);
                        w--;
                    }
                }
            }
        }
       
        for (unsigned int i = 0; i < grid.size(); i++) {
            for (unsigned int j = 0; j < grid[i].size(); j++) {
                grid[i][j].x = 0;
                grid[i][j].y = 0;
                grid[i][j].l = 0;
                grid[i][j].a = 0;
                grid[i][j].b = 0;
                
                for (unsigned int u = 0; u < grid[i][j].pixels.size(); u++) {
                    Pixel p = grid[i][j].pixels[u];
                    grid[i][j].x += p.x;
                    grid[i][j].y += p.y;
                    grid[i][j].l += p.l;
                    grid[i][j].a += p.a;
                    grid[i][j].b += p.b;
                }
                
                if (grid[i][j].pixels.size() > 0) {
                    grid[i][j].x /= grid[i][j].pixels.size();
                    
                    grid[i][j].y /= grid[i][j].pixels.size();
                  
                    grid[i][j].l /= grid[i][j].pixels.size();
                 
                    grid[i][j].a /= grid[i][j].pixels.size();
                    grid[i][j].b /= grid[i][j].pixels.size();
                }
                else {
                    grid[i][j].x /= 1;
                    grid[i][j].y /= 1;
                    grid[i][j].l /= 1;
                    grid[i][j].a /= 1;
                    grid[i][j].b /= 1;
                }
                

            }
            
        }
      
  }

    

  fstream fs;

  
  fs.open(cNomImgEcrite, fstream::out);
  fs << nW << " " << nH << endl;
  for (unsigned int i = 0; i < grid.size(); i++) {
      for (unsigned int j = 0; j < grid[i].size(); j++) {

          vector<vector<int> > pos_x;
          pos_x.resize(nW);
          for (unsigned int w = 0; w < grid[i][j].pixels.size(); w++) {
              pos_x[grid[i][j].pixels[w].x].push_back(grid[i][j].pixels[w].y);
          }
          fs << grid[i][j].pixels.size() << " " << (int)grid[i][j].l << " " << (int)grid[i][j].a << " " << (int)grid[i][j].b << endl;
          for (unsigned int w = 0; w < pos_x.size(); w++) {
              if (pos_x[w].size() > 0)
                fs << (OCTET)pos_x[w].size()<< (OCTET)w;
              for (unsigned int h = 0; h < pos_x[w].size(); h++) {
                  fs << (OCTET)pos_x[w][h];
              }
              if (pos_x[w].size() > 0)
                fs << endl;
          }
      }
  }
  fs.close();

  fs.open("ImgCompresseAscii.txt", fstream::out);
  fs << nW << " " << nH << endl;
  for (unsigned int i = 0; i < grid.size(); i++) {
      for (unsigned int j = 0; j < grid[i].size(); j++) {

          vector<vector<int> > pos_x;
          pos_x.resize(nW);
          for (unsigned int w = 0; w < grid[i][j].pixels.size(); w++) {
              pos_x[grid[i][j].pixels[w].x].push_back(grid[i][j].pixels[w].y);
          }
          fs << grid[i][j].pixels.size() << " "<< (int)grid[i][j].l << " " << (int)grid[i][j].a << " " << (int)grid[i][j].b << endl;
          for (unsigned int w = 0; w < pos_x.size(); w++) {
              if(pos_x[w].size()>0)
                fs <<pos_x[w].size()<<" "<< w;
              for (unsigned int h = 0; h < pos_x[w].size(); h++) {
                  fs <<" " << pos_x[w][h];
              }
              if (pos_x[w].size() > 0)
                fs << endl;
          }
      }
  }
 
  fs.close(); 


 
   free(ImgIn);
   return 1;
}