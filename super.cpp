#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <conio.h>//��getch();���û�����ĳ���ַ�ʱ�������Զ���ȡ�����谴�س���
using namespace std;
class Goods
{
public:
	Goods()
	{
	}
	int kind;
	char name[20];//����
	char Id[20];//���
	char place[10];//������
	char brand[10];//Ʒ��
	float buyprice;  //�����ۣ�
	float saleprice; //�����ۣ�
	int amount;  //���������
	int amount1; //�ۻ�������
	int profit;  //������
	Goods * Next;
	void InputAll()
	{
		InputName();
		InputKind();
		InputID();
		InputOther();
	}
	void InputKind()
	{
		cout << "\t\t��ѡ�����ࣺ"; cin >> kind;
	}
	void InputName()
	{
		cout << "\t\t��������Ʒ�����ƣ�";  cin >> name;
	}
	void InputID()
	{
		cout << "\t\t��������Ʒ�ı�ţ�";  cin >> Id;
	}
	void InputBuyprice()
	{
		cout << "\t\t����������ۣ�"; cin >> buyprice;
	}
	void InputSaleprice()
	{
		cout << "\t\t�������۳��ۣ�"; cin >> saleprice;
	}
	void InputAmount()
	{
		cout << "\t\t������ʣ����Ʒ������"; cin >> amount;
	}
	void InputProfit()
	{
		cout << "\t\t�����뾻����"; cin >> profit;
	}
	void InputPlace()
	{
		cout << "\t\t��������Ʒ���أ�"; cin >> place;
	}
	void Inputbrand()
	{
		cout << "\t\t������������Ʒ�ƣ�"; cin >> brand;
	}
	void InputOther()
	{
		cout << "\t\t����������ۣ�"; cin >> buyprice;
		cout << "\t\t�������۳��ۣ�"; cin >> saleprice;
		cout << "\t\t��������������"; cin >> amount;
		cout << "\t\t��������Ʒ�Ĳ��أ�"; cin >> place;
		cout << "\t\t������������Ʒ�ƣ�"; cin >> brand;
		profit = 0;
	}

	void ReadFile(istream & in) //������Ķ��������ļ�
	{
		in >> name >> kind >> Id >> buyprice >> saleprice >> amount >> place >> brand >> profit;
	}
	void Show()
	{
		cout << "��Ʒ��: " << name << endl << "����:" << kind << endl << "���: " << Id << endl << "������ " << buyprice << endl << "�۳��� " << saleprice << endl << "ʣ����Ʒ����: " <<
			amount << endl << "������" << profit << endl << "��Ʒ�Ĳ���: " << place << endl << "������Ʒ��: " << brand << endl << endl << endl;
	}
};
class Goodsmessage : public Goods            //�k�k�k�k�k�k�k�k�kGoodsmessage��k�k�k�k�k�k�k�k�k�k�k�k
{
public:
	Goodsmessage();
	~Goodsmessage();
	void showMenu(int n);
	void Find();
	void Save();
	void ModifyItem();
	void RemoveItem();
	void Swap(Goods *, Goods *);
	void Paixu();
	void Saleprice();
	int ListCount();
	void Display()
	{
		system("cls");
		i = 0;
		for (Goods * p = Head->Next; p != End; p = p->Next)
		{
			p->Show();
			i++;
		}
		cout << "����" << i << "����Ʒ" << "\n" << endl;
		cout << "���������ַ�����������";
		_getch();
	}
	void AddItem()//�Ӽ���������Ʒ��Ϣ
	{
		system("cls");
		End->InputName();
		showMenu(1);
		End->InputKind();
		do
		{
			End->InputID();
		} while (FindID(End->Id));
		End->InputOther();

		End->Next = new Goods;
		End = End->Next;
		cout << "��ӳɹ�!" << endl;
		Save();
		cout << "���������ַ�����������";
		_getch();
	}
private:
	Goods * Head, *End;
	int i;
	ifstream in;
	ofstream out;
	Goods *FindItem(char * name)
	{
		for (Goods * p = Head; p->Next != End; p = p->Next)//ƥ��ɹ��򷵻���һ��ָ�룬���ɹ��ͷ��ؿ�
		if (!strcmp(p->Next->name, name))return p;
		return NULL;
	}
	Goods *FindID(char * Id)
	{
		for (Goods * p = Head; p->Next != End; p = p->Next)//ƥ��ɹ��򷵻���һ��ָ�룬���ɹ��ͷ��ؿ�
		if (!strcmp(p->Next->Id, Id))return p;
		return NULL;
	}
};

