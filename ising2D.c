#include <stdio.h>
#include <stdlib.h> // exit(),
#include <math.h>
#include <time.h>
#include<unistd.h> // usleep

#define  DimX  10
#define  DimY  10
#define T      1

#define UP     1        // spin orienté vers le haut
#define DOWN   (-1)     // spin orienté vers le bas
#define H      (0.5)
#define MAX    100


int M[DimX][DimY];
double beta;
double E;
/*
Objectif
--------
Simuler le modèle d'Ising en dimension 2 en utiliant la méthode de Monte Carlo et de Metropolis

Le but est de déterminer la distribution des l'énergie et de la magnétisation du
 à la fin de la simulation.

--- Valeur enrégistrée:
*/


/* ==================================================== */
							/*generer les nombres entre 0 et 1 */
double randf()
{return( (double)(rand())/(double)(RAND_MAX+1.0));
}



/* ======================================================*/

int probability()
{

 const int N = 1000;

 int i;
 int arr[N];
 srand((unsigned)time(NULL));
 for(i=0; i < N; i++){
    arr[i] = rand() % MAX + 1; // toujours <= MAX
    usleep(100); // man usleep
 }

 int index = rand() % N; // toujours entre 0 et N-1
 int x = arr[index];  // x est aléatoirement choice
 //double p  = ((double)x )/ MAX; // >= 0.0 et <= 1.0
 return x;
}



/* =================================================  */


void init()                /* initialisation des spin  */
{
   int i, j;
   for (i=0; i < DimY; i++){
        for (j=0; j<DimX; j++){
        /*
        ----------------------------
        |     |    |    |    |     |
        ----------------------------
        |     |    |    |    |     |
        ----------------------------
        |     |    |    |    |     |
        ----------------------------
        |     |    |    |    |     |
        ----------------------------
        */

			 // A chaque calculer la probalité
			 int p = probability();
			 if (p <50)
                M[i][j] = DOWN;
             else
                M[i][j] = UP;

			}
    }
return ;
}



/*================================================== */

/*   Algorithme de Metropolis pour le modèle d'Ising  */

void flip(void) //int fx, int fy)
{
// Sur la base de l'algorithme de Wolff, simuler l'interaction entre les spins
// puis calculer, l'énergie,
    int sum,j,i,spin;
    double p;
    float r, DE;
    //spin=M[i][j];
    //spin=-1;

    /* si DE < 0 ou p < 1- exp(-2*beta) ==> flip
        sinon pas de flip
        calcul de E, magnetisation, etc..
    */
    for(i=0; i < DimX; i++){
        for(j=0; j < DimY; j++){
          spin = M[i][j];
         sum = M[i+1][j]+M[i-1][j]+M[i][j+1]+M[i][j-1];
          DE = -H*spin*sum;
         // DE = -H*M[i][j]*sum; avec H=0.5
          if (DE < 0)
            M[i][j] = -1* M[i][j];

          // determine la probabilité i.e une valeur comprise entre 0 et 1
          p = rand();
          if (p < 1-exp(-2*beta))
             M[i][j] = -1*M[i][j];
        }
    }


    return;
}
/*
/* Determine la magnétisation*/
void Mesures(void)
{
    int i,j;
    int m = 0; // initialisation
    for(i=0; i< DimX; i++){
        for(j=0; j < DimY; j++)
        {
            m+=M[j][i];
        }
    }
    //return m;
}
/* s===========================================================*/

int main()
{
    FILE *fp;
    char *filename = "resultat.txt";
    fp = fopen(filename, "w");
    if(fp == NULL){
        fprintf(stderr, "Erreur: Impossible d'ouvrir le fichier '%s'", filename);
        exit(EXIT_FAILURE);
    }
    int i, j , x , y, NN;
    int t;
    NN=DimX*DimY;
    beta=1.0/T;
    // Initialisation
    init();
    int m;
    const int NMAX = 100; // nomber d'essais
    for(i=0; i < NMAX; i++){
            for (j=0;j<NMAX;j++){

            }
        flip();
        Mesures();
        fprintf(fp, "%3d %d\n",i,m);
    }
    fclose(fp);

    for(i=0; i < DimX; i++){
        for(j=0; j < DimY; j++){
            printf("%4d",M[i][j]);
        }
        putchar('\n');
    }
    putchar('\n');

    getchar();


 return 0;
}



/* =========================================================== */
//             Fin *** du ***Programme
/*============================================================*/
