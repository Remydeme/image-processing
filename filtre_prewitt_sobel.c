//
//  filtre_prewitt_sobel.c
//  projet7
//

//

#include "filtre_prewitt_sobel.h"


void normalisation ( int matrice[3][3])
{
          int i ,j ; 
          for ( i = 0 ; i < 3 ; i++ )
                {
                    for ( j = 0 ; j < 3 ; j++)
                          {
                              if (matrice[i][j]  > 255  )
                                    {
                                        matrice[i][j] = 255; 
                                    }
                              else if ( matrice[i][j] < 0 )
                                    {
                                        matrice[i][j] = 0 ; 
                                    }
                          }
                }
}
  

void square_matrice (  int matrice[3][3]) 
{
          int i , j , k; 
          int temp[3][3] = {0} ;   
          for ( i = 0 ; i < 3 ; i++ )
                {
                    for ( j = 0 ; j < 3 ; j++ )
                          {
                              temp[i][j] = matrice[i][j] ;
                              matrice[i][j] = 0 ; 
                          }
                }
          
          for (  k = 0 ; k < 3 ; k ++ )
                {
                    for ( i = 0 ; i < 3 ; i++)
                          {
                              for ( j = 0 ; j < 3 ; j ++ )
                                    {
                                        matrice[i][k] += temp[i][j] *temp[j][k] ; 
                                        
                                    }
                          }
                }
          
}


         
void somme ( int matrice_resultante[3][3], int matrice_1[3][3], int matrice_2[3][3] )
{
          int i , j ; 
          for ( i = 0 ; i < 3 ; i++ )
                {
                    for ( j = 0 ; j < 3 ; j++ )
                          {
                              matrice_resultante [i][j] = sqrt((double)(matrice_1[i][j] + matrice_2[i][j])) ;  
                          }
                }
}


          //  copier les éléments ( pixels ) dans la matrice 3 * 3  via la valeur de hauteur et largeur 
void copie_vers_mini_matrice (  unsigned char **source, int  destinataire[3][3] , const int hauteur , const int largeur)
{
          int i , j ; 
          int x= 0  , y =0 ;  
          for ( i = hauteur  ; i < hauteur+3  ; i++ )
                {
                    for ( j = largeur; j < largeur+3  ; j++)
                          {
                              destinataire[y][x] = source[i][j] ; 
                              x++; 
                          }
                    y++ ;
                }
}
 
void copie_vers_matrice ( unsigned char  **destinataire , int  source[3][3] , const int hauteur , const int largeur   )
{
          int i , j ; 
          int x , y ; 
          for ( i = hauteur , x = 0 ; i < hauteur +3 ; i++, x++ )
                {
                    for ( j = largeur , y = 0 ; j < largeur + 3 ; j++ , y++)
                          {
                              
                              destinataire[i][j] = source[x][y]; 
                          }
                }
                  
          
          
}


      
void gradient (  int G[3][3])
{
          int i = 0 ; 
          int j = 0 ; 
          int tableau[3][3] = {0}; 
          int  Matrice_1[3][3] = {0};// ord
          int Matrice_2[3][3] = {0}; 
          multiplication(Matrice_1, Matrice_2,G);
          square_matrice(Matrice_1); 
          square_matrice(Matrice_2); 

          somme(G, Matrice_1, Matrice_2); 
          normalisation(G);
  
          for ( i = 0 ; i < 3 ; i++ )
                {
                    for ( j = 0 ; j < 3 ; j++)
                          {
                              tableau[i][j] = G[2-i][2-j] ; 
                          }
                }
          for ( i = 0 ; i < 3 ; i++ )
                {
                    for ( j = 0 ; j < 3 ; j++)
                          {
                              G[i][j] = tableau[i][j] ; 
                          }
                }
}

void multiplication ( int Matrice_1[3][3] , int Matrice_2[3][3] , int M3[3][3])
{
          int i , j ,  k ;
          int Derive_X[3][3] = {{-1,0,1},{-1,0,1},{-1,0,1}}; // 
          int Derive_X_Y [3][3] = {{-1,-1,-1},{0,0,0},{1,1,1}}; // 
          for (  k = 0 ; k < 3 ; k ++ )
                {
                    for ( i = 0 ; i < 3 ; i++)
                          {
                              for ( j = 0 ; j < 3 ; j ++ )
                                    {
                                        
                                        Matrice_1[i][k] += Derive_X[i][j]*M3[j][k] ; 
                                        Matrice_2[i][k] += Derive_X_Y[i][j]*M3[j][k] ; 
                                    }
                          }
                }
}