Goodsmessage::Goodsmessage()                 //�k�k�k�k�k�k�k�k�k�k�k�k���캯���k�k�k�k�k�k�k�k�k�k�k�k
{
	Head = new Goods;
	Head->Next = new Goods;
	End = Head->Next;
	in.open("supermarket.txt");
	if (!in)
		cout << "����Ʒ��Ϣ�����Ƚ�����" << endl;
	else
	{
		while (!in.eof())
		{
			End->ReadFile(in);
			if (End->name[0] == '\0')break;
			End->Next = new Goods;
			End = End->Next;
		}
		in.close();
		cout << "\t\t\t\t��ȡ��Ʒ��Ϣ�ɹ�!" << "\n" << endl;
	}
}


Goodsmessage::~Goodsmessage()                //�k�k�k�k�k�k�k�k�k�k�k�k���������k�k�k�k�k�k�k�k�k�k�k�k
{
	//Save();
	for (Goods * temp; Head->Next != End;)
	{
		temp = Head->Next;
		Head->Next = Head->Next->Next;
		delete temp;
	}
	delete Head, End;
}

void Goodsmessage::showMenu(int n)//�˵�      //�k�k�k�k�k�k�k�k�k�k�k�k�˵��k�k�k�k�k�k�k�k�k�k�k�k
{
	switch (n)
	{
	case 1:
	{
			  cout << "********************************************************************************\n"
				  << "      1. ʳƷ      2. ��ױƷ      3. ����Ʒ      4. ����      \n"
				  << "********************************************************************************\n" << endl;
			  break; }
	case 2:
	{
			  system("cls");
			  cout << "��������������������  ��   �� �� �� Ʒ �� �� ϵ  ͳ     ��  ��������������������" << endl;
			  cout << "��������������������  ��          1.���ӳ�����Ʒ        ��  �度����������������" << endl;
			  cout << "��������������������  ��          2.��ʾ������Ʒ        ��  �度����������������" << endl;
			  cout << "��������������������  ��          3.����ͳ����Ʒ        ��  �度����������������" << endl;
			  cout << "��������������������  ��          4.���ҳ�����Ʒ        ��  �度����������������" << endl;
			  cout << "��������������������  ��          5.ɾ��������Ʒ        ��  �度����������������" << endl;
			  cout << "��������������������  ��          6.�޸ĳ�����Ʒ        ��  �度����������������" << endl;
			  cout << "��������������������  ��          7.�۳�������Ʒ        ��  �度����������������" << endl;
			  cout << "��������������������  ��        8.���泬����Ʒ��Ϣ      ��  �度����������������" << endl;
			  cout << "��������������������  ��          0.��ȫ�˳�ϵͳ        ��  �度����������������" << endl;

			  cout << "\t\t\n\t\t\t\t  ��ѡ��0-8" << endl;
			  break; }
	case 3:
	{
			  system("cls");
			  cout << "********************************************************************************\n"
				  << "\t   1. �޸���Ʒ��      4. �޸Ľ�����\t\t7. �޸ľ�����\n"
				  << "\t   2. �޸�����        5. �޸��۳���\t\t8. �޸��޸���Ʒ����\n"
				  << "\t   3. �޸ı��        6. �޸�ʣ����Ʒ��\t\t9. �޸�������Ʒ��\n"
				  << "\t\t\t\t10.�޸�ȫ��\n"
				  << "********************************************************************************" << endl;
			  cout << "\t\t\n\t\t\t\t  ��ѡ��0-10" << endl;
			  break;
	}
	case 4:
	{
			  system("cls");
			  cout << "********************************************************************************\n"
				  << "\t   1. ������������        2. �����������       3. ������������\n"
				  << "********************************************************************************" << endl;
			  cout << "\t\t\n\t\t\t\t  ��ѡ��0-3" << endl;
			  break;
	}
	case 5:
	{
			  system("cls");
			  cout << "\n\t\t        *********************************\n";
			  cout << "\t\t        *****   1.����Ʒ�����Ʋ���  *****\n\t\t        *****    2.����Ʒ��Ų���   *****";
			  cout << "\n\t\t        *********************************\n��ѡ��0-2";
			  break;
	}
	}
}

