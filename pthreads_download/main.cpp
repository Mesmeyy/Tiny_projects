/*************************************************************************
	> File Name: main.cpp
	> Author: 朱紫钰
	> Mail: zhuziyu1157817544@gmail.com
	> Created Time: 2017年12月25日 星期一 22时17分38秒
 ************************************************************************/

#include<iostream>
#include<string>
#include<stdlib.h>
#include"configure.h"
#include"processthread.h"
using namespace std;
using std::string;
int main(int argc,char *argv[])
{
    //解析参数
    if(argc != 3)
    show_error("Parameter is not equals 3.");
    
    PROCESSTHREAD pt;
    pt.set_clients(atoi(argv[1]));
    pt.set_para(argv[2]);
    pt.start();
    //构建http包
    //
    //发送确定能够支持多线程Range:bytes ,确定传输的文件格式
    //下分到多线程
        //构建http包
        //多线程每次固定接收**个
        //接收n次
        //接收后上锁写
        //解锁
    //爸爸线程等待子线程工作完毕
}
