#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<conio.h>
#include<string.h>
#include<windows.h>

#define MAX_USER 1000  //����û���
#define LENGTH_OF_USERID  4  //�˺���󳤶�
#define LENGTH_OF_PASS  6  //������󳤶�

char *role[]={
    "ϵͳ����Ա;",  //0
    "��̨��Ա",       //1
    "�û�"            //2
};//role Ϊ��ɫ��������

struct datenode
{
    short year;
    short month;
    short day;
};
typedef struct datenode date;//���ڽṹ����

struct usernode
{
    char userId[LENGTH_OF_USERID+1];//�˺�
    char name[9];//����
    int role;//��ɫ
    char phonenumber[11];//�ֻ���
    int balance;//��ǰ���
    char password[LENGTH_OF_PASS+1];//����
};
typedef struct usernode user;//�û��ṹ������


/*
    @��������:gotox    �������ܣ�����Ļ�ĵ�x��
*/
void gotox(int x)
{
    int i;
    for (i=0;i<x-1;i++)
        putchar('\n');
}


/*
    @�������ƣ�mainMenu      ��ڲ�������
    @�������ܣ���¼�˵��������û�ѡ��
*/
int mainMenu()
{
    int c;
    gotox(6);
    printf("\t\t\t         С�����й���ϵͳ\n");
    printf("\t\t\t=================================\n");
    printf("\t\t\t*          1  ��¼ϵͳ\t\t*\n");
    printf("\t\t\t*          0  �˳�ϵͳ\t\t*\n");
    printf("\t\t\t=================================\n");
    printf("\t\t\t������ѡ��[ ]\b\b");
    scanf("%d",&c);
    return c;
}

/*
    @�������ƣ�menuManager      ��ڲ�������
    @�������ܣ���ʾ��̨��Ա�˵��������û�ѡ��
*/
int menuManager()
{
    int c;
    gotox(6);
    printf("\t\t\t  С�����й���ϵͳ������̨��Ա\n");
    printf("\t\t\t=================================\n");
    printf("\t\t\t*  1\t����û�\t\t*\n");
    printf("\t\t\t*  2\t����û�\t\t*\n");
    printf("\t\t\t*  3\tɾ���û�\t\t*\n");
    printf("\t\t\t*  4\t��ѯ���\t\t*\n");
    printf("\t\t\t*  5\t���\t\t\t*\n");
    printf("\t\t\t*  6\tȡ��\t\t\t*\n");
    printf("\t\t\t*  7\t������Ʋ�Ʒ\t\t*\n");
    printf("\t\t\t*  8\t��ʼ���û�����\t\t*\n");
    printf("\t\t\t*  9\t�޸ĵ�¼����\t\t*\n");
    printf("\t\t\t*  0\tע��\t\t\t*\n");
    printf("\t\t\t=================================\n");
    printf("\t\t\t������ѡ��[ ]\b\b");
    scanf("%d",&c);
    return c;
}


/*
    @�������ƣ�menuAdmin     ��ڲ�������
    @�������ܣ���ʾϵͳ����Ա�˵��������û�ѡ��
*/
int menuAdmin()
{
    int c;
    gotox(6);
    printf("\t\t\t   С�����й���ϵͳ����ϵͳ����\n");
    printf("\t\t\t=================================\n");
    printf("\t\t\t*  1\t����û�\t\t*\n");
    printf("\t\t\t*  2\t����û�\t\t*\n");
    printf("\t\t\t*  3\tɾ���û�\t\t*\n");
    printf("\t\t\t*  4\t��ʼ���û�����\t\t*\n");
    printf("\t\t\t*  5\t�޸ĵ�¼����\t\t*\n");
    printf("\t\t\t*  6\tϵͳ����\t\t*\n");
    printf("\t\t\t*  0\tע��\t\t\t*\n");
    printf("\t\t\t=================================\n");
    printf("\t\t\t������ѡ��[ ]\b\b");
    scanf("%d",&c);
    return c;
}

/*
    @�������ƣ�menuBankers    ��ڲ�������
    @�������ܣ���ʾ�û��˵��������û�ѡ��
*/
int menuBankers()
{
    int c;
    gotox(6);
    printf("\t\t\t  С�����й���ϵͳ�����û�\n");
    printf("\t\t\t=================================\n");
    printf("\t\t\t*  1\tת��\t\t\t*\n");
    printf("\t\t\t*  2\t���\t\t\t*\n");
    printf("\t\t\t*  3\tȡ��\t\t\t*\n");
    printf("\t\t\t*  4\t��ѯ���\t\t*\n");
    printf("\t\t\t*  5\t������Ʋ�Ʒ\t\t*\n");
    printf("\t\t\t*  6\t����������\t\t*\n");
    printf("\t\t\t*  7\t�޸ĸ�����Ϣ\t\t*\n");
    printf("\t\t\t*  8\t�޸ĵ�¼����\t\t*\n");
    printf("\t\t\t*  0\tע��\t\t\t*\n");
    printf("\t\t\t=================================\n");
    printf("\t\t\t������ѡ��[ ]\b\b");
    scanf("%d",&c);
    return c;
}
/*
    @�������ƣ�displayTopic      ��ڲ�����char *s
    @�������ܣ���ʾ��ģ������
*/
void displayTopic(char *s)
{
    int i;
    gotox(6);           //����6��
    printf("%s\n",s);
    for (i=0;i<80;i++)
            printf("-");
    printf("\n");
}
/*
    @�������ƣ�showtime()        ��ڲ�����int k
    @�������ܣ���ʾʱ���뻶ӭ����
*/
void showtime(int k)
{
    time_t nowtime;
    struct tm *t;
    time(&nowtime);

    t=localtime(&nowtime);
    if (t->tm_hour>=5 && t->tm_hour<9)
        printf("���Ϻã�\n  ");
    else
           if (t->tm_hour>=9 && t->tm_hour<12)
                  printf("����ã�\n  ");
           else
                   if (t->tm_hour>12 && t->tm_hour<18)
                        printf("����ã�\n    ");
                   else
                        printf("���Ϻã�\n    ");

    switch(k)
    {
        case 0: printf("  ��ӭʹ�����й���ϵͳ��");        //����ϵͳʱ����showtime(0);
            break;
        case 1: printf("\tллʹ�����й���ϵͳ��\n");      //�˳�ϵͳʱ����showtime(0);
                printf("\t��ǰʱ��: %s",  ctime(&nowtime));
            break;
    }
}
