#include "banksystem.h"

int mainMenu();//��¼�˵�
int menuAdmin();//ϵͳ����Ա��ɫ�ӳ���˵�
int menuManager();//��̨��Ա��ɫ�ӳ���˵�
int menuBankers();//�û���ɫ�ӳ���˵�

void AdminSystem(char currentUserId[]);//ϵͳ����Ա��ɫ�ӳ���
void ManagerSystem(char currentUserId[]);//��̨��Ա��ɫ�ӳ���
void BankersSystem(char currentUserId[]);//�û���ɫ�ӳ���

char *getRole(int code);                                //���ݴ����ȡ�û���ɫ
int login(char currentUserId[]);
void enterSystem(int c,char currentUserId[]);
void encryption(char password[]) ;    //����
void decryption(char password[]) ;    //����

void inputUser(user userArray[],int *n);                        //�ֹ��û���Ϣ
void printUser(user userArray[],int userTotal);                 //���û���Ϣ��ʾ����Ļ��
int readUserFromFile(user userArray[],char *f);                 //���ļ������û���Ϣ

void writeUserToFile(user userArray[],int n,char *f);           //���û���Ϣ�����ļ�
void AdmindeleteUser(user userArray[],int *n);                       //ϵͳ����Աɾ���û���Ϣ
int userSearch(user userArray[], int userTotal, char id[]);     //�����û���Ϣ

void workersdeleteUser(user userArray[],int *n);                 //��̨��Աɾ���û���Ϣ
void searchBalance(user userArray[],int *n);                    //��ѯ���
void workersReturnMoney(user userArray[], int *n);       //��̨��Ա���
void workersNeedMoney(user userArray[], int *n);       //��̨��Աȡ��
void workersDoFinanceProduct(user userArray[],int userTotal);    //��̨��Ա������Ʋ�Ʒ

void userDoFinanceProduct(user userArray[],int userTotal,char userId[]);   //�û�������Ʋ�Ʒ
void yu_ebao(user userArray[],int userTotal,int pos);            //��Ʋ�Ʒ����
void lingqianton(user userArray[],int userTotal,int pos);         //��Ʋ�Ʒ����Ǯͨ
void jijin(user userArray[],int userTotal,int pos);               //��Ʋ�Ʒ������
void modifyUserInfo(user userArray[],int userTotal,char userId[]);         //�޸��û�������Ϣ
void deposit(user userArray[],int userTotal,char userId[]);         //�û����
void withdrawal(user userArray[],int userTotal,char userId[]);      //�û�ȡ��
void userSearchbalance(user userArray[],int userTotal,char userId[]); //�û���ѯ���
void userTransfer(user userArray[],int userTotal,char userId[]);   //�û�ת��
void userDoService(user userArray[],int userTotal,char userId[]);               //�û�����������
void userPayeBill(user userArray[],int userTotal,char userId[]);            //�����
void userPaywBill(user userArray[],int userTotal,char userId[]);            //��ˮ��
void userPaynBill(user userArray[],int userTotal,char userId[]);            //������

void inputPassWord(char password[],int n);                      //�Բ����Է�ʽ�����û�����
void getVerificationCode(char verificationCode[],int n);        //����nλ�����
void modifyPassWord(user userArray[],int userTatal, char userId[]);//�޸�����
void initPassWord(user userArray[],int userTotal);              //��ʼ���û�����
void backupUser(user userArray[],int userTotal);                //�����û�����

int main()
{
    int c,loop=1;
    char currentUserId[LENGTH_OF_USERID+1];
    char transfUserId[LENGTH_OF_USERID+1];
    while (loop==1)
    {
        system("cls");  //�����Ļ

        c=mainMenu();   //��ʾ��¼�˵�
        switch(c)
        {
            case    1:  //��¼ϵͳ
                        c=login(currentUserId);      //���������֤�����������û���ɫ
                        enterSystem(c,currentUserId); //��ʾ��ͬ��ɫ��Ӧ�Ĳ˵�
                        break;
            default:    //�˳�ϵͳ
                        loop=0;
                        break;
        }
        showtime(1);
    }
    return 0;
}

/*
    @�������ƣ�getVerificationCode   ��ڲ���:char verificationCode[],int n
    @�������ܣ�����nλ��֤��
*/
void getVerificationCode(char verificationCode[],int n)
{
    char str[]="2323456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    //0,1������ĸ��o���롮l'����������
    int i;
    srand(time(NULL));
    for (i=0;i<n;i++)
        verificationCode[i]=str[rand()%62];
    verificationCode[n]='\0';
}

/*
    @�������ƣ�inputPassWord         ��ڲ�����char password[],int n
    @�������ܣ�������󳤶�Ϊn������
*/
void inputPassWord(char password[],int n)
{
    int i;
    char c;
    i=0;
    while (i<n)
    {
        c=getch();
        if (c=='\r') break;         //�س���
        if (c==8 && i>0 )           //�˸��
            {   printf("\b \b");
                i--;
            }
         else
            {   password[i++]=c;    //��Ч�����ַ�
                printf("*");        //����*��
            }
    }
    printf("\n");
    password[i]='\0';
}

/*
    @�������ƣ�login     ��ڲ�������
    @�������ܣ��û������֤��Ϣ�������û���ɫ
*/

