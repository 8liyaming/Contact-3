#pragma once
//contact.h文件用于相关函数声明、符号说明、头文件的包含

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

//类型的定义
typedef struct PeoInfo  //加（typedef...PeoInfo）：后面调用时不用在前面加struct,直接PeoInfo即可
{
	char name[MAX_NAME];  //姓名
	char sex[MAX_SEX];  //性别
	int age;  //年龄
	char tele[MAX_TELE];  //电话
	char addr[MAX_ADDR];  //地址
}PeoInfo;

//通讯录
typedef struct Contact
{
	PeoInfo* data;  //指向动态申请的空间，用来存放联系人的信息
	int sz;  //记录的是当前通讯录中有效信息的个数
	int capacity;  //记录当前通讯录的最大容量
}Contact;

//初始化通讯录
void InitContact(Contact* pc);

//增加联系人
void AddContact(Contact* pc);

//打印联系人信息
void PrintContact(const Contact* pc);  //打印不用修改，加上const修饰更加安全

//删除联系人信息
void DelContact(Contact* pc);

//查找联系人信息
void SearchContact(Contact* pc);

//修改联系人信息
void ModifyContact(Contact* pc);

//排序通讯论的信息
void SortContact(Contact* pc);

//销毁通讯录
void DestoryContact(Contact* pc);

//保存通讯录信息到文件
void SaveContact(Contact* pc);

//加载文件内容到通讯录
void LoadContact(Contact* pc);

//检测增容的问题
void CheckCapacity(Contact* pc);