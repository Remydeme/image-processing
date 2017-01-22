//
//  tools.h
//  projet7
//
//  Created by remy DEME on 25/03/2016.
//  Copyright © 2016 DEME Rémy. All rights reserved.
//

#ifndef tools_h
#define tools_h

#include "filtre_prewitt_sobel.h"
#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <assert.h>
#include <errno.h>
#include <limits.h> 

#define TAILLE_BUFF 500
          // booléenne 
#define TRUE 1 
#define FALSE 2 
#define AFFICHE_VALEUR(a,b) printf ( " %s : %d \n",a,b);  
          // typedef // 


          // chemin absolue fichier sauvegarde centres 

#define CHEMIN_CENTRE "/Users/remydeme/Documents/programmes/projet7/projet7/database_center/centre_"
#define CHEMIN_FICHIER_TEMPS_EXEC "/Users/remydeme/Documents/programmes/projet7/projet7/database_center/temp_exec"

typedef struct infoImage infoBMP ; 
typedef struct  pixel pix ;
          // struct 

struct pixel 
{
          unsigned char v;
          unsigned char r;
          unsigned  char b; 
};
#pragma pack(1)// permet un alignement mémoir de 1 octet 
struct infoImage 
{
                    // entete de fichier 
          unsigned  char signature[2] ;// bon 
          unsigned  int tailleTotale ; // a voir 
          unsigned   int champReserve ; 
          unsigned   int  offsetDecalage ; // apparemment 
                                           // entete image // 
          unsigned int  tailleEntete ; // apparemment 
          unsigned int largeur ; // apprmment 
          unsigned  int hauteur ; // idem
          unsigned short nbrPlans; // 8 au lieu de 1 
          unsigned short profCodage ; 
          unsigned   int metCompression; 
          unsigned int tailleTot ;// taille sans offset  
          unsigned  int resolutionHori; 
          unsigned  int resolutionVerticale ; 
          unsigned  int couleurPalette; 
          unsigned  int nombreCouleurImportante; 
          char c[4]; 
};

          // fonctions 


          // ____________________ PHASE 2 ______________________// 

typedef struct cluster cluster;
typedef struct centre centre;
typedef  struct moyenne means;
typedef struct centre_PNS centre_PNS ; 
#pragma pack( ) 
struct centre 
{
          int x ; 
          int y ; 
          int r ; 
          int v ; 
          int b ; 
};
typedef struct centre_NG centre_NG ; 
struct centre_NG
{
          int x ; 
          int y; 
          int g ; 
};

typedef struct cluster_NG cluster_NG ; 
struct cluster_NG 
{
          int x ; 
          int y ; 
          int g ; 
          int cluster ; 
};

typedef struct centre_PNS_NG centre_PNS_NG; 
struct centre_PNS /* structure qui permet de manipuler les variables de type centre */ 
{
          centre * centre_p ; 
          centre * centre_n ; 
          centre * centre_s ; 
};

struct centre_PNS_NG /* structure qui permet de manipuler les variables de type centre */ 
{
          centre_NG * centre_p ; 
          centre_NG * centre_n ; 
          centre_NG * centre_s ; 
};
struct cluster
{
          int x ; // largeur 
          int y ; // hauteur 
          int r ;// intensité
          int v ; // intensité 
          int b ; 
          short int cluster ; 
};

struct moyenne 
{
         unsigned  char b ; 
         unsigned  char r ; 
          unsigned char g ; 
};

typedef struct sommes_NG sommes_NG ; 
struct sommes_NG 
{
          int *somme_x ;
          int *somme_y;
          int *somme_g ; 
          int *moyenne_x;
          int *moyenne_y;
          int * moyenne_g; 
};

 
/* structure de pointeurs sur tableau contenant les sommes  des coordonnées //  */
typedef struct sommes sommes ; 
struct sommes 
{
          int *somme_x ;
          int *somme_y;
          int *somme_r ;
          int *somme_v ;
          int *somme_b ;
          int *moyenne_x;
          int *moyenne_y; 
          int *moyenne_r ;
          int *moyenne_v ;
          int *moyenne_b;
};
          // prototyes fonctions 
          // phase 1 fonctions 
void affiche_header ( infoBMP*infoEntete );
void filtre_prewitt (  unsigned char**matrice , infoBMP*infoEntete ); 
int normalisation_pixels ( int valeur ); 
          // ensembles de fonctions utilisé pour la coloration des pixels par des couleurs alèatoires // 
void  fausse_couleur_centre (  centre * centre , const int nombre_cluster ); 
unsigned char generateur_couleur_aleatoir ( );

          // file_name // prototype de fonction de sauvegarde de fichier // 

void change_to_char ( char *centaine , char *dizaine , char *unite  ,const int centaine_int , const int dizaine_int, const int unite_int  );
char * convert_int_to_char ( const int valeur ); 
char * center_name ( const int nombre_centre , char * name  ); 
int temp_exec ( const float time_exec , const int nombre_couleur ); 
 void save_center ( const int nombre_cluster , centre * c  , const float temps_exec ); 
void initialiser_centre_memoir ( const int nombre_de_cluster , centre_PNS *centres ); 
int * alloc_memoir ( const int size );
pix **allocation_tableau (const infoBMP*infoEntete  ); 
void free_memory( sommes * sigma  ); 
int initialiser_centre_s ( const int nombre_cluster , centre * c  ); 
void free_memory_NG( sommes_NG * sigma  ); 
          // kmeans 
void initialiser_centre_memoir_NG ( const int nombre_de_cluster , centre_PNS_NG *centres ); 

int means_matrice(  const infoBMP * infoEntete , const unsigned char ** matrice ); 
int new_x (  const int means , const unsigned char valeur_pix , const int ecart_type_1 , const int ecart_type_2  ); 
void modifier_image_NG  ( const centre_NG c[], unsigned char **matrice , const int k , const infoBMP *infoEntete, cluster_NG **groupe); 
void viderBuff ( );
#endif /* tools_h */
