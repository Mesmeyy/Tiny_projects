/*************************************************************************
	> File Name: file.h
	> Author: 朱紫钰
	> Mail: zhuziyu1157817544@gmail.com
	> Created Time: 2017年08月14日 星期一 13时03分06秒
 ************************************************************************/

#ifndef _FILE_H
#define _FILE_H
#include<string>
class file
{
    public:
    char *url;
    int all_size;//文件大小
    int count;//一共多少块
    std::string now_count;//这个属于哪一块
    char *content;
    std::string end;
};

#endif
