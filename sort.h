//
//  sort.h
//  projet7
//
//  Created by remy DEME on 27/03/2016.
//  Copyright © 2016 DEME Rémy. All rights reserved.
//

#ifndef sort_h
#define sort_h
#include "tools.h" 

void merge_sort(cluster *temp , const int lenght ); 
void merge ( cluster *t , const unsigned int begin , const unsigned int middle , const unsigned int end , cluster *tab); 
void copy_tab ( cluster *origine , cluster *destinataire , int lenght); 
void print_tab ( const cluster tab[], const int lenght); 

#endif /* sort_h */



          // _______________________PHASE 2 ____________________________________//
          //____________________________________________________________________//


/*
 void  clusterise( int x , int y,  centre *c,const int k , int * compteur ,  cluster *groupe_1 , pix**ptrTab )// a modifier 
 {
 
 int *distances = calloc(k,sizeof(int)); 
 int i ; 
 static int j = 0 ; 
 int indice  = 0 ; 
 int min ; 
 for ( i = 0 ; i < k ; i++ )
 {
 distances[i] = module(x, y, c[i], ptrTab); 
 
 }
 // printf(" distance  c1 : %d \n",distance_C1);
 //  printf ( "Distance c2 : %d \n", distance_C2); 
 min = 10000; // affecte a min la 1 eer dist
 for ( i = 0 ; i < k ; i++ )
 {
 if ( min > distances[i])
 {
 min = distances[i]; 
 indice = i ; 
 }
 
 }
 groupe_1[j].d = min; 
 groupe_1[j].x = x ; 
 groupe_1[j].y = y ; 
 groupe_1[j].r =ptrTab[x][y].r ;  
 groupe_1[j].v =ptrTab[x][y].v ;  
 groupe_1[j].b =ptrTab[x][y].b ;  
 groupe_1[j].cluster =  indice; 
 compteur[indice]++ ; 
 
 if ( j == 512*512) 
 {
 j = 0 ; 
 }
 else 
 {
 j++; // ajoute un à j
 }
 
 }
 
 //____________________________________________________//
 
 void calcul_centre (centre * c , cluster *groupe, const int *taille_cluster , const int k )// à  modifier 
 {
 int i ; 
 int *somme_x  = calloc(k, sizeof(int));
 int *somme_y=  calloc(k, sizeof(int));
 int *somme_r =calloc(k, sizeof(int));
 int *somme_v =calloc(k, sizeof(int));
 int *somme_b =calloc(k, sizeof(int));
 int *moyenne_x =  calloc(k, sizeof(int));
 int *moyenne_y = calloc(k, sizeof(int)); 
 int *moyenne_r =calloc(k, sizeof(int));
 int *moyenne_v =calloc(k, sizeof(int));
 int *moyenne_b =calloc(k, sizeof(int));
 
 for ( i = 0 ; i < 512*512 ; i++)
 {
 
 somme_x[groupe[i].cluster] += (*(groupe+i)).x;
 somme_y[groupe[i].cluster] += (*(groupe+i)).y; 
 somme_r[groupe[i].cluster] +=(*(groupe+i)).r; 
 somme_v[groupe[i].cluster] += (*(groupe+i)).v ; 
 somme_b[groupe[i].cluster] += (*(groupe+i)).b;
 
 
 
 }
 for ( i = 0 ; i < k ; i++ )
 {
 moyenne_x[i] =  somme_x[i]/taille_cluster[i]; 
 moyenne_y[i] = somme_y[i]/taille_cluster[i];
 moyenne_r[i] =  somme_r[i]/taille_cluster[i]; 
 moyenne_v[i] = somme_v[i]/taille_cluster[i]; 
 moyenne_b[i]= somme_b[i]/taille_cluster[i]; 
 }
 for ( i = 0 ; i < k ; i++ )
 {
 c[i].x = moyenne_x[i]; 
 c[i].y = moyenne_y[i];
 c[i].r = moyenne_r[i]; 
 c[i].v = moyenne_v[i]; 
 c[i].b = moyenne_b[i]; 
 
 }
 
 
 
 
 }
 
 
 void afficher_dist ( cluster * group , int taille_cluster )// garde 
 {
 int i ; 
 for ( i = 0  ; i < taille_cluster ; i++ )
 {
 printf ( " Distance : %d ",group[i].d); 
 printf ( "Coordonnées : (%d, %d) \n ",group[i].x,group[i].y); 
 }
 }
 
 
 //_________________________ Entrer la valeur des centres ___________//
 void entrer_centre( centre *c , const int k )// garde 
 {
 int i ; 
 for ( i = 0 ; i < k ; i++)
 {
 printf ( " La coordonnées en x : \t");
 scanf( "%d",&c[i].x);  getchar(); 
 printf ("\n");
 printf ( " La coordonnées en y : \t");
 scanf( "%d",&c[i].y); getchar(); 
 printf ("\n");
 printf ( " La coordonnées en r : \t");
 scanf( "%d",&c[i].r); getchar(); 
 printf ("\n");
 printf ( " La coordonnées en b : \t");
 scanf( "%d",&c[i].b); getchar(); 
 printf ("\n");
 printf ( " La coordonnées en v : \t");
 scanf( "%d",&c[i].v); getchar(); 
 printf ("\n");
 }
 }
 
 // 
 
 
 void affiche_centre ( const centre * c  , const int k )
 {
 int i ;
 for ( i = 0 ; i < k ; i++ )
 {
 printf ( " Centre : %d %d %d %d ",c[i].b,c[i].r,c[i].v,c[i].x); 
 }
 }
 
 
 int module (int x , int y,  const centre c, pix**ptrTab  )
 {
 int module ; 
 double  somme_quadratique ; 
 somme_quadratique = x-c.x*x-c.x + y-c.y*y-c.y + (ptrTab[x][y].b+ptrTab[x][y].r+ptrTab[x][y].b - c.b+c.r+c.v )* (ptrTab[x][y].b+ptrTab[x][y].r+ptrTab[x][y].b - c.b+c.r+c.v ) ; 
 module = (int)sqrt(somme_quadratique); 
 return module; 
 }
 
 
 
 int egalite_centre ( const centre c[] ,const centre c_p[], const int k )
 {
 int i ; 
 int b  ; 
 for ( i = 0 ; i < k ; i++ )
 {
 if ( c[i].b==c_p[i].b&& c[i].v==c_p[i].v && c[i].r==c_p[i].r && c[i].y== c_p[i].y && c[i].x== c_p[i].x)
 b++ ; 
 }
 if ( b == k ) return 1 ;
 
 return 0 ; 
 }
 
 
 void modifier_image  ( const centre c[], pix**ptrTab , const int k , const infoBMP *infoEntete, cluster * groupe_1)
 {
 int i , j , l ; 
 for ( i = 0, l = 0 ; i < infoEntete->hauteur ; i++)
 {
 for ( j = 0 ; j < infoEntete->largeur ; j++,l++)
 {
 ptrTab[i][j].b = c[groupe_1[l].cluster].b ;  
 ptrTab[i][j].r = c[groupe_1[l].cluster].r ;  
 ptrTab[i][j].v = c[groupe_1[l].cluster].v ;  
 }
 
 }
 
 }
 
 
 */

