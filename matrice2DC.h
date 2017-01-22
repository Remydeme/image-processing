//
//  matrice2DC.h
//  projet7
//
//  Created by remy DEME on 25/03/2016.
//  Copyright © 2016 DEME Rémy. All rights reserved.
//

#ifndef matrice2DC_h
#define matrice2DC_h

          // define 
#include "bmplib.h"

#define CHEMIN_ABSOLUE  100
#define PIXEL 1 
#define OFFSET_SET 4
#define DECALAGE 20
          // define fonction K_means 
#define NBR_MAX_BOUCLES 1000

          // define save file 
#define TAILLE_BUFF 500

          // define limite de nombre de calcul de centre 
#define LIMITE_NOMBRE_TOURS 1000 
          // prototype de fonctions  couleurs 
infoBMP* read_header2D_C( const char file_name[]); 
pix  ** builtTab2D_C ( const infoBMP * infoEntete, const char fileName[] ); 
void restore_picture_retouch2D_C ( pix **ptrTab ,const char fileName[] ,const infoBMP *infoEntete );
pix **retouch2D_IMC ( pix**ptrTab , const infoBMP*infoEntete , const pix pixel); 
pix **retouch2D_IMC_2( pix**ptrTab , const infoBMP*infoEntete ,const pix pixel);
pix **retouch2D_IMC_2_greyscale( pix**ptrTab , const infoBMP*infoEntete ); 
void retouch2D_IMC_2_K_means( pix**matrice , const infoBMP*infoEntete ); 
void retouch2D_IMC_2_K_means_option( pix**matrice , const infoBMP*infoEntete ); 
          // fonction utilisé pour K_means 
void  fausse_couleur_centre (  centre * centre , const int nombre_cluster );
pix **allocation_tableau (const infoBMP*infoEntete  ); 
void  dessinner_histogramme_IMC2D ( pix** ptrTab , const infoBMP *infoEntete); 
#endif /* matrice2DC_h */