void Goodsmessage::Find()       //�k�k�k�k�k�k�k�k�k�k�k�k���Һ����k�k�k�k�k�k�k�k�k�k�k�k
{
	system("cls");
	char name[20], Id[10];
	int x;
	Goods * p = NULL;
	showMenu(5);
	cin >> x;
	switch (x)
	{
	case 1:{cout << "\t\t������Ҫ���ҵ���Ʒ�����ƣ�"; cin >> name;
		if (p = FindItem(name))
		{
			p->Next->Show();
			cout << "���������ַ�����������";
			_getch();
		}
		else
		{
			cout << "\t\tû���ҵ������Ƶ���Ʒ��" << '\n' << endl;
			cout << "���������ַ�����������";
			_getch();
		}
	}break;
	case 2:
	{
			  cout << "\t\t������Ҫ���ҵ���Ʒ�ı�ţ�"; cin >> Id;
			  if (p = FindID(Id))
			  {
				  p->Next->Show();
				  cout << "���������ַ�����������";
				  _getch();
			  }
			  else
			  {
				  cout << "\t\tû���ҵ��ñ�ŵ���Ʒ��" << '\n' << endl;
				  cout << "���������ַ�����������";
				 _getch();
			  }
	}break;
	}
}

void Goodsmessage::ModifyItem()         //�޸���Ʒ��Ϣ
{

	showMenu(3);
	int x;
	cin >> x;
	switch (x)
	{
	case 1:
	{
			  char Id[20];
			  Goods * p = NULL;
			  cout << "\t\t������Ҫ�޸ĵ���Ʒ�ı��:"; cin >> Id;
			  if (p = FindID(Id))
			  {
				  cout << "\t\t���ҵ���Ʒ����Ϣ���������µ���Ϣ!" << endl;
				  p->Next->InputName();
				  cout << "�޸ĳɹ���" << endl;
				  cout << "���������ַ�����������";
				 _getch();
			  }
			  else
			  {
				  cout << "\t\tû���ҵ�����Ҫ����Ʒ!" << endl;
				  cout << "���������ַ�����������";
				  _getch();
			  }
			  break;
	}
	case 2:
	{
			  char Id[20];
			  Goods * p = NULL;
			  cout << "\t\t������Ҫ�޸ĵ���Ʒ�ı��:"; cin >> Id;
			  if (p = FindID(Id))
			  {
				  cout << "\t\t���ҵ���Ʒ����Ϣ���������µ���Ϣ!" << endl;
				  p->Next->InputKind();
				  cout << "�޸ĳɹ���" << endl;
				  cout << "���������ַ�����������";
				  _getch();
			  }
			  else
			  {
				  cout << "\t\tû���ҵ�����Ҫ����Ʒ!" << endl;
				  cout << "���������ַ�����������";
				  _getch();
			  }
			  break;
	}
	case 3:
	{
			  char Id[20];
			  Goods * p = NULL;
			  cout << "\t\t������Ҫ�޸ĵ���Ʒ�ı��:"; cin >> Id;
			  if (p = FindID(Id))
			  {
				  cout << "\t\t���ҵ���Ʒ����Ϣ���������µ���Ϣ!" << endl;
				  p->Next->InputID();
				  cout << "�޸ĳɹ���" << endl;
				  cout << "���������ַ�����������";
				  _getch();
			  }
			  else
			  {
				  cout << "\t\tû���ҵ�����Ҫ����Ʒ!" << endl;
				  cout << "���������ַ�����������";
				  _getch();
			  }
			  break;
	}
	case 4:
	{
			  char Id[20];
			  Goods * p = NULL;
			  cout << "\t\t������Ҫ�޸ĵ���Ʒ�ı��:"; cin >> Id;
			  if (p = FindID(Id))
			  {
				  cout << "\t\t���ҵ���Ʒ����Ϣ���������µ���Ϣ!" << endl;
				  p->Next->InputBuyprice();
				  cout << "�޸ĳɹ���" << endl;
				  cout << "���������ַ�����������";
				  _getch();
			  }
			  else
			  {
				  cout << "\t\tû���ҵ�����Ҫ����Ʒ!" << endl;
				  cout << "���������ַ�����������";
				  _getch();
			  }
			  break;
	}
	case 5:
	{
			  char Id[20];
			  Goods * p = NULL;
			  cout << "\t\t������Ҫ�޸ĵ���Ʒ�ı��:"; cin >> Id;
			  if (p = FindID(Id))
			  {
				  cout << "\t\t���ҵ���Ʒ����Ϣ���������µ���Ϣ!" << endl;
				  p->Next->InputSaleprice();
				  cout << "�޸ĳɹ���" << endl;
				  cout << "���������ַ�����������";
				  _getch();
			  }
			  else
			  {
				  cout << "\t\tû���ҵ�����Ҫ����Ʒ!" << endl;
				  cout << "���������ַ�����������";
				  _getch();
			  }
			  break;
	}
	case 6:
	{
			  char Id[20];
			  Goods * p = NULL;
			  cout << "\t\t������Ҫ�޸ĵ���Ʒ�ı��:"; cin >> Id;
			  if (p = FindID(Id))
			  {
				  cout << "\t\t���ҵ���Ʒ����Ϣ���������µ���Ϣ!" << endl;
				  p->Next->InputAmount();
				  cout << "�޸ĳɹ���" << endl;
				  cout << "���������ַ�����������";
				  _getch();
			  }
			  else
			  {
				  cout << "\t\tû���ҵ�����Ҫ����Ʒ!" << endl;
				  cout << "���������ַ�����������";
				  _getch();
			  }
			  break;
	}
	case 7:
	{
			  char Id[20];
			  Goods * p = NULL;
			  cout << "\t\t������Ҫ�޸ĵ���Ʒ�ı��:"; cin >> Id;
			  if (p = FindID(Id))
			  {
				  cout << "\t\t���ҵ���Ʒ����Ϣ���������µ���Ϣ!" << endl;
				  p->Next->InputProfit();
				  cout << "�޸ĳɹ���" << endl;
				  cout << "���������ַ�����������";
				  _getch();
			  }
			  else
			  {
				  cout << "\t\tû���ҵ�����Ҫ����Ʒ!" << endl;
				  cout << "���������ַ�����������";
				  _getch();
			  }
			  break;
	}
	case 8:
	{
			  char Id[20];
			  Goods * p = NULL;
			  cout << "\t\t������Ҫ�޸ĵ���Ʒ�ı��:"; cin >> Id;
			  if (p = FindID(Id))
			  {
				  cout << "\t\t���ҵ���Ʒ����Ϣ���������µ���Ϣ!" << endl;
				  p->Next->InputPlace();
				  cout << "�޸ĳɹ���" << endl;
				  cout << "���������ַ�����������";
				 _getch();
			  }
			  else
			  {
				  cout << "\t\tû���ҵ�����Ҫ����Ʒ!" << endl;
				  cout << "���������ַ�����������";
				  _getch();
			  }
			  break;
	}
	case 9:
	{
			  char Id[20];
			  Goods * p = NULL;
			  cout << "\t\t������Ҫ�޸ĵ���Ʒ�ı��:"; cin >> Id;
			  if (p = FindID(Id))
			  {
				  cout << "\t\t���ҵ���Ʒ����Ϣ���������µ���Ϣ!" << endl;
				  p->Next->Inputbrand();
				  cout << "�޸ĳɹ���" << endl;
				  cout << "���������ַ�����������";
				  _getch();
			  }
			  else
			  {
				  cout << "\t\tû���ҵ�����Ҫ����Ʒ!" << endl;
				  cout << "���������ַ�����������";
				  _getch();
			  }
			  break;
	}
	case 10:
	{
			   char Id[20];
			   Goods * p = NULL;
			   cout << "\t\t������Ҫ�޸ĵ���Ʒ�ı��:"; cin >> Id;
			   if (p = FindID(Id))
			   {
				   cout << "\t\t���ҵ���Ʒ����Ϣ���������µ���Ϣ!" << endl;
				   p->Next->InputAll();
				   cout << "�޸ĳɹ���" << endl;
				   cout << "���������ַ�����������";
				   _getch();
			   }
			   else
			   {
				   cout << "\t\tû���ҵ�����Ҫ����Ʒ!" << endl;
				   cout << "���������ַ�����������";
				   _getch();
			   }
	}
	}

}

