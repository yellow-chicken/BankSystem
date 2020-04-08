#include "banksystem.h"

int mainMenu();//登录菜单
int menuAdmin();//系统管理员角色子程序菜单
int menuManager();//柜台人员角色子程序菜单
int menuBankers();//用户角色子程序菜单

void AdminSystem(char currentUserId[]);//系统管理员角色子程序
void ManagerSystem(char currentUserId[]);//柜台人员角色子程序
void BankersSystem(char currentUserId[]);//用户角色子程序

char *getRole(int code);                                //根据代码获取用户角色
int login(char currentUserId[]);
void enterSystem(int c,char currentUserId[]);
void encryption(char password[]) ;    //加密
void decryption(char password[]) ;    //解密

void inputUser(user userArray[],int *n);                        //手工用户信息
void printUser(user userArray[],int userTotal);                 //将用户信息显示在屏幕上
int readUserFromFile(user userArray[],char *f);                 //从文件读入用户信息

void writeUserToFile(user userArray[],int n,char *f);           //将用户信息存入文件
void AdmindeleteUser(user userArray[],int *n);                       //系统管理员删除用户信息
int userSearch(user userArray[], int userTotal, char id[]);     //查找用户信息

void workersdeleteUser(user userArray[],int *n);                 //柜台人员删除用户信息
void searchBalance(user userArray[],int *n);                    //查询余额
void workersReturnMoney(user userArray[], int *n);       //柜台人员存款
void workersNeedMoney(user userArray[], int *n);       //柜台人员取款
void workersDoFinanceProduct(user userArray[],int userTotal);    //柜台人员办理理财产品

void userDoFinanceProduct(user userArray[],int userTotal,char userId[]);   //用户办理理财产品
void yu_ebao(user userArray[],int userTotal,int pos);            //理财产品：余额宝
void lingqianton(user userArray[],int userTotal,int pos);         //理财产品：零钱通
void jijin(user userArray[],int userTotal,int pos);               //理财产品：基金
void modifyUserInfo(user userArray[],int userTotal,char userId[]);         //修改用户个人信息
void deposit(user userArray[],int userTotal,char userId[]);         //用户存款
void withdrawal(user userArray[],int userTotal,char userId[]);      //用户取款
void userSearchbalance(user userArray[],int userTotal,char userId[]); //用户查询余额
void userTransfer(user userArray[],int userTotal,char userId[]);   //用户转账
void userDoService(user userArray[],int userTotal,char userId[]);               //用户办理便民服务
void userPayeBill(user userArray[],int userTotal,char userId[]);            //交电费
void userPaywBill(user userArray[],int userTotal,char userId[]);            //交水费
void userPaynBill(user userArray[],int userTotal,char userId[]);            //交话费

void inputPassWord(char password[],int n);                      //以不回显方式输入用户密码
void getVerificationCode(char verificationCode[],int n);        //产生n位随机码
void modifyPassWord(user userArray[],int userTatal, char userId[]);//修改密码
void initPassWord(user userArray[],int userTotal);              //初始化用户密码
void backupUser(user userArray[],int userTotal);                //备份用户数据

int main()
{
    int c,loop=1;
    char currentUserId[LENGTH_OF_USERID+1];
    char transfUserId[LENGTH_OF_USERID+1];
    while (loop==1)
    {
        system("cls");  //清除屏幕

        c=mainMenu();   //显示登录菜单
        switch(c)
        {
            case    1:  //登录系统
                        c=login(currentUserId);      //调用身份验证函数，返回用户角色
                        enterSystem(c,currentUserId); //显示不同角色对应的菜单
                        break;
            default:    //退出系统
                        loop=0;
                        break;
        }
        showtime(1);
    }
    return 0;
}

/*
    @函数名称：getVerificationCode   入口参数:char verificationCode[],int n
    @函数功能：产生n位验证码
*/
void getVerificationCode(char verificationCode[],int n)
{
    char str[]="2323456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    //0,1易与字母‘o’与‘l'混消，不用
    int i;
    srand(time(NULL));
    for (i=0;i<n;i++)
        verificationCode[i]=str[rand()%62];
    verificationCode[n]='\0';
}

/*
    @函数名称：inputPassWord         入口参数：char password[],int n
    @函数功能：输入最大长度为n的密码
*/
void inputPassWord(char password[],int n)
{
    int i;
    char c;
    i=0;
    while (i<n)
    {
        c=getch();
        if (c=='\r') break;         //回车键
        if (c==8 && i>0 )           //退格键
            {   printf("\b \b");
                i--;
            }
         else
            {   password[i++]=c;    //有效密码字符
                printf("*");        //回显*号
            }
    }
    printf("\n");
    password[i]='\0';
}

/*
    @函数名称：login     入口参数：无
    @函数功能：用户身份验证信息，返回用户角色
*/

