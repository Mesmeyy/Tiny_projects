/*************************************************************************
	> File Name: 18.c
	> Author: 朱紫钰
	> Mail: zhuziyu1157817544@gmail.com
	> Created Time: 2017年05月24日 星期三 19时09分58秒
 ************************************************************************/

#include<stdio.h>
#define NAME(n) x##n
#define PRINTVAL(y,...)printf("x"#y":" __VA_ARGS__)
int main()
{
    int NAME(1);
    short *NAME(2) = (short *)&NAME(1);
    char *NAME(3) = (char *)&NAME(1);
    NAME(1) = 0;
    *NAME(2) = -1;

    PRINTVAL(1,"%x\n",NAME(1));
    PRINTVAL(2,"%x\n",*NAME(2));
    PRINTVAL(3,"%x\n",*NAME(3));
    return 0;
}
