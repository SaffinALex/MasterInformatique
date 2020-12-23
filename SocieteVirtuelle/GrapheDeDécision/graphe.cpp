#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>  
#include <iostream>   
#include <fstream>
#include <vector>
#include <sys/time.h>
using namespace std;
struct noeud {
	vector<noeud*> parent;
	int etat;
    bool estFeuille;
    int ind;
};

int main(int argc, char* argv[])
{
    srand(time(NULL));
    int nbrNoeud;
    
    struct timeval current_time;
    gettimeofday(&current_time, NULL);



    // Ton programme

    if (argc != 2)
    {
        printf("Usage: n \n");
        exit(1);
    }

    nbrNoeud = atoi(argv[1]);

    
    vector<noeud> graphe;
    graphe.resize(nbrNoeud);
    int cible;
    bool stop = false;
    while (!stop || graphe[0].parent.size() == 0) {
       // cout << !stop << " " << graphe[0].parent.size() << endl;
        stop = false;
        graphe.clear();
        graphe.resize(nbrNoeud);
        for (unsigned int i = 0; i < graphe.size(); i++) {
            graphe[i].etat = 1;
            graphe[i].estFeuille = true;
            graphe[i].ind = i;
        }
        for (int i = 1; i < nbrNoeud; i++) {
            bool test = false;
            do {
                test = false;
                cible = rand() % nbrNoeud;
                for (unsigned int u = 0; u < graphe[cible].parent.size(); u++) {
                    if (graphe[cible].parent[u]->ind == graphe[i].ind) test = true;
                }
                
            } while (cible == i || test);
           
            graphe[cible].parent.push_back(&graphe[i]);
            graphe[cible].estFeuille = false;
            for (unsigned int j = 0; j < graphe[cible].parent.size(); j++) {
                if (graphe[cible].parent[j]->etat == 1) {
                    graphe[cible].etat = 0;
                }
            }
        }

        stop = true;
       /* */
        for (int i = 1; i < nbrNoeud; i++) {
            noeud s;
            for (unsigned int j = 0; j < graphe[i].parent.size(); j++) {
                s = graphe[i];
                
                  //  std::cout << "jihjiiji" << endl;
                    if ((s.etat == s.parent[j]->etat ) && !s.estFeuille) {
                        stop = false;
                        break;
                        
                    }
                /*    else {
                        s.etat = s.parent[j]->etat;
                        s.estFeuille = s.parent[j]->estFeuille;
                        vector<noeud*> p;
                        for (unsigned int u = 0; u < s.parent[j]->parent.size();u++) {
                            p.push_back(s.parent[j]->parent[u]);
                        }
                        s.parent.clear();
                        for (unsigned int u = 0; u < p.size();u++) {
                            s.parent.push_back(p[u]);
                        }
                    } */
                   
            }
        }


    }
    cout << "-----------------------------" << endl;
    for (int i = 0; i < nbrNoeud; i++) {
        for (unsigned int j = 0; j < graphe[i].parent.size(); j++) {
            cout << graphe[i].parent[j]->ind << " ";
        }
        cout << "est feuille : " << graphe[i].estFeuille << endl;
    }
    cout << endl;
    
    struct timeval current_time2;
    gettimeofday(&current_time2, NULL);

    cout<<"Temps d'execution = "<< (current_time2.tv_sec - current_time.tv_sec)*1000000 + (current_time2.tv_usec - current_time.tv_usec) <<" ms "<<endl;
    return 0;

}