void Goodsmessage::RemoveItem()          //�k�k�k�k�k�k�k�k�k�k�k�kɾ����Ʒ��Ϣ�k�k�k�k�k�k�k�k�k�k�k�k
{
	system("cls");
	char Id[20];
	Goods * p = NULL, *temp = NULL;
	cout << "\t\t������Ҫɾ������Ʒ�ı��:" << endl; cin >> Id;
	if (p = FindID(Id))
	{
		temp = p->Next;
		p->Next = p->Next->Next;
		delete temp;
		cout << "\t\tɾ���ɹ�!" << endl;
		cout << "���������ַ�����������";
		_getch();
	}
	else
	{
		cout << "\t\tû���ҵ�����Ҫ����Ʒ!" << endl;
		cout << "���������ַ�����������";
		_getch();
	}
}
void Goodsmessage::Saleprice()           //�k�k�k�k�k�k�k�k�k�k�k�k�۳���Ʒ�k�k�k�k�k�k�k�k�k�k�k�k
{
	system("cls");
	char Id[20]; int i;
	Goods * p = NULL;
	Goods * temp = NULL;
	cout << "\t\t������Ҫ�۳�����Ʒ�ı�ź�����:" << endl; cin >> Id; cin >> i;

	if (p = FindID(Id))
	{
		if (p->Next->amount>i)
		{
			p->Next->amount -= i;
			p->Next->amount1 += i;
			p->Next->profit += i*(p->Next->saleprice - p->Next->buyprice);
			cout << "��Ʒ�۳��ɹ�!" << "\n";
			cout << "�۳���Ʒ���: " << Id << "\t" << "����: " << i << "\n";
			cout << "\n";
			cout << "�۳�����Ʒ��Ϣ: " << endl;

			p->Next->Show();
			Save();
			cout << "���������ַ�����������";
			_getch();

		}
		else
		{
			cout << "��Ʒ�������������ܹ���" << endl;
			cout << "���������ַ�����������";
			_getch();
			Saleprice();
		}

	}
	else
	{
		cout << "�޴�����Ʒ�����ܹ���" << endl;
		cout << "���������ַ�����������";
		_getch();
		showMenu(2);
	}

}
void Goodsmessage::Swap(Goods *p1, Goods *p2)        //����������Ʒ������
{
	Goods *temp = new Goods;
	strcpy(temp->name, p1->name);
	temp->kind = p1->kind;
	strcpy(temp->Id, p1->Id);
	strcpy(temp->place, p1->place);
	temp->saleprice = p1->saleprice;
	temp->buyprice = p1->buyprice;
	temp->amount = p1->amount;
	temp->profit = p1->profit;
	strcpy(temp->brand, p1->brand);

	strcpy(p1->name, p2->name);
	p1->kind = p2->kind;
	strcpy(p1->Id, p2->Id);
	strcpy(p1->place, p2->place);
	p1->saleprice = p2->saleprice;
	p1->buyprice = p2->buyprice;
	p1->amount = p2->amount;
	p1->profit = p2->profit;
	strcpy(p1->brand, p2->brand);

	strcpy(p2->name, temp->name);
	p2->kind = temp->kind;
	strcpy(p2->Id, temp->Id);
	strcpy(p2->place, temp->place);
	p2->saleprice = temp->saleprice;
	p2->buyprice = temp->buyprice;
	p2->amount = temp->amount;
	p2->profit = temp->profit;
	strcpy(p2->brand, temp->brand);
}

