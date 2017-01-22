//
//  dessinner_histogramme.c
//  projet7
//
//  Created by remy DEME on 12/04/2016.
//  Copyright © 2016 DEME Rémy. All rights reserved.
//

#include "histogramme.h"

/* cette fonction permet de calculer l'effectif pour chaque couleur */
void determination_effectif( unsigned char ** matrice , const infoBMP * infoEntete, int *tableau_effectif)
{
          int i , j ; 
                  for ( i = 0 ; i < infoEntete->hauteur ; i++ )
                {
                    for ( j = 0 ; j < infoEntete->largeur ; j++ )
                          {
                              tableau_effectif[matrice[i][j]]+= 1 ; 
                                        // printf ( " valeur matrice :ici  %d ", matrice[i][j]);
                          }
                     
                }
}

/* Cette fonction permet de calculer la fréquence */
void calcul_frequence (int *tableau_effectif , int *tableau_frequence, const infoBMP*infoEntete )
{
          int i ; 
          for ( i = 0 ; i < NBR_COULEUR ; i++ )
                {
                    tableau_frequence[i] = (tableau_effectif[i]/(infoEntete->hauteur*infoEntete->largeur)); 
                }
}


          /*creation des classe on somme l'ensemble de frequence de (beg à beg + largeur de classe ) */
void  creation_classe ( int *tableau_classe , int * tableau_effectif)
{
          int i ;
          int j ;
          int compteur = 0; 
          const unsigned int nombre_classe = sqrt((double)NBR_COULEUR); 
                    //printf ( " nombre_classe : %d \n ", nombre_classe);
          for ( i = 0 ; i < nombre_classe ; i++ )
                {
                    for ( j = compteur ; j < compteur + nombre_classe ; j++ )
                          {
                                        // printf ( " effectif%d  %d \n",j,tableau_effectif[j]); 
                              tableau_classe[i] += tableau_effectif[j] ; 
                          }
                    compteur += nombre_classe ;  
                              // printf ( "tableau :  %d \n", tableau_classe[i]); 
                   }
}

            /* fonction qui réalise l'histogramme  */
void dessiner_histogramme ( unsigned char **matrice , int *tableau_classe, const infoBMP*infoEntete )
{
          int i ; 
          int max = determiner_max(tableau_classe); 
          const int nombre_classe = sqrt((double)NBR_COULEUR); 
          int compteur = 0 ; 
          for ( i = 0 ;  i < nombre_classe  ; i++ )
                {
                    tracer_barre(pourcentage(tableau_classe[i], infoEntete,max), compteur, matrice);
                    compteur += nombre_classe ;
                }
}

void tracer_barre ( const int hauteur , const int colonne , unsigned char ** matrice )
{
     const int largeur_classe =  512/sqrt(NBR_COULEUR);  
          int i , j ; 
          for ( i = 0 ; i < hauteur ; i++ )
                {
                    for ( j = colonne ; j < colonne + largeur_classe ; j++ )
                          {
                              matrice[i][j] = 0 ;  
                          }
                }
}


void tapis_blanc ( unsigned char ** matrice ,const  infoBMP*infoEntete)
{
          int i , j ; 
          for ( i = 0 ; i < infoEntete->hauteur ; i++ )
                {
                    for ( j = 0 ; j < infoEntete->largeur ; j++ )
                          {
                                         matrice[i][j]= 250 ; 
                          }
                    
                }
}


/* Pourcentage retourne une valeur qui correspond à la lageur du trai tracé par la fonction tracer // on utilise max qui représente la vale*/ 
int pourcentage ( const int valeur , const infoBMP*infoEntete , const int max )
{
          return ((float)( valeur*(infoEntete->hauteur-2))/(max)); 
}

void afficher_taff ( int * tab )
{
          int i ; 
          for ( i = 0 ; i < 16 ; i++ )
                {
                    printf ( " valeur : %d \n", tab[i] ); 
                }
}


int determiner_max ( const int * tableau  )
{
          int max  = tableau[0]; 
          int i ; 
          for ( i = 0 ; i < NBR_COULEUR; i++  )
                {
                    if ( tableau[i] > max )
                          {
                              max = tableau[i];
                          }
                }
          return max ;          
}

          // histogramme couleur // 

