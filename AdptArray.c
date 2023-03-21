#include "AdptArray.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

typedef struct AdptArray_
{
    PElement *PElemArr;
    int num_of_elements;
    int arr_cap;
    COPY_FUNC copy_func;
    DEL_FUNC del_func;
    PRINT_FUNC print_func;
} AdptArr, *PAdptArray;

PAdptArray CreateAdptArray(COPY_FUNC cf, DEL_FUNC df, PRINT_FUNC pf)
{
    PAdptArray pa = (PAdptArray)malloc(sizeof(AdptArr));
    if (pa == NULL)
    {
        return NULL;
    }
    pa->num_of_elements = 0;
    pa->arr_cap = 1;
    pa->PElemArr = (PElement *)malloc(pa->arr_cap * sizeof(PElement));
    pa->PElemArr[0] = NULL;
    if (pa->PElemArr == NULL)
    {
        return NULL;
    }
    pa->copy_func = cf;
    pa->del_func = df;
    pa->print_func = pf;
    return pa;
}

void DeleteAdptArray(PAdptArray pa)
{
    if (pa == NULL)
    {
        return;
    }
    PElement curr;
    int length = pa->arr_cap;
    for (int i = 0; i < length; i++)
    {
        curr = pa->PElemArr[i];
        if (curr)
        {
            pa->del_func(curr);
        }
    }
    free(pa->PElemArr);
    free(pa);
}

Result SetAdptArrayAt(PAdptArray pa, int indx, PElement val)
{
    if (pa == NULL)
    {
        return FAIL;
    }
    if (indx < 0)
    {
        return FAIL;
    }
    if (indx >= pa->arr_cap)
    {
        int pre_cap = pa->arr_cap;
        pa->arr_cap = indx + 1;
        pa->PElemArr = (PElement *)realloc(pa->PElemArr, pa->arr_cap * sizeof(PElement));
        if (pa->PElemArr == NULL)
        {
            return FAIL;
        }
        for(int i = pre_cap; i < pa->arr_cap; i++)
        {
            pa->PElemArr[i] = NULL;
        }
    }

    if (pa->PElemArr[indx])
    {
        pa->del_func(pa->PElemArr[indx]);
        pa->PElemArr[indx] = NULL;
        pa->num_of_elements--;
    }
    pa->PElemArr[indx] = pa->copy_func(val);
    if (pa->PElemArr[indx] == NULL)
    {
        return FAIL;
    }
    pa->num_of_elements++;
    return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray pa, int indx)
{
    if (pa == NULL)
    {
        return NULL;
    }
    if (indx < 0)
    {
        return NULL;
    }
    if (indx >= pa->arr_cap)
    {
        return NULL;
    }
    if (pa->PElemArr[indx])
    {
        return pa->copy_func(pa->PElemArr[indx]);
    }
    return NULL;
}

int GetAdptArraySize(PAdptArray pa)
{
    if (pa == NULL)
    {
        return -1;
    }
    return pa->arr_cap;
}

void PrintDB(PAdptArray pa)
{
    if (pa == NULL)
    {
        return;
    }
    PElement curr;
    int length = pa->arr_cap;
    for (int i = 0; i < length; i++)
    {
        curr = pa->PElemArr[i];
        if (curr)
        {
            pa->print_func(curr);
        }
    }
}
