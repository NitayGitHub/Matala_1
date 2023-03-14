#include "AdptArray.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct AdptArray_{
    PElement* PElemArr;
    int arr_size;
    COPY_FUNC copy_func;
    DEL_FUNC del_func;
    PRINT_FUNC print_func;
} AdptArr, * PAdptArray;

PAdptArray CreateAdptArray(COPY_FUNC cf, DEL_FUNC df,PRINT_FUNC pf){
    PAdptArray pa = (PAdptArray)malloc(sizeof(AdptArr));
    pa->arr_size = 0;
    pa->PElemArr = (PElement*)malloc(sizeof(PElement));
    pa->copy_func = &cf;
}