int login(char currentUserId[])
{
user userArray[MAX_USER];                   //�û�����
    int userTotal;                              //�û�����
    int counter=3;
    char verificationCode[5];                   //�����֤��
    char inputVerificationCode[5];              //�����û��������֤��
    char originalPassWord[LENGTH_OF_PASS+1];
    char password[LENGTH_OF_PASS+1];
    int pos;

    userTotal=readUserFromFile(userArray,"user.dat");   //���ļ��ж����û���Ϣ
    while (counter>0)
    {   system("cls");
        counter--;
        displayTopic("С�����й���ϵͳ-->�û���¼");
        printf("�û�����[           ]\b\b\b\b\b\b\b\b\b\b\b\b");
        scanf("%s",currentUserId);
        printf("��  �룺[           ]\b\b\b\b\b\b\b\b\b\b\b\b");
        inputPassWord(password,7);
        getVerificationCode(verificationCode,4);
        printf("��֤�룺[           ] %s\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b",verificationCode);
        scanf("%s",inputVerificationCode);

        pos=userSearch(userArray,userTotal,currentUserId);
        if (pos==-1)
            {   printf("���û������ڣ�����%d�ε�¼���ᡣ\n",counter);
                getch();
                continue;
            }
        else
        {   strcpy(originalPassWord,userArray[pos].password);
            decryption(originalPassWord);        //����ԭʼ����
            if (strcmp(originalPassWord,password)!=0)
                {   printf("������������󣬻���%d�ε�¼���ᡣ\n",counter);
                    getch();
                    continue;
                }
            else
                if ( strcasecmp(verificationCode,inputVerificationCode)!=0)
                {   printf("�������֤�����󣬻���%d�ε�¼���ᡣ\n",counter);
                    getch();
                    continue;
                }
            else
                return userArray[pos].role;     //�����û���ɫ
        }
    }
    return -1;       //��¼ʧ��
}

/*
    @�������ƣ�enterSystem     ��ڲ�����int c,char currentUserId[]
    @�������ܣ������û��Ľ�ɫ���ò�ͬ�Ĺ�����ϵͳ
*/
void enterSystem(int c,char currentUserId[])
{
    switch(c)
    {
        case 0://c==0 ��ʾϵͳ������Ա
            AdminSystem(currentUserId);
            break;
        case 1://c==1 ��ʾ��̨��Ա
            ManagerSystem(currentUserId);
            break;
        case 2:////c==2 ��ʾ�û�
            BankersSystem(currentUserId);
            break;
        default:
            break;
    }
}

/*
    @�������ƣ�AdminSystem     ��ڲ�������
    @�������ܣ�ϵͳ����Ա�ӳ���
*/
void AdminSystem(char currentUserId[])
{
    int pos,c,loop=1;
    user userArray[MAX_USER];   //�û�����
    int userTotal;              //�û�����
    userTotal=readUserFromFile(userArray,"user.dat");               //���ļ��ж����û���Ϣ
    pos=userSearch(userArray,userTotal,currentUserId);  //���ļ��ж��������Ϣ
    while (loop==1)
    {
        system("cls");
        printf("%s:",userArray[pos].name);  //��ʾ��ǰ�л�����
        showtime(0);                        //��ʾ��ӭ����
        c=menuAdmin();  //��ʾϵͳ����Ա��ɫ�˵�
        switch(c)
        {
            case    1:  //����û�
                        printUser(userArray,userTotal);
                        system("pause");
                        break;
            case    2:  //����û�
                        inputUser(userArray,&userTotal);
                        writeUserToFile(userArray,userTotal,"user.dat");    //����
                        break;
            case    3:  //ɾ���û�
                        AdmindeleteUser(userArray,&userTotal);
                        writeUserToFile(userArray,userTotal,"user.dat");
                        printUser(userArray,userTotal);
                        break;
            case    4:  //��ʼ���û�����
                        printUser(userArray,userTotal);
                        initPassWord(userArray,userTotal);
                        break;
            case    5:  //�޸ĵ�¼����
                        modifyPassWord(userArray,userTotal,currentUserId);
                        system("pause");
                        break;
            case    6:  //ϵͳ����
                        system("cls");
                        displayTopic("С�����й���ϵͳ����ϵͳ����");
                        backupUser(userArray,userTotal);
                        system("pause");
                        break;
            default:    //ע����¼
                        loop=0;
                        break;
        }
    }
    return;
}

