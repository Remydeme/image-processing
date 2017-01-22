//
//  sort.c
//  projet7
//
//  Created by remy DEME on 27/03/2016.
//  Copyright © 2016 DEME Rémy. All rights reserved.
//

#include "sort.h"
void merge_sort ( cluster* tab , const int lenght )
{
          cluster *temp = calloc(lenght, sizeof(cluster));  
          unsigned int graine = 1 ; // taille élémentaire de largeur entre les cellules 
          unsigned int begin = 0  , middle = 0 , end = 0 ; 
          while (  graine < lenght )
                {
                    begin = 0 ; 
                    while ( begin < lenght )
                          {
                              middle = begin + graine ; // middle situé à graine de begin ; 
                              end = middle + graine - 1 ; //end situé à graine - 1 du middle 
                              if( middle > lenght)
                                        middle = lenght - 1 ; 
                              if ( end > lenght)
                                        end = lenght - 1 ; 
                              merge(temp, begin, middle,end, tab); // appel de la fonction merge 
                              
                              begin = end + 1 ; 
                              
                          }
                    copy_tab(temp,tab,lenght);// appel de copy qui recopie temp dans tab   
                    graine = graine * 2 ; // l'etendu des tableau traités double ; 
                }
          free(temp); 
          temp = NULL ; 
}


void copy_tab ( cluster *origine , cluster *destinataire, int lenght) 
{
          int i ; 
          
          for ( i = 0 ; i < lenght ; i++ )
                {
                    *(destinataire + i ) = *(origine + i);// copy de origine dans source 
                }
}


void merge ( cluster*t , unsigned int begin , const unsigned int middle , const unsigned int end , cluster*tab)
{
          int i = begin ; 
          int j = middle; 
          int k ; // variable de boucle for ; 
          for ( k = begin ; k <= end ; k++ )
                {
                    if ( i >= middle)
                              t[k] = tab[j++]; // je place tous les éléments à partir du middle dans le tableau 
                    else if ( j > end )
                              t[k] = tab[i++]; // je place tous les éléments du début dans le reste du tableau 
                    else if ( (tab[i].x+tab[i].y) >= (tab[j].x+tab[j].y))
                              t[k] = tab[j++]; 
                    else 
                              t[k] = tab[i++];
                }
          
}

void print_tab ( const cluster tab[] , const int lenght )
{
          int i ; 
          for ( i = 0 ; i < lenght ; i++ )
                {
                    printf (" Valeur tab : %d : %d %d \n", i+1, tab[i].x,tab[i].y); 
                }
}
