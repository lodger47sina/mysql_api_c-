#include <iostream>
#include "MysqlApi.h"

int main()
{
    MysqlApi api;

    char buf[1024] = {0};
    sprintf(buf,"insert into %s(name,passwd,classid) value(\"%s\",%d,%d)","student","萧萧",222,1);
    cout<<string(buf)<<endl;

    /*
    int res = api.exeSql(string(buf));
    if(res)
    {
        cout<<"失败了"<<endl;
    }else{
        cout<<"成功了"<<endl;
    }
    */
    api.selectData("select * from student");
    return 0;
}

