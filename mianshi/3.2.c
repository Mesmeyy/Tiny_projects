/*************************************************************************
	> File Name: 3.2.c
	> Author: 朱紫钰
	> Mail: zhuziyu1157817544@gmail.com
	> Created Time: 2017年05月23日 星期二 19时29分16秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

void fun(int **p,int **q)
{
    int **t;
    t = p;
    *p = *q;
    *t = *q;
}

int main()
{
    int a = 1,b = 3;
    int *p = &a;
    int *q = &b;

    fun(&p,&q);

    printf("*p = %d  \n*q = %d  \na = %d \nb = %d \n",*p,*q,a,b);
}
