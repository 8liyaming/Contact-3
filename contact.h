#pragma once
//contact.h�ļ�������غ�������������˵����ͷ�ļ��İ���

#include<string.h>
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>


#define MAX_NAME 20
#define MAX_SEX 10
#define MAX_TELE 20
#define MAX_ADDR 40

#define MAX 1000

#define DEFAULT_SZ 3
#define INC_SZ 2

//���͵Ķ���
typedef struct PeoInfo  //�ӣ�typedef...PeoInfo�����������ʱ������ǰ���struct,ֱ��PeoInfo����
{
	char name[MAX_NAME];  //����
	char sex[MAX_SEX];  //�Ա�
	int age;  //����
	char tele[MAX_TELE];  //�绰
	char addr[MAX_ADDR];  //��ַ
}PeoInfo;

//ͨѶ¼
typedef struct Contact
{
	PeoInfo* data;  //ָ��̬����Ŀռ䣬���������ϵ�˵���Ϣ
	int sz;  //��¼���ǵ�ǰͨѶ¼����Ч��Ϣ�ĸ���
	int capacity;  //��¼��ǰͨѶ¼���������
}Contact;

//��ʼ��ͨѶ¼
void InitContact(Contact* pc);

//������ϵ��
void AddContact(Contact* pc);

//��ӡ��ϵ����Ϣ
void PrintContact(const Contact* pc);  //��ӡ�����޸ģ�����const���θ��Ӱ�ȫ

//ɾ����ϵ����Ϣ
void DelContact(Contact* pc);

//������ϵ����Ϣ
void SearchContact(Contact* pc);

//�޸���ϵ����Ϣ
void ModifyContact(Contact* pc);

//����ͨѶ�۵���Ϣ
void SortContact(Contact* pc);

//����ͨѶ¼
void DestoryContact(Contact* pc);

//����ͨѶ¼��Ϣ���ļ�
void SaveContact(Contact* pc);

//�����ļ����ݵ�ͨѶ¼
void LoadContact(Contact* pc);

//������ݵ�����
void CheckCapacity(Contact* pc);