//
// Created by Reeb Deve on 2021/11/17.
//

#ifndef WEBSERVER_LOG_H
#define WEBSERVER_LOG_H

#include <stdio.h>
#include "block_queue.h"
#include <stdarg.h>

class Log
{
public:
    static Log *get_instance()
    {
        static Log instance;
        return &instance;
    }
    static void* flush_log_thread(void* args)
    {
        Log::get_instance()->async_write_log();
    }
    //可选择的参数有日志文件，日志缓冲区大小，最大行数以及最长日志条队列
    bool init(const char* file_name,int log_buf_size = 8192,int split_lines = 5000000,int max_queue_size = 0);

    void write_log(int level,const char* format,...);

    void flush(void);

private:
    Log();

    virtual ~Log();

    void* async_write_log()
    {
        std::string  single_log;
        while(m_log_queue->pop(single_log))
        {
            m_mutex.lock();
            fputs(single_log.c_str(),m_fp);
            m_mutex.unlock();
        }
    }

private:
    char dir_name[128];//路径名
    char log_name[128];//log文件名
    int  m_split_lines;//日志最大行数
    int  m_log_buf_size;//日志缓冲区大小
    long long m_count;  //日志行数记录
    int  m_today;       //因为按天分类，记录当前是哪一天
    FILE* m_fp;         //打开log的文件指针
    char* m_buf;        //缓冲区
    block_queue<std::string>* m_log_queue;//阻塞队列
    bool m_is_async;    //阻塞队列
    locker m_mutex;
};


#define LOG_DEBUG(format,...) Log::get_instance()->write_log(0,format,##_VA_ARGS_)
#define LOG_INFO(format,...) Log::get_instance()->write_log(1,format,##_VA_ARGS_)
#define LOG_WARN(format,...) Log::get_instance()->write_log(2,format,##_VA_ARGS_)
#define LOG_ERROR(format,...) Log::get_instance()->write_log(3,format,##_VA_ARGS_)

#endif //WEBSERVER_LOG_H