/*
    @�������ƣ�ManagerSystem     ��ڲ�������
    @�������ܣ���̨��Ա�ӳ���
*/
void ManagerSystem(char currentUserId[])
{
    int pos,c,loop=1;
    user userArray[MAX_USER];   //�û�����
    int userTotal;              //�û�����
    userTotal=readUserFromFile(userArray,"user.dat");               //���ļ��ж����û���Ϣ
    pos=userSearch(userArray,userTotal,currentUserId);  //���ļ��ж��������Ϣ
    while (loop==1)
    {
        system("cls");
        printf("%s:",userArray[pos].name);  //��ʾ��ǰ�л�����
        showtime(0);                        //��ʾ��ӭ����
        c=menuManager();     //��ʾ�û���ɫ�ӳ���˵�
        switch(c)
        {
            case    1:  //����û�
                        printUser(userArray,userTotal);
                        system("pause");
                        break;
            case    2:  //����û�
                        inputUser(userArray,&userTotal);
                        writeUserToFile(userArray,userTotal,"user.dat");    //����
                        break;
            case    3:  //ɾ���û�
                        workersdeleteUser(userArray,&userTotal);
                        writeUserToFile(userArray,userTotal,"user.dat");
                        printUser(userArray,userTotal);
                        break;
            case    4:  //��ѯ�û����
                        searchBalance(userArray,&userTotal);
                        writeUserToFile(userArray,userTotal,"user.dat");    //����
                        break;
            case    5:  //���
                        workersReturnMoney(userArray,&userTotal);
                        writeUserToFile(userArray,userTotal,"user.dat");    //����
                        break;
            case    6:  //ȡ��
                        workersNeedMoney(userArray,&userTotal);
                        writeUserToFile(userArray,userTotal,"user.dat");    //����
                        break;
            case    7:  //������Ʋ�Ʒ
                        workersDoFinanceProduct(userArray,userTotal);
                        writeUserToFile(userArray,userTotal,"user.dat");    //����
                        break;
            case    8:  //��ʼ���û�����
                        printUser(userArray,userTotal);
                        initPassWord(userArray,userTotal);
                        break;
            case    9:  //�޸ĵ�¼����
                        modifyPassWord(userArray,userTotal,currentUserId);
                        system("pause");
                        break;
            default:    //ע��
                        loop=0;
                        break;
        }
    }
    return;
}

/*
    @�������ƣ�BankersSystem     ��ڲ�������
    @�������ܣ��û��ӳ���
*/
void BankersSystem(char currentUserId[])
{
    int pos,c,loop=1;
    user userArray[MAX_USER];   //�û�����
    int userTotal;              //�û�����
    userTotal=readUserFromFile(userArray,"user.dat");               //���ļ��ж����û���Ϣ
    pos=userSearch(userArray,userTotal,currentUserId);  //���ļ��ж��������Ϣ
    while (loop==1)
    {
        system("cls");
        printf("%s:",userArray[pos].name);  //��ʾ��ǰ�л�����
        showtime(0);                        //��ʾ��ӭ����
        c=menuBankers();     //��ʾ�û���ɫ�ӳ���˵�
        switch(c)
        {
            case    1:  //ת��
                        system("cls");
                        userTransfer(userArray,userTotal,currentUserId);   //ת��
                        writeUserToFile(userArray,userTotal,"user.dat");    //����
                        break;
            case    2:  //���
                        system("cls");
                        deposit(userArray,userTotal,currentUserId);
                        writeUserToFile(userArray,userTotal,"user.dat");    //����
                        break;
            case    3:  //ȡ��
                        system("cls");
                        withdrawal(userArray,userTotal,currentUserId);
                        writeUserToFile(userArray,userTotal,"user.dat");    //����
                        break;
            case    4:  //��ѯ���
                        system("cls");
                        userSearchbalance(userArray,userTotal,currentUserId);
                        writeUserToFile(userArray,userTotal,"user.dat");    //����
                        break;
            case    5:  //������Ʋ�Ʒ
                        userDoFinanceProduct(userArray,userTotal,currentUserId);
                        writeUserToFile(userArray,userTotal,"user.dat");    //����
                        break;
            case    6:  //����������
                        userDoService(userArray,userTotal,currentUserId);
                        writeUserToFile(userArray,userTotal,"user.dat");    //����
                        break;
            case    7:  //�޸ĸ�����Ϣ
                        system("cls");
                        modifyUserInfo(userArray,userTotal,currentUserId);
                        break;
            case    8:  //�޸�����
                        modifyPassWord(userArray,userTotal,currentUserId);
                        system("pause");
                        break;
            default:    //ע��
                        loop=0;
                        break;
        }
    }
    return;
}

