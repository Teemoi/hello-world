#include<stdio.h>
#include <malloc.h>
#include <windows.h>
#define  LIST_INIT_SIZE 80
#define LISTINCREMENT 10
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;
typedef int ElemType;
typedef struct {
    ElemType * elem;
    int length;
    int listsize;
}SqList;

Status InitList(SqList &L){
    L.elem = (ElemType *) malloc (LIST_INIT_SIZE * sizeof(ElemType));
    if(!L.elem){
        exit(OVERFLOW);
    }
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    return OK;
}

Status ListInsert(SqList &L, int i, ElemType e){
    ElemType  *newbase, *p, *q;
    if(i<1||i>L.length+1){
        return ERROR;
    }
    if(L.length >= L.listsize){
        newbase = (ElemType *) realloc(L.elem, (L.listsize+LISTINCREMENT) * sizeof(ElemType));
        if(!newbase){
            printf("OVERFLOW");
            return ERROR;
        }
        L.elem = newbase;
        L.listsize += LISTINCREMENT;
    }
    q = &(L.elem[i-1]);
    for(p = &(L.elem[L.length-1]);p>=q;--p){
        *(p+1) = *p;
    }
    *q = e;
    ++L.length;
    return OK;
}

Status MergeList(SqList L_a, SqList L_b, SqList &L_c){
    int i = 1; int j = 1; int k  = 1;
    InitList(L_c);
    while(i <= L_a.length && j <= L_b.length){
        if(L_a.elem[i-1]<L_b.elem[j-1]){
            ListInsert(L_c, k, L_a.elem[i-1]);
            i++;
        }else if(L_a.elem[i-1]==L_b.elem[j-1]){
            ListInsert(L_c, k, L_a.elem[i-1]);
            i++;
            j++;

        }else{
            ListInsert(L_c, k, L_b.elem[j-1]);
            j++;
        }
        k++;
    }
    while(i<=L_a.length){
        ListInsert(L_c, k, L_a.elem[i-1]);
        k++;
        i++;
    }
    while(j<= L_b.length){
        ListInsert(L_c, k, L_b.elem[j-1]);
        k++;
        j++;
    }
    return OK;

}

//以下为测试
int main(){
    SqList a,b,c;
    InitList( a);
    InitList(b);
    a.elem[0] = 1;
    a.length = 1;
    b.elem[0] = 1;
    b.length = 1;
    MergeList(a,b,c);
    for(int i = 0; i<c.length;i++){
        printf("%d ",c.elem[i]);
    }
}