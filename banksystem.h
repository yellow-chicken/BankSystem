#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<conio.h>
#include<string.h>
#include<windows.h>

#define MAX_USER 1000  //最大用户数
#define LENGTH_OF_USERID  4  //账号最大长度
#define LENGTH_OF_PASS  6  //密码最大长度

char *role[]={
    "系统管理员;",  //0
    "柜台人员",       //1
    "用户"            //2
};//role 为角色名称数组

struct datenode
{
    short year;
    short month;
    short day;
};
typedef struct datenode date;//日期结构类型

struct usernode
{
    char userId[LENGTH_OF_USERID+1];//账号
    char name[9];//姓名
    int role;//角色
    char phonenumber[11];//手机号
    int balance;//当前余额
    char password[LENGTH_OF_PASS+1];//密码
};
typedef struct usernode user;//用户结构体类型


/*
    @函数名称:gotox    函数功能：到屏幕的第x行
*/
void gotox(int x)
{
    int i;
    for (i=0;i<x-1;i++)
        putchar('\n');
}


/*
    @函数名称：mainMenu      入口参数：无
    @函数功能：登录菜单，返回用户选择
*/
int mainMenu()
{
    int c;
    gotox(6);
    printf("\t\t\t         小型银行管理系统\n");
    printf("\t\t\t=================================\n");
    printf("\t\t\t*          1  登录系统\t\t*\n");
    printf("\t\t\t*          0  退出系统\t\t*\n");
    printf("\t\t\t=================================\n");
    printf("\t\t\t请输入选项[ ]\b\b");
    scanf("%d",&c);
    return c;
}

/*
    @函数名称：menuManager      入口参数：无
    @函数功能：显示柜台人员菜单，返回用户选择
*/
int menuManager()
{
    int c;
    gotox(6);
    printf("\t\t\t  小型银行管理系统——柜台人员\n");
    printf("\t\t\t=================================\n");
    printf("\t\t\t*  1\t浏览用户\t\t*\n");
    printf("\t\t\t*  2\t添加用户\t\t*\n");
    printf("\t\t\t*  3\t删除用户\t\t*\n");
    printf("\t\t\t*  4\t查询余额\t\t*\n");
    printf("\t\t\t*  5\t存款\t\t\t*\n");
    printf("\t\t\t*  6\t取款\t\t\t*\n");
    printf("\t\t\t*  7\t办理理财产品\t\t*\n");
    printf("\t\t\t*  8\t初始化用户密码\t\t*\n");
    printf("\t\t\t*  9\t修改登录密码\t\t*\n");
    printf("\t\t\t*  0\t注消\t\t\t*\n");
    printf("\t\t\t=================================\n");
    printf("\t\t\t请输入选项[ ]\b\b");
    scanf("%d",&c);
    return c;
}


/*
    @函数名称：menuAdmin     入口参数：无
    @函数功能：显示系统管理员菜单，返回用户选择
*/
int menuAdmin()
{
    int c;
    gotox(6);
    printf("\t\t\t   小型银行管理系统——系统管理\n");
    printf("\t\t\t=================================\n");
    printf("\t\t\t*  1\t浏览用户\t\t*\n");
    printf("\t\t\t*  2\t添加用户\t\t*\n");
    printf("\t\t\t*  3\t删除用户\t\t*\n");
    printf("\t\t\t*  4\t初始化用户密码\t\t*\n");
    printf("\t\t\t*  5\t修改登录密码\t\t*\n");
    printf("\t\t\t*  6\t系统备份\t\t*\n");
    printf("\t\t\t*  0\t注销\t\t\t*\n");
    printf("\t\t\t=================================\n");
    printf("\t\t\t请输入选项[ ]\b\b");
    scanf("%d",&c);
    return c;
}

/*
    @函数名称：menuBankers    入口参数：无
    @函数功能：显示用户菜单，返回用户选择
*/
int menuBankers()
{
    int c;
    gotox(6);
    printf("\t\t\t  小型银行管理系统——用户\n");
    printf("\t\t\t=================================\n");
    printf("\t\t\t*  1\t转账\t\t\t*\n");
    printf("\t\t\t*  2\t存款\t\t\t*\n");
    printf("\t\t\t*  3\t取款\t\t\t*\n");
    printf("\t\t\t*  4\t查询余额\t\t*\n");
    printf("\t\t\t*  5\t办理理财产品\t\t*\n");
    printf("\t\t\t*  6\t办理便民服务\t\t*\n");
    printf("\t\t\t*  7\t修改个人信息\t\t*\n");
    printf("\t\t\t*  8\t修改登录密码\t\t*\n");
    printf("\t\t\t*  0\t注消\t\t\t*\n");
    printf("\t\t\t=================================\n");
    printf("\t\t\t请输入选项[ ]\b\b");
    scanf("%d",&c);
    return c;
}
/*
    @函数名称：displayTopic      入口参数：char *s
    @函数功能：显示子模块名称
*/
void displayTopic(char *s)
{
    int i;
    gotox(6);           //到第6行
    printf("%s\n",s);
    for (i=0;i<80;i++)
            printf("-");
    printf("\n");
}
/*
    @函数名称：showtime()        入口参数：int k
    @函数功能：显示时间与欢迎界面
*/
void showtime(int k)
{
    time_t nowtime;
    struct tm *t;
    time(&nowtime);

    t=localtime(&nowtime);
    if (t->tm_hour>=5 && t->tm_hour<9)
        printf("早上好！\n  ");
    else
           if (t->tm_hour>=9 && t->tm_hour<12)
                  printf("上午好！\n  ");
           else
                   if (t->tm_hour>12 && t->tm_hour<18)
                        printf("下午好！\n    ");
                   else
                        printf("晚上好！\n    ");

    switch(k)
    {
        case 0: printf("  欢迎使用银行管理系统！");        //进入系统时调用showtime(0);
            break;
        case 1: printf("\t谢谢使用银行管理系统！\n");      //退出系统时调用showtime(0);
                printf("\t当前时间: %s",  ctime(&nowtime));
            break;
    }
}
