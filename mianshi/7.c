/*************************************************************************
	> File Name: 7.c
	> Author: 朱紫钰
	> Mail: zhuziyu1157817544@gmail.com
	> Created Time: 2017年05月23日 星期二 21时41分11秒
 ************************************************************************/

#include<stdio.h>
char temp  = 't';
char Temp = 'T';
const char *p = &temp;
char const *q = &temp;
char *const r = &temp;
const char *const s = &temp;

int main()
{
    // 11111111
    *p = 'P';
    temp = 'P';

    // 22222222
    *q = 'P';
    temp = 'P';

    // 33333333
    r = &Temp;

    // 44444444
    *s = temp;
    s = &Temp;
}
