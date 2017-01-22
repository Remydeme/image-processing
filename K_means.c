//
//  K_means.c
//  projet7
//
//  Created by remy DEME on 14/05/2016.
//  Copyright © 2016 DEME Rémy. All rights reserved.
//

#include "K_means.h"
          // _______________________PHASE 2 ____________________________________//
          //____________________________________________________________________//

/*fonction calculant le module id es la distance de chaque point au centre ici */
int  module ( const int x , const int y , centre c, pix**matrice )
{
          int  module_carre ; 
          module_carre = ((x-c.x)*(x-c.x) + (y-c.y)*(y-c.y)+((matrice[y][x].r)-(c.r))*((matrice[y][x].r)-(c.r))+((matrice[y][x].b)-(c.b))*((matrice[y][x].b)-(c.b))+((matrice[y][x].v)-(c.v))*((matrice[y][x].v)-(c.v)) ); 
          return module_carre; 
}


/*Associe à chaque point un centre */
void clusterise (const int num_c, cluster **groupe , pix**matrix , const int x , const int y )
{
          groupe[y][x].x = x ; 
          groupe[y][x].y = y ; 
          groupe[y][x].r= matrix[y][x].r ;
          groupe[y][x].v= matrix[y][x].v ;
          groupe[y][x].b = matrix[y][x].b; 
          groupe[y][x].cluster = num_c; 
          
}
/*Recherche un minimum parmis les valeur suivantes */
void  recherche_min ( const int *distances, const int nombre_cluster, int *match )
{
          int i ; 
          *match = 0 ; 
          for ( i = 0 ; i < nombre_cluster ; i++ )
                {
                    if (   distances[(*match)] > distances[i] )
                          {
                              *match = i ; 
                          }
                }
}



          // genere le tableau deux dimension de cluster // 
/* create groupe alloue dynamiquement la mémoire du groupe de cluster et renvoi un pointeur su le tableau deux dimensions */
cluster **create_groupe ( const infoBMP * infoEntete )
{
          int i ;  
          cluster** groupe = malloc(sizeof(cluster*)*(infoEntete->hauteur)); 
          if ( groupe )// on vérifie que l'allocation dynamique à bien été faite 
                {
                    for ( i = 0 ; i < infoEntete->hauteur ; i++)
                          {
                              groupe[i] = calloc(infoEntete->largeur, sizeof(cluster)); 
                          }
                    for ( i = 0 ; i < infoEntete->hauteur ; i++)
                          {
                              if (!groupe[i])
                                    {
                                        perror(" Bad allocation "); 
                                        exit(EXIT_FAILURE); 
                                    }
                          }
                }
          return groupe; 
}


/**Fonction à améliorer remplacer les allocation dynamique **  cette fonction calcule les centre à partir des valeur ( distances valeur des pixels contenu dans groupe ) et taille cluster qui correspond au nombre d'élément contenu dans la fonction  */ 
void calcul_centre (centre * c , cluster **groupe, const int *taille_cluster , const int k , sommes*sigma, const infoBMP*infoEntete)// à  modifier 
{
          int i , j; /* variables de boucle */ 
          /* Allocation dynamique de variables somme et moyenne */ 
          for ( i = 0 ; i < infoEntete->hauteur ; i++)
                {
                    for ( j = 0 ; j < infoEntete->largeur ; j++)
                          {
                              sigma->somme_x[groupe[i][j].cluster] += groupe[i][j].x;
                              sigma->somme_y[groupe[i][j].cluster] += groupe[i][j].y; 
                              sigma->somme_r[groupe[i][j].cluster] +=  groupe[i][j].r; 
                              sigma->somme_v[groupe[i][j].cluster] += groupe[i][j].v      ; 
                              sigma->somme_b[groupe[i][j].cluster] += groupe[i][j].b; 
                          }/*calcul de la somme des diff valeurs */
                    
                }
          for ( i = 0 ; i < k ; i++ )
                {
                    if ( taille_cluster[i]== 0 )// si la taille du cluster est null la moyenne est donc null 
                          {
                              sigma->moyenne_x[i] = 0; 
                              sigma->moyenne_y[i] = 0;
                              sigma->moyenne_r[i] =  0; 
                              sigma->moyenne_v[i] = 0; 
                              sigma->moyenne_b[i]=  0; 
                              
                          }
                    else 
                          { /*Calucul des moyennes associé à chaque centre */
                                    (sigma->moyenne_x)[i] =  (sigma->somme_x)[i]/taille_cluster[i]; 
                                    (sigma->moyenne_y)[i] = (sigma->somme_y)[i]/taille_cluster[i];
                                    (sigma->moyenne_r)[i] =  (sigma->somme_r)[i]/taille_cluster[i]; 
                                    (sigma->moyenne_v)[i] =  (sigma->somme_v)[i]/taille_cluster[i]; 
                                    (sigma->moyenne_b)[i]=   (sigma->somme_b[i])/taille_cluster[i]; 
                          }
                    
                    
                }
          for ( i = 0 ; i < k ; i++ )
                {
                    c[i].x = sigma->moyenne_x[i]; 
                    c[i].y = sigma->moyenne_y[i];
                    c[i].r = sigma->moyenne_r[i]; 
                    c[i].v = sigma->moyenne_v[i]; 
                    c[i].b = sigma->moyenne_b[i]; 
                    
                }/* affectation et définition des nouveaux centre*/ 
          
          
}

