/*************************************************************************
	> File Name: 14.3.c
	> Author: 朱紫钰
	> Mail: zhuziyu1157817544@gmail.com
	> Created Time: 2017年05月24日 星期三 14时26分59秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
void swap(void *a,void *b)
{
    double temp  = *(double *)a;
    *(double *)a = *(double *)b;
    *(double *)b = temp;
}
int main()
{
    int a = 1;
    int b = 2;
    swap(&a,&b);
    printf("a = %d , b = %d \n",a,b);
}