/*
    @�������ƣ�inputUser()   ��ڲ�����user userArray[],int *n
    @�������ܣ������û���Ϣ
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
                displayTopic("С�����й���ϵͳ-->����û�");
                printf("�����˺ţ�Ϊqʱ��������[            ]\b\b\b\b\b\b\b\b\b\b\b\b\b");
                scanf("%s",account.userId);                                         //�����ʺ�
                if (account.userId[0]=='q')
                                break;
                if (userSearch(userArray,*n,account.userId)==-1)   //���Ҹ��˺��Ƿ����
                {
                        printf("����\t�绰����\t��ɫ����\t��ǰ���\n");
                        for (int i=0;i<80;i++)  putchar('-');
                        printf("\n");
                        scanf("%s",account.name);                                 //��������
                        scanf("%s",&account.phonenumber);                   //����绰����
                        scanf("%d",&account.role);                               //�����ɫ����
                        scanf("%d",&account.balance);                           //���뵱ǰ��Ĭ��Ϊ0��
                        strcpy(account.password,"123456");                  //��ʼ����Ϊ"123456"
                        encryption(account.password);                           //����
                        j=*n-1;
                        while ( j>=0 &&   strcmp(userArray[j].userId,account.userId) >0   )
                                {
                                    userArray[j+1]=userArray[j];
                                    j--;
                                }
                        userArray[j+1]=account;                                     //���û��ʺ�����뵽�ʵ�λ��
                        (*n)++;
                        counter++;
                        printf("success...\n");
                        system("pause");
                        if (*n==MAX_USER) break;                            //��������
                }
                else
                    {
                            printf("���˺��Ѵ��ڣ����������룡\n");
                            system("pause");
                    }
            }
            printf("�ɹ�����%d���ʻ���Ϣ!\n",counter);
            system("pause");
        }
}
/*
    @�������ƣ�readUserFromFile    ��ڲ�����user userArray[],char *f
    @�������ܣ����ļ��ж�ȡ�û���Ϣ�����飬�������ؼ�¼����
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
    @�������ƣ�printUser     ��ڲ�����user userArray[],int userTotal
    @�������ܣ����û���Ϣ��ʾ����Ļ��
*/
void printUser(user userArray[],int userTotal)
{   int i,j,k,page=0,totalPage;
    unsigned short ch;
    if (userTotal>0)
    {   totalPage=(userTotal-1)/10;                         //ÿҳ��ʾ10����¼
        if (totalPage*10<userTotal-1) totalPage++;          //������ҳ��
        for (i=0;i<userTotal;)
        {   system("cls");
            displayTopic("С�����й���ϵͳ-->��ʾ�û�");
            page++;
            printf("%12s%9s%15s%11s%11s\n","�����˺�","����","�绰����","��ɫ","��ǰ���");
            for (k=0;k<80;k++)  putchar('-');
            printf("\n");

            for (j=0;j<10&&i<userTotal;j++)
            {
                if ((userArray[i].role!=0)&&(userArray[i].role!=1))      //����ʾϵͳ����Ա�͹�̨��Ա�ʻ���Ϣ
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
            printf("��%dҳ����%dҳ����һҳ������  ��һҳ��������ESC��������ʾ\n",page,totalPage);
            ch=getch();
            if (27==ch) return ;                        //ESC��
            if (0==ch||0xe0==ch) ch|=getch()<<8;        //���ַ���
            if (0x48e0==ch)                             //���ϼ�������
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
    @�������ƣ�userSearch     ��ڲ�����user userArray[],int userTotal
    @�������ܣ���userArray[]�в����û��ʺ�Ϊid[]�ļ�¼λ�ã�����ʧ�ܷ���-1
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
    @�������ƣ�writeUserToFile   ��ڲ�����user userArray[],int userTotal,char *f
    @�������ܣ����û���Ϣ�����ļ�
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
        printf("����ʧ�ܣ�");
}

/*
    @�������ƣ�AdmindeleteUser    ��ڲ�����user userArray[],int *n,user currentUser[]
    @�������ܣ�ϵͳ����Աɾ���û���Ϣ
*/
void AdmindeleteUser(user userArray[],int *n)
{
    char id[LENGTH_OF_USERID +1],ans;
    int pos,i;
    system("cls");
    printUser(userArray,*n);
    printf("������Ҫɾ�����û��ʺţ�");
    scanf("%s",id);
    if (strcmp(id,"0000")!=0)
    {
        printf("���Ҫɾ����(y/n)");
        scanf(" %c",&ans);
        if (ans=='y'|| ans=='Y')
            {
                pos=userSearch(userArray,*n,id);        //����λ��
                if (pos==-1)                            //����ʧ��
                    {   printf("�޴��û���\n");
                        system("pause");
                        return ;
                    }
                else                                    //ɾ��
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
                printf("����ɾ��ϵͳ����Ա��\n");
                system("pause");
                return ;
        }
}

/*
    @�������ƣ�workersdeleteUser    ��ڲ�����user userArray[],int *n,user currentUser[]
    @�������ܣ�ϵͳ����Աɾ���û���Ϣ
*/
void workersdeleteUser(user userArray[],int *n)
{
    char id[LENGTH_OF_USERID +1],ans;
    int pos,i;
    system("cls");
    printUser(userArray,*n);
    printf("������Ҫɾ�����û��ʺţ�");
    scanf("%s",id);
    if (strcmp(id,"0000") && strcmp(id,"1111")!=0)
    {
        printf("���Ҫɾ����(y/n)");
        scanf(" %c",&ans);
        if (ans=='y'|| ans=='Y')
            {
                pos=userSearch(userArray,*n,id);        //����λ��
                if (pos==-1)                            //����ʧ��
                    {   printf("�޴��û���\n");
                        system("pause");
                        return ;
                    }
                else                                    //ɾ��
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
                printf("����ɾ��ϵͳ����Ա���̨��Ա��\n");
                system("pause");
                return ;
        }
}

/*

    @�������ƣ�searchbalance        ��ڲ�����user userArray[],int *n
    @�������ܣ���̨��Ա��ѯ���
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
            displayTopic("С�����й���ϵͳ-->��ѯ���");
        tip:printf("��������Ҫ��ѯ���˺ţ�[            ]\b\b\b\b\b\b\b\b\b\b\b\b\b");
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
                                printf("��ǰ�û����Ϊ��%dԪ",userArray[i].balance);
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
                        printf("���û������ڣ����������룡\n");
                        goto tip;
                    }
                }
            else
            {
                printf("���û������ڣ����������룡\n");
                goto tip;
            }
        }
    }
}

/*
    @�������ƣ�workersReturnMoney      ��ڲ�����user userArray[],int *n
    @�������ܣ���̨��Ա���
*/
void workersReturnMoney(user userArray[], int *n) //���
{
    int balance1,i;
    user account;
    system("cls");
    displayTopic("С�����й���ϵͳ-->���");
tip:printf("��������Ҫ�����˺ţ�[            ]\b\b\b\b\b\b\b\b\b\b\b\b\b");
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
                    printf("��ǰ�û����Ϊ��%dԪ",userArray[i].balance);
                    printf("\n");
                    printf("�������Ľ�[      ]Ԫ\b\b\b\b\b\b\b\b\b");
                    scanf("%d",&balance1);
                    userArray[i].balance=userArray[i].balance+balance1;
                    printf("\n��ϲ�㣬���ɹ�!\n��ǰ�û����Ϊ��%dԪ",userArray[i].balance);
                }
            }
            printf("\n");
            for (i=0;i<80;i++)  putchar('-');
            printf("\n");
            system("pause");
        }
        else
        {
            printf("���û������ڣ����������룡\n");
            goto tip;
        }
    }
    else
    {
        printf("���û������ڣ����������룡\n");
        goto tip;
    }
}

/*
    @�������ƣ�workersNeedMoney      ��ڲ�����user userArray[],int *n
    @�������ܣ���̨��Աȡ��
*/
void workersNeedMoney(user userArray[], int *n) //��̨��Աȡ��
{
    int balance2,i;
    user account;
    system("cls");
    displayTopic("С�����й���ϵͳ-->ȡ��");
tip:printf("��������Ҫȡ����˺ţ�[            ]\b\b\b\b\b\b\b\b\b\b\b\b\b");
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
                    printf("��ǰ�û����Ϊ��%dԪ",userArray[i].balance);
                    printf("\n");
                 op:printf("����ȡ���Ľ�[      ]Ԫ\b\b\b\b\b\b\b\b\b");
                    scanf("%d",&balance2);
                    if(balance2>userArray[i].balance)
                    {
                        printf("���㣬���������룡\n");
                        goto op;
                    }
                    else
                    {
                        userArray[i].balance=userArray[i].balance-balance2;
                        printf("\n��ϲ�㣬ȡ��ɹ�!\n��ǰ�û����Ϊ��%dԪ",userArray[i].balance);
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
            printf("���û������ڣ����������룡\n");
            goto tip;
        }
    }
    else
    {
        printf("���û������ڣ����������룡\n");
        goto tip;
    }
}

