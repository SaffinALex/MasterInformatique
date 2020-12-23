#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <math.h>
#include "Wave.hpp"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <math.h>
#include "Wave.hpp"
#include <assert.h> 
#define BO 100.6 
#define DO 261.6
#define RE 293.7
#define MI 329.6
#define FA  349.2
#define SOL 392.0
#define LA 440.0
#define SI  493.9


void timeToFrequentialDFT(Wave *w,int nb_donnee, double* signal, double *partie_reelle, double *partie_imaginaire);
void frequentialToTimeIDFT(Wave *w,int nb_donnee, int freq, double *signal, double *partie_reelle, double *partie_imaginaire);
void timeToFrequential(Wave *w, int nb_donnee, double *partie_reelle, double *partie_imaginaire);
void frequentialToTime(Wave *w, int nb_donnee, int freq, double *partie_reelle, double *partie_imaginaire, char* filename);
double range(double value, double leftMin, double leftMax, double rightMin, double rightMax);
/*
	This FFT has been proposed by Paul Bourke 
	http://paulbourke.net/miscellaneous/dft/
	This computes an in-place complex-to-complex FFT 
	x and y are the real and imaginary arrays of 2^m points.
	dir =  1 gives forward transform
	dir = -1 gives reverse transform 
	You MUST compute first the value m such that
	2^(m-1) < n (size of your signal) <= 2^m
	allocate a new signal of nm=2^m values
	then fill the n first values of this new signal 
 with your signal and fill the rest with 0
	WARNING : you must pass m, not nm !!!
	*/



int FFT(int dir,int m,double *x,double *y)
{
	int n,i,i1,j,k,i2,l,l1,l2;
	double c1,c2,tx,ty,t1,t2,u1,u2,z;
	
	/* Calculate the number of points */
	n = 1;
	for (i=0;i<m;i++) 
		n *= 2;
	
	/* Do the bit reversal */
	i2 = n >> 1;
	j = 0;
	for (i=0;i<n-1;i++) {
		if (i < j) {
			tx = x[i];
			ty = y[i];
			x[i] = x[j];
			y[i] = y[j];
			x[j] = tx;
			y[j] = ty;
		}
		k = i2;
		while (k <= j) {
			j -= k;
			k >>= 1;
		}
		j += k;
	}
	
	/* Compute the FFT */
	c1 = -1.0; 
	c2 = 0.0;
	l2 = 1;
	for (l=0;l<m;l++) {
		l1 = l2;
		l2 <<= 1;
		u1 = 1.0; 
		u2 = 0.0;
		for (j=0;j<l1;j++) {
			for (i=j;i<n;i+=l2) {
				i1 = i + l1;
				t1 = u1 * x[i1] - u2 * y[i1];
				t2 = u1 * y[i1] + u2 * x[i1];
				x[i1] = x[i] - t1; 
				y[i1] = y[i] - t2;
				x[i] += t1;
				y[i] += t2;
			}
			z =  u1 * c1 - u2 * c2;
			u2 = u1 * c2 + u2 * c1;
			u1 = z;
		}
		c2 = sqrt((1.0 - c1) / 2.0);
		if (dir == 1) 
			c2 = -c2;
		c1 = sqrt((1.0 + c1) / 2.0);
	}
	
	/* Scaling for forward transform */
	if (dir == 1) {
		for (i=0;i<n;i++) {
			x[i] /= n;
			y[i] /= n;
		}
	}
	
	return(1);
}


void DFT(double *signal, double *partie_reelle, double *partie_imaginaire, int N){
  std::fstream fs;
  double somme1=0;
  double somme2=0;
  fs.open("data.txt", std::fstream::out);
  double  s = 2.0*M_PI/(double)N;

  for(int i = 0; i < N; i++){ //n = j , k = i
    double  t = s*i;
    somme1=0.0;
    somme2=0.0;
    for(int j = 0; j< N;j++){
      somme1+=signal[j]*cos(t*j);
      somme2-=signal[j]*sin(t*j);
    }
    
    partie_imaginaire[i] = somme2;
    if(partie_imaginaire[i]<0.001)
      partie_imaginaire[i] = 0;
    partie_reelle[i] = somme1;
    if(partie_reelle[i]<0.001)
      partie_reelle[i] = 0;
    fs<<i<<" "<<partie_reelle[i]<<" "<<partie_imaginaire[i]<<std::endl;
  }
  
  fs.close();
}

