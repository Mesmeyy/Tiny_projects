/*************************************************************************
	> File Name: 3.c
	> Author: 朱紫钰
	> Mail: zhuziyu1157817544@gmail.com
	> Created Time: 2017年05月23日 星期二 19时21分11秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
/*
void get_str(char *ptr)
{
    ptr = (char *)malloc(17);
    strcpy(ptr,"Xiyou Linux Group");
}
*/
/*
void get_str(char **ptr)
{
    *ptr = malloc(18);
    strcpy(*ptr,"Xiyou Linux Group");
}
*/
/*
char * get_str()
{
    char *ptr = malloc(18);
    strcpy(ptr,"Xiyou Linux Group");
    return ptr;
}
int fun()
{
    ;
}*/
char * get_str()
{
    return "Xiyou Linux Group";
}
int main(int argc,char **argv)
{
    char *str = NULL;
    str = get_str();
    printf("%s\n",str);
}
