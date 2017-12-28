/*************************************************************************
	> File Name: processthread.h
	> Author: 朱紫钰
	> Mail: zhuziyu1157817544@gmail.com
	> Created Time: 2017年12月28日 星期四 09时23分03秒
 ************************************************************************/

#ifndef _PROCESSTHREAD_H
#define _PROCESSTHREAD_H
#include <string>
#define CLIENTS 1

using namespace std;
using std::string;
class   PROCESSTHREAD
{
private:
    static int clients;
    string url;
    string host;
    int port;
public:
    PROCESSTHREAD();
    void set_clients(int number);
    void set_para(char * s);
    int set_socket();
    void start();
    void* sondo(void* p);
};
#endif
