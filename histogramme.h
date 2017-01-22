//
//  histogramme.h
//  projet7
//
//  Created by remy DEME on 14/05/2016.
//  Copyright © 2016 DEME Rémy. All rights reserved.
//

#ifndef histogramme_h
#define histogramme_h
#include "bmplib.h"

#define NBR_C 256 
typedef struct effectif_pix effec_pix ; 
typedef struct frequence_pix frequence_pix ; 
struct effectif_pix  
{
          int effectif_r[NBR_C] ; 
          int effectif_v[NBR_C] ; 
          int effectif_b[NBR_C]; 
};

struct frequence_pix 
{
          int frequence_r[NBR_C] ; 
          int frequence_v[NBR_C] ; 
          int frequence_b[NBR_C]; 
};


          //void calcul_frequence (int *tableau_effectif , int *tableau_frequence, const infoBMP*infoEntete );
void creation_classe ( int *tableau_classe , int * tableau_effectif); 
void tracer_barre ( const int hauteur ,const int colonne , unsigned char** matrice );
void dessiner_histogramme ( unsigned char **matrice , int *tableau_classe, const infoBMP*infoEntete ); 
int pourcentage ( const int valeur , const  infoBMP*infoEntete , const int max );
void dessinner_histogramme_1 ( unsigned char ** ptrTab , const infoBMP *infoEntete,const unsigned char couleurPix ); 
void afficher_taff ( int * tab ); 
void tapis_blanc ( unsigned char ** matrice , const infoBMP*infoEntete); 
int determiner_max ( const int * tableau  ); 

          // image couleur 
void dessiner_histogramme_IMC ( pix**matrice , const infoBMP*infoEntete, effec_pix * effectif ); 
int pourcentage_IMC ( const int valeur , const infoBMP*infoEntete , const int max ); 
void tracer_barre_IMC_R ( const int hauteur , const int colonne , pix ** matrice ); 
void tracer_barre_IMC_B ( const int hauteur , const int colonne , pix ** matrice );
void tracer_barre_IMC_V( const int hauteur , const int colonne , pix ** matrice );
void tapis_blanc_IMC ( pix ** matrice ,const  infoBMP*infoEntete); 
void determination_effectif_IMC( pix ** matrice , const infoBMP * infoEntete,effec_pix * effectif ); 
#endif /* histogramme_h */