int login(char currentUserId[])
{
user userArray[MAX_USER];                   //用户数组
    int userTotal;                              //用户总数
    int counter=3;
    char verificationCode[5];                   //存放验证码
    char inputVerificationCode[5];              //存入用户输入的验证码
    char originalPassWord[LENGTH_OF_PASS+1];
    char password[LENGTH_OF_PASS+1];
    int pos;

    userTotal=readUserFromFile(userArray,"user.dat");   //从文件中读入用户信息
    while (counter>0)
    {   system("cls");
        counter--;
        displayTopic("小型银行管理系统-->用户登录");
        printf("用户名：[           ]\b\b\b\b\b\b\b\b\b\b\b\b");
        scanf("%s",currentUserId);
        printf("密  码：[           ]\b\b\b\b\b\b\b\b\b\b\b\b");
        inputPassWord(password,7);
        getVerificationCode(verificationCode,4);
        printf("验证码：[           ] %s\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b",verificationCode);
        scanf("%s",inputVerificationCode);

        pos=userSearch(userArray,userTotal,currentUserId);
        if (pos==-1)
            {   printf("该用户不存在！还有%d次登录机会。\n",counter);
                getch();
                continue;
            }
        else
        {   strcpy(originalPassWord,userArray[pos].password);
            decryption(originalPassWord);        //解密原始密码
            if (strcmp(originalPassWord,password)!=0)
                {   printf("输入的密码有误，还有%d次登录机会。\n",counter);
                    getch();
                    continue;
                }
            else
                if ( strcasecmp(verificationCode,inputVerificationCode)!=0)
                {   printf("输入的验证码有误，还有%d次登录机会。\n",counter);
                    getch();
                    continue;
                }
            else
                return userArray[pos].role;     //返回用户角色
        }
    }
    return -1;       //登录失败
}

/*
    @函数名称：enterSystem     入口参数：int c,char currentUserId[]
    @函数功能：根据用户的角色调用不同的箮理子系统
*/
void enterSystem(int c,char currentUserId[])
{
    switch(c)
    {
        case 0://c==0 表示系统管理人员
            AdminSystem(currentUserId);
            break;
        case 1://c==1 表示柜台人员
            ManagerSystem(currentUserId);
            break;
        case 2:////c==2 表示用户
            BankersSystem(currentUserId);
            break;
        default:
            break;
    }
}

/*
    @函数名称：AdminSystem     入口参数：无
    @函数功能：系统管理员子程序
*/
void AdminSystem(char currentUserId[])
{
    int pos,c,loop=1;
    user userArray[MAX_USER];   //用户数组
    int userTotal;              //用户总数
    userTotal=readUserFromFile(userArray,"user.dat");               //从文件中读入用户信息
    pos=userSearch(userArray,userTotal,currentUserId);  //从文件中读入借书信息
    while (loop==1)
    {
        system("cls");
        printf("%s:",userArray[pos].name);  //显示当前有户姓名
        showtime(0);                        //显示欢迎界面
        c=menuAdmin();  //显示系统管理员角色菜单
        switch(c)
        {
            case    1:  //浏览用户
                        printUser(userArray,userTotal);
                        system("pause");
                        break;
            case    2:  //添加用户
                        inputUser(userArray,&userTotal);
                        writeUserToFile(userArray,userTotal,"user.dat");    //存盘
                        break;
            case    3:  //删除用户
                        AdmindeleteUser(userArray,&userTotal);
                        writeUserToFile(userArray,userTotal,"user.dat");
                        printUser(userArray,userTotal);
                        break;
            case    4:  //初始化用户密码
                        printUser(userArray,userTotal);
                        initPassWord(userArray,userTotal);
                        break;
            case    5:  //修改登录密码
                        modifyPassWord(userArray,userTotal,currentUserId);
                        system("pause");
                        break;
            case    6:  //系统备份
                        system("cls");
                        displayTopic("小型银行管理系统——系统备份");
                        backupUser(userArray,userTotal);
                        system("pause");
                        break;
            default:    //注销登录
                        loop=0;
                        break;
        }
    }
    return;
}

/*
    @函数名称：ManagerSystem     入口参数：无
    @函数功能：柜台人员子程序
*/
void ManagerSystem(char currentUserId[])
{
    int pos,c,loop=1;
    user userArray[MAX_USER];   //用户数组
    int userTotal;              //用户总数
    userTotal=readUserFromFile(userArray,"user.dat");               //从文件中读入用户信息
    pos=userSearch(userArray,userTotal,currentUserId);  //从文件中读入借书信息
    while (loop==1)
    {
        system("cls");
        printf("%s:",userArray[pos].name);  //显示当前有户姓名
        showtime(0);                        //显示欢迎界面
        c=menuManager();     //显示用户角色子程序菜单
        switch(c)
        {
            case    1:  //浏览用户
                        printUser(userArray,userTotal);
                        system("pause");
                        break;
            case    2:  //添加用户
                        inputUser(userArray,&userTotal);
                        writeUserToFile(userArray,userTotal,"user.dat");    //存盘
                        break;
            case    3:  //删除用户
                        workersdeleteUser(userArray,&userTotal);
                        writeUserToFile(userArray,userTotal,"user.dat");
                        printUser(userArray,userTotal);
                        break;
            case    4:  //查询用户余额
                        searchBalance(userArray,&userTotal);
                        writeUserToFile(userArray,userTotal,"user.dat");    //存盘
                        break;
            case    5:  //存款
                        workersReturnMoney(userArray,&userTotal);
                        writeUserToFile(userArray,userTotal,"user.dat");    //存盘
                        break;
            case    6:  //取款
                        workersNeedMoney(userArray,&userTotal);
                        writeUserToFile(userArray,userTotal,"user.dat");    //存盘
                        break;
            case    7:  //办理理财产品
                        workersDoFinanceProduct(userArray,userTotal);
                        writeUserToFile(userArray,userTotal,"user.dat");    //存盘
                        break;
            case    8:  //初始化用户密码
                        printUser(userArray,userTotal);
                        initPassWord(userArray,userTotal);
                        break;
            case    9:  //修改登录密码
                        modifyPassWord(userArray,userTotal,currentUserId);
                        system("pause");
                        break;
            default:    //注销
                        loop=0;
                        break;
        }
    }
    return;
}

