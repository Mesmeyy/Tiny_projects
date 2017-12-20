/*************************************************************************
	> File Name: 4.c
	> Author: 朱紫钰
	> Mail: zhuziyu1157817544@gmail.com
	> Created Time: 2017年05月23日 星期二 19时39分04秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
size_t q(size_t b)
{
    return b;
}
size_t (*p(char *str)) (size_t a)
{
    printf("%s\n",str);
    return q;
}
int main(int argc,char **argv)
{
    char str[] = "XiyouLinuxGroup";
    printf("%lu\n",p(str)(strlen(str)));
    return 0;
}
