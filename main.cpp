#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>


//日志写模式定义
#define SYNLOG //同步写日志
//#define ASYNLOG //异步写日志

//LT/ET 模式
#define listenfdLT //水平触发阻塞
//#define listenfdET //边缘触发非阻塞


int main() {
    #ifdef SYNLOG
    //调用同步日志模型
    #endif
    #ifdef ASYNLOG
    //调用异步日志模型
    #endif
}