/* initialisation des pointeurs sur les tableau de sommes */ 
void initialisation_sigma ( sommes *sigma, const int nombre_de_cluster  )
{
          sigma->somme_x = calloc(nombre_de_cluster, sizeof(int));
          sigma->somme_y = calloc(nombre_de_cluster, sizeof(int)); 
          sigma->somme_r = calloc(nombre_de_cluster, sizeof(int)); 
          sigma->somme_b = calloc(nombre_de_cluster, sizeof(int)); 
          sigma->somme_v = calloc(nombre_de_cluster, sizeof(int)); 
          sigma->moyenne_x = calloc(nombre_de_cluster, sizeof(int));
          sigma->moyenne_y = calloc(nombre_de_cluster, sizeof(int));
          sigma->moyenne_r = calloc(nombre_de_cluster, sizeof(int));
          sigma->moyenne_b = calloc(nombre_de_cluster, sizeof(int));
          sigma->moyenne_v = calloc(nombre_de_cluster, sizeof(int));
          if ( !(sigma->somme_x ||sigma->somme_y||sigma->somme_r||sigma->somme_b||sigma->moyenne_x||sigma->moyenne_y|| sigma->moyenne_r||sigma->moyenne_b||sigma->moyenne_v))
                {
                    perror("Bad allocation: "); 
                    exit(EXIT_FAILURE); 
                }
}

/*fonction permettant d'afficher les coordonnées des centres */
void affiche_centre ( const centre * c  , const int k )
{
          int i ;
          for ( i = 0 ; i < k ; i++ )
                {
                    printf ( " Centre : b:%d r:%d v:%d  x: %d  y: %d \n ",c[i].b,c[i].r,c[i].v,c[i].x,c[i].y); 
                }
}

/* vérifie que le centre n'a pas changé entre deux boucle while */
int egalite_centre ( const centre c[] ,const centre c_p[], const int k )
{
          int i ; 
          int b = 0  ; 
          for ( i = 0 ; i < k ; i++ )
                {
                    if ( c[i].b==c_p[i].b&& c[i].v==c_p[i].v && c[i].r==c_p[i].r && c[i].y== c_p[i].y && c[i].x== c_p[i].x)/* compare chaque coordonnées*/
                              b++ ; 
                }
          printf ( " \n\n Nombre de similitudes : %d  \n\n",b); 
          return b == k ; 
}


          // remise à zéro des  variables distance 

void remise_zero ( int * distances , const int nombre_cluster )
{
          int i ; 
          for ( i = 0 ; i  < nombre_cluster ; i++ )
                {
                    distances[i] = 0 ; 
                }
}

/*Cette fonction applique à chaque cluster les valeurs des coordonnées de ces centres une fois le taff terminé */ 
void modifier_image  ( const centre c[], pix**matrice , const int k , const infoBMP *infoEntete, cluster **groupe)
{
          int i , j , l ; 
          for ( i = infoEntete->hauteur-1, l = 0 ;  i >= 0 ; i--)
                {
                    for ( j = 0  ; j <  infoEntete->largeur ; j++ ,l++)
                          {
                              matrice[i][j].b = c[groupe[i][j].cluster].b ;  
                              matrice[i][j].r = c[groupe[i][j].cluster].r ;  
                              matrice[i][j].v = c[groupe[i][j].cluster].v ;  
                          }
                    
                }
          
}