void IDFT(double *signal, double *partie_reelle, double *partie_imaginaire, int N){
  double somme = 0;
  for(int i = 0; i < N; i++){
    for(int k = 0; k<N; k++){
      somme += partie_reelle[k]*cos(2*M_PI*k*i/(double)N);
      signal[i] = somme/(double)N;
    }
  }
   
}

void convertReal(unsigned char* data8, double* signal, int N){
  for(int i = 0; i < N; i++){
    //  $range(b, 0, 255, -1.0, 1.0);
    signal[i] = range((double)data8[i], 0, 255, -1.0, 1.0);

  }
  printf("fdfrg\n");
}

//normalisation avant
void convertChar(unsigned char* data8, double* signal, int N){
  for(int i = 0; i < N; i++){
    data8[i] = signal[i]*127.5 * 2 +1;
  }
}

int char2real(char* s_char, double* s_real, int N){
  int i;
  char *ptc;
  double *pt;
  double *fin;
  pt = s_real;
  ptc = s_char;
  fin = pt+N;
  while(pt < fin){
    (*pt++) = ((double)(*ptc)/127.5)-1.0;
  }
  return 1;
}

double min(double* tab, int nb_donnee){
  double min = tab[0];
  for(int i = 0; i<nb_donnee; i++){
    if(tab[i]<min)
      min = tab[i];
  }
  return min;
}

double max(double* tab, int nb_donnee){
  double max = tab[0];
  for(int i = 0; i<nb_donnee; i++){
    if(tab[i]>max)
      max = tab[i];
  }
  return max;
}
int real2char(char* s_char, double* s_real, int N){
  int i;
  char *ptc;
  double *pt;
  double *fin;
  double* valeur;
  pt = s_real;
  ptc = s_char;
  fin = pt+N;
  while(pt < fin){
    (*pt) *= 127.5;
    (*pt) = (*pt) > 255.0 ? 255.0 : (*pt);
    (*pt) = (*pt) < 0.0 ? 0.0 : (*pt);
    (*ptc++) = (char) floor(*pt++);
    
  }
  return 1;
}

double range(double value, double leftMin, double leftMax, double rightMin, double rightMax){
  double leftSpan = leftMax - leftMin;
  double rightSpan = rightMax - rightMin;
  double valueScaled = ((double)(value - leftMin))/((double)(leftSpan));
  double valeurFinale = (valueScaled * (rightSpan)) + rightMin;
  assert((valeurFinale >= rightMin) && (valeurFinale <= rightMax));
  return valeurFinale;
}

unsigned char cast_char(double signal_ech){
  return floor((signal_ech + 1.0) * 127.5);
}

void normalisation(unsigned char* data8, double* signal, double* partie_reelle, double* partie_imaginaire, int nb_donnee){
  double maxFreq = max(partie_reelle, nb_donnee);
  double minFreq = min(partie_reelle, nb_donnee);
  
  for(size_t i=0 ; i<nb_donnee ; i++){
    signal[i] = range(partie_reelle[i], minFreq, maxFreq, -1.0, 1.0);
  }
  for(int i = 0; i<nb_donnee; i++){
    data8[i] = cast_char(signal[i]);
  }
}
  
void createAccord(int nb_donnee, int nbrNote, double* notes, int freq, double* partie_reelle, double* partie_imaginaire){
  int k[nbrNote];
  for(int i=0; i<nbrNote; i++){
    k[i] = (int)floor(notes[i]/(double)freq * (double)nb_donnee);
  }
  
  for(int i=0; i<nb_donnee; i++){
    partie_reelle[i] = 0;
    partie_imaginaire[i] = 0;
  }
  
  for(int i=0; i<nbrNote; i++){
    partie_reelle[k[i]] = 1;
    partie_reelle[nb_donnee - k[i]] = 1;
  }
}

int pow2m(int nb_donnee){
  int m = 0;
  int i = 1; 
  while(i<nb_donnee){
    i*=2;
    m++;
  }
  return m;
}


