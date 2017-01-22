//
//  K_means.h
//  projet7
//
//  Created by remy DEME on 14/05/2016.
//  Copyright © 2016 DEME Rémy. All rights reserved.
//

#ifndef K_means_h
#define K_means_h

#include "tools.h"
void remise_zero_sigma ( sommes *sigma, const int nombre_cluster ); 
int  module ( const int x , const int y , centre c, pix**matrice ); 
void recherche_min ( const int *distances, const int nombre_cluster, int *match ); 
void clusterise (const int num_c, cluster **groupe , pix**matrix , const int x , const int y ); 
cluster **create_groupe ( const infoBMP * infoEntete ); //  
void calcul_centre (centre * c , cluster **groupe, const int *taille_cluster , const int k , sommes *sigma,const infoBMP*infoEntete);// 
void affiche_centre ( const centre * c  , const int k ); // affiche les centres 
int egalite_centre ( const centre c[] ,const centre c_p[], const int k ); // vérifie si les  coods de centres precedents sont égal à celle//   
void remise_zero ( int * distances , const int nombre_cluster ); // remet à 0 les distances moyennes contenu dans les tableau // 
void modifier_image  ( const centre c[], pix**matrice , const int k , const infoBMP *infoEntete, cluster ** groupe); 
void initialise_center ( centre * centres , const int nombre_cluster, const infoBMP*infoEntete  ); 
void k_means (  const centre *centres , const int nombre_clusters , const infoBMP *infoEntete , pix**matrice , int *nombre_element , cluster **groupe ); 
void initialisation_sigma ( sommes *sigma, const int nombre_de_cluster  ); 
unsigned char generateur_couleur_aleatoir (void); 

          // k-means couler 

cluster_NG**create_groupe_NG ( const infoBMP * infoEntete ); 
int  module_NG( const int x , const int y , centre_NG c, unsigned char **matrice ); 
void  recherche_min_NG ( const int *distances, const int nombre_cluster,  int *match ); 
void calcul_centre_NG (centre_NG * c , cluster_NG **groupe, const int *taille_cluster , const int k , sommes_NG*sigma, const infoBMP*infoEntete); 
int egalite_centre_NG ( const centre_NG c[] ,const centre_NG c_p[], const int k ); 
void remise_zero_NG ( int * distances , const int nombre_cluster ); 
void calcul_centre_NG (centre_NG * c , cluster_NG **groupe, const int *taille_cluster , const int k , sommes_NG*sigma, const infoBMP*infoEntete); 
void k_means_NG (  const centre_NG *centres , const int nombre_clusters , const infoBMP *infoEntete , unsigned char **matrice , int *nombre_element , cluster_NG **groupe ); 
void clusterise_NG( const int num_c , cluster_NG **groupe , unsigned char **matrix , const int x , const int y ); 
void remise_zero_sigma_NG ( sommes_NG *sigma, const int nombre_cluster ); 
void initialise_center_NG ( centre_NG * centres , const int nombre_cluster, const infoBMP*infoEntete );
void initialisation_sigma_NG ( sommes_NG *sigma, const int nombre_de_cluster  ); 
void affiche_centre_NG ( const centre_NG * c  , const int k ); 
void modifier_image_NG  ( const centre_NG c[], unsigned char **matrice , const int k , const infoBMP *infoEntete, cluster_NG **groupe)
; 
#endif /* K_means_h */