void initialise_center ( centre * centres , const int nombre_cluster, const infoBMP*infoEntete )
{
          int i ; 
          for ( i = 0 ; i < nombre_cluster ; i++ )
                {
                    centres[i].x = random()%infoEntete->largeur ; 
                    centres[i].y = random()%infoEntete->hauteur;
                    centres[i].r = random()%256 ;
                    centres[i].v = random()%256 ; 
                    centres[i].b = random()%256 ; 
                }
}


          // fonction principale qui s 'occupe de construire les clusters  // 



void k_means (  const centre *centres , const int nombre_clusters , const infoBMP *infoEntete , pix**matrice , int *nombre_element , cluster **groupe )
{
          int i , j ,k ; 
          int match ; /*valeur qui guarde le min */
          int *distance = calloc(nombre_clusters, sizeof(int)) ;
          if ( distance )
                {
                    for ( i = 0 ; i < infoEntete->hauteur ; i++)
                          {
                              for ( j = 0 ; j < infoEntete->hauteur ; j++ )
                                    {
                                        for ( k = 0 ; k < nombre_clusters ; k++)
                                              {
                                                  distance[k] = module(j, i,centres[k], matrice); /*calcul de la distances d'un point à chaque centre */
                                              }
                                        recherche_min(distance,nombre_clusters,&match); 
                                        nombre_element[match]++; /*on ajoute un au compteur du groupe*/ 
                                        clusterise(match, groupe,matrice,j, i); /*associe à un groupe */ 
                                    }
                          }/*Ces trois boucles permettent de calculer la distances de tous les points et de les affecter à un cluster */
                    free(distance); 
                }
          else 
                {
                    assert(distance != NULL ); 
                }
}


/*remise à 0 des sommes et moyennes*/

void remise_zero_sigma ( sommes *sigma, const int nombre_cluster )
{
          int i ; 
          for ( i = 0 ; i < nombre_cluster ; i++ )
                {
                    sigma->somme_x[i] = 0;
                    sigma->somme_y[i] = 0;
                    sigma->somme_r[i] = 0;
                    sigma->somme_v[i] = 0;
                    sigma->somme_b[i] = 0; 
                    (sigma->moyenne_x)[i] = 0; 
                    (sigma->moyenne_y)[i] = 0;
                    (sigma->moyenne_r)[i] =  0; 
                    (sigma->moyenne_v)[i] = 0; 
                    (sigma->moyenne_b)[i]=  0; 
                }
}





void  fausse_couleur_centre (  centre * centres , const int nombre_cluster )
{
          int i ; 
          for ( i = 0 ; i < nombre_cluster ; i++)
                {
                    centres[i].r = generateur_couleur_aleatoir() ;  
                    printf ( "cluster n° %d rouge : %d \n ",i,centres[i].r); 
                    centres[i].b = generateur_couleur_aleatoir();
                    printf ( "cluster n° %d bleu : %d \n ",i,centres[i].b); 
                    centres[i].v = generateur_couleur_aleatoir();
                    printf ( "cluster n° %d vert : %d \n",i,centres[i].v); 
                }
}

/* gènère aléatoirement une couleur comprise entre 0 et 254  */

unsigned char generateur_couleur_aleatoir (void)
{
          return random()%255 ; 
}
  
          
          
          
          
          
          
          //____________________________________________------------------------------______________________________________//
          //______________________________________________________________________________________________________//
          // -------------------------------------------------------------------Kmeans Noir et blanc ---------------------------------------------------------//
          //______________________________________________________________________________________________________//
          //____________________________________________------------------------------______________________________________//

          /*Calcul de modul*/ 
int  module_NG( const int x , const int y , centre_NG c, unsigned char **matrice )
{
          return ((x-c.x)*(x-c.x) + (y-c.y)*(y-c.y)+( (matrice[y][x]-c.g) *(matrice[y][x]-c.g) ) );  
}