int Goodsmessage::ListCount()       //ͳ�Ƶ�ǰ����ļ�¼����������һ������
{
	if (!Head)
		return 0;
	int n = 0;
	for (Goods * p = Head->Next; p != End; p = p->Next)
	{
		n++;
	}
	return n;
}

void Goodsmessage::Paixu()       //�k�k�k�k�k�k�k�k�k�k������Ʒ�k�k�k�k�k�k�k�k�k�k�k�k�k�k
{
	showMenu(4);
	int x;
	cin >> x;
	switch (x)
	{
	case 1:
	{
			  system("cls");
			  cout << "\t\t������..." << endl;
			  cout << "\n";
			  Goods *p = NULL, *p1 = NULL, *k = NULL;
			  int n = Goodsmessage::ListCount();
			  if (n<2)
				  return;
			  for (p = Head->Next; p != End; p = p->Next)
			  for (k = p->Next; k != End; k = k->Next)
			  {
				  if (p->buyprice>k->buyprice)
				  {
					  Goodsmessage::Swap(p, k);
				  }
			  }
			  Display();
			  out.open("������.txt");
			  for (Goods *q = Head->Next; q != End; q = q->Next)
				  out << q->name << "\t" << q->kind << "\t" << q->Id << "\t" << q->buyprice << "\t" << q->saleprice << "\t" << q->amount << "\t" << q->place << "\t" << q->brand << "\t" << q->profit << '\n';
			  out.close();
			  cout << "������Ϣ�ɹ�" << endl;
			  cout << "������ɣ�" << endl;
			  _getch();
			  return;
	}
	case 2:
	{
			  system("cls");
			  cout << "\t\t������..." << endl;
			  cout << "\n";
			  Goods *p = NULL, *p1 = NULL, *k = NULL;
			  int n = Goodsmessage::ListCount();
			  if (n<2)
				  return;
			  for (p = Head->Next; p != End; p = p->Next)
			  for (k = p->Next; k != End; k = k->Next)
			  {
				  if (p->amount>k->amount)
				  {
					  Goodsmessage::Swap(p, k);
				  }
			  }
			  Display();
			  out.open("�����.txt");
			  for (Goods *q = Head->Next; q != End; q = q->Next)
				  out << q->name << "\t" << q->kind << "\t" << q->Id << "\t" << q->buyprice << "\t" << q->saleprice << "\t" << q->amount << "\t" << q->place << "\t" << q->brand << "\t" << q->profit << '\n';
			  out.close();
			  cout << "������Ϣ�ɹ�" << endl;
			  cout << "������ɣ�" << endl;
			  _getch();
			  return;
	}
	case 3:
	{
			  system("cls");
			  cout << "\t\t������..." << endl;
			  cout << "\n";
			  Goods *p = NULL, *p1 = NULL, *k = NULL;
			  int n = Goodsmessage::ListCount();
			  if (n<2)
				  return;
			  for (p = Head->Next; p != End; p = p->Next)
			  for (k = p->Next; k != End; k = k->Next)
			  {
				  if (p->profit>k->profit)
				  {
					  Goodsmessage::Swap(p, k);
				  }
			  }
			  Display();
			  out.open("������.txt");
			  for (Goods *q = Head->Next; q != End; q = q->Next)
				  out << q->name << "\t" << q->kind << "\t" << q->Id << "\t" << q->buyprice << "\t" << q->saleprice << "\t" << q->amount << "\t" << q->place << "\t" << q->brand << "\t" << q->profit << '\n';
			  out.close();
			  cout << "������Ϣ�ɹ�" << endl;
			  cout << "������ɣ�" << endl;
			  _getch();
			  return;
	}
	}
}


