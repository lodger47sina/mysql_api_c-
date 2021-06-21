#pragma once
#include <iostream>
#include <mysql/mysql.h>

using namespace std;

struct MysqlInfo{
    string ip;
    unsigned short port;
    string usr;
    string pwd;
    string db_name;
};

class MysqlApi
{
public:
    MysqlApi();
    // 执行sql语句
    int exeSql(string sql);
    // 查询sql返回结果数
    void  selectDataCount(string sql);
    // 现实结果集
    int selectData(string sql);
    ~MysqlApi();
private:
    void initConnectInfo();
    void show_result();
private:
    MysqlInfo m_info;
    MYSQL* m_mysql= NULL;
public:
    MYSQL_RES* m_result = NULL;
};