/* Clusterise répartie les différents pixel dans leur groupe en fonctions des distances au centres */
void clusterise_NG (const int num_c, cluster_NG **groupe ,  unsigned char **matrix , const int x , const int y )
{
          groupe[y][x].x = x ; 
          groupe[y][x].y = y ; 
          groupe[y][x].g = matrix[y][x] ; 
          groupe[y][x].cluster = num_c; 
}


/* Détermine la distance minimum */
void  recherche_min_NG ( const int *distances, const int nombre_cluster,  int *match )
{
          int i ; 
          *match = 0 ; 
          for ( i = 0 ; i < nombre_cluster ; i++ )
                {
                    if (   distances[(*match)] > distances[i] )/* si la valreur du rang i est inférieur alors je sauvegarde les données */ 
                          {
                              *match = i ; 
                          }
                }
}
          /* Alloue dynamiquement la mémoir néscéssaire */
cluster_NG**create_groupe_NG ( const infoBMP * infoEntete )
{
          cluster_NG** groupe  = NULL ; 
          if ( infoEntete)
                {
                    int i ;  
                    groupe = malloc(sizeof(cluster_NG*)*(infoEntete->hauteur)); 
                    if ( groupe )// on vérifie que l'allocation dynamique à bien été faite 
                          {
                              for ( i = 0 ; i < infoEntete->hauteur ; i++)
                                    {
                                        groupe[i] = calloc(infoEntete->largeur, sizeof(cluster_NG)); 
                                    }
                              for ( i = 0 ; i < infoEntete->hauteur ; i++)
                                    {
                                        if (!groupe[i])
                                              {
                                                  perror(" Bad allocation "); 
                                                  exit(EXIT_FAILURE); 
                                              }
                                    }
                          }
                     
                }
          else 
                {
                    assert(infoEntete != NULL ); 
                }
           return groupe ;        
}


void calcul_centre_NG (centre_NG * c , cluster_NG **groupe, const int *taille_cluster , const int k , sommes_NG*sigma, const infoBMP*infoEntete)// à  modifier 
{
          int i , j; /* variables de boucle */ 
          /* Allocation dynamique de variables somme et moyenne */ 
          for ( i = 0 ; i < infoEntete->hauteur ; i++)
                {
                    for ( j = 0 ; j < infoEntete->largeur ; j++)
                          {
                              sigma->somme_x[groupe[i][j].cluster] += groupe[i][j].x;
                              sigma->somme_y[groupe[i][j].cluster] += groupe[i][j].y; 
                              sigma->somme_g[groupe[i][j].cluster] += groupe[i][j].g; 
                          }/*calcul de la somme des diff valeurs */
                    
                }
          for ( i = 0 ; i < k ; i++ )
                {
                    if ( taille_cluster[i]== 0 )// si la taille du cluster est null la moyenne est donc null 
                          {
                              sigma->moyenne_x[i] = 0; 
                              sigma->moyenne_y[i] = 0;
                              sigma->moyenne_g[i] = 0 ; 
                          }
                    else 
                          { /*Calucul des moyennes associé à chaque centre */
                                    sigma->moyenne_x[i] =  sigma->somme_x[i]/taille_cluster[i]; 
                                    sigma->moyenne_y[i] = sigma->somme_y[i]/taille_cluster[i];
                                    sigma->moyenne_g[i] = sigma->somme_g[i]/taille_cluster[i]; 
                          }
                }
          for ( i = 0 ; i < k ; i++ )
                {
                    c[i].x = sigma->moyenne_x[i]; 
                    c[i].y = sigma->moyenne_y[i];
                    c[i].g =  sigma->moyenne_g[i];                    
                }/* affectation et définition des nouveaux centre*/ 
          
          
}


          /* Initialisation des pointeur par des addresse */
void initialisation_sigma_NG ( sommes_NG *sigma, const int nombre_de_cluster  )
{
          sigma->somme_x = calloc(nombre_de_cluster, sizeof(int));
          sigma->somme_y = calloc(nombre_de_cluster, sizeof(int)); 
          sigma->somme_g = calloc(nombre_de_cluster, sizeof(int)); 
          sigma->moyenne_x = calloc(nombre_de_cluster, sizeof(int));
          sigma->moyenne_y = calloc(nombre_de_cluster, sizeof(int));
          sigma->moyenne_g = calloc(nombre_de_cluster, sizeof(int)); 
          if ( !(sigma->somme_x ||sigma->somme_y||sigma->somme_g || sigma->moyenne_x||sigma->moyenne_y|| sigma->moyenne_g))
                {
                    perror("Bad allocation: "); 
                    exit(EXIT_FAILURE); 
                }
}