/*
    @函数名称：BankersSystem     入口参数：无
    @函数功能：用户子程序
*/
void BankersSystem(char currentUserId[])
{
    int pos,c,loop=1;
    user userArray[MAX_USER];   //用户数组
    int userTotal;              //用户总数
    userTotal=readUserFromFile(userArray,"user.dat");               //从文件中读入用户信息
    pos=userSearch(userArray,userTotal,currentUserId);  //从文件中读入借书信息
    while (loop==1)
    {
        system("cls");
        printf("%s:",userArray[pos].name);  //显示当前有户姓名
        showtime(0);                        //显示欢迎界面
        c=menuBankers();     //显示用户角色子程序菜单
        switch(c)
        {
            case    1:  //转账
                        system("cls");
                        userTransfer(userArray,userTotal,currentUserId);   //转账
                        writeUserToFile(userArray,userTotal,"user.dat");    //存盘
                        break;
            case    2:  //存款
                        system("cls");
                        deposit(userArray,userTotal,currentUserId);
                        writeUserToFile(userArray,userTotal,"user.dat");    //存盘
                        break;
            case    3:  //取款
                        system("cls");
                        withdrawal(userArray,userTotal,currentUserId);
                        writeUserToFile(userArray,userTotal,"user.dat");    //存盘
                        break;
            case    4:  //查询余额
                        system("cls");
                        userSearchbalance(userArray,userTotal,currentUserId);
                        writeUserToFile(userArray,userTotal,"user.dat");    //存盘
                        break;
            case    5:  //办理理财产品
                        userDoFinanceProduct(userArray,userTotal,currentUserId);
                        writeUserToFile(userArray,userTotal,"user.dat");    //存盘
                        break;
            case    6:  //办理便民服务
                        userDoService(userArray,userTotal,currentUserId);
                        writeUserToFile(userArray,userTotal,"user.dat");    //存盘
                        break;
            case    7:  //修改个人信息
                        system("cls");
                        modifyUserInfo(userArray,userTotal,currentUserId);
                        break;
            case    8:  //修改密码
                        modifyPassWord(userArray,userTotal,currentUserId);
                        system("pause");
                        break;
            default:    //注销
                        loop=0;
                        break;
        }
    }
    return;
}

/*
    @函数名称：inputUser()   入口参数：user userArray[],int *n
    @函数功能：输入用户信息
*/
void inputUser(user userArray[],int *n)
{
    int counter=0,j;
    user account;
    if (*n<MAX_USER)
        {
            while (1)
            {
                system("cls");
                displayTopic("小型银行管理系统-->添加用户");
                printf("银行账号（为q时结束）：[            ]\b\b\b\b\b\b\b\b\b\b\b\b\b");
                scanf("%s",account.userId);                                         //输入帐号
                if (account.userId[0]=='q')
                                break;
                if (userSearch(userArray,*n,account.userId)==-1)   //查找该账号是否存在
                {
                        printf("姓名\t电话号码\t角色代码\t当前余额\n");
                        for (int i=0;i<80;i++)  putchar('-');
                        printf("\n");
                        scanf("%s",account.name);                                 //输入姓名
                        scanf("%s",&account.phonenumber);                   //输入电话号码
                        scanf("%d",&account.role);                               //输入角色代码
                        scanf("%d",&account.balance);                           //输入当前余额（默认为0）
                        strcpy(account.password,"123456");                  //初始密码为"123456"
                        encryption(account.password);                           //加密
                        j=*n-1;
                        while ( j>=0 &&   strcmp(userArray[j].userId,account.userId) >0   )
                                {
                                    userArray[j+1]=userArray[j];
                                    j--;
                                }
                        userArray[j+1]=account;                                     //按用户帐号序插入到适当位置
                        (*n)++;
                        counter++;
                        printf("success...\n");
                        system("pause");
                        if (*n==MAX_USER) break;                            //容量已满
                }
                else
                    {
                            printf("该账号已存在！请重新输入！\n");
                            system("pause");
                    }
            }
            printf("成功创建%d条帐户信息!\n",counter);
            system("pause");
        }
}
/*
    @函数名称：readUserFromFile    入口参数：user userArray[],char *f
    @函数功能：从文件中读取用户信息至数组，函数返回记录总数
*/
int readUserFromFile(user userArray[],char *f)
{
    FILE *fp;
    int counter=0,k;

    fp=fopen(f,"r");
    if (fp==NULL) return 0;
    else
    {
        while (1)
        {
            k=fread(userArray+counter,sizeof(user),1,fp);
            if (k==1) counter++;
            else    break;
        }
        fclose(fp);
        return counter;
    }
}

/*
    @函数名称：printUser     入口参数：user userArray[],int userTotal
    @函数功能：将用户信息显示在屏幕上
*/
void printUser(user userArray[],int userTotal)
{   int i,j,k,page=0,totalPage;
    unsigned short ch;
    if (userTotal>0)
    {   totalPage=(userTotal-1)/10;                         //每页显示10条记录
        if (totalPage*10<userTotal-1) totalPage++;          //计算总页数
        for (i=0;i<userTotal;)
        {   system("cls");
            displayTopic("小型银行管理系统-->显示用户");
            page++;
            printf("%12s%9s%15s%11s%11s\n","银行账号","姓名","电话号码","角色","当前余额");
            for (k=0;k<80;k++)  putchar('-');
            printf("\n");

            for (j=0;j<10&&i<userTotal;j++)
            {
                if ((userArray[i].role!=0)&&(userArray[i].role!=1))      //不显示系统管理员和柜台人员帐户信息
                {
                    printf("%12s",userArray[i].userId);
                    printf("%9s",userArray[i].name);
                    printf("%15s",userArray[i].phonenumber);
                    printf("%11s",getRole(userArray[i].role));
                    printf("%11d\n",userArray[i].balance);
                }
                i++;
            }
            for (k=0;k<80;k++)  putchar('-');
            printf("\n");
            printf("第%d页，共%d页，上一页（↑）  下一页（↓），ESC键结束显示\n",page,totalPage);
            ch=getch();
            if (27==ch) return ;                        //ESC键
            if (0==ch||0xe0==ch) ch|=getch()<<8;        //非字符键
            if (0x48e0==ch)                             //向上键（↑）
            {
                    i=i-j;
                    if (i>10)
                        { i=i-10; page-=2;}
                    else
                        {i=0; page=0;}
            }
        }
    }
}


