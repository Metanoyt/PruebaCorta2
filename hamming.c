#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


int * errorList;

unsigned int setParity(unsigned int bits){

    int parityP1 = (bits & 1) ^ ((bits & 4)>>2) ^ ((bits & 16)>>4)  ^ ((bits & 64)>>6) ^ ((bits & 256)>>8);
    int parityP2 = (bits & 1) ^ ((bits & 2)>>1) ^ ((bits & 16)>>4)  ^ ((bits & 32)>>5) ^ ((bits & 256)>>8);
    int parityP4 = ((bits & 16)>>4) ^ ((bits & 32)>>5) ^ ((bits & 64)>>6);
    int parityP8 = (bits & 1) ^ ((bits & 2) >> 1) ^ ((bits & 4)>>2);
    
    bits += pow(parityP1*2,3);
    bits += pow(parityP2*2,7);
    bits += pow(parityP4*2,9);
    bits += pow(parityP8*2,10);
    return bits;
}

double log2(double n){
    return log(n)/log(2);
}

void encode(unsigned int message){
    unsigned int result;
    int amountOfZeros= 7-((int) log2(message)+1)%7;
    int amountOfWords = ceil(((int) log2(message)+1)/7);
    
    unsigned int wordList[amountOfWords];
    /*for (int index = 0; index < amountOfWords; index++)
    {
        wordList[index]=0;
    }*/
    for(int index=0; index<amountOfWords; index++){
        for(int j=0; j<11;j++){
            if(j==3 || j==7 || j>=9){
                continue;
            }
            else{
                if(message % 2) {
                    wordList[index] += pow(2,j);
                }
                message = message >> 1;
            }
        }
        wordList[index]= setParity(wordList[index]);
    }

    printf("informacion codificada:");
    for (int i = 0; i < amountOfWords; i++)
    {
         printf("%x",wordList[i]);
    }
    printf("\n");
     
}

void decode(unsigned int message){
    unsigned int messageError=8;
    unsigned int result=0;
    printf("informacion recuperada: %x\n", message);
    printf("informacion despues del error: %x\n",messageError);
    printf("informacion final: %x\n",result);
}


int main(int argc, char **argv){
    char* mode = argv[1];
    unsigned int message;
    sscanf(argv[3],"%x",&message);
    int creationIndex=0;
    errorList = (int*) malloc(sizeof(int)*(argc-3)/2);
    
    if(strcmp("decode", mode)==0){
        for(int i=2;i<argc;i++){
            if(strcmp("--error", argv[i])==0){
                sscanf(argv[i+1],"%d", &errorList[creationIndex]);
                creationIndex++;
            }
        }
        decode(message);
    }
    else{
        encode(message);
    }
    
    return 0;
}