/*
    @�������ƣ�workersDoFinanceProduct      ��ڲ�����user userArray[],userTotal
    @�������ܣ���̨��Ա������Ʋ�Ʒ
*/
void workersDoFinanceProduct(user userArray[],int userTotal)
{
    int i,product,pos;
    user account;
    system("cls");
    displayTopic("С�����й���ϵͳ-->������Ʋ�Ʒ");
tip:printf("��������Ҫ������Ʋ�Ʒ���˺ţ�[            ]\b\b\b\b\b\b\b\b\b\b\b\b\b");
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
                    printf("��ǰ�û����Ϊ��%dԪ\n",userArray[i].balance);
                    printf("�����������Ĳ�Ʒ��1.��   2.��Ǯͨ   3.����\n");
                    printf("������ѡ�[   ]\b\b\b\b");
                    scanf("%d",&product);
                    switch(product)
                    {
                        case 1://������
                                yu_ebao(userArray,userTotal,pos);
                                break;
                        case 2://������Ǯͨ
                                lingqianton(userArray,userTotal,pos);
                                break;
                        case 3://�������
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
            printf("���˺Ų����ڣ����������룡\n");
            goto tip;
        }
    }
    else
    {
        printf("���û������ڣ����������룡\n");
        goto tip;
    }
}

/*
    @�������ƣ�userDoFinanceProduct      ��ڲ�����user userArray[],int userTotal,char userId[]
    @�������ܣ��û�������Ʋ�Ʒ
*/
void userDoFinanceProduct(user userArray[],int userTotal,char userId[])
{
    int pos,i,product;
    pos=userSearch(userArray,userTotal,userId);
    system("cls");
    displayTopic("�����˻���Ϣ����ϵͳ-->������Ʋ�Ʒ");
    printf("\n");
    printf("��ǰ�û����Ϊ��%dԪ\n",userArray[pos].balance);
    printf("�����������Ĳ�Ʒ��1.��   2.��Ǯͨ   3.����\n");
                printf("������ѡ�[   ]\b\b\b");
                scanf("%d",&product);
                switch(product)
                {
                    case 1://������
                            yu_ebao(userArray,userTotal,pos);
                            break;
                    case 2://������Ǯͨ
                            lingqianton(userArray,userTotal,pos);
                            break;
                    case 3://�������
                            jijin(userArray,userTotal,pos);
                            break;
                    default:break;
                }
                for (i=0;i<80;i++)  putchar('-');
                printf("\n");
                system("pause");
}


/*
    @�������ƣ�yu_ebao           ��ڲ�����user userArray[],int userTotal,int pos
    @�������ܣ�������Ʋ�Ʒ��
*/
void yu_ebao(user userArray[],int userTotal,int pos)
{
    int time,money,i;
    float lixi,benxihe;
tip:printf("����������[      ]Ԫ\b\b\b\b\b\b\b\b");
    scanf("%d",&money);
     for(i=0;i<userTotal;i++)
     {
         if(userArray[pos].balance<money)
        {
            printf("�˻����㣡���������룡\n");
            goto tip;
        }
        else
        {
            printf("���������������[   ]��\b\b\b\b\b\b");
            scanf("%d",&time);
            lixi=(float)((money*0.0001)*0.65*time);
            printf("������ɹ���\n");
            printf("%d���Ԥ�����ս��õ���Ϣ��%.4fԪ\n",time,lixi);
            benxihe=(float)(userArray[pos].balance+lixi);
            printf("��Ϣ��Ϊ��%.4fԪ\n",benxihe);
            printf("\n");
            break;
        }
     }
}