/*
    @函数名称：userSearch     入口参数：user userArray[],int userTotal
    @函数功能：在userArray[]中查找用户帐号为id[]的记录位置，查找失败返回-1
*/
int userSearch(user userArray[], int userTotal, char id[])
{
    int left=0,right=userTotal-1,mid;
    int k;
    while (left<=right)
    {
        mid=(left+right)/2;
        k=strcmp(userArray[mid].userId,id);
        if (k==0)
            return mid;
        else
            if (k<0)
                left=mid+1;
            else
                right=mid-1;
    }
    return -1;
}

/*
    @函数名称：writeUserToFile   入口参数：user userArray[],int userTotal,char *f
    @函数功能：将用户信息存入文件
*/
void writeUserToFile(user userArray[],int userTotal,char *f)
{
    FILE *fp;
    fp=fopen(f,"wb");
    if (fp!=NULL)
    {
        fwrite(userArray,sizeof(user), userTotal, fp);
        fclose(fp);
    }
    else
        printf("保存失败！");
}

/*
    @函数名称：AdmindeleteUser    入口参数：user userArray[],int *n,user currentUser[]
    @函数功能：系统管理员删除用户信息
*/
void AdmindeleteUser(user userArray[],int *n)
{
    char id[LENGTH_OF_USERID +1],ans;
    int pos,i;
    system("cls");
    printUser(userArray,*n);
    printf("请输入要删除的用户帐号：");
    scanf("%s",id);
    if (strcmp(id,"0000")!=0)
    {
        printf("真的要删除吗？(y/n)");
        scanf(" %c",&ans);
        if (ans=='y'|| ans=='Y')
            {
                pos=userSearch(userArray,*n,id);        //查找位置
                if (pos==-1)                            //查找失败
                    {   printf("无此用户！\n");
                        system("pause");
                        return ;
                    }
                else                                    //删除
                {
                        for (i=pos+1;i<*n;i++)
                            userArray[i-1]=userArray[i];
                        *n=*n-1;
                        writeUserToFile(userArray,*n,"user.dat");
                        printUser(userArray,*n);
                        system("pause");
                }
            }
            else
            {
                printUser(userArray,*n);
                system("pause");
            }
    }
    else
        {
                printf("不能删除系统管理员！\n");
                system("pause");
                return ;
        }
}

/*
    @函数名称：workersdeleteUser    入口参数：user userArray[],int *n,user currentUser[]
    @函数功能：系统管理员删除用户信息
*/
void workersdeleteUser(user userArray[],int *n)
{
    char id[LENGTH_OF_USERID +1],ans;
    int pos,i;
    system("cls");
    printUser(userArray,*n);
    printf("请输入要删除的用户帐号：");
    scanf("%s",id);
    if (strcmp(id,"0000") && strcmp(id,"1111")!=0)
    {
        printf("真的要删除吗？(y/n)");
        scanf(" %c",&ans);
        if (ans=='y'|| ans=='Y')
            {
                pos=userSearch(userArray,*n,id);        //查找位置
                if (pos==-1)                            //查找失败
                    {   printf("无此用户！\n");
                        system("pause");
                        return ;
                    }
                else                                    //删除
                {
                        for (i=pos+1;i<*n;i++)
                            userArray[i-1]=userArray[i];
                        *n=*n-1;
                        writeUserToFile(userArray,*n,"user.dat");
                        printUser(userArray,*n);
                        system("pause");
                }
            }
            else
            {
                printUser(userArray,*n);
                system("pause");
            }
    }
    else
        {
                printf("不能删除系统管理员或柜台人员！\n");
                system("pause");
                return ;
        }
}

/*

    @函数名称：searchbalance        入口参数：user userArray[],int *n
    @函数功能：柜台人员查询余额
*/
void searchBalance(user userArray[],int *n)
{
	int i;
	user account;
	if (*n<MAX_USER)
        {
            while (1)
            {
			system("cls");
            displayTopic("小型银行管理系统-->查询余额");
        tip:printf("请输入需要查询的账号：[            ]\b\b\b\b\b\b\b\b\b\b\b\b\b");
            scanf("%s",account.userId);
                if(strcmp(account.userId,"0000") && strcmp(account.userId,"1111")!=0)
                {
                    if(userSearch(userArray,*n,account.userId)!=-1)
                    {
                        for(i=0;i<*n;i++)
                        {
                            if(strcmp(userArray[i].userId,account.userId)==0)
                            {
                                printf("\n");
                                printf("当前用户余额为：%d元",userArray[i].balance);
                            }
                        }
                        printf("\n");
                        for (i=0;i<80;i++)  putchar('-');
                        printf("\n");
                        system("pause");
                        break;
                    }
                    else
                    {
                        printf("该用户不存在！请重新输入！\n");
                        goto tip;
                    }
                }
            else
            {
                printf("该用户不存在！请重新输入！\n");
                goto tip;
            }
        }
    }
}

