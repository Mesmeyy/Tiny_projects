/*************************************************************************
	> File Name: 13.c
	> Author: 朱紫钰
	> Mail: zhuziyu1157817544@gmail.com
	> Created Time: 2017年05月24日 星期三 09时17分39秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
int main()
{
    char str[512];
    int i ;
    for(i= 0;i<512;i++){
        str[i] = -1-i;
    }
    printf("%lu\n",strlen(str));
    return 0;

}
