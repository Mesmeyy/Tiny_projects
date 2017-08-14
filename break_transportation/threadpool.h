/*************************************************************************
	> File Name: threadpool.h
	> Author: 朱紫钰
	> Mail: zhuziyu1157817544@gmail.com
	> Created Time: 2017年08月14日 星期一 12时31分08秒
 ************************************************************************/

#ifndef _THREADPOOL_H
#define _THREADPOOL_H
#include<iostream>
#include<thread>
#include<vector>
#include<string.h>
#include<condition_variable>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include"file.h"
using namespace std;
using std::string;
std::condition_variable_any m_t;     //条件变量
std::mutex locks;                     //互斥锁
int i = 1;                           //打印机资源 初始为1 表示可用
int j = 1;

using namespace std;

template<typename T>
class threadpool
{
public:
    threadpool (int &sockfd);
    ~threadpool();
    static void work(void *arg);
    bool dofile(T &t);
    public:
    const int thread_numbr = 5;
    std::vector<thread> vec;//线程存放在这里
    static int m_sockfd ;
    int max_count = 0;
};

template<typename T>
int threadpool<T>::m_sockfd = -1;

void sub(int i)
{
    std::lock_guard<std::mutex> locker(locks);
    while(i == 0){
        m_t.wait(locks);
    }
    i--;
}
void add(int i)
{
    std::lock_guard<std::mutex> locker(locks);
    i++;
    m_t.notify_all();
}
template<typename T>
threadpool<T>::threadpool(int &sockfd){
    m_sockfd = sockfd;
    for(int i = 0;i < thread_numbr;i++){
        thread t(work,this);
        vec.push_back(move(t));
    }//创建好了5个线程
    max_count = 4;
}

template<typename T>
threadpool<T>::~threadpool(){
    //delete vec;
}
/*
template<typename T>
threadpool::request(T *request)
{
    lock_guard(std::mutex) locker(lock);
    que.push(request);
    m_t.notify_all();
}
*/
template<typename T>
bool threadpool<T>::dofile(T &temp)
{
    char filename[512];
    const char *p = temp.now_count.data();
    memset(filename,0,512);
    strcpy(filename,"temp");
    strcat(filename,p);
    strcat(filename,temp.url);
    cout << "filename :"<<filename <<endl;

    int fd = open(filename,O_RDWR|O_CREAT|O_APPEND,0664);
    if(fd < 0){
        cout << "建立"<<temp.url<<"文件失败"<<endl;
        return false ;
    }
    int ret = write(fd,temp.content,strlen(temp.content));
    if(ret < 0){
        cout <<"write wrong"<<endl;
        return false;
    }
    return true;
}

template<typename T>
void threadpool<T>::work(void *arg)
{
    threadpool *pool = (threadpool*)arg;
    bool non_stop = true;
    while(non_stop){
        //subi();
        T *temp ;
        char read_buf[1024];
        memset(read_buf,0,1024);
        sub(i);
        int ret = recv(m_sockfd,read_buf,1024,0);
        add(i);
        temp = (T*)read_buf;
        if(ret < 0){
            cout <<"recv error"<<endl;
            return ;
        }
        if(!pool -> dofile(*temp)){
            cout << "dofile wrong,return "<<endl;
            //杀这个线程
        }
        if(ret < 1024){
            if((temp->now_count == "4") && (temp->end=="\r\n")){
                //杀死所有的线程，收集资源,退出这个线程池
               cout << "所有线程即将死掉"<<endl;
            }else{
                //只杀死这个线程,其余的线程不杀死
                cout <<"只杀死这一个线程"<<endl;
            }
        }
    }     
}
#endif