/*
    @函数名称：workersReturnMoney      入口参数：user userArray[],int *n
    @函数功能：柜台人员存款
*/
void workersReturnMoney(user userArray[], int *n) //存款
{
    int balance1,i;
    user account;
    system("cls");
    displayTopic("小型银行管理系统-->存款");
tip:printf("请输入需要存款的账号：[            ]\b\b\b\b\b\b\b\b\b\b\b\b\b");
    scanf("%s",account.userId);
    if(strcmp(account.userId,"0000") && strcmp(account.userId,"1111")!=0)
    {
        if(userSearch(userArray,*n,account.userId)!=-1)
        {
            for(i=0;i<*n;i++)
            {
                if(strcmp(userArray[i].userId,account.userId)==0)
                {
                    printf("\n");
                    printf("当前用户余额为：%d元",userArray[i].balance);
                    printf("\n");
                    printf("输入存入的金额：[      ]元\b\b\b\b\b\b\b\b\b");
                    scanf("%d",&balance1);
                    userArray[i].balance=userArray[i].balance+balance1;
                    printf("\n恭喜你，存款成功!\n当前用户余额为：%d元",userArray[i].balance);
                }
            }
            printf("\n");
            for (i=0;i<80;i++)  putchar('-');
            printf("\n");
            system("pause");
        }
        else
        {
            printf("该用户不存在！请重新输入！\n");
            goto tip;
        }
    }
    else
    {
        printf("该用户不存在，请重新输入！\n");
        goto tip;
    }
}

/*
    @函数名称：workersNeedMoney      入口参数：user userArray[],int *n
    @函数功能：柜台人员取款
*/
void workersNeedMoney(user userArray[], int *n) //柜台人员取款
{
    int balance2,i;
    user account;
    system("cls");
    displayTopic("小型银行管理系统-->取款");
tip:printf("请输入需要取款的账号：[            ]\b\b\b\b\b\b\b\b\b\b\b\b\b");
    scanf("%s",account.userId);
    if(strcmp(account.userId,"0000") && strcmp(account.userId,"1111")!=0)
    {
        if(userSearch(userArray,*n,account.userId)!=-1)
        {
            for(i=0;i<*n;i++)
            {
                if(strcmp(userArray[i].userId,account.userId)==0)
                {
                    printf("\n");
                    printf("当前用户余额为：%d元",userArray[i].balance);
                    printf("\n");
                 op:printf("输入取出的金额：[      ]元\b\b\b\b\b\b\b\b\b");
                    scanf("%d",&balance2);
                    if(balance2>userArray[i].balance)
                    {
                        printf("余额不足，请重新输入！\n");
                        goto op;
                    }
                    else
                    {
                        userArray[i].balance=userArray[i].balance-balance2;
                        printf("\n恭喜你，取款成功!\n当前用户余额为：%d元",userArray[i].balance);
                    }
                }
            }
            printf("\n");
            for (i=0;i<80;i++)  putchar('-');
            printf("\n");
            system("pause");
        }
    else
        {
            printf("该用户不存在！请重新输入！\n");
            goto tip;
        }
    }
    else
    {
        printf("该用户不存在，请重新输入！\n");
        goto tip;
    }
}

/*
    @函数名称：workersDoFinanceProduct      入口参数：user userArray[],userTotal
    @函数功能：柜台人员办理理财产品
*/
void workersDoFinanceProduct(user userArray[],int userTotal)
{
    int i,product,pos;
    user account;
    system("cls");
    displayTopic("小型银行管理系统-->办理理财产品");
tip:printf("请输入需要办理理财产品的账号：[            ]\b\b\b\b\b\b\b\b\b\b\b\b\b");
    scanf("%s",account.userId);
    pos=userSearch(userArray,userTotal,account.userId);
    if(strcmp(account.userId,"0000") && strcmp(account.userId,"1111")!=0)
    {
        if(userSearch(userArray,userTotal,account.userId)!=-1)
        {
            for(i=0;i<userTotal;i++)
            {
                if(strcmp(userArray[i].userId,account.userId)==0)
                {
                    printf("\n");
                    printf("当前用户余额为：%d元\n",userArray[i].balance);
                    printf("输入你想办理的产品，1.余额宝   2.零钱通   3.基金\n");
                    printf("请输入选项：[   ]\b\b\b\b");
                    scanf("%d",&product);
                    switch(product)
                    {
                        case 1://办理余额宝
                                yu_ebao(userArray,userTotal,pos);
                                break;
                        case 2://办理零钱通
                                lingqianton(userArray,userTotal,pos);
                                break;
                        case 3://办理基金
                                jijin(userArray,userTotal,pos);
                                break;
                        default:break;
                    }
                }
            }
            printf("\n");
            for (i=0;i<80;i++)  putchar('-');
            printf("\n");
            system("pause");
        }
    else
        {
            printf("该账号不存在！请重新输入！\n");
            goto tip;
        }
    }
    else
    {
        printf("该用户不存在，请重新输入！\n");
        goto tip;
    }
}

/*
    @函数名称：userDoFinanceProduct      入口参数：user userArray[],int userTotal,char userId[]
    @函数功能：用户办理理财产品
*/
void userDoFinanceProduct(user userArray[],int userTotal,char userId[])
{
    int pos,i,product;
    pos=userSearch(userArray,userTotal,userId);
    system("cls");
    displayTopic("银行账户信息管理系统-->办理理财产品");
    printf("\n");
    printf("当前用户余额为：%d元\n",userArray[pos].balance);
    printf("输入你想办理的产品，1.余额宝   2.零钱通   3.基金\n");
                printf("请输入选项：[   ]\b\b\b");
                scanf("%d",&product);
                switch(product)
                {
                    case 1://办理余额宝
                            yu_ebao(userArray,userTotal,pos);
                            break;
                    case 2://办理零钱通
                            lingqianton(userArray,userTotal,pos);
                            break;
                    case 3://办理基金
                            jijin(userArray,userTotal,pos);
                            break;
                    default:break;
                }
                for (i=0;i<80;i++)  putchar('-');
                printf("\n");
                system("pause");
}


