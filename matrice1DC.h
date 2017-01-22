//
//  matrice1DC.h
//  projet7
//
//  Created by remy DEME on 25/03/2016.
//  Copyright © 2016 DEME Rémy. All rights reserved.
//

#ifndef matrice1DC_h
#define matrice1DC_h


#include "tools.h"

          // define 
#define PIXEL_COULEUR 3 
#define PIXEL_NB 1
#define OFFQET_SET 4
#define DECALAGE 20

          // prototype fonctions // 
infoBMP* read_header1D_IMC ( const char file_name[]); 
          // image NB prototype de fonctions

          // image couleur prototype de fonctions 

          // 1D dimenssion 
pix  * builtTab1D_IMC ( const infoBMP * infoEntete, const char fileName[] ); 
void restore_picture_retouch1D_IMC ( pix ptrTab[] , const char fileName[] ,const infoBMP *infoEntete ); 
pix * retouch1D_IMC ( pix *ptrTab , const infoBMP * infoEntete,const pix pixel); 
pix * retouch1D_IMC_2 ( pix *ptrTab , const infoBMP * infoEntete, const pix pixel); 
#define CHEMIN_ABSOLUE  100

#endif /* matrice1DC_h */
