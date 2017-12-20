/*************************************************************************
	> File Name: 14.c
	> Author: 朱紫钰
	> Mail: zhuziyu1157817544@gmail.com
	> Created Time: 2017年05月24日 星期三 13时45分42秒
 ************************************************************************/

#include<stdio.h>
#define swap(a,b){a = a+b;b = a-b;a = a-b;}
int main(int argc,char **argv)
{
    int a = 1;
    int b = 2;
    swap(a,b);
    printf("a = %d , b = %d\n",a,b);
}