/*
    @函数名称：yu_ebao           入口参数：user userArray[],int userTotal,int pos
    @函数功能：办理理财产品余额宝
*/
void yu_ebao(user userArray[],int userTotal,int pos)
{
    int time,money,i;
    float lixi,benxihe;
tip:printf("请输入存入金额：[      ]元\b\b\b\b\b\b\b\b");
    scanf("%d",&money);
     for(i=0;i<userTotal;i++)
     {
         if(userArray[pos].balance<money)
        {
            printf("账户余额不足！请重新输入！\n");
            goto tip;
        }
        else
        {
            printf("请输入办理天数：[   ]天\b\b\b\b\b\b");
            scanf("%d",&time);
            lixi=(float)((money*0.0001)*0.65*time);
            printf("余额宝办理成功！\n");
            printf("%d天后预计最终将得到利息：%.4f元\n",time,lixi);
            benxihe=(float)(userArray[pos].balance+lixi);
            printf("本息和为：%.4f元\n",benxihe);
            printf("\n");
            break;
        }
     }
}

/*
    @函数名称：lingqianton       入口参数：user userArray[],int userTotal,int pos
    @函数功能：办理理财产品零钱通
*/
void lingqianton(user userArray[],int userTotal,int pos)
{
    int time,money,i;
    float lixi,benxihe;
tip:printf("请输入存入金额：[      ]元\b\b\b\b\b\b\b\b");
    scanf("%d",&money);
    for(i=0;i<userTotal;i++)
    {
        if(userArray[pos].balance<money)
        {
            printf("账户余额不足！请重新输入！\n");
            goto tip;
        }
        else
        {
            printf("请输入办理天数：[   ]天\b\b\b\b\b\b");
            scanf("%d",&time);
            lixi=(float)((money*0.0001)*0.67*time);
            printf("零钱通办理成功！\n");
            printf("%d天后预计最终将得到利息：%.4f元\n",time,lixi);
            benxihe=(float)(userArray[pos].balance+lixi);
            printf("本息和为：%.4f元\n",benxihe);
            break;
        }
    }
}

/*
    @函数名称：jijin         入口参数：user userArray[],int userTotal,int pos
    @函数功能：办理理财产品基金
*/
void jijin(user userArray[],int userTotal,int pos)
{
    int time,money,i;
    float lixi,benxihe;
tip:printf("请输入存入金额：[      ]元\b\b\b\b\b\b\b\b");
    scanf("%d",&money);
    for(i=0;i<userTotal;i++)
    {
        if(userArray[pos].balance<money)
        {
            printf("账户余额不足！请重新输入！\n");
            goto tip;
        }
        else
        {
            printf("请输入办理天数：[   ]天\b\b\b\b\b\b");
            scanf("%d",&time);
            lixi=(float)((money*0.0001)*0.70*time);
            printf("基金办理成功！\n");
            printf("%d天后预计最终将得到利息：%.4f元\n",time,lixi);
            benxihe=(float)(userArray[pos].balance+lixi);
            printf("本息和为：%.4f元\n",benxihe);
            break;
        }
    }
}