void filtrepassehaut(Wave *w, double freqC,double freq, int nb_donnee, double *partie_reelle, double *partie_imaginaire){
  unsigned char* data8 = new unsigned char[nb_donnee];
  double form;
  int m = pow2m(nb_donnee);
  int n = pow(2,m);
  timeToFrequential(w, nb_donnee, partie_reelle, partie_imaginaire);
  size_t k1 = n*(freqC/freq);
  size_t k2 = n - k1;
  int j = 0;
  while(j < k1){
    partie_reelle[j] = 0;
    partie_imaginaire[j] = 0;
    j++;
  }
  j=k2;
  while(j < n){
    partie_reelle[j] = 0;
    partie_imaginaire[j] = 0;
    j++;
  }
  frequentialToTime(w, nb_donnee, freq, partie_reelle, partie_imaginaire, "SoundWithFilterHaut.wav");
  //w->modifData8(data8);
  //w->write("SoundWithFilter.wav");

}


void filtrepassebas(Wave *w, double freqC,double freq, int nb_donnee, double *partie_reelle, double *partie_imaginaire){
  unsigned char* data8 = new unsigned char[nb_donnee];
  double form;
  int m = pow2m(nb_donnee);
  int n = pow(2,m);
  timeToFrequential(w, nb_donnee, partie_reelle, partie_imaginaire);
  size_t k1 = n*(freqC/freq);
  size_t k2 = n - k1;
  while(k1 != k2){
    partie_reelle[k1] = 0;
    partie_imaginaire[k1] = 0;
    partie_reelle[k2] = 0;
    partie_imaginaire[k2] = 0;
    k1++;
    k2--;
  }
  frequentialToTime(w, nb_donnee, freq, partie_reelle, partie_imaginaire, "SoundWithFilterBas.wav");
  //w->modifData8(data8);
  //w->write("SoundWithFilter.wav");

}

void filtrepasse(Wave *w, double freqC1, double freqC2, double freq, int nb_donnee, double *partie_reelle, double *partie_imaginaire){
  
  filtrepassehaut(w, freqC1,freq, nb_donnee, partie_reelle, partie_imaginaire);
  filtrepassebas(w, freqC2,freq,nb_donnee,partie_reelle,partie_imaginaire);
  //w->modifData8(data8);
  //w->write("SoundWithFilter.wav");

}
void deletePart(Wave *w, double inf, double sup, int freq, int nb_donnee){
  unsigned char *data8;
  int m = pow2m(nb_donnee);
  int t;
  w->getData8(&data8, &t);
  if(nb_donnee < inf*freq || nb_donnee < sup*freq ){
    printf("mauvaise borne pour suppression\n");
  }
  else{
    for(int i = (int) floor(inf*freq); i < (int) floor(sup*freq) ; i++ )
      data8[i] = 0;
    w->modifData8(data8);
    w->write("SoundWithDeletePart.wav");
  }
}


void createNote(int nbSeconde, double freqNote, int freq, Wave *w){
  unsigned char data8[nbSeconde*freq];
  int nb_donnee = nbSeconde*freq;
  int cpt = 0;
  double signal[nb_donnee];
  for(int i = 0 ; i < nb_donnee; i++){
    data8[i] = 100 + 100 * sin(((double)i/(double)freq)*(double)M_PI*2*freqNote);
    cpt ++;
  }
  w->modifData8(data8);
  w->write("note3.wav");
}

void createGammeNote(int nbSeconde, double* freqNote, int nbrNotes, int freq, Wave *w){
  unsigned char data8[nbSeconde*freq];
  int nb_donnee = nbSeconde*freq;
  int b = nb_donnee/nbrNotes;
  int cpt = 0;
  double signal[nb_donnee];
  for(int i = 0 ; i < nb_donnee; i++){
    data8[i] = 127 + 127 * cos(((double)i/(double)freq)*(double)M_PI*2*freqNote[cpt]);
    if(i >= b){
      cpt ++;
      printf("%d\n",cpt );
      b += nb_donnee/nbrNotes;
    }
  }
  w->modifData8(data8);
  w->write("gammeNote.wav");
}
//pas besoin nb donnee avec get
void timeToFrequentialDFT(Wave *w,int nb_donnee, double* signal, double *partie_reelle, double *partie_imaginaire){
  unsigned char *data8;
  int s;
  w->getData8(&data8, &s);
  convertReal(data8, signal, s);
  DFT(signal, partie_reelle, partie_imaginaire, nb_donnee);
}

