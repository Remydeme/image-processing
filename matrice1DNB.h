//
//  matrice1DNB.h
//  projet7
//
//  Created by remy DEME on 25/03/2016.
//  Copyright © 2016 DEME Rémy. All rights reserved.
//

#ifndef matrice1DNB_h
#define matrice1DNB_h

#define __projet5__matrice1DNB__


#include "tools.h"
          // define 
#define PIXEL_COULEUR 3 
#define PIXEL_NB 1
#define CHEMIN_ABSOLUE  100
#define DECALAGE 20

          // prototype de fonctions 
unsigned char  * builtTab1D_NB ( const infoBMP * infoEntete, const char fileName[] ); 
void restore_picture_retouch1D_NB ( unsigned char ptrTab[] , const char fileName[] , const infoBMP *infoEntete );

unsigned char * retouche1D_NB ( unsigned char * ptrTab, const infoBMP*infoEntete , const char couleurPix);
#endif /* matrice1DNB_h */