/*
    @�������ƣ�lingqianton       ��ڲ�����user userArray[],int userTotal,int pos
    @�������ܣ�������Ʋ�Ʒ��Ǯͨ
*/
void lingqianton(user userArray[],int userTotal,int pos)
{
    int time,money,i;
    float lixi,benxihe;
tip:printf("����������[      ]Ԫ\b\b\b\b\b\b\b\b");
    scanf("%d",&money);
    for(i=0;i<userTotal;i++)
    {
        if(userArray[pos].balance<money)
        {
            printf("�˻����㣡���������룡\n");
            goto tip;
        }
        else
        {
            printf("���������������[   ]��\b\b\b\b\b\b");
            scanf("%d",&time);
            lixi=(float)((money*0.0001)*0.67*time);
            printf("��Ǯͨ����ɹ���\n");
            printf("%d���Ԥ�����ս��õ���Ϣ��%.4fԪ\n",time,lixi);
            benxihe=(float)(userArray[pos].balance+lixi);
            printf("��Ϣ��Ϊ��%.4fԪ\n",benxihe);
            break;
        }
    }
}

/*
    @�������ƣ�jijin         ��ڲ�����user userArray[],int userTotal,int pos
    @�������ܣ�������Ʋ�Ʒ����
*/
void jijin(user userArray[],int userTotal,int pos)
{
    int time,money,i;
    float lixi,benxihe;
tip:printf("����������[      ]Ԫ\b\b\b\b\b\b\b\b");
    scanf("%d",&money);
    for(i=0;i<userTotal;i++)
    {
        if(userArray[pos].balance<money)
        {
            printf("�˻����㣡���������룡\n");
            goto tip;
        }
        else
        {
            printf("���������������[   ]��\b\b\b\b\b\b");
            scanf("%d",&time);
            lixi=(float)((money*0.0001)*0.70*time);
            printf("�������ɹ���\n");
            printf("%d���Ԥ�����ս��õ���Ϣ��%.4fԪ\n",time,lixi);
            benxihe=(float)(userArray[pos].balance+lixi);
            printf("��Ϣ��Ϊ��%.4fԪ\n",benxihe);
            break;
        }
    }
}

