/*************************************************************************
	> File Name: 11.3.c
	> Author: 朱紫钰
	> Mail: zhuziyu1157817544@gmail.com
	> Created Time: 2017年05月30日 星期二 21时13分23秒
 ************************************************************************/

#include<stdio.h>
int main()
{
    long a = 10;
    long *p = &a;
    long **q = &p;

    q = &a;

    printf("%ld\n",*p);
    printf("%ld\n",*q);
}
