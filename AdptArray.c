#include "AdptArray.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define INITIAL_SIZE 10
#define GROWTH_FACTOR 3

typedef struct AdptArray_{
    PElement* PElemArr;
    int arr_length;
    int arr_cap;
    COPY_FUNC copy_func;
    DEL_FUNC del_func;
    PRINT_FUNC print_func;
} AdptArr, * PAdptArray;

PAdptArray CreateAdptArray(COPY_FUNC cf, DEL_FUNC df,PRINT_FUNC pf){
    PAdptArray pa = (PAdptArray)malloc(sizeof(AdptArr));
    if(pa == NULL){
        perror("Error allocating PAdptArray memory.\n");
        return NULL;
    }
    pa->arr_length = 0;
    pa->arr_cap = INITIAL_SIZE;
    pa->PElemArr = (PElement*)calloc(INITIAL_SIZE, sizeof(PElement));
    if(pa->PElemArr == NULL){
        perror("Error allocating PElemArr memory.\n");
        return NULL;
    }
    pa->copy_func = cf;
    pa->del_func = df;
    pa->print_func = pf;
    return pa;
}

void DeleteAdptArray(PAdptArray pa){
    if(pa == NULL){
        perror("PAdptArray is NULL. No action was made.\n");
        return NULL;
    }
    PElement * curr = pa->PElemArr;
    PElement * pre;
    int length = pa->arr_length;
    for(int i = 0; i < length; i++)
    {
        pre = curr;
        curr = curr + 1;
        pa->del_func(*pre);
        pre = NULL;
    }
    free(pa);
}

Result SetAdptArrayAt(PAdptArray pa, int indx, PElement val){
    if (pa == NULL){
        perror("PAdptArray is NULL. Please create an array first.\n");
        return NULL;
    }
    if (indx < 0){
        perror("Index must be a positive.\n");
        return NULL;
    }
    if (indx >= pa->arr_cap){
        pa->arr_cap = indx * GROWTH_FACTOR;
        pa->PElemArr = (PElement*)realloc(pa->PElemArr, pa->arr_cap * sizeof(PElement));
        if(pa->PElemArr == NULL){
            perror("Error allocating PElemArr memory.\n");
            return NULL;
        }
        
    }

}