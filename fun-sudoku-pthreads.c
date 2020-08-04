#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_THREADS 11
#define GRID_SIZE 9

//protocols
void* rowRunner(void *v);
void* colRunner(void *v);
void* gridRunner(void *v);
void genSudoku();

//threads store validation as 1/0 in validator array
struct validator{
  int index;
  int results;
};

//valid array
const int validArr[GRID_SIZE] = {1,2,3,4,5,6,7,8,9};


//initialize to valid sudoku
int sudoku[GRID_SIZE][GRID_SIZE] = { { 3, 1, 6, 5, 7, 8, 4, 9, 2 },
         { 5, 2, 9, 1, 3, 4, 7, 6, 8 },
         { 4, 8, 7, 6, 2, 9, 5, 3, 1 },
         { 2, 6, 3, 4, 1, 5, 9, 8, 7 },
         { 9, 7, 4, 8, 6, 3, 1, 2, 5 },
         { 8, 5, 1, 7, 9, 2, 6, 4, 3 },
         { 1, 3, 8, 9, 4, 7, 2, 5, 6 },
         { 6, 9, 2, 3, 5, 1, 8, 7, 4 },
         { 7, 4, 5, 2, 8, 6, 3, 1, 9 } };;

//picked up by qsort         
int compare(const void *a, const void *b) {
    return ( *(int*)a - *(int*)b );
}
         
void* rowRunner(void *va){
    //need to typecast the void pointer
    struct validator *va_struct = (struct validator*)va;
    
    //store results
    int temp[GRID_SIZE];
    
    //check rows
    for (int i = 0; i < GRID_SIZE; i++){
        for (int j = 0; j < GRID_SIZE; j++) {
            //store row vars into temp and sort temp
            temp[j] = sudoku[i][j];
        }//end row
        
        // Compare row each to validArr row
        qsort(temp, sizeof(temp)/sizeof(*temp),sizeof(*temp),compare);
        for (int i = 0; i < GRID_SIZE; i++){
            if (temp[i] != validArr[i]){
                //if a row isn't valid row thread 0 becomes false
                va_struct->results = 0;
                pthread_exit(0);
            }
        }
    }//end outer for
    //rows all are valid
    va_struct->results = 1;
    pthread_exit(0);
}
void* colRunner(void *va){
    //need to typecast the void pointer
    struct validator *va_struct = (struct validator*)va;
    
    //store results
    int temp[GRID_SIZE];
    
    //check cols
    for (int i = 0; i < GRID_SIZE; i++){
        for (int j = 0; j < GRID_SIZE; j++) {
            //store row vars into temp and sort temp
            temp[j] = sudoku[j][i];
        }//end col
        
        // Compare each col to validArr col
        qsort(temp, sizeof(temp)/sizeof(*temp),sizeof(*temp),compare);
        for (int i = 0; i < GRID_SIZE; i++){
            if (temp[i] != validArr[i]){
                //if a col isn't valid col thread 1 becomes false
                va_struct->results = 0;
                pthread_exit(0);
            }
        }
    }//end outer for
    
    //cols all are valid
    va_struct->results = 1;
    pthread_exit(0);
}

int checkSubgrid(int x, int y){
    
    //check and store subgrid
    int temp[GRID_SIZE];
    int c = 0;
     for(int i = x; i < x + 3; i++){
         for(int j = y; j < y + 3; j++){
             temp[c] = sudoku[i][j];
             c++;
        }
     }
     // Compare each subgrid to validArr 
        qsort(temp, sizeof(temp)/sizeof(*temp),sizeof(*temp),compare);
        for (int i = 0; i < GRID_SIZE; i++){
            if (temp[i] != validArr[i]){
                //invalid: thread becomes false
                return 0;
            }
        }
    //valid: thread is true
    return 1;
}