/*
    @函数名称：modifyUserInfo    @入口参数：user userArray[],int userTotal,char userId[]
    @函数功能：修改用户信息（phonenumber）
*/
void  modifyUserInfo(user userArray[],int userTotal,char userId[])
{
    int pos,i;
    char phonenumber[12];
    pos=userSearch(userArray,userTotal,userId);
    displayTopic("银行账户信息管理系统-->修改个人信息");
    printf("%12s%9s%15s%11s","银行账号","姓名","手机号","角色");
    printf("\n");
    for (i=0;i<80;i++)  putchar('-');
    printf("\n");
    printf("%12s",userArray[pos].userId);
    printf("%9s",userArray[pos].name);
    printf("%15s",userArray[pos].phonenumber);
    printf("%11s",getRole(userArray[pos].role));
    printf("\n");
    for (i=0;i<80;i++)  putchar('-');
    printf("\n");
    printf("若需修改手机号,请输入(直接回车不修改)");
    printf(":[               ]\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
    getchar();              //去除键盘缓冲区中的回车符
    gets(phonenumber);
    if (phonenumber[0]!='\0')
    {
        strcpy(userArray[pos].phonenumber,phonenumber);
        writeUserToFile(userArray,userTotal,"user.dat");       //存盘
    }
}

/*
    @函数名称：deposit     入口参数：user userArray[],int userTotal,char userId[]
    @函数功能：用户存款
*/
void deposit(user userArray[],int userTotal,char userId[])
{
    int pos,i,balance1;
    pos=userSearch(userArray,userTotal,userId);
    displayTopic("银行账户信息管理系统-->存款");
    printf("\n");
    printf("当前用户余额为：%d元",userArray[pos].balance);
    printf("\n");
    printf("输入存入的金额：[      ]元\b\b\b\b\b\b\b\b");
    scanf("%d",&balance1);
    userArray[pos].balance=userArray[pos].balance+balance1;
    printf("\n恭喜你，存款成功!当前用户余额为：%d元",userArray[pos].balance);
    printf("\n");
    for (i=0;i<80;i++)  putchar('-');
        printf("\n");
        system("pause");

}

/*
    @函数名称：withdrawal      入口参数：user userArray[],int userTotal,char userId[]
    @函数功能：用户取款
*/
void withdrawal(user userArray[],int userTotal,char userId[])
{
    int pos,i,balance2;
    pos=userSearch(userArray,userTotal,userId);
    displayTopic("银行账户信息管理系统-->取款");
    printf("\n");
    printf("当前用户余额为：%d元",userArray[pos].balance);
    printf("\n");
tip:printf("输入取出的金额：[      ]元\b\b\b\b\b\b\b\b");
    scanf("%d",&balance2);
    if(balance2>userArray[pos].balance)
    {
        printf("余额不足，请重新输入！\n");
        goto tip;
    }
    else
    {
        userArray[pos].balance=userArray[pos].balance-balance2;
        printf("\n恭喜你，取款成功!当前用户余额为：%d元",userArray[pos].balance);
    }
    printf("\n");
    for (i=0;i<80;i++)  putchar('-');
        printf("\n");
        system("pause");

}

/*
    @函数名称：userSearchbalance      入口参数：user userArray[],int userTotal,char userId[]
    @函数功能：用户查询余额
*/
void userSearchbalance(user userArray[],int userTotal,char userId[])
{
    int pos,i,balance1;
    pos=userSearch(userArray,userTotal,userId);
    displayTopic("银行账户信息管理系统-->查询余额");
    printf("\n");
    printf("当前用户余额为：%d元",userArray[pos].balance);
    printf("\n");
    for (i=0;i<80;i++)  putchar('-');
    printf("\n");
    system("pause");
}

/*
    @函数名称：userTransfer    入口参数：user userArray[],int userTotal,char userId[],char transfUserId[]
    @函数功能：用户转账
*/
void userTransfer(user userArray[],int userTotal,char userId[])
{
    int pos1,pos2,i,balance;
    user account;
    pos1=userSearch(userArray,userTotal,userId);

    displayTopic("银行账户信息管理系统-->转账");
    printf("\n");
    printf("当前用户余额为：%d元",userArray[pos1].balance);
    printf("\n");

tip:printf("请输入需要转账的账号：[            ]\b\b\b\b\b\b\b\b\b\b\b\b\b");
    scanf("%s",account.userId);
    pos2=userSearch(userArray,userTotal,account.userId);
    if(strcmp(userId,account.userId)==0)
    {
        printf("不能给自己转账，请重新输入！\n");
        goto tip;
    }
    if(strcmp(account.userId,"0000") && strcmp(account.userId,"1111")!=0)
    {
        if(userSearch(userArray,userTotal,account.userId)!=-1)
        {
            printf("\n");
         op:printf("输入转账的金额：[     ]元\b\b\b\b\b\b\b");
            scanf("%d",&balance);
            if(balance>userArray[pos1].balance)
            {
                printf("余额不足，请重新输入！\n");
                goto op;
            }
            else
            {
                userArray[pos2].balance=userArray[pos2].balance+balance;
                userArray[pos1].balance=userArray[pos1].balance-balance;
                printf("\n恭喜你，转账成功!当前用户余额为：%d元",userArray[pos1].balance);
                printf("\n");
                for (i=0;i<80;i++)  putchar('-');
                printf("\n");
                system("pause");
            }
        }
        else
        {
            printf("该账号不存在！请重新输入！\n");
            goto tip;
        }
    }
    else
    {
        printf("该账号不存在！请重新输入！\n");
        goto tip;
    }
}

/*
    @函数名称：userDoService    入口参数：user userArray[],int userTotal,char userId[]
    @函数功能：办理便民服务
*/
void userDoService(user userArray[],int userTotal,char userId[])
{
    int pos,i,product;
    pos=userSearch(userArray,userTotal,userId);
    system("cls");
    displayTopic("银行账户信息管理系统-->办理便民服务");
    printf("\n");
    printf("当前用户余额为：%d元",userArray[pos].balance);
    printf("\n");
    printf("请选择要办理的便民服务：1.交电费   2.交水费   3.交话费");
    printf("\n");
    printf("请输入选项：[   ]\b\b\b");
    scanf("%d",&product);
    switch(product)
    {
        case 1://交电费
                userPayeBill(userArray,userTotal,userId);
                break;
        case 2://交水费
                userPaywBill(userArray,userTotal,userId);
                break;
        case 3://交话费
                userPaynBill(userArray,userTotal,userId);
                break;
        default:break;
    }
}

/*
    @函数名称：    入口参数：user userArray[],int userTotal,char userId[]
    @函数功能：交电费
*/
void userPayeBill(user userArray[],int userTotal,char userId[])
{
    int pos,i,balance;
    pos=userSearch(userArray,userTotal,userId);
    printf("请输入缴纳金额：[      ]元\b\b\b\b\b\b\b\b\b");
    scanf("%d",&balance);
    if(balance>userArray[pos].balance)
    {
        printf("账户余额不足，请退出！");
        printf("\n");
        for (i=0;i<80;i++)  putchar('-');
        printf("\n");
        system("pause");
    }
    else
    {
        userArray[pos].balance=userArray[pos].balance-balance;
        printf("\n用户%s缴纳电费%d元成功！\n",userArray[pos].phonenumber,balance);
        printf("当前用户余额为：%d元",userArray[pos].balance);
        printf("\n");
        for (i=0;i<80;i++)  putchar('-');
        printf("\n");
        system("pause");
    }
}


/*
    @函数名称：    入口参数：user userArray[],int userTotal,char userId[]
    @函数功能：交水费
*/
void userPaywBill(user userArray[],int userTotal,char userId[])
{
    int pos,i,balance;
    pos=userSearch(userArray,userTotal,userId);
    printf("请输入缴纳金额：[      ]元\b\b\b\b\b\b\b\b\b");
    scanf("%d",&balance);
    if(balance>userArray[pos].balance)
    {
        printf("账户余额不足，请退出！");
        printf("\n");
        for (i=0;i<80;i++)  putchar('-');
        printf("\n");
        system("pause");
    }
    else
    {
        userArray[pos].balance=userArray[pos].balance-balance;
        printf("\n用户%s缴纳水费%d元成功！\n",userArray[pos].phonenumber,balance);
        printf("当前用户余额为：%d元",userArray[pos].balance);
        printf("\n");
        for (i=0;i<80;i++)  putchar('-');
        printf("\n");
        system("pause");
    }
}


/*
    @函数名称：    入口参数：user userArray[],int userTotal,char userId[]
    @函数功能：交话费
*/
void userPaynBill(user userArray[],int userTotal,char userId[])
{
    int pos,i,balance;
    char phonenum[12];
    pos=userSearch(userArray,userTotal,userId);
    printf("请输入手机号码：[            ]\b\b\b\b\b\b\b\b\b\b\b\b\b");
    scanf("%s",&phonenum);
    printf("请输入缴纳金额：[      ]元\b\b\b\b\b\b\b\b\b");
    scanf("%d",&balance);
    if(balance>userArray[pos].balance)
    {
        printf("账户余额不足，请退出！");
        printf("\n");
        for (i=0;i<80;i++)  putchar('-');
        printf("\n");
        system("pause");
    }
    else
    {
        userArray[pos].balance=userArray[pos].balance-balance;
        printf("\n%s缴纳话费%d元成功！\n",phonenum,balance);
        printf("当前用户余额为：%d元",userArray[pos].balance);
        printf("\n");
        for (i=0;i<80;i++)  putchar('-');
        printf("\n");
        system("pause");
    }
}

/*
    @函数名称：modifyPassWord    入口参数：user userArray[],int userTatal, char userId[]
    @函数功能：修改个人密码
*/
void modifyPassWord(user userArray[],int userTotal, char userId[])//修改密码
{
    int pos;
    char originalPassWord[LENGTH_OF_PASS+1];
    char password1[LENGTH_OF_PASS+1];
    char password2[LENGTH_OF_PASS+1];
    char password3[LENGTH_OF_PASS+1];
    pos=userSearch(userArray,userTotal,userId);
    strcpy(originalPassWord,userArray[pos].password);
    decryption(originalPassWord);
    system("cls");
    displayTopic("小型图书管理系统-->修改密码");
    printf("原始密码：[           ]\b\b\b\b\b\b\b\b\b\b\b\b");
    inputPassWord(password1,7);
    printf("新设密码：[           ]\b\b\b\b\b\b\b\b\b\b\b\b");
    inputPassWord(password2,7);
    printf("再输一遍：[           ]\b\b\b\b\b\b\b\b\b\b\b\b");
    inputPassWord(password3,7);
    if (strcmp(originalPassWord,password1)!=0)
        printf("原始密码有误！修改失败。\n");
    else
        if (strcmp(password2,password3)!=0)
            printf("两次输入的密码不一致！修改失败。\n");
        else  //成功
        {
            encryption(password2);
            strcpy(userArray[pos].password,password2);
            writeUserToFile(userArray,userTotal,"user.dat");
            printf("密码修改成功！\n");
        }
}
/*
    @函数名称：initPassWord  入口参数：user userArray[],int userTotal
    @函数功能：初始化用户密码
*/
void initPassWord(user userArray[],int userTotal)
{
    char ans,userId[LENGTH_OF_USERID +1];
    int pos;
    printf("请输入用户帐号：[           ]\b\b\b\b\b\b\b\b\b\b\b\b");
    scanf("%s",userId);
    pos=userSearch(userArray,userTotal,userId);
    if (pos==-1)
    {   printf("用户不存在！\n");
        system("pause");
        return ;
    }
    else
    {
        printf("%s,您好！\n",userArray[pos].name);
        printf("确认初始化(y/n):[   ]\b\b\b");
        scanf(" %c",&ans);
        if (ans=='Y' || ans=='y')
            {
                strcpy(userArray[pos].password,"123456");
                encryption(userArray[pos].password);
                writeUserToFile(userArray,userTotal,"user.dat");
                printf("%s: 您的密码已初始为123456，请及时修改密码!\n\n",userArray[pos].name);
                system("pause");
            }
        else
            return ;
    }
}
/*
    @函数名称：backupUser        入口参数：user userArray[],int userTotal
    @函数功能：备份用户信息
*/
void backupUser(user userArray[],int userTotal)
{
    char filename[30]="user_";
    time_t t;
    time(&t);
    strcat(filename,ctime(&t));
    strcpy(filename+strlen(filename)-15,".dat");
    printf("用户数据备份至:%s\n",filename);
    writeUserToFile(userArray,userTotal,filename);
}

/*
    @函数名称：encryption        函数功能：对密码进行加密
*/
void encryption(char password[])                   //加密
{
    int i=0;
    while (password[i]!='\0')                     //password加密
    {
        password[i]=password[i]^0xba;
        i++;
    }
}

/*
    @函数名称：decryption        函数功能：对密码进行解密
*/
void decryption(char password[])               //加密
{
    int i=0;
    while (password[i]!='\0')                  //password加密
    {
        password[i]=password[i]^0xba;
        i++;
    }
}

/*
    @函数名称：getRole     @函数功能：根据角色代码获取角色名称
*/
char *getRole(int code)
{
    return role[code];
}
