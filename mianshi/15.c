/*************************************************************************
	> File Name: 15.c
	> Author: 朱紫钰
	> Mail: zhuziyu1157817544@gmail.com
	> Created Time: 2017年05月24日 星期三 10时48分12秒
 ************************************************************************/

#include<stdio.h>
#ifdef __linux__
int a = 1;
#elif _WIN32
int a = 2;
#elif __APPLE__
int a = 3;
#else 
int a = 4;
#endif

int main()
{
    printf("a = %d\n",a);
    return 0;
}