void frequentialToTimeIDFT(Wave *w,int nb_donnee, int freq, double *signal, double *partie_reelle, double *partie_imaginaire){
  unsigned char data8[nb_donnee];
  IDFT(signal, partie_reelle, partie_imaginaire, nb_donnee);
  convertChar(data8, signal, nb_donnee);
  w->modifData8(data8);
  w->write("noteIDFT.wav");
}



void timeToFrequential(Wave *w, int nb_donnee, double *partie_reelle, double *partie_imaginaire){
  unsigned char *data8;
  int t;
  w->getData8(&data8, &t);
  int m = pow2m(nb_donnee);
  int s = (int)pow(2,m);
  for(int i = 0; i < s ; i++){
    partie_reelle[i] = 0;
    partie_imaginaire[i] = 0;
  }
  convertReal(data8, partie_reelle, nb_donnee);
  FFT(1,m, partie_reelle, partie_imaginaire);
}


void frequentialToTime(Wave *w, int nb_donnee, int freq, double *partie_reelle, double *partie_imaginaire, char* filename){
  unsigned char *data8 = new unsigned char[nb_donnee];
  double *signal = new double[nb_donnee];
  int m = pow2m(nb_donnee);
  FFT(-1,m, partie_reelle, partie_imaginaire); 
  //convertChar(data8, partie_reelle, s);
  normalisation(data8, signal, partie_reelle, partie_imaginaire, nb_donnee);
  //normalisation(data8, signal, partie_reelle, partie_imaginaire, nb_donnee);
  //convertChar(data8, signal, nb_donnee);
  w->modifData8(data8);
  w->write(filename);
}

double process_alpha(double freqCoupure, double freqEch, double n){
  return (M_PI) * (freqCoupure / freqEch);
}

double A(double alpha){
  return 1.0 + (2.0 * alpha) + (2.0 * pow(alpha, 2.0)) + pow(alpha, 3.0);
}

double B(double alpha){
  return -3.0 - (2.0 * alpha) + (2.0 * pow(alpha, 2.0)) + (3.0 * pow(alpha, 3.0));
}

double C(double alpha){
  return 3.0 - (2.0 * alpha) - (2.0 * pow(alpha, 2.0)) + (3.0 * pow(alpha, 3.0));
}

double D(double alpha){
  return -1.0 + (2.0 * alpha) - (2.0 * pow(alpha, 2.0)) + pow(alpha, 3.0);
}

double get(double* signal, long int index){
  if(index < 0){
    return 0.0;
  }
  else{
    return signal[index];
  }
}

double process_a(double alpha){
  return (pow(alpha, 3.0) / A(alpha));
}

double process_b(double alpha){
  return ((3.0 * pow(alpha, 3.0)) / A(alpha));
}

double process_c(double alpha){
  return ((3.0 * pow(alpha, 3.0)) / A(alpha));
}

double process_d(double alpha){
  return (pow(alpha, 3.0) / A(alpha));
}

double process_e(double alpha){
  return (-1.0 * B(alpha) / A(alpha));
}

double process_f(double alpha){
  return (-1.0 * C(alpha) / A(alpha));
}

double process_g(double alpha){
  return (-1.0 * D(alpha) / A(alpha));
}

// e = le sinal d'entrée
// fc = frequence de frequence de coupure
// fe = frequence d'echantillonage
void butterworth(Wave* w, int fc, int fe, double* e, double* partie_imaginaire, int nb_donnee){
  int m = pow2m(nb_donnee);
  int u = pow(2,m);
  double alpha = process_alpha(fc, fe,u);
  double* s = new double[u];
  for(int i = 0; i<pow(2,m);i++){
    s[i]=0;
  }
  double coeff_a = process_a(alpha);
  double coeff_b = process_b(alpha);
  double coeff_c = process_c(alpha);
  double coeff_d = process_d(alpha);
  double coeff_e = process_e(alpha);
  double coeff_f = process_f(alpha);
  double coeff_g = process_g(alpha);

  for(long int k = 0 ; k < u; k++){
    s[k] = (coeff_a * get(e, k-3)) + (coeff_b * get(e, k-2)) + (coeff_c * get(e, k-1)) + (coeff_d * get(e, k)) + (coeff_e * get(s, k-1)) + (coeff_f * get(s, k-2)) + (coeff_g * get(s, k-3));
  }

  unsigned char *data8 = new unsigned char[nb_donnee];
  double *signal = new double[nb_donnee];
  //convertChar(data8, partie_reelle, s);
  normalisation(data8, signal, s, partie_imaginaire, nb_donnee);
  //normalisation(data8, signal, partie_reelle, partie_imaginaire, nb_donnee);
  //convertChar(data8, signal, nb_donnee);
  w->modifData8(data8);
  w->write("butterworth.wav");

}