void Goodsmessage::Save()       //�k�k�k�k�k�k�k�k�k�k�k������Ʒ��Ϣ���ļ������k�k�k�k�k�k�k�k�k�k�k�k�k
{
	out.open("supermarket.txt");
	for (Goods *p = Head->Next; p != End; p = p->Next)
		out << p->name << "\t" << p->kind << "\t" << p->Id << "\t" << p->buyprice << "\t" << p->saleprice << "\t" << p->amount << "\t" << p->place << "\t" << p->brand << "\t" << p->profit << '\n';

	out.close();
	cout << "������Ϣ�ɹ�" << endl;
}


int main()
{
	cout << "\t\t" << endl;
	for (int i = 0; i<3; i++)
		cout << "\t\t��\t\t\t\t\t\t��" << endl; cout << "\t\t�������ӭ���볬����Ʒ����ϵͳ��������" << endl;
	for (int i = 0; i<3; i++)
		cout << "\t\t��\t\t\t\t\t\t��" << endl;
	cout << "\t\t$$\n" << endl;;
	Goodsmessage Grade;
	cout << "\t\t\t\t���������ʼ����";
	_getch();
	int x;
	bool quit = false;
	while (!quit)
	{
		Grade.showMenu(2);
		cin >> x;
		switch (x)
		{
		case 0:{quit = true; break; }
		case 1:{Grade.AddItem(); break; }
		case 2:{Grade.Display(); break; }
		case 3:{Grade.Paixu(); break; }
		case 4:{Grade.Find(); break; }
		case 5:{Grade.RemoveItem(); break; }
		case 6:{Grade.ModifyItem(); break; }
		case 7:{Grade.Saleprice(); break; }
		case 8:{Grade.Save(); break; }
		}
	}
	return 0;
}
