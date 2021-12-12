/**
 * @file Triplet.c
 * @author your name (you@domain.com)
 * @brief 通过抽象数据类型三元组学习数据抽象
 * @version 0.1
 * @date 2021-12-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

Status InitTriplet(Triplet *T, int a, int b, int c);
Status DestroyTriplet(Triplet *T);
ElemType Get(Triplet *T, int i);
Status Put(Triplet *T, int i, ElemType *elem);
Status IsAscending(Triplet *T);
Status IsDescending(Triplet *T);
ElemType Max(Triplet *T);
ElemType Min(Triplet *T);
