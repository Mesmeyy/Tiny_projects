/*************************************************************************
	> File Name: 17.c
	> Author: 朱紫钰
	> Mail: zhuziyu1157817544@gmail.com
	> Created Time: 2017年05月24日 星期三 16时36分41秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node
{
    char a;
    short b;
    int c;
};
int main()
{
    struct node s;
    memset(&s,0,sizeof(s));

    s.a = 3;
    s.b = 5;
    s.c = 7;
    struct node *pt = &s;

    printf("%d\n",*(int*)pt);
    printf("%lld\n",*(long long *)pt);
    return 0;
}
