//
//  rotation_image.c
//  projet7
//
//  Created by remy DEME on 13/04/2016.
//  Copyright © 2016 DEME Rémy. All rights reserved.
//


          // ici structure 
/*
  cood  x_new 
 cood y_new 
 valeur 
 */


#include "bmplib.h"

int  module_rotation ( const int x , const int y , center  O  )
{
          return ( sqrt((x - O.x)*(x - O.x) + (y-O.y)*(y-O.y) ) ); // a voir 
}

float calcul_angle ( const int x , const int y , center O)
{
          float cood_x = x-O.x ; 
          float  cood_y = y - O.y ; 
                    // printf ( " x : %f \n",cood_x);
                    // printf ( " y : %f\n ",cood_y); 
          if (  ((cood_x*cood_x)+ (cood_y*cood_y))   > 0 ||  ((cood_x*cood_x)+ (cood_y*cood_y) )  < 0)
                {
                              //       printf ( " angle : %f ", acosf( 1.0*cood_x / ((cood_x*cood_x)+ (cood_y*cood_y)) ) ); 
                    return  acosf( cood_x / ((cood_x*cood_x)+ (cood_y*cood_y)) ) ;
                }
          else 
                {
                    return 0 ; 
                }
}


int calcul_new_x ( const int module , const float angle , const float teta )
{
          printf ( " angle %f module : %d teta : %f  \n",angle,module,teta); 
          return (-module *cos(angle+teta)) ; // bon 
}

int calcul_new_y ( const int module , const float angle , const float teta  )
{
          return (-module*sin(angle+teta)); 
}


          // initi centre 

void init_centre ( center *O )
{
          printf ( " Entrez la valeur x : \t "); 
          scanf ( "%d",&(O->x)); 
          printf ( "\n"); 
          printf ( " Entrez la valeur y : \t"); 
          scanf("%d",&(O->y)); 
          printf ( "\n"); 
}

          // reglages 

void normalisation_hauteur( int valeur, const infoBMP*infoEntete )
{
          if ( valeur >  infoEntete->hauteur )
                {
                    valeur = infoEntete->hauteur - 1 ; 
                }
          else if ( valeur < 0 )
                {
                    valeur = 0 ; 
                }
}
void normalisation_largeur ( int valeur , const infoBMP*infoEntete)
{
          if ( valeur >  infoEntete->largeur )
                {
                    valeur = infoEntete->largeur - 1 ; 
                }
          else if ( valeur < 0 )
                {
                    valeur = 0 ; 
                }

}
new_coord *create_tableau_type_new_coord (const  int taille_ligne , const int taille_colonne )
{
          new_coord * ptrTab = NULL ; 
          ptrTab = calloc(taille_ligne*taille_colonne, sizeof(new_coord)); 
          return ptrTab; 
}

          // fonction principale 
void rotation_image (unsigned char ** ptrTab , const infoBMP *infoEntete )
{
          int new_x ; 
          int new_y ; 
          int nombre_pix_total_vignette = 0 ; 
          center origine ; 
          int hauteur ; 
          int largeur ; 
          new_coord*temp = NULL ;  // tableau temporaire qui contient les valeurs déplacées 
          int compteur = 0  ; 
          int module ; 
          float angle ; 
          float teta ; 
          int x_h , x_b, y_g , y_d ; 
          int i , j ; // var de boucles 
          init_centre(&origine); 
          printf ( "Entrez la hauteur et la largeur de votre vignette : \t");
          scanf ( "%d%d",&hauteur,&largeur);
          printf ( "\n"); 
          printf ( " Veuillez entrer la valeur de l'angle (préférence pi pi/2 ) : ");
          scanf ( "%f",&teta); 
          x_h= origine.x - hauteur ; // ligne du haut 
          x_b = origine.x + hauteur ; // ligne du bas 
          y_g = origine.y - largeur ; // colonne gauche 
          y_d = origine.y + largeur; // colonne droite 
          normalisation_hauteur(x_h, infoEntete); // au cas ou l'utilisateur entre des valeurs trop grandes // 
          normalisation_hauteur(x_b, infoEntete); // *** // 
          normalisation_largeur(y_d, infoEntete); // ***//
          normalisation_largeur(y_g, infoEntete); // ***//
          temp = create_tableau_type_new_coord((x_b-x_h), (y_d-y_g)); 
          nombre_pix_total_vignette = (x_b-x_h )*(y_d-y_g); 
          printf ( " Valeurs : hauteur : %d largeur : %d  x_h %d : y_g :%d  x_b : %d y_d %d  teta : %f \n ",hauteur, largeur, x_h,y_g,x_b,y_d,teta); 
            for ( i = x_h  ; i < x_b   ; i++ )
                {
                    for ( j = y_g ; j < y_d ; j++)
                          {
                             angle = calcul_angle(j, i, origine); 
                              printf ( "angle : %f \n ",angle); 
                             module =  module_rotation(i, j, origine); 
                                        //printf ( "module %d \n",module);
                              new_x = calcul_new_x(module, angle,teta);
                              new_y = calcul_new_y(module,angle, teta); 
                                        printf ( "x N :  %d , y_new : %d ", new_x,new_y); 
                              temp[compteur].x_new = new_x; 
                              temp[compteur].y_new = new_y ; 
                              temp[compteur].valeur_pix = ptrTab[i][j] ; 
                              compteur++ ; 
                          }
                }
          printf ( " nombre pix ///// %d ",nombre_pix_total_vignette);   
          for ( i = 0   ; i < nombre_pix_total_vignette   ; i++ )
                {
                    printf ( " temp x : %d  temp y : %d ",temp[i].x_new,temp[i].y_new); 
                    ptrTab[(temp[i].x_new)][(temp[i].y_new)] = temp[i].valeur_pix  ; 
                }

          
          
}


