/*************************************************************************
	> File Name: 1.c
	> Author: 朱紫钰
	> Mail: zhuziyu1157817544@gmail.com
	> Created Time: 2017年05月23日 星期二 16时44分10秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(int argc,char **argv)
{
    int t = 4;
    
    //printf("%lu\n",sizeof(t--));
    //printf("%lu\n",sizeof("ab c\nt\012\xa1*2"));
    //printf("%d\n",t);
    
    //证明sizeof时关键字
    // printf("%lu\n",sizeof t);
    // int y;
    /*
    int n ;
    int array[15];
    scanf("%d",&n);
    char *p = (char *)malloc(sizeof(char) * n);
    char *q = "asd";
    printf("%lu %lu\n",sizeof(p),strlen(p));
    printf("%lu %lu\n",sizeof(q),strlen(q));
    //这个区别也是和strlen的区别
    printf("%lu\n ",sizeof(array));
    
    */
    /*
    int n;
    scanf("%d",&n);
    char brray[n];
    printf("%lu\n",sizeof(brray));//c99
    */
    return 0;
}
