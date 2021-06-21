#include "MysqlApi.h"
void MysqlApi::initConnectInfo()
{
    m_info.db_name = "test";
    m_info.ip = "127.0.0.1";
    m_info.port = 3306;
    m_info.usr = "root";
    m_info.pwd = "123456";
}

MysqlApi::MysqlApi()
{
    initConnectInfo();
    m_mysql = mysql_init(NULL);
    if(NULL == m_mysql)
    {
        cout<<"mysql_init failed..."<<endl;
    }
    cout<<"初始化成功"<<endl;
    m_mysql = mysql_real_connect(m_mysql
                                 ,m_info.ip.c_str()
                                 ,m_info.usr.c_str()
                                 ,m_info.pwd.c_str()
                                 ,m_info.db_name.c_str()
                                 ,m_info.port
                                 ,NULL
                                 ,0);
    if (NULL == m_mysql)
    {
        cout<<"连接失败"<<endl;
    }
    cout<<"连接成功"<<endl;
}

MysqlApi::~MysqlApi()
{
    if(NULL != m_mysql)
    {
        mysql_close(m_mysql);
        cout<<"释放了 m_mysql"<<endl;
    }
    if(NULL != m_result)
    {
        mysql_free_result(m_result);
        cout<<"释放了 m_result"<<endl;
    }
}

// 成功0 失败非0
int MysqlApi::exeSql(string sql)
{
    cout<<"正在插入"<<endl;
    return mysql_query(m_mysql,sql.c_str());
}

void  MysqlApi::selectDataCount(string sql)
{
    int RowCount = 0;
    if(exeSql(sql))
    {
        cout<<"run Sql err:"<<sql<<endl;
    }
    // 取出结果集
    MYSQL_RES *result = mysql_store_result(m_mysql);
    if(result)
    {
        // 获取结果集的行数
        // RowCount = result->row_count;
        m_result = result;
    }else{
        m_result = NULL;
    }
}


int MysqlApi::selectData(string sql)
{
    selectDataCount(sql);
    if(m_result !=  NULL)
    {
        show_result();
    }
}

// 打印结果集
void MysqlApi::show_result()
{
    unsigned int num_fields;
    unsigned int i;
    MYSQL_FIELD *fields;

    num_fields = mysql_num_fields(m_result); // 取结果集的字段个数
    fields = mysql_fetch_field(m_result); // 取结果集中的字段结构信息 数组
    for (i=0;i<num_fields;++i)
    {
        printf("%s\t\t",fields[i].name); // 打印结果集的字段名
    }

    printf("==================================\n"); // 分割线
    // 获取行
    MYSQL_ROW row;
    while((row = mysql_fetch_row(m_result)) != NULL)
    {
        for (i=0;i<num_fields;++i)
        {
            printf("%s\t\t",row[i]);
        }
        printf("\n");
    }
    printf("-------------------------------\n");
    printf("%d rows in set \n",m_result->row_count);
}

