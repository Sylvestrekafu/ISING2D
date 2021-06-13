#include <stdio.h>
#include <stdlib.h> // exit(),
#include <math.h>
#include <time.h>
#include<unistd.h> // usleep

#define Npoints 100
#define Kiir 10
#define  DimX  30
#define  DimY  30
#define T      1

#define UP     1        // spin orienté vers le haut
#define DOWN   (-1)     // spin orienté vers le bas

#define MAX    100

int M[DimX][DimY];
double beta;
double E;
/*
Objectif
--------
Simuler le modèle d'Ising en dimension 2 en utiliant l'algorithme de Métropolis

Le but est de déterminer la distribution des l'énergie et de la magnétisation du
plasma à la fin de la simulation.

--- Valeur enrégistrée:
*/


/* ==================================================== */
							/*generer les nombres entre 0 et 1 */
double randf()
{return( (double)(rand())/(double)(RAND_MAX+1.0));
}



/* ======================================================*/

int probability() // int wi
{
 //int x;
 //x=(int)((double)(rand())/(double)(RAND_MAX+1.0)*wi)+1;
 const int N = 1000;
 //const int MAX = 100;
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


void init()                /* initializes the spin configuration */
{
   int i, j, pt;
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
			 //pt=2*ram(2)-3;
			 // A chaque calculer la probalité
			 int p = probability();
			 if (p <50)
                M[i][j] = DOWN;
             else
                M[i][j] = UP;
			 //M[jj][ii]=pt;
			}
    }

return;
}



/*================================================== */

/*   Algorithme de Metropolis pour le modèle d'Ising  */

void flip(void) //int fx, int fy)
{
// sur la base de l'algorithme de Métropolis, simuler l'interaction entre les spins
// puis calculer, l'énergie, la magnétisation et
    int sum,j,i,spin;
    double p;
    float r, DE;
    //spin=M[i][j];
    //spin=-1;

    /* si DE < 0 our p < exp(....) ==> flip
        sinon pas de flip
        calcul de E, magnetisation, etc..
    */
    for(i=0; i < DimX; i++){
        for(j=0; j < DimY; j++){
          //spin = M[i][j];
          sum = M[i+1][j]+M[i-1][j]+M[i][j+1]+M[i][j-1];
          //DE = 2*spin*sum;
          DE = 2*M[i][j]*sum;
          if (DE < 0)
            M[i][j] = -1* M[i][j];

          // determine la probabilité i.e une valeur comprise entre 0 et 1
          p = 0.1; // à calculer correctement
          if (p < exp(-beta* DE/T))
             M[i][j] = -1*M[i][j];
        }
    }

    /*
    if (DE>0)
        p=exp(-beta*DE);
    else
        p=1;
    r=randf();
    if (r<=p)
        M[fx][fy]=-spin;
    */
    return;
}

/* Determine l'énergie */
void Mesures(void)
{
    int i,j;
    const double J = 1.0;   // intensité d'interaction
    const double U0= 1.0;   // moment magnétique
    const double B = 0.0;
    int nn = 0; // Nombre de plus proches voisins
    for(i=0; i < DimX; i++){
        for(j=0; j < DimY; j++){
            if(M[i][j]==M[i+1][j])
                nn++;
            else
                nn--;
            if(M[i][j]==M[i][j+1])
                nn++;
            else
                nn--;
        }
    }

    /* Energie */
    double m = 1.0; // magnetisation
    E = -J*(double)nn - U0*B*m;
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
    const int NMAX = 100; // nomber d'essais
    for(i=0; i < NMAX; i++){
        flip();
        Mesures();
        fprintf(fp, "%4d %d\n", i, (int)E);
    }
    fclose(fp);

    for(i=0; i < DimX; i++){
        for(j=0; j < DimY; j++){
            printf("%3d", M[i][j]);
        }
        putchar('\n');
    }
    putchar('\n');

    getchar();

 /* for(i=1; i<Npoints+1; i++)
	 {
		 printf("%d\n",i);
		 for(j=1; j<Kiir+1; j++)
		 {
			  for(t=1; t<NN+1; t++)
			  {
			  x=ram(DimX);
			  y=ram(DimY);
			  flip(x,y);
			  }
		  }

		pconf();
		getchar();
	  }
*/

 return 0;
}



/* =========================================================== */
