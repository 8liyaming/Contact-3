#define _CRT_SECURE_NO_WARNINGS
//test.c�ļ����ڲ����߼�

//ͨѶ¼-�汾3
// **��ͨѶ¼�˳���ʱ�򣬰���Ϣд���ļ�
// **��ͨѶ¼��ʼ����ʱ�򣬼����ļ�����Ϣ��ͨѶ¼��
// 
// *ͨѶ¼��ʼ�����ܴ��3���˵���Ϣ
// *�����ǿռ������˺���������2����Ϣ��3+2+2+2+2+2...
// 
//1.ͨѶ¼���ܹ����1000���˵���Ϣ��ÿ���˵���Ϣ������+����+�Ա�+�绰+��ַ��
//2.������ϵ�˵���Ϣ��
//3.ɾ��ָ����ϵ�˵���Ϣ��
//4.�޸�ָ����ϵ�˵���Ϣ��
//5.����ָ����ϵ�˵���Ϣ��
//6.����ͨѶ�۵���Ϣ

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
	//����ͨѶ¼
	Contact con;  //ͨѶ¼
	//��ʼ��ͨѶ¼
	InitContact(&con); //��data����һ�������Ŀռ��ڶ����ϣ�sz=0,capacity��ʼ��Ϊ��ǰ��������
	do
	{
		menu();
		printf("��ѡ��:>");
		scanf("%d", &input);
		switch (input)
		{
		case ADD:   //������ϵ�˵���Ϣ
			AddContact(&con);  //����Contact con��ͬ����ı�con
			break;
		case DEL:   //ɾ��ָ����ϵ�˵���Ϣ
			DelContact(&con);
			break;
		case SEARCH:  //����ָ����ϵ�˵���Ϣ
			SearchContact(&con);
			break;
		case MODIFY:  //�޸�ָ����ϵ�˵���Ϣ
			ModifyContact(&con);
			break;
		case SORT:  //����ͨѶ�۵���Ϣ
			SortContact(&con);
			break;
		case PRINT:  //��ӡͨѶ�۵���Ϣ
			PrintContact(&con);  //�˴����Դ�con,��Ϊֻ�Ǵ�ӡ������ı�con����Ч�ʲ���(�ṹ�崫����ô���ַ��ѹջ������)
			break;
		case EXIT:  //�˳�
			//������Ϣ���ļ�
			SaveContact(&con);
			//����ͨѶ¼
			DestoryContact(&con);
			printf("�˳�ͨѶ¼\n");
			break;
		default:
			printf("ѡ���������ѡ��\n");
			break;
		}
	} while (input);
	return 0;
}