int main(int argc, char** argv){
  int nb_donnee;
  double nbrSeconde = 10;
  int freq = 44100;
  Wave* w;
  double *partie_reelle;
  double *partie_imaginaire;
  double *signal;
  double notes[10];
  double accord[10];
  double  inf = 2.2;
  double sup = 3;
  unsigned char *data8;

  notes[0] = BO;
  notes[1] = RE;
  notes[2] = MI;
  notes[3] = FA;
  notes[4] = SOL;
  notes[5] = LA;
  notes[6] = SI;
  notes[7] = DO;

  nb_donnee = freq * nbrSeconde;
  data8 = new unsigned char[nb_donnee];
  w = new Wave(data8,nb_donnee,1,freq);
  printf("CREATION DE NOTE\n");
  createNote(nbrSeconde, LA, freq, w);
  printf("CREATION DE GAMME DE NOTE\n");
  createGammeNote(nbrSeconde, notes, 8, freq, w);
  partie_imaginaire = new double[nb_donnee];
  partie_reelle = new double[nb_donnee];
  signal = new double[nb_donnee];
    
  /*printf("DFT\n");
  timeToFrequentialDFT(w, nb_donnee, signal, partie_reelle, partie_imaginaire);
  printf("IDFT\n"); 
  frequentialToTimeIDFT(w, nb_donnee, freq, signal, partie_reelle, partie_imaginaire); */

  /*IDFT(signal, partie_reelle, partie_imaginaire, nb_donnee);
  convertChar(data8, signal, nb_donnee);
  w->modifData8(data8);*/


  
  accord[0] = DO;
  accord[1] = MI;
  accord[2] = LA;
  int m = pow2m(nb_donnee);
  int s = (int)pow(2,m);
  partie_imaginaire = new double[s];
  partie_reelle = new double[s];
  signal = new double[s];
 /* printf("CREATION D'UN ACCORD\n");
  createAccord(s, 3, accord, freq, partie_reelle, partie_imaginaire);
  printf("APPLICATION DE LA IFFT\n");
  frequentialToTime(w, nb_donnee, freq, partie_reelle, partie_imaginaire,"accordVrai.wav"); */
  
  w->read("gammeNote.wav");
  int t;
  w->getData8(&data8, &t);
  m = pow2m(t);
  s = (int)pow(2,m);
  printf("%d , %d, %d\n",t, m,s  );
  partie_imaginaire = new double[s];
  partie_reelle = new double[s];
  signal = new double[s];
  printf("APPLICATION DE LA FFT\n");
  timeToFrequential(w, t, partie_reelle, partie_imaginaire); 
  printf("APPLICATION DE LA IFFT\n");
  frequentialToTime(w, t, freq, partie_reelle, partie_imaginaire,"accord2.wav");
  /*printf("APPLICATION DE LA FFT\n");
  timeToFrequential(w, t, partie_reelle, partie_imaginaire); 
  printf("APPLICATION DE LA IFFT\n");
  frequentialToTime(w, t, freq, partie_reelle, partie_imaginaire,"accord3.wav"); 
  printf("APPLICATION DE LA FFT\n");
  timeToFrequential(w, t, partie_reelle, partie_imaginaire); 
  printf("APPLICATION DE LA IFFT\n");
  frequentialToTime(w, t, freq, partie_reelle, partie_imaginaire,"accord4.wav"); */
//  filtrepassebas(w, 400.0,freq, t, partie_reelle, partie_imaginaire); 
/*  for(int i = 0; i < s ; i++){
    partie_reelle[i] = 0;
    partie_imaginaire[i] = 0;
  }*/
 // convertReal(data8, partie_reelle, t);
  butterworth(w,400, freq, partie_reelle, partie_imaginaire, t);
  //deletePart(w, inf, sup, freq, t);
  return 0;
}