/*void display ( cluster *groupe, const int k , const  infoBMP * infoEntete , const centre*c  )// utiliser pour créer la photo restorer 
 {
 int i ,j = 0 ; 
 int follow = 0 ; 
 int cluster = 0 ; 
 while (cluster < k) 
 {
 for ( i = 0 ; i < infoEntete->hauteur ; i++ )
 {
 for ( j = j ; j < follow*(infoEntete->largeur) ; j++ )
 {
 if ( cluster == groupe[j].cluster )Ici si la diff entre centre et le point et >  0 => le point et vers le bas sinon vers le haut / au centre 
 {
 groupe[j].x = (c[cluster].x >= groupe[j].x) ?  (c[cluster].x - groupe[j].x) : (c[cluster].x + groupe[j].x)  ; 
 groupe[j].y = (c[cluster].y >= groupe[j].y) ?  (c[cluster].y - groupe[j].y) : (c[cluster].y + groupe[j].y)  ;
 groupe[j].i = (c[cluster].i >= groupe[j].i) ?  (c[cluster].i - groupe[j].i) : 0  ;
 }
 }
 
 follow++; // permet de passer à la rangé suivante et que la condition de superiorité soit la meme // 
 }
 follow = 0 ; // follow remis à 0 
 j = 0 ; // remet j à 0 
 cluster++; 
 
 }
 }
 */ 





          // ____________________________________ Before restore the pic ________________//

