//
// Created by Reeb Deve on 2021/11/19.
//
#include "sql_connection_pool.h"
#include <string>
#include <iostream>

connection_pool::connection_pool() {
    this->CurConn = 0;
    this->FreeConn = 0;
}

connection_pool* connection_pool::GetInstance()
{
    static connection_pool connPool;
    return &connPool;
}

//构造初始化
void connection_pool::init(std::string url, std::string User, std::string PassWord,std::string DataBaseName, int Port, unsigned int MaxConn) {
    this->url = url;
    this->Port = Port;
    this->User = User;
    this->PassWord = PassWord;
    this->DatabaseName = DatabaseName;

    lock.lock();
    for(int i = 0;i < MaxConn;i++)
    {
        MYSQL* con = NULL;
        con = mysql_init(con);

        if( con == NULL)
        {
            std::cout << "Error:"<<mysql_error(con);
            exit(1);
        }
        con = mysql_real_connect(con,url.c_str(),User.c_str(),PassWord.c_str(),DataBaseName.c_str(),Port,NULL,0);

        if(con == NULL)
        {
            std::cout<<"Error"<<mysql_error(con);
            exit(1);
        }
        connList.push_back(con);
        ++FreeConn;
    }

    reserve = sem(FreeConn);

    this->MaxConn = FreeConn;

    lock.unlock();

}


