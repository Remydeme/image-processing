//
//  bmplib.h
//  projet7
//
//  Created by remy DEME on 25/03/2016.
//  Copyright © 2016 DEME Rémy. All rights reserved.
//

#ifndef bmplib_h
#define bmplib_h
#include "matrice1DC.h"
#include "matrice1DNB.h"
#include "matrice2DNB.h"
#include "matrice2DC.h"
#include "sort.h"
#include "tools.h"
#include "K_means.h"
#include "histogramme.h"
#include "sujet_9.h"

          // define Main // 

#define BIENVENU printf( "Bienvenue. \n \t RETOUCH BMP PIC  ( RBM2P) \n " );
#define QUESTION_WDW printf ( "Que souhaitez vous faire ?\n"); 
#define PRESENTATION_APP printf ( "RBM2P est un logiciel de modification d'image.  \".BMP\" \n");
#define QUESTION_CC printf ( "Quel couleur souhaitez vous pour votre cadre ? :\t ");

#define NOM_IMAGE_COULEUR "yacine.bmp"
#define NOM_IMAGE_NB "lena_NB.bmp"

          // define switch // 
#define DIMENSION_1 1
#define DIMENSION_2 2
#define  AFFICHE_HEADER 3 
#define K_MEANS 4 
#define EFFET_NEGATIF 6 
#define K_MEANS_FC_OPTION 7 

          // define switch NB 
#define FILTRE_PREWIT_SOBEL 3 
#define SEUILLAGE_DAMIER 4 
#define HISTOGRAMME 5 
          // fonction couleur 

          // define messages

#define FONCTION_NON_TERMINEE printf ( " Désolé mais cette fonction n'est pas encore tout à fais au point ");\
                                                                          break; 
          //  /* Macro prmettant de faire un choix de couleur lors de la modification des bords */
#define SWITCH_COULEUR(couleur,r,v,b) switch((couleur)){\
case 'a': \
r = 200 ; b = 0 ; v = 0; break; \
case 'b': r= 0 ; b =200; v = 0 ; break; \
case 'c' : r = 0 ; b = 0 ; v = 200 ; break; \
case 'd' : r = 200 ; v = 200 ; b = 200 ; break; \
default : r = 200 ; v = 200 ; b = 200 ; break; \
}

#define SWITCH_COULEUR_NB(couleur,c) switch((couleur)){\
case 'n': \
c = 0 ; break; \
case 'b': c = 250 ; break; \
case 'c': c = 250 ; break; \
default : c = 100 ; break; \
}

          // fonction 
#endif /* bmplib_h */
