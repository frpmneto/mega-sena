#include <stdio.h>
#include <stdlib.h>

void merge(int* vetor,int inicio, int meio, int fim){
    int i,j,k;
    int aux1 = meio - inicio + 1;
    int aux2 =  fim - meio;
    int e[aux1];
    int d[aux2];
 
    //preencher os vetores auxiliares
    for(i=0;i<aux1;i++){
        e[i]=vetor[inicio+i];
    }
    for(i=0;i<aux2;i++){
        d[i]=vetor[meio+i+1];
    }
    //fazer a troca
    i=0;
    j=0;
    k=inicio;
    while(i<aux1 && j<aux2){
        if(e[i]<=d[j]){
            vetor[k]=e[i];
            i++;
        }
        else{
            vetor[k]=d[j];
            j++;
        }
        k++;
    }
    while(i<aux1){
        vetor[k]=e[i];
        i++;
        k++;
    }
    while(j<aux2){
        vetor[k]=d[j];
        j++;
        k++;
    }
};
void mergesort(int* vetor,int inicio,int fim){
    if(inicio<fim){
        int meio= (inicio+fim)/2;
        mergesort(vetor,inicio,meio);
        mergesort(vetor,meio+1,fim);
        merge(vetor,inicio,meio,fim);
    }
};
  
  
void getnumbetween(int min,int max,int* n){//a simple function that reads an integer in between a maximun and a minimun limiter
    scanf("%i",n);
    while(*n < min || *n > max){
        if(*n < min){
            printf("digite um valor maior ou igual a %i:\n",min);//the number is too small
        }
        else{
            printf("digite um valor menor ou igual a %i:\n",max);//the number is too big
        }
        scanf("%i",n);
    }
    return;
}
  
void gerajogo(int tam,int* jogo){//this is the function that generate the random game
    int aux[61] = {0};//this array will make sure we dong get repeated numbers
    int cont = 0;

    aux[0] = 1;//0 is not a valid number
    while(cont<tam){//this will generate random numbers untill we have the requested ammount of random numbers
        int r = rand() % 61;//this line will generate a pseudorandom number between 0 and 60
        if(!aux[r]){//if we find a number not already generated we add it to the current game
            jogo[cont] = r;
            aux[r] = 1;
            cont++;
        }
    }
    
    return;
}
  
  
  
int main(){
    int quantjogos;
    int** jogos;
    int* tamjogo;

    //here we get the ammount of games to be generated
    printf("digite a quantidade de jogos que voce quer fazer\n");
    printf("a quantidade deve ser no minimo 1 e no maximo 20\n");
    getnumbetween(1,20,&quantjogos);

    //and here we allocate the needed memory    
    jogos = (int**) malloc(quantjogos*sizeof(int*));//array of games
    tamjogo = (int*) malloc(quantjogos*sizeof(int));//array that stores the size of each game
    
    for(int i=0;i<quantjogos;i++){
        //read the amount of numbers to be generated
        int bolas;
        printf("\ndigite a quantidade de bolas do jogo %i\n",i+1);
        printf("a quantidade deve ser no minimo 6 e no maximo 15\n");
        getnumbetween(6,15,&bolas);
        
        tamjogo[i] = bolas;//this will store the size of this game
        
        jogos[i] = (int*) malloc(bolas*sizeof(int));//allocate the memory for this game
        gerajogo(bolas,jogos[i]);//generate a random game
        mergesort(jogos[i],0,bolas-1);//that is an implementation of the mergesort i have already done, just for ordering the game
    }

    //this is only for printing the generated games:
    printf("\nJOGOS GERADOS:"); 
    for(int i=0;i<quantjogos;i++){
        printf("\njogo %i: ",i+1);
        printf("%i",jogos[i][0]);
        for(int j=1;j<tamjogo[i];j++){
            printf(", %i",jogos[i][j]);
        }
    }
    printf("\n");

    //and this will free the allocated memory
    for(int i=0;i<quantjogos;i++){
        free(jogos[i]);
    }
    free(jogos);

    return 0;
}
