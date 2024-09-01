#define _CRT_SECURE_NO_WARNINGS
//contact.c�ļ�������غ�����ʵ��

#include"contact.h"

void LoadContact(Contact* pc)
{
	FILE* pf = fopen("contact.dat", "r");
	if (pf == NULL)
	{
		perror("LoadContact");
		return;
	}
	//���ļ�
	PeoInfo tmp = { 0 };
	while (fread(&tmp, sizeof(PeoInfo), 1, pf))
	{
		//�Ƿ���Ҫ����
		CheckCapacity(pc);
		pc->data[pc->sz] = tmp;
		pc->sz++;
	}
	//�ر��ļ�
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

	pc->sz = 0;  //��ʼ����Ĭ����0
	pc->capacity = DEFAULT_SZ;

	//�����ļ�
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
	//д�ļ�
	int i = 0;
	for (i = 0; i < pc->sz; i++)
	{
		fwrite(pc->data+i, sizeof(PeoInfo), 1, pf);
	}
	//�ر��ļ�
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
		printf("���ݳɹ�\n");
	    }
	    else
	    {
		perror("AddContact");
		printf("������ϵ��ʧ��\n");
		return;
	    }
    }
}

void AddContact(Contact* pc)
{
	assert(pc);
	// ��������
	//if (pc->sz == pc->capacity)
	//{
	//	PeoInfo* ptr = (PeoInfo*)realloc(pc->data, (pc->capacity + INC_SZ) * sizeof(PeoInfo));
	//	if (ptr != NULL)
	//	{
	//		pc->data = ptr;
	//		pc->capacity += INC_SZ;
	//		printf("���ݳɹ�\n");
	//	}
	//	else
	//	{
	//		perror("AddContact");
	//		printf("������ϵ��ʧ��\n");
	//		return;
	//	}
	//}
	CheckCapacity(pc);
	//����һ����ϵ�˵���Ϣ
	printf("����������:>");
	scanf("%s", pc->data[pc->sz].name);  //name��һ�����飬�����������׵�ַ���ʲ��ü�&
	printf("����������:>");
	scanf("%d", &(pc->data[pc->sz].age));  //scanfӦ����ȡ��ַ��age��һ����������Ҫ��&
	printf("�������Ա�:>");
	scanf("%s", pc->data[pc->sz].sex);
	printf("������绰:>");
	scanf("%s", pc->data[pc->sz].tele);
	printf("�������ַ:>");
	scanf("%s", pc->data[pc->sz].addr);

	pc->sz++;
	printf("���ӳɹ�\n");
}

void PrintContact(const Contact* pc)
{
	assert(pc);
	int i = 0;
	//��ӡ����
	printf("%-10s\t%-5s\t%-5s\t%-20s\t%-10s\n", "����", "����", "�Ա�", "�绰", "��ַ");
	//��-10s������10���ַ��������ÿո���䣬�Ա�֤ͬ���Ŀ��,���Ŵ�������룬û�и����Ҷ���;��\t����֤�м�հף���������
	//��ӡ����
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

static int FindByName(Contact* pc, char name[])  //����staticֻ���ڸ�Դ�ļ��п��������ᱩ¶������Դ�ļ�
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
	return -1;  //�Ҳ��������
}

void DelContact(Contact* pc)
{
	assert(pc);
	char name[MAX_NAME] = { 0 };
	if (pc->sz == 0)
	{
		printf("ͨѶ¼Ϊ�գ�����ɾ��\n");
		return;
	}
	printf("������Ҫɾ����ϵ�˵�����:>");
	scanf("%s", name);

	//step1:����Ҫɾ������ϵ��(��/û��)
	int pos = FindByName(pc, name);
	if (pos == -1)
	{
		printf("Ҫɾ������ϵ�˲�����\n");
		return;
	}
	//step2:ɾ��(˼�룺���ҵ�����ϵ����Ϣ�����һ����ϵ�˵���Ϣ����ǰŲһλ)
	int i = 0;
	for (i = pos; i < pc->sz - 1; i++) //ע����sz-1,����sz,��Ϊ���һ����Ϣֻ����ǰŲ�����ú�ߵ���Ϣȥ������
	{
		pc->data[i] = pc->data[i + 1];
	}
	pc->sz--;  //ͬʱ��֤�����һ����ϵ�˵���Ϣ�ܹ���Ч��ɾ��
	printf("ɾ���ɹ�\n");
}

void SearchContact(Contact* pc)
{
	assert(pc);
	char name[MAX_NAME] = { 0 };
	printf("������Ҫ���ҵ���ϵ�˵�����\n");
	scanf("%s", name);
	int pos = FindByName(pc, name);
	if (pos == -1)
	{
		printf("Ҫɾ������ϵ�˲�����\n");
		return;
	}
	else
	{
		//��ӡ����
		printf("%-10s\t%-5s\t%-5s\t%-20s\t%-10s\n", "����", "����", "�Ա�", "�绰", "��ַ");
		//��ӡ����
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
	printf("������Ҫ�޸ĵ���ϵ�˵�����\n");
	scanf("%s", name);
	int pos = FindByName(pc, name);
	if (pos == -1)
	{
		printf("Ҫ�޸ĵ���ϵ�˲�����\n");
		return;
	}
	else
	{
		printf("����������:>");
		scanf("%s", pc->data[pos].name);
		printf("����������:>");
		scanf("%d", &(pc->data[pos].age));
		printf("�������Ա�:>");
		scanf("%s", pc->data[pos].sex);
		printf("������绰:>");
		scanf("%s", pc->data[pos].tele);
		printf("�������ַ:>");
		scanf("%s", pc->data[pos].addr);

		printf("�޸ĳɹ�\n");
	}
}

int cmp_name(const void* e1, const void* e2)
{
	return (strcmp(((Contact*)e1)->data->name, ((Contact*)e2)->data->name));
}
//��ϵ������
void SortContact(Contact* pc)
{
	assert(pc);
	qsort(pc->data, pc->sz, sizeof(pc->data[0]), cmp_name);

	printf("�������\n");
	PrintContact(pc);
}
