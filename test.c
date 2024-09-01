#define _CRT_SECURE_NO_WARNINGS
//test.c文件用于测试逻辑

//通讯录-版本3
// **当通讯录退出的时候，把信息写到文件
// **当通讯录初始化的时候，加载文件的信息到通讯录中
// 
// *通讯录初始化后，能存放3个人的信息
// *当我们空间存放满了后，我们增加2个信息：3+2+2+2+2+2...
// 
//1.通讯录中能够存放1000个人的信息，每个人的信息：名字+年龄+性别+电话+地址；
//2.增加联系人的信息；
//3.删除指定联系人的信息；
//4.修改指定联系人的信息；
//5.查找指定联系人的信息；
//6.排序通讯论的信息

#include"contact.h"

void menu()
{
	printf("***********************************\n");
	printf("******  1. add      2.  del  ******\n");
	printf("******  3. search   4.  modify ****\n");
	printf("******  5. sort     6. print  *****\n");
	printf("******  0. exit          **********\n");
	printf("***********************************\n");
}

enum Option
{
	EXIT,
	ADD,
	DEL,
	SEARCH,
	MODIFY,
	SORT,
	PRINT
};

int main()
{
	int input = 0;
	//创建通讯录
	Contact con;  //通讯录
	//初始化通讯录
	InitContact(&con); //给data申请一块连续的空间在堆区上，sz=0,capacity初始化为当前最大的容量
	do
	{
		menu();
		printf("请选择:>");
		scanf("%d", &input);
		switch (input)
		{
		case ADD:   //增加联系人的信息
			AddContact(&con);  //存入Contact con，同样会改变con
			break;
		case DEL:   //删除指定联系人的信息
			DelContact(&con);
			break;
		case SEARCH:  //查找指定联系人的信息
			SearchContact(&con);
			break;
		case MODIFY:  //修改指定联系人的信息
			ModifyContact(&con);
			break;
		case SORT:  //排序通讯论的信息
			SortContact(&con);
			break;
		case PRINT:  //打印通讯论的信息
			PrintContact(&con);  //此处可以传con,因为只是打印而不会改变con；但效率不高(结构体传参最好传地址，压栈开销低)
			break;
		case EXIT:  //退出
			//保存信息到文件
			SaveContact(&con);
			//销毁通讯录
			DestoryContact(&con);
			printf("退出通讯录\n");
			break;
		default:
			printf("选择错误，重新选择\n");
			break;
		}
	} while (input);
	return 0;
}
