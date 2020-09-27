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

//空线性表的初始化
Status InitList(SqList &L){
    L.elem = (ElemType *) malloc (LIST_INIT_SIZE * sizeof(ElemType));   //分配预定义大小的储存空间，返回值强子转化
    if(!L.elem){                                                             //为ElemType类型的指针并且赋值给L.elem
        exit(OVERFLOW);
    }
    L.length = 0;                                                            //置当前顺序表的长度为0
    L.listsize = LIST_INIT_SIZE;                                            //暂存当前的储存空间，为初始值
    return OK;
}

Status ListInsert(SqList &L, int i, ElemType e){
    ElemType  *newbase, *p, *q;
    if(i<1||i>L.length+1){                  //判断插入元素的位置是否合理
        return ERROR;
    }
    if(L.length >= L.listsize){                 //如果当前储存空间已满，则分配空间，每次分配LISTINCREMENT个空间
        newbase = (ElemType *) realloc(L.elem, (L.listsize+LISTINCREMENT) * sizeof(ElemType));    //定义新的基点
        if(!newbase){                                                                                       //基点不存在则报错
            printf("OVERFLOW");
            return ERROR;
        }
        L.elem = newbase;                           //newbase只是一个中间变量
        L.listsize += LISTINCREMENT;                //储存空间+1
    }
    q = &(L.elem[i-1]);                             //q指针为要插入元素的位置
    for(p = &(L.elem[L.length-1]);p>=q;--p){        //把第i以后的数据元素往后移动一个单位
        *(p+1) = *p;
    }
    *q = e;                                         //插入该元素
    ++L.length;                                     //表的储存空间+1
    return OK;
}

//顺序表相加，并且排序，且去除重复元素
Status MergeList(SqList L_a, SqList L_b, SqList &L_c){                  //L_a,L_b为需要相加的两个顺序表，L_c为相加后的结果
    int i = 1; int j = 1; int k  = 1;                                   //i,j,k，分别为表a,b,c的下标，负初始值为1是因为为了契合书本上的函数，但是在本方法中需要在1的基础上-1
    InitList(L_c);                                                  //创建数据表L_c
    while(i <= L_a.length && j <= L_b.length){                         //确保每一个元素都能遍历
        if(L_a.elem[i-1]<L_b.elem[j-1]){                               //比较L_a,L_b两个顺序表中的每一个元素，把小的值放入L_c中
            ListInsert(L_c, k, L_a.elem[i-1]);
            i++;
        }else if(L_a.elem[i-1]==L_b.elem[j-1]){
            ListInsert(L_c, k, L_a.elem[i-1]);
            i++;                                                        //i,j都++，确保了去除重复元素
            j++;

        }else{
            ListInsert(L_c, k, L_b.elem[j-1]);
            j++;
        }
        k++;                                                            //L_c表的下标+1，为了存放下一个数据元素
    }           //该函数的写法有缺陷，当某一个L_a或L_b某一个数据表遍历完了之后，循环会停止，两个表中，某一个表的元素会被提取完毕，而
                //剩下的那个表中还会存在元素

    //判断是哪个表还有元素，把这个表的剩余元素添加到L_c中
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
    a.elem[1] = 2;
    a.length = 2;
    b.elem[0] = 1;
    b.elem[1] = 3;
    b.length = 2;
    MergeList(a,b,c);
    for(int i = 0; i<c.length;i++){
        printf("%d ",c.elem[i]);
    }
}