/*
    @�������ƣ�modifyUserInfo    @��ڲ�����user userArray[],int userTotal,char userId[]
    @�������ܣ��޸��û���Ϣ��phonenumber��
*/
void  modifyUserInfo(user userArray[],int userTotal,char userId[])
{
    int pos,i;
    char phonenumber[12];
    pos=userSearch(userArray,userTotal,userId);
    displayTopic("�����˻���Ϣ����ϵͳ-->�޸ĸ�����Ϣ");
    printf("%12s%9s%15s%11s","�����˺�","����","�ֻ���","��ɫ");
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
    printf("�����޸��ֻ���,������(ֱ�ӻس����޸�)");
    printf(":[               ]\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
    getchar();              //ȥ�����̻������еĻس���
    gets(phonenumber);
    if (phonenumber[0]!='\0')
    {
        strcpy(userArray[pos].phonenumber,phonenumber);
        writeUserToFile(userArray,userTotal,"user.dat");       //����
    }
}

/*
    @�������ƣ�deposit     ��ڲ�����user userArray[],int userTotal,char userId[]
    @�������ܣ��û����
*/
void deposit(user userArray[],int userTotal,char userId[])
{
    int pos,i,balance1;
    pos=userSearch(userArray,userTotal,userId);
    displayTopic("�����˻���Ϣ����ϵͳ-->���");
    printf("\n");
    printf("��ǰ�û����Ϊ��%dԪ",userArray[pos].balance);
    printf("\n");
    printf("�������Ľ�[      ]Ԫ\b\b\b\b\b\b\b\b");
    scanf("%d",&balance1);
    userArray[pos].balance=userArray[pos].balance+balance1;
    printf("\n��ϲ�㣬���ɹ�!��ǰ�û����Ϊ��%dԪ",userArray[pos].balance);
    printf("\n");
    for (i=0;i<80;i++)  putchar('-');
        printf("\n");
        system("pause");

}

/*
    @�������ƣ�withdrawal      ��ڲ�����user userArray[],int userTotal,char userId[]
    @�������ܣ��û�ȡ��
*/
void withdrawal(user userArray[],int userTotal,char userId[])
{
    int pos,i,balance2;
    pos=userSearch(userArray,userTotal,userId);
    displayTopic("�����˻���Ϣ����ϵͳ-->ȡ��");
    printf("\n");
    printf("��ǰ�û����Ϊ��%dԪ",userArray[pos].balance);
    printf("\n");
tip:printf("����ȡ���Ľ�[      ]Ԫ\b\b\b\b\b\b\b\b");
    scanf("%d",&balance2);
    if(balance2>userArray[pos].balance)
    {
        printf("���㣬���������룡\n");
        goto tip;
    }
    else
    {
        userArray[pos].balance=userArray[pos].balance-balance2;
        printf("\n��ϲ�㣬ȡ��ɹ�!��ǰ�û����Ϊ��%dԪ",userArray[pos].balance);
    }
    printf("\n");
    for (i=0;i<80;i++)  putchar('-');
        printf("\n");
        system("pause");

}

/*
    @�������ƣ�userSearchbalance      ��ڲ�����user userArray[],int userTotal,char userId[]
    @�������ܣ��û���ѯ���
*/
void userSearchbalance(user userArray[],int userTotal,char userId[])
{
    int pos,i,balance1;
    pos=userSearch(userArray,userTotal,userId);
    displayTopic("�����˻���Ϣ����ϵͳ-->��ѯ���");
    printf("\n");
    printf("��ǰ�û����Ϊ��%dԪ",userArray[pos].balance);
    printf("\n");
    for (i=0;i<80;i++)  putchar('-');
    printf("\n");
    system("pause");
}

/*
    @�������ƣ�userTransfer    ��ڲ�����user userArray[],int userTotal,char userId[],char transfUserId[]
    @�������ܣ��û�ת��
*/
void userTransfer(user userArray[],int userTotal,char userId[])
{
    int pos1,pos2,i,balance;
    user account;
    pos1=userSearch(userArray,userTotal,userId);

    displayTopic("�����˻���Ϣ����ϵͳ-->ת��");
    printf("\n");
    printf("��ǰ�û����Ϊ��%dԪ",userArray[pos1].balance);
    printf("\n");

tip:printf("��������Ҫת�˵��˺ţ�[            ]\b\b\b\b\b\b\b\b\b\b\b\b\b");
    scanf("%s",account.userId);
    pos2=userSearch(userArray,userTotal,account.userId);
    if(strcmp(userId,account.userId)==0)
    {
        printf("���ܸ��Լ�ת�ˣ����������룡\n");
        goto tip;
    }
    if(strcmp(account.userId,"0000") && strcmp(account.userId,"1111")!=0)
    {
        if(userSearch(userArray,userTotal,account.userId)!=-1)
        {
            printf("\n");
         op:printf("����ת�˵Ľ�[     ]Ԫ\b\b\b\b\b\b\b");
            scanf("%d",&balance);
            if(balance>userArray[pos1].balance)
            {
                printf("���㣬���������룡\n");
                goto op;
            }
            else
            {
                userArray[pos2].balance=userArray[pos2].balance+balance;
                userArray[pos1].balance=userArray[pos1].balance-balance;
                printf("\n��ϲ�㣬ת�˳ɹ�!��ǰ�û����Ϊ��%dԪ",userArray[pos1].balance);
                printf("\n");
                for (i=0;i<80;i++)  putchar('-');
                printf("\n");
                system("pause");
            }
        }
        else
        {
            printf("���˺Ų����ڣ����������룡\n");
            goto tip;
        }
    }
    else
    {
        printf("���˺Ų����ڣ����������룡\n");
        goto tip;
    }
}

/*
    @�������ƣ�userDoService    ��ڲ�����user userArray[],int userTotal,char userId[]
    @�������ܣ�����������
*/
void userDoService(user userArray[],int userTotal,char userId[])
{
    int pos,i,product;
    pos=userSearch(userArray,userTotal,userId);
    system("cls");
    displayTopic("�����˻���Ϣ����ϵͳ-->����������");
    printf("\n");
    printf("��ǰ�û����Ϊ��%dԪ",userArray[pos].balance);
    printf("\n");
    printf("��ѡ��Ҫ����ı������1.�����   2.��ˮ��   3.������");
    printf("\n");
    printf("������ѡ�[   ]\b\b\b");
    scanf("%d",&product);
    switch(product)
    {
        case 1://�����
                userPayeBill(userArray,userTotal,userId);
                break;
        case 2://��ˮ��
                userPaywBill(userArray,userTotal,userId);
                break;
        case 3://������
                userPaynBill(userArray,userTotal,userId);
                break;
        default:break;
    }
}

/*
    @�������ƣ�    ��ڲ�����user userArray[],int userTotal,char userId[]
    @�������ܣ������
*/
void userPayeBill(user userArray[],int userTotal,char userId[])
{
    int pos,i,balance;
    pos=userSearch(userArray,userTotal,userId);
    printf("��������ɽ�[      ]Ԫ\b\b\b\b\b\b\b\b\b");
    scanf("%d",&balance);
    if(balance>userArray[pos].balance)
    {
        printf("�˻����㣬���˳���");
        printf("\n");
        for (i=0;i<80;i++)  putchar('-');
        printf("\n");
        system("pause");
    }
    else
    {
        userArray[pos].balance=userArray[pos].balance-balance;
        printf("\n�û�%s���ɵ��%dԪ�ɹ���\n",userArray[pos].phonenumber,balance);
        printf("��ǰ�û����Ϊ��%dԪ",userArray[pos].balance);
        printf("\n");
        for (i=0;i<80;i++)  putchar('-');
        printf("\n");
        system("pause");
    }
}


/*
    @�������ƣ�    ��ڲ�����user userArray[],int userTotal,char userId[]
    @�������ܣ���ˮ��
*/
void userPaywBill(user userArray[],int userTotal,char userId[])
{
    int pos,i,balance;
    pos=userSearch(userArray,userTotal,userId);
    printf("��������ɽ�[      ]Ԫ\b\b\b\b\b\b\b\b\b");
    scanf("%d",&balance);
    if(balance>userArray[pos].balance)
    {
        printf("�˻����㣬���˳���");
        printf("\n");
        for (i=0;i<80;i++)  putchar('-');
        printf("\n");
        system("pause");
    }
    else
    {
        userArray[pos].balance=userArray[pos].balance-balance;
        printf("\n�û�%s����ˮ��%dԪ�ɹ���\n",userArray[pos].phonenumber,balance);
        printf("��ǰ�û����Ϊ��%dԪ",userArray[pos].balance);
        printf("\n");
        for (i=0;i<80;i++)  putchar('-');
        printf("\n");
        system("pause");
    }
}


/*
    @�������ƣ�    ��ڲ�����user userArray[],int userTotal,char userId[]
    @�������ܣ�������
*/
void userPaynBill(user userArray[],int userTotal,char userId[])
{
    int pos,i,balance;
    char phonenum[12];
    pos=userSearch(userArray,userTotal,userId);
    printf("�������ֻ����룺[            ]\b\b\b\b\b\b\b\b\b\b\b\b\b");
    scanf("%s",&phonenum);
    printf("��������ɽ�[      ]Ԫ\b\b\b\b\b\b\b\b\b");
    scanf("%d",&balance);
    if(balance>userArray[pos].balance)
    {
        printf("�˻����㣬���˳���");
        printf("\n");
        for (i=0;i<80;i++)  putchar('-');
        printf("\n");
        system("pause");
    }
    else
    {
        userArray[pos].balance=userArray[pos].balance-balance;
        printf("\n%s���ɻ���%dԪ�ɹ���\n",phonenum,balance);
        printf("��ǰ�û����Ϊ��%dԪ",userArray[pos].balance);
        printf("\n");
        for (i=0;i<80;i++)  putchar('-');
        printf("\n");
        system("pause");
    }
}

/*
    @�������ƣ�modifyPassWord    ��ڲ�����user userArray[],int userTatal, char userId[]
    @�������ܣ��޸ĸ�������
*/
void modifyPassWord(user userArray[],int userTotal, char userId[])//�޸�����
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
    displayTopic("С��ͼ�����ϵͳ-->�޸�����");
    printf("ԭʼ���룺[           ]\b\b\b\b\b\b\b\b\b\b\b\b");
    inputPassWord(password1,7);
    printf("�������룺[           ]\b\b\b\b\b\b\b\b\b\b\b\b");
    inputPassWord(password2,7);
    printf("����һ�飺[           ]\b\b\b\b\b\b\b\b\b\b\b\b");
    inputPassWord(password3,7);
    if (strcmp(originalPassWord,password1)!=0)
        printf("ԭʼ���������޸�ʧ�ܡ�\n");
    else
        if (strcmp(password2,password3)!=0)
            printf("������������벻һ�£��޸�ʧ�ܡ�\n");
        else  //�ɹ�
        {
            encryption(password2);
            strcpy(userArray[pos].password,password2);
            writeUserToFile(userArray,userTotal,"user.dat");
            printf("�����޸ĳɹ���\n");
        }
}
/*
    @�������ƣ�initPassWord  ��ڲ�����user userArray[],int userTotal
    @�������ܣ���ʼ���û�����
*/
void initPassWord(user userArray[],int userTotal)
{
    char ans,userId[LENGTH_OF_USERID +1];
    int pos;
    printf("�������û��ʺţ�[           ]\b\b\b\b\b\b\b\b\b\b\b\b");
    scanf("%s",userId);
    pos=userSearch(userArray,userTotal,userId);
    if (pos==-1)
    {   printf("�û������ڣ�\n");
        system("pause");
        return ;
    }
    else
    {
        printf("%s,���ã�\n",userArray[pos].name);
        printf("ȷ�ϳ�ʼ��(y/n):[   ]\b\b\b");
        scanf(" %c",&ans);
        if (ans=='Y' || ans=='y')
            {
                strcpy(userArray[pos].password,"123456");
                encryption(userArray[pos].password);
                writeUserToFile(userArray,userTotal,"user.dat");
                printf("%s: ���������ѳ�ʼΪ123456���뼰ʱ�޸�����!\n\n",userArray[pos].name);
                system("pause");
            }
        else
            return ;
    }
}
/*
    @�������ƣ�backupUser        ��ڲ�����user userArray[],int userTotal
    @�������ܣ������û���Ϣ
*/
void backupUser(user userArray[],int userTotal)
{
    char filename[30]="user_";
    time_t t;
    time(&t);
    strcat(filename,ctime(&t));
    strcpy(filename+strlen(filename)-15,".dat");
    printf("�û����ݱ�����:%s\n",filename);
    writeUserToFile(userArray,userTotal,filename);
}

/*
    @�������ƣ�encryption        �������ܣ���������м���
*/
void encryption(char password[])                   //����
{
    int i=0;
    while (password[i]!='\0')                     //password����
    {
        password[i]=password[i]^0xba;
        i++;
    }
}

/*
    @�������ƣ�decryption        �������ܣ���������н���
*/
void decryption(char password[])               //����
{
    int i=0;
    while (password[i]!='\0')                  //password����
    {
        password[i]=password[i]^0xba;
        i++;
    }
}

/*
    @�������ƣ�getRole     @�������ܣ����ݽ�ɫ�����ȡ��ɫ����
*/
char *getRole(int code)
{
    return role[code];
}
