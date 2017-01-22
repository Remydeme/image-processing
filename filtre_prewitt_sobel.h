//
//  filtre_prewitt_sobel.h
//  projet7
//


#ifndef filtre_prewitt_sobel_h
#define filtre_prewitt_sobel_h
#include "tools.h"

void multiplication ( int M1[3][3] , int M2[3][3] , int M3[3][3]);  
void transposer ( int  matrice[2][2] ); 
void square_matrice (  int matrice[3][3]); 
void somme ( int matrice_resultante[3][3], int matrice_1[3][3], int matrice_2[3][3] ); 
void gradient ( int G[3][3]); 
void normalisation ( int matrice[3][3]); 
void copie_vers_mini_matrice (  unsigned char **source, int  destinataire[3][3] , const int hauteur , const int largeur); 
void copie_vers_matrice ( unsigned char  **destinataire , int  source[3][3] , const int hauteur , const int largeur   ); 
#endif /* filtre_prewitt_sobel_h */