void determination_effectif_IMC( pix ** matrice , const infoBMP * infoEntete,effec_pix * effectif )
{
          int i , j ; 
          for ( i = 0 ; i < infoEntete->hauteur ; i++ )
                {
                    for ( j = 0 ; j < infoEntete->largeur ; j++ )
                          {
                              effectif->effectif_b[matrice[i][j].b]++ ; 
                              effectif->effectif_r[matrice[i][j].r]++ ; 
                              effectif->effectif_v[matrice[i][j].v]++ ; 
                          }
                    
                }
          for ( i = 0 ; i < NBR_COULEUR ; i++ )
                {
                    printf ( "\n effectif b - %d \n %d ",i,effectif->effectif_b[i]);  
                }
          for ( i = 0 ; i < NBR_COULEUR ; i++ )
                {
                    printf ( "\n effectif  r - %d :  \n %d  ",i,effectif->effectif_r[i]);  
                }
          for ( i = 0 ; i < NBR_COULEUR ; i++ )
                {
                    printf ( "\n effectif  v - %d :  \n %d  ",i,effectif->effectif_v[i]);  
                }

}

/*void determination_frequence_IMC( const infoBMP * infoEntete, const effec_pix * const effectif , frequence_pix * const frequence)
{
          int i ;  
          long nombre_pixel = infoEntete->hauteur*infoEntete->largeur ; 
          for ( i  = 0 ; i < NBR_COULEUR ; i++ )
                          {
                             frequence->frequence_b[i] = (float)effectif->effectif_b[i]/(nombre_pixel); 
                              frequence->frequence_r[i] = (float)effectif->effectif_r[i] /nombre_pixel; 
                              frequence->frequence_v[i] = (float)effectif->effectif_v[i]/nombre_pixel ; 
                          }
                    
                
}*/

void tapis_blanc_IMC ( pix ** matrice ,const  infoBMP*infoEntete)
{
          int i , j ; 
          for ( i = 0 ; i < infoEntete->hauteur ; i++ )
                {
                    for ( j = 0 ; j < infoEntete->largeur ; j++ )
                          {
                              matrice[i][j].r= 0 ; 
                              matrice[i][j].v=0;
                              matrice[i][j].b = 0 ;
                          }
                    
                }
}


void tracer_barre_IMC_R ( const int hauteur , const int colonne , pix ** matrice )
{
          const int largeur_classe = 1 ;  
          int i , j ; 
          for ( i = 0 ; i < hauteur ; i++ )
                {
                    for ( j = colonne ; j < colonne + largeur_classe ; j++ )
                          {
                              matrice[i][j].r = 250;  
                          }
                }
}
void tracer_barre_IMC_V ( const int hauteur , const int colonne , pix ** matrice )
{
          const int largeur_classe = 1 ;  
          int i , j ; 
          for ( i = 0 ; i < hauteur ; i++ )
                {
                    for ( j = colonne ; j < colonne + largeur_classe ; j++ )
                          {
                              matrice[i][j].v = 250;  
                          }
                }
}

void tracer_barre_IMC_B ( const int hauteur , const int colonne , pix ** matrice )
{
          const int largeur_classe = 1 ;  
          int i , j ; 
          for ( i = 0 ; i < hauteur ; i++ )
                {
                    for ( j =  colonne ; j < colonne + largeur_classe ; j++ )
                          {
                              matrice[i][j].b = 250;  
                          }
                }
}


int pourcentage_IMC ( const int valeur , const infoBMP*infoEntete , const int max )
{
          return (( valeur*(infoEntete->hauteur-2))/(max)); 
}

void dessiner_histogramme_IMC ( pix**matrice , const infoBMP*infoEntete, effec_pix * effectif )
{
          int i ;
          int max_r = determiner_max(effectif->effectif_r); // détermine l'effectif le plus important pour la fonction pourcentage 
          int max_b = determiner_max(effectif->effectif_b); 
          int max_v = determiner_max(effectif->effectif_v); 
          const int nombre_classe = 1 ; 
          int compteur = 0 ; 
          for ( i = 0 ;  i < NBR_COULEUR ; i++ )
                {
                    tracer_barre_IMC_R(pourcentage(effectif->effectif_r[i], infoEntete,max_r), compteur, matrice);
                    tracer_barre_IMC_V(pourcentage(effectif->effectif_v[i], infoEntete,max_v), compteur, matrice);
                    tracer_barre_IMC_B(pourcentage(effectif->effectif_b[i], infoEntete,max_b), compteur, matrice);
                    compteur += nombre_classe ;
                }
}