/* vérifie que le centre n'a pas changé entre deux boucle while */
int egalite_centre_NG ( const centre_NG c[] ,const centre_NG c_p[], const int k )
{
          int i ; 
          int b = 0  ; 
          for ( i = 0 ; i < k ; i++ )
                {
                    if ( c[i].g==c_p[i].g && c[i].y== c_p[i].y && c[i].x== c_p[i].x)/* compare chaque coordonnées*/
                              b++ ; 
                }
          printf ( " \n\n Nombre de similitudes : %d  \n\n",b); 
          return b == k ; 
}

/* remet à zéro les distances */
void remise_zero_NG ( int * distances , const int nombre_cluster )
{
          int i ; 
          for ( i = 0 ; i  < nombre_cluster ; i++ )
                {
                    distances[i] = 0 ; 
                }
}


void k_means_NG (  const centre_NG *centres , const int nombre_clusters , const infoBMP *infoEntete , unsigned char **matrice , int *nombre_element , cluster_NG **groupe )
{
          int i , j ,k ; 
          int match ; /*valeur qui guarde le min */
          int *distance = calloc(nombre_clusters, sizeof(int)) ;
          if ( distance )
                {
                    for ( i = 0 ; i < infoEntete->hauteur ; i++)
                          {
                              for ( j = 0 ; j < infoEntete->hauteur ; j++ )
                                    {
                                        for ( k = 0 ; k < nombre_clusters ; k++)
                                              {
                                                  distance[k] = module_NG(j, i,centres[k], matrice); /*calcul de la distances d'un point à chaque centre */
                                              }
                                        recherche_min_NG(distance,nombre_clusters,&match); 
                                        nombre_element[match]++; /*on ajoute un au compteur du groupe*/ 
                                        clusterise_NG(match, groupe,matrice,j, i); /*associe à un groupe */ 
                                    }
                          }/*Ces trois boucles permettent de calculer la distances de tous les points et de les affecter à un cluster */
                    free(distance); 
                }
          else 
                {
                    perror("Bad allocation : "); printf ( "\t ligne : %d \n",__LINE__);
                    distance = NULL;   
                }
}

/*remise à 0 des sommes et moyennes*/

void remise_zero_sigma_NG ( sommes_NG *sigma, const int nombre_cluster )
{
          int i ; 
          for ( i = 0 ; i < nombre_cluster ; i++ )
                {
                    sigma->somme_x[i] = 0;
                    sigma->somme_y[i] = 0;
                    sigma->somme_g[i] = 0 ; 
                    (sigma->moyenne_x)[i] = 0; 
                    (sigma->moyenne_y)[i] = 0;
                    sigma->moyenne_g[i] = 0 ; 
                    
                }
}



void initialise_center_NG ( centre_NG * centres , const int nombre_cluster, const infoBMP*infoEntete )
{
          int i ; 
          for ( i = 0 ; i < nombre_cluster ; i++ )
                {
                    centres[i].x = random()%infoEntete->largeur ; 
                    centres[i].y = random()%infoEntete->hauteur;
                    centres[i].g = random()%infoEntete->hauteur;
                }
}


void affiche_centre_NG ( const centre_NG * c  , const int k )
{
          int i ;
          for ( i = 0 ; i < k ; i++ )
                {
                    printf ( " Centre :g : %d x: %d  y: %d \n ",c[i].g,c[i].x,c[i].y); 
                }
}


void modifier_image_NG  ( const centre_NG c[], unsigned char **matrice , const int k , const infoBMP *infoEntete, cluster_NG **groupe)
{
          int i , j , l ; 
          for ( i = infoEntete->hauteur-1, l = 0 ;  i >= 0 ; i--)
                {
                    for ( j = 0  ; j <  infoEntete->largeur ; j++ ,l++)
                          {
                              matrice[i][j]= c[groupe[i][j].cluster].g ;  
                           }
                }
}
