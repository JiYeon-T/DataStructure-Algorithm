#ifndef __TRIPLET_H__
#define __TRIPLET_H__


// 宏定义的常量
#define TRUE    1
#define FALSE   0
#define OK      1
#define ERROR   0
#define INFEASIBLE  -1
#define OVERFLOW    -2

// 变量
typedef int Status;
typedef int ElemType;

// class type
typedef struct Triplet
{
    /* data */
    ElemType data[3];
} Triplet;

// member functions
Triplet* InitTriplet(ElemType a, ElemType b, ElemType c);
Status DestroyTriplet(Triplet *T);
ElemType Get(Triplet *T, int i);
Status Put(Triplet *T, int i, ElemType elem);
Status IsAscending(Triplet *T);
Status IsDescending(Triplet *T);
ElemType Max(Triplet *T);
ElemType Min(Triplet *T);

void TripletTest();

#endif // end __TRIPLET_H__
