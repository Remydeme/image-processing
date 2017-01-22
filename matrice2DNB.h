//
//  matrice2DNB.h
//  projet7
//
//  Created by remy DEME on 25/03/2016.
//  Copyright © 2016 DEME Rémy. All rights reserved.
//

#ifndef matrice2DNB_h
#define matrice2DNB_h
#include "bmplib.h"


          // define 
#define PIXEL_COULEUR 3 
#define PIXEL_NB 1
#define CHEMIN_ABSOLUE  100
#define DECALAGE 20

#define NBR_COULEUR 256 
          
          // structure  fonction rotation image 
typedef struct center center ; 
struct center 
{
          int x ; 
          int y ; 
};

typedef struct new_coord new_coord ; 
struct new_coord 
{
          int x_new ; 
          int  y_new ; 
          int valeur_pix ; 
};

          // prototype de fonctions 
infoBMP* read_header2D_NB ( const char file_name[] );
unsigned char  **builtTab2D_NB ( const infoBMP * infoEntete, const char fileName[] ); 
void restore_picture_retouch2D_NB ( unsigned char **ptrTab , const char fileName[] ,const infoBMP *infoEntete ); 
unsigned char ** retouchIM2D_NB ( unsigned char ** ptrTab , const infoBMP *infoEntete,const unsigned char couleurPix);
void seuillage_damier ( unsigned char ** ptrTab , const infoBMP *infoEntete,const unsigned char couleurPix ) ; 



void determination_effectif(unsigned  char ** matrice , const infoBMP * infoEntete, int *tableau_effectif); 
       
          // prototype de fonctions fichier rotaion 
int  module_rotation ( const int x , const int y , center O  ); 
int calcul_new_y ( const int module , const float angle , const float teta  ); 
int calcul_new_x ( const int module , const float angle , const float teta ); 
void rotation_image (unsigned char ** ptrTab , const infoBMP *infoEntete );
void normalisation_largeur ( int valeur , const infoBMP*infoEntete);
void normalisation_hauteur( int valeur, const infoBMP*infoEntete ); 
new_coord * create_tableau_type_new_coord (const  int taille_ligne , const int taille_colonne ); 

          // k-means 
void retouch2D_IMC_2_K_means_NG( unsigned char **matrice , const infoBMP*infoEntete ); 

          // gauss 
void difference_gauss ( const infoBMP * infoEntete ,  unsigned char ** matrice  ); 
void filtre_prewitt( unsigned  char**matrice , infoBMP *infoEntete ); 

          // echangr pix
void change_pix (  unsigned  char**matrice , infoBMP*infoEntete); 

#endif /* matrice2DNB_h */