void* gridRunner(void *va){
    
    //need to typecast the void pointer
    struct validator *va_struct = (struct validator*)va;
    
    //dif threads to check dif subgrid
    //pass upper left coords of subgrid
    switch(va_struct->index){
        case 2:{
            int i = checkSubgrid(0,0);
            va_struct->results = i;
            pthread_exit(0);
        }
        case 3:{
            int i = checkSubgrid(0,3);
            va_struct->results = i;
            pthread_exit(0);
        }
        case 4:{
            int i = checkSubgrid(0,6);
            va_struct->results = i;
            pthread_exit(0);
        }
        case 5:{
            int i = checkSubgrid(3,0);
            va_struct->results = i;
            pthread_exit(0);
        }
        case 6:{
            int i = checkSubgrid(3,3);
            va_struct->results = i;
            pthread_exit(0);
        }
        case 7:{
            int i = checkSubgrid(3,6);
            va_struct->results = i;
            pthread_exit(0);
        }
        case 8:{
            int i = checkSubgrid(6,0);
            va_struct->results = i;
            pthread_exit(0);
        }
        case 9:{
            int i = checkSubgrid(6,3);
            va_struct->results = i;
            pthread_exit(0);
        }
        case 10:{
            int i = checkSubgrid(6,6);
            va_struct->results = i;
            pthread_exit(0);
        }
        default: printf("Error Thread Not Valid");
    }//end switch
    pthread_exit(0);
}

void genSudoku(){
    
    //generate a valid sudoku 25% of the time
    srand ( time(NULL) );
    int r = rand() % 4;
    
    if(r == 0){ // valid sudoku 25% of the time
        for (int i = 0; i < GRID_SIZE; i++){
            for (int j = 0; j < GRID_SIZE; j++) {
                printf("|%d|",sudoku[i][j]);
            }//end inner for
            printf("\n");
        }//end outter for
    }
    else if(r == 1){ //only cols valid 25% of the time
        for (int i = 0; i < GRID_SIZE; i++){
            for (int j = 0; j < GRID_SIZE; j++) {
                sudoku[i][j] = i + 1;
                printf("|%d|",sudoku[i][j]);
            }//end inner for
            printf("\n");
        }//end outter for
    }
    else{ // only rows valid 50% of the time
       for (int i = 0; i < GRID_SIZE; i++){
            for (int j = 0; j < GRID_SIZE; j++) {
                sudoku[i][j] = j + 1;
                printf("|%d|",sudoku[i][j]);
            }
            printf("\n");
        }
    }
}

int checkResults(struct validator v[]){
    int flag = 1;
    
    //check rows
    if(v[0].results == 0){
        printf("Rows are not valid.\n");
        flag = 0;
    }
    else
        printf("Rows are valid.\n");
    //check cols
    if(v[1].results == 0){
        printf("Columns are not valid.\n");
        flag = 0;
    }
    else
        printf("Columns are valid.\n");
    //check subgrids
    int subflag = 1;
    for(int i = 2; i < MAX_THREADS; i++){
        if(v[i].results == 0){
            printf("Subgrids are not valid.\n");
            flag = 0;
            subflag = 0;
            break;
        }
    }
    if(subflag)
        printf("Subgrids are valid.\n");
    
    return flag ? 1 : 0;
}

int main(int argc, char *argv[]){
    
    //create validator
    struct validator v[MAX_THREADS];

    printf("Generating Random Sudoku\n");
    genSudoku();

    //decalare threads
    pthread_t tids[MAX_THREADS];
    
    //set default attr (use for all threads)
    pthread_attr_t attr; 
    pthread_attr_init(&attr);
    
    //create row checker thread
    pthread_create(&tids[0],&attr,rowRunner,&v[0]);
    v[0].index = 0;

    //create column checker thread
    pthread_create(&tids[1],&attr,colRunner,&v[1]);
    v[1].index = 1;
    
    //create subgrid checker threads
    for(int i = 2; i < MAX_THREADS; i++){
        v[i].index = i;
        pthread_create(&tids[i],&attr,gridRunner,&v[i]);
    }
    
    //join threads 
    for(int i = 0; i < MAX_THREADS; i++)
        pthread_join(tids[i], NULL);
    
    //print results
    printf("\n");
    int i = checkResults(v);
    printf("\n***Results***\n");
    if(i)
        printf("\nVALID SUDOKU.\n\n");
    else
        printf("\nNOT A VALID SUDOKU.\n\n");
    
    
    return 0;
}
