/*************************************************************************
	> File Name: 14.2.c
	> Author: 朱紫钰
	> Mail: zhuziyu1157817544@gmail.com
	> Created Time: 2017年05月24日 星期三 13时48分51秒
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include<string.h>
void swap(void *a,void *b,int size)
{
    void *temp = NULL;
    temp = malloc(size);
    if(!temp)return;

    memcpy(temp,a,size);
    memcpy(a,b,size);
    memcpy(b,temp,size);
}
int main()
{
    int a = 1;
    //int c = 0;
    int b = 2;
    swap(&a,&b,4);
    printf("a = %d , b = %d \n",a,b);
}
