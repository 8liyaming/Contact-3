#define _CRT_SECURE_NO_WARNINGS
//contact.c文件用于相关函数的实现

#include"contact.h"

void LoadContact(Contact* pc)
{
	FILE* pf = fopen("contact.dat", "r");
	if (pf == NULL)
	{
		perror("LoadContact");
		return;
	}
	//读文件
	PeoInfo tmp = { 0 };
	while (fread(&tmp, sizeof(PeoInfo), 1, pf))
	{
		//是否需要增容
		CheckCapacity(pc);
		pc->data[pc->sz] = tmp;
		pc->sz++;
	}
	//关闭文件
	fclose(pf);
	pf = NULL;
}

void InitContact(Contact* pc)
{
	assert(pc);
	pc->data = (PeoInfo*)malloc(DEFAULT_SZ * sizeof(PeoInfo));
	if (pc->data == NULL)
	{
		perror("InitContact");
		return;
	}

	pc->sz = 0;  //初始化后默认是0
	pc->capacity = DEFAULT_SZ;

	//加载文件
	LoadContact(pc);
}

void DestoryContact(Contact* pc)
{
	free(pc->data);
	pc->data = NULL;
	pc->sz = 0;
	pc->capacity = 0;
}

void SaveContact(Contact* pc)
{
	FILE* pf = fopen("contact.dat","w");
	if (pf == NULL)
	{
		perror("SaveContact");
		return;
	}
	//写文件
	int i = 0;
	for (i = 0; i < pc->sz; i++)
	{
		fwrite(pc->data+i, sizeof(PeoInfo), 1, pf);
	}
	//关闭文件
	fclose(pf);
	pf = NULL;
}

void CheckCapacity(Contact* pc)
{
	if (pc->sz == pc->capacity)
    {
	    PeoInfo* ptr = (PeoInfo*)realloc(pc->data, (pc->capacity + INC_SZ) * sizeof(PeoInfo));
	    if (ptr != NULL)
	    {
		pc->data = ptr;
		pc->capacity += INC_SZ;
		printf("增容成功\n");
	    }
	    else
	    {
		perror("AddContact");
		printf("增加联系人失败\n");
		return;
	    }
    }
}

void AddContact(Contact* pc)
{
	assert(pc);
	// 考虑增容
	//if (pc->sz == pc->capacity)
	//{
	//	PeoInfo* ptr = (PeoInfo*)realloc(pc->data, (pc->capacity + INC_SZ) * sizeof(PeoInfo));
	//	if (ptr != NULL)
	//	{
	//		pc->data = ptr;
	//		pc->capacity += INC_SZ;
	//		printf("增容成功\n");
	//	}
	//	else
	//	{
	//		perror("AddContact");
	//		printf("增加联系人失败\n");
	//		return;
	//	}
	//}
	CheckCapacity(pc);
	//增加一个联系人的信息
	printf("请输入名字:>");
	scanf("%s", pc->data[pc->sz].name);  //name是一个数组，数组名就是首地址，故不用加&
	printf("请输入年龄:>");
	scanf("%d", &(pc->data[pc->sz].age));  //scanf应搭配取地址，age是一个变量，需要加&
	printf("请输入性别:>");
	scanf("%s", pc->data[pc->sz].sex);
	printf("请输入电话:>");
	scanf("%s", pc->data[pc->sz].tele);
	printf("请输入地址:>");
	scanf("%s", pc->data[pc->sz].addr);

	pc->sz++;
	printf("增加成功\n");
}

void PrintContact(const Contact* pc)
{
	assert(pc);
	int i = 0;
	//打印标题
	printf("%-10s\t%-5s\t%-5s\t%-20s\t%-10s\n", "名字", "年龄", "性别", "电话", "地址");
	//“-10s”代表10个字符，不够用空格填充，以保证同样的宽度,负号代表左对齐，没有负号右对齐;“\t”保证中间空白，更加美观
	//打印数据
	for (i = 0; i < pc->sz; i++)
	{
		printf("%-10s\t%-5d\t%-5s\t%-20s\t%-10s\n",
			pc->data[i].name,
			pc->data[i].age,
			pc->data[i].sex,
			pc->data[i].tele,
			pc->data[i].addr);
	}
}

static int FindByName(Contact* pc, char name[])  //加了static只能在该源文件中看到，不会暴露给其他源文件
{
	assert(pc);
	int i = 0;
	for (i = 0; i < pc->sz; i++)
	{
		if (strcmp(pc->data[i].name, name) == 0)
		{
			return i;
		}
	}
	return -1;  //找不到的情况
}

void DelContact(Contact* pc)
{
	assert(pc);
	char name[MAX_NAME] = { 0 };
	if (pc->sz == 0)
	{
		printf("通讯录为空，无需删除\n");
		return;
	}
	printf("请输入要删除联系人的名字:>");
	scanf("%s", name);

	//step1:查找要删除的联系人(有/没有)
	int pos = FindByName(pc, name);
	if (pos == -1)
	{
		printf("要删除的联系人不存在\n");
		return;
	}
	//step2:删除(思想：查找到的联系人信息到最后一个联系人的信息都往前挪一位)
	int i = 0;
	for (i = pos; i < pc->sz - 1; i++) //注意是sz-1,不是sz,因为最后一个信息只用往前挪，不用后边的信息去覆盖它
	{
		pc->data[i] = pc->data[i + 1];
	}
	pc->sz--;  //同时保证了最后一个联系人的信息能够有效被删除
	printf("删除成功\n");
}

void SearchContact(Contact* pc)
{
	assert(pc);
	char name[MAX_NAME] = { 0 };
	printf("请输入要查找的联系人的名字\n");
	scanf("%s", name);
	int pos = FindByName(pc, name);
	if (pos == -1)
	{
		printf("要删除的联系人不存在\n");
		return;
	}
	else
	{
		//打印标题
		printf("%-10s\t%-5s\t%-5s\t%-20s\t%-10s\n", "名字", "年龄", "性别", "电话", "地址");
		//打印数据
		printf("%-10s\t%-5d\t%-5s\t%-20s\t%-10s\n",
			pc->data[pos].name,
			pc->data[pos].age,
			pc->data[pos].sex,
			pc->data[pos].tele,
			pc->data[pos].addr);
	}
}

void ModifyContact(Contact* pc)
{
	assert(pc);
	char name[MAX_NAME] = { 0 };
	printf("请输入要修改的联系人的名字\n");
	scanf("%s", name);
	int pos = FindByName(pc, name);
	if (pos == -1)
	{
		printf("要修改的联系人不存在\n");
		return;
	}
	else
	{
		printf("请输入名字:>");
		scanf("%s", pc->data[pos].name);
		printf("请输入年龄:>");
		scanf("%d", &(pc->data[pos].age));
		printf("请输入性别:>");
		scanf("%s", pc->data[pos].sex);
		printf("请输入电话:>");
		scanf("%s", pc->data[pos].tele);
		printf("请输入地址:>");
		scanf("%s", pc->data[pos].addr);

		printf("修改成功\n");
	}
}

int cmp_name(const void* e1, const void* e2)
{
	return (strcmp(((Contact*)e1)->data->name, ((Contact*)e2)->data->name));
}
//联系人排序
void SortContact(Contact* pc)
{
	assert(pc);
	qsort(pc->data, pc->sz, sizeof(pc->data[0]), cmp_name);

	printf("排序完成\n");
	PrintContact(pc);
}
