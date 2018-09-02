#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <conio.h>//用getch();当用户按下某个字符时，函数自动读取，无需按回车。
using namespace std;
class Goods
{
public:
	Goods()
	{
	}
	int kind;
	char name[20];//名字
	char Id[20];//编号
	char place[10];//生产地
	char brand[10];//品牌
	float buyprice;  //进货价；
	float saleprice; //卖出价；
	int amount;  //存货数量；
	int amount1; //售货数量；
	int profit;  //净利润；
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
		cout << "\t\t请选择种类："; cin >> kind;
	}
	void InputName()
	{
		cout << "\t\t请输入商品的名称：";  cin >> name;
	}
	void InputID()
	{
		cout << "\t\t请输入商品的编号：";  cin >> Id;
	}
	void InputBuyprice()
	{
		cout << "\t\t请输入进货价："; cin >> buyprice;
	}
	void InputSaleprice()
	{
		cout << "\t\t请输入售出价："; cin >> saleprice;
	}
	void InputAmount()
	{
		cout << "\t\t请输入剩余商品数量："; cin >> amount;
	}
	void InputProfit()
	{
		cout << "\t\t请输入净利润："; cin >> profit;
	}
	void InputPlace()
	{
		cout << "\t\t请输入商品产地："; cin >> place;
	}
	void Inputbrand()
	{
		cout << "\t\t请输入生产商品牌："; cin >> brand;
	}
	void InputOther()
	{
		cout << "\t\t请输入进货价："; cin >> buyprice;
		cout << "\t\t请输入售出价："; cin >> saleprice;
		cout << "\t\t请输入存货数量："; cin >> amount;
		cout << "\t\t请输入商品的产地："; cin >> place;
		cout << "\t\t请输入生产商品牌："; cin >> brand;
		profit = 0;
	}

	void ReadFile(istream & in) //将输入的东西存入文件
	{
		in >> name >> kind >> Id >> buyprice >> saleprice >> amount >> place >> brand >> profit;
	}
	void Show()
	{
		cout << "商品名: " << name << endl << "种类:" << kind << endl << "编号: " << Id << endl << "进货价 " << buyprice << endl << "售出价 " << saleprice << endl << "剩余商品数量: " <<
			amount << endl << "净利润：" << profit << endl << "商品的产地: " << place << endl << "生产商品牌: " << brand << endl << endl << endl;
	}
};
class Goodsmessage : public Goods            //﹌﹌﹌﹌﹌﹌﹌﹌﹌Goodsmessage类﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌
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
		cout << "共有" << i << "个商品" << "\n" << endl;
		cout << "输入任意字符！继续……";
		_getch();
	}
	void AddItem()//从键盘输入商品信息
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
		cout << "添加成功!" << endl;
		Save();
		cout << "输入任意字符！继续……";
		_getch();
	}
private:
	Goods * Head, *End;
	int i;
	ifstream in;
	ofstream out;
	Goods *FindItem(char * name)
	{
		for (Goods * p = Head; p->Next != End; p = p->Next)//匹配成功则返回上一个指针，不成功就返回空
		if (!strcmp(p->Next->name, name))return p;
		return NULL;
	}
	Goods *FindID(char * Id)
	{
		for (Goods * p = Head; p->Next != End; p = p->Next)//匹配成功则返回上一个指针，不成功就返回空
		if (!strcmp(p->Next->Id, Id))return p;
		return NULL;
	}
};

Goodsmessage::Goodsmessage()                 //﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌构造函数﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌
{
	Head = new Goods;
	Head->Next = new Goods;
	End = Head->Next;
	in.open("supermarket.txt");
	if (!in)
		cout << "无商品信息。请先进货。" << endl;
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
		cout << "\t\t\t\t读取商品信息成功!" << "\n" << endl;
	}
}


Goodsmessage::~Goodsmessage()                //﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌析构函数﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌
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

void Goodsmessage::showMenu(int n)//菜单      //﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌菜单﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌
{
	switch (n)
	{
	case 1:
	{
			  cout << "********************************************************************************\n"
				  << "      1. 食品      2. 化妆品      3. 日用品      4. 饮料      \n"
				  << "********************************************************************************\n" << endl;
			  break; }
	case 2:
	{
			  system("cls");
			  cout << "▉▉▉▉▉▉▉▉▉▉  ☆   超 市 商 品 管 理 系  统     ☆  ▉▉▉▉▉▉▉▉▉▉" << endl;
			  cout << "▉▉▉▉▉▉▉▉▉★  ☆          1.增加超市商品        ☆  ★▉▉▉▉▉▉▉▉▉" << endl;
			  cout << "▉▉▉▉▉▉▉▉▉★  ☆          2.显示超市商品        ☆  ★▉▉▉▉▉▉▉▉▉" << endl;
			  cout << "▉▉▉▉▉▉▉▉▉★  ☆          3.排序统计商品        ☆  ★▉▉▉▉▉▉▉▉▉" << endl;
			  cout << "▉▉▉▉▉▉▉▉▉★  ☆          4.查找超市商品        ☆  ★▉▉▉▉▉▉▉▉▉" << endl;
			  cout << "▉▉▉▉▉▉▉▉▉★  ☆          5.删除超市商品        ☆  ★▉▉▉▉▉▉▉▉▉" << endl;
			  cout << "▉▉▉▉▉▉▉▉▉★  ☆          6.修改超市商品        ☆  ★▉▉▉▉▉▉▉▉▉" << endl;
			  cout << "▉▉▉▉▉▉▉▉▉★  ☆          7.售出超市商品        ☆  ★▉▉▉▉▉▉▉▉▉" << endl;
			  cout << "▉▉▉▉▉▉▉▉▉★  ☆        8.保存超市商品信息      ☆  ★▉▉▉▉▉▉▉▉▉" << endl;
			  cout << "▉▉▉▉▉▉▉▉▉★  ☆          0.安全退出系统        ☆  ★▉▉▉▉▉▉▉▉▉" << endl;

			  cout << "\t\t\n\t\t\t\t  请选择：0-8" << endl;
			  break; }
	case 3:
	{
			  system("cls");
			  cout << "********************************************************************************\n"
				  << "\t   1. 修改商品名      4. 修改进货价\t\t7. 修改净利润\n"
				  << "\t   2. 修改种类        5. 修改售出价\t\t8. 修改修改商品产地\n"
				  << "\t   3. 修改编号        6. 修改剩余商品量\t\t9. 修改生产商品牌\n"
				  << "\t\t\t\t10.修改全部\n"
				  << "********************************************************************************" << endl;
			  cout << "\t\t\n\t\t\t\t  请选择：0-10" << endl;
			  break;
	}
	case 4:
	{
			  system("cls");
			  cout << "********************************************************************************\n"
				  << "\t   1. 按进货价排序        2. 按库存量排序       3. 按净利润排序\n"
				  << "********************************************************************************" << endl;
			  cout << "\t\t\n\t\t\t\t  请选择：0-3" << endl;
			  break;
	}
	case 5:
	{
			  system("cls");
			  cout << "\n\t\t        *********************************\n";
			  cout << "\t\t        *****   1.按商品的名称查找  *****\n\t\t        *****    2.按商品编号查找   *****";
			  cout << "\n\t\t        *********************************\n请选择：0-2";
			  break;
	}
	}
}

void Goodsmessage::Find()       //﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌查找函数﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌
{
	system("cls");
	char name[20], Id[10];
	int x;
	Goods * p = NULL;
	showMenu(5);
	cin >> x;
	switch (x)
	{
	case 1:{cout << "\t\t请输入要查找的商品的名称："; cin >> name;
		if (p = FindItem(name))
		{
			p->Next->Show();
			cout << "输入任意字符！继续……";
			_getch();
		}
		else
		{
			cout << "\t\t没有找到该名称的商品！" << '\n' << endl;
			cout << "输入任意字符！继续……";
			_getch();
		}
	}break;
	case 2:
	{
			  cout << "\t\t请输入要查找的商品的编号："; cin >> Id;
			  if (p = FindID(Id))
			  {
				  p->Next->Show();
				  cout << "输入任意字符！继续……";
				  _getch();
			  }
			  else
			  {
				  cout << "\t\t没有找到该编号的商品！" << '\n' << endl;
				  cout << "输入任意字符！继续……";
				 _getch();
			  }
	}break;
	}
}

void Goodsmessage::ModifyItem()         //修改商品信息
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
			  cout << "\t\t请输入要修改的商品的编号:"; cin >> Id;
			  if (p = FindID(Id))
			  {
				  cout << "\t\t已找到商品的信息，请输入新的信息!" << endl;
				  p->Next->InputName();
				  cout << "修改成功！" << endl;
				  cout << "输入任意字符！继续……";
				 _getch();
			  }
			  else
			  {
				  cout << "\t\t没有找到您需要的商品!" << endl;
				  cout << "输入任意字符！继续……";
				  _getch();
			  }
			  break;
	}
	case 2:
	{
			  char Id[20];
			  Goods * p = NULL;
			  cout << "\t\t请输入要修改的商品的编号:"; cin >> Id;
			  if (p = FindID(Id))
			  {
				  cout << "\t\t已找到商品的信息，请输入新的信息!" << endl;
				  p->Next->InputKind();
				  cout << "修改成功！" << endl;
				  cout << "输入任意字符！继续……";
				  _getch();
			  }
			  else
			  {
				  cout << "\t\t没有找到您需要的商品!" << endl;
				  cout << "输入任意字符！继续……";
				  _getch();
			  }
			  break;
	}
	case 3:
	{
			  char Id[20];
			  Goods * p = NULL;
			  cout << "\t\t请输入要修改的商品的编号:"; cin >> Id;
			  if (p = FindID(Id))
			  {
				  cout << "\t\t已找到商品的信息，请输入新的信息!" << endl;
				  p->Next->InputID();
				  cout << "修改成功！" << endl;
				  cout << "输入任意字符！继续……";
				  _getch();
			  }
			  else
			  {
				  cout << "\t\t没有找到您需要的商品!" << endl;
				  cout << "输入任意字符！继续……";
				  _getch();
			  }
			  break;
	}
	case 4:
	{
			  char Id[20];
			  Goods * p = NULL;
			  cout << "\t\t请输入要修改的商品的编号:"; cin >> Id;
			  if (p = FindID(Id))
			  {
				  cout << "\t\t已找到商品的信息，请输入新的信息!" << endl;
				  p->Next->InputBuyprice();
				  cout << "修改成功！" << endl;
				  cout << "输入任意字符！继续……";
				  _getch();
			  }
			  else
			  {
				  cout << "\t\t没有找到您需要的商品!" << endl;
				  cout << "输入任意字符！继续……";
				  _getch();
			  }
			  break;
	}
	case 5:
	{
			  char Id[20];
			  Goods * p = NULL;
			  cout << "\t\t请输入要修改的商品的编号:"; cin >> Id;
			  if (p = FindID(Id))
			  {
				  cout << "\t\t已找到商品的信息，请输入新的信息!" << endl;
				  p->Next->InputSaleprice();
				  cout << "修改成功！" << endl;
				  cout << "输入任意字符！继续……";
				  _getch();
			  }
			  else
			  {
				  cout << "\t\t没有找到您需要的商品!" << endl;
				  cout << "输入任意字符！继续……";
				  _getch();
			  }
			  break;
	}
	case 6:
	{
			  char Id[20];
			  Goods * p = NULL;
			  cout << "\t\t请输入要修改的商品的编号:"; cin >> Id;
			  if (p = FindID(Id))
			  {
				  cout << "\t\t已找到商品的信息，请输入新的信息!" << endl;
				  p->Next->InputAmount();
				  cout << "修改成功！" << endl;
				  cout << "输入任意字符！继续……";
				  _getch();
			  }
			  else
			  {
				  cout << "\t\t没有找到您需要的商品!" << endl;
				  cout << "输入任意字符！继续……";
				  _getch();
			  }
			  break;
	}
	case 7:
	{
			  char Id[20];
			  Goods * p = NULL;
			  cout << "\t\t请输入要修改的商品的编号:"; cin >> Id;
			  if (p = FindID(Id))
			  {
				  cout << "\t\t已找到商品的信息，请输入新的信息!" << endl;
				  p->Next->InputProfit();
				  cout << "修改成功！" << endl;
				  cout << "输入任意字符！继续……";
				  _getch();
			  }
			  else
			  {
				  cout << "\t\t没有找到您需要的商品!" << endl;
				  cout << "输入任意字符！继续……";
				  _getch();
			  }
			  break;
	}
	case 8:
	{
			  char Id[20];
			  Goods * p = NULL;
			  cout << "\t\t请输入要修改的商品的编号:"; cin >> Id;
			  if (p = FindID(Id))
			  {
				  cout << "\t\t已找到商品的信息，请输入新的信息!" << endl;
				  p->Next->InputPlace();
				  cout << "修改成功！" << endl;
				  cout << "输入任意字符！继续……";
				 _getch();
			  }
			  else
			  {
				  cout << "\t\t没有找到您需要的商品!" << endl;
				  cout << "输入任意字符！继续……";
				  _getch();
			  }
			  break;
	}
	case 9:
	{
			  char Id[20];
			  Goods * p = NULL;
			  cout << "\t\t请输入要修改的商品的编号:"; cin >> Id;
			  if (p = FindID(Id))
			  {
				  cout << "\t\t已找到商品的信息，请输入新的信息!" << endl;
				  p->Next->Inputbrand();
				  cout << "修改成功！" << endl;
				  cout << "输入任意字符！继续……";
				  _getch();
			  }
			  else
			  {
				  cout << "\t\t没有找到您需要的商品!" << endl;
				  cout << "输入任意字符！继续……";
				  _getch();
			  }
			  break;
	}
	case 10:
	{
			   char Id[20];
			   Goods * p = NULL;
			   cout << "\t\t请输入要修改的商品的编号:"; cin >> Id;
			   if (p = FindID(Id))
			   {
				   cout << "\t\t已找到商品的信息，请输入新的信息!" << endl;
				   p->Next->InputAll();
				   cout << "修改成功！" << endl;
				   cout << "输入任意字符！继续……";
				   _getch();
			   }
			   else
			   {
				   cout << "\t\t没有找到您需要的商品!" << endl;
				   cout << "输入任意字符！继续……";
				   _getch();
			   }
	}
	}

}

void Goodsmessage::RemoveItem()          //﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌删除商品信息﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌
{
	system("cls");
	char Id[20];
	Goods * p = NULL, *temp = NULL;
	cout << "\t\t请输入要删除的商品的编号:" << endl; cin >> Id;
	if (p = FindID(Id))
	{
		temp = p->Next;
		p->Next = p->Next->Next;
		delete temp;
		cout << "\t\t删除成功!" << endl;
		cout << "输入任意字符！继续……";
		_getch();
	}
	else
	{
		cout << "\t\t没有找到您需要的商品!" << endl;
		cout << "输入任意字符！继续……";
		_getch();
	}
}
void Goodsmessage::Saleprice()           //﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌售出商品﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌
{
	system("cls");
	char Id[20]; int i;
	Goods * p = NULL;
	Goods * temp = NULL;
	cout << "\t\t请输入要售出的商品的编号和数量:" << endl; cin >> Id; cin >> i;

	if (p = FindID(Id))
	{
		if (p->Next->amount>i)
		{
			p->Next->amount -= i;
			p->Next->amount1 += i;
			p->Next->profit += i*(p->Next->saleprice - p->Next->buyprice);
			cout << "商品售出成功!" << "\n";
			cout << "售出商品编号: " << Id << "\t" << "数量: " << i << "\n";
			cout << "\n";
			cout << "售出后商品信息: " << endl;

			p->Next->Show();
			Save();
			cout << "输入任意字符！继续……";
			_getch();

		}
		else
		{
			cout << "商品数量不够，不能购买" << endl;
			cout << "输入任意字符！继续……";
			_getch();
			Saleprice();
		}

	}
	else
	{
		cout << "无此种商品，不能购买" << endl;
		cout << "输入任意字符！继续……";
		_getch();
		showMenu(2);
	}

}
void Goodsmessage::Swap(Goods *p1, Goods *p2)        //交换两个商品的数据
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

int Goodsmessage::ListCount()       //统计当前链表的记录总数，返回一个整数
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

void Goodsmessage::Paixu()       //﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌排序商品﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌
{
	showMenu(4);
	int x;
	cin >> x;
	switch (x)
	{
	case 1:
	{
			  system("cls");
			  cout << "\t\t排序中..." << endl;
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
			  out.open("进货价.txt");
			  for (Goods *q = Head->Next; q != End; q = q->Next)
				  out << q->name << "\t" << q->kind << "\t" << q->Id << "\t" << q->buyprice << "\t" << q->saleprice << "\t" << q->amount << "\t" << q->place << "\t" << q->brand << "\t" << q->profit << '\n';
			  out.close();
			  cout << "保存信息成功" << endl;
			  cout << "排序完成！" << endl;
			  _getch();
			  return;
	}
	case 2:
	{
			  system("cls");
			  cout << "\t\t排序中..." << endl;
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
			  out.open("库存量.txt");
			  for (Goods *q = Head->Next; q != End; q = q->Next)
				  out << q->name << "\t" << q->kind << "\t" << q->Id << "\t" << q->buyprice << "\t" << q->saleprice << "\t" << q->amount << "\t" << q->place << "\t" << q->brand << "\t" << q->profit << '\n';
			  out.close();
			  cout << "保存信息成功" << endl;
			  cout << "排序完成！" << endl;
			  _getch();
			  return;
	}
	case 3:
	{
			  system("cls");
			  cout << "\t\t排序中..." << endl;
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
			  out.open("净利润.txt");
			  for (Goods *q = Head->Next; q != End; q = q->Next)
				  out << q->name << "\t" << q->kind << "\t" << q->Id << "\t" << q->buyprice << "\t" << q->saleprice << "\t" << q->amount << "\t" << q->place << "\t" << q->brand << "\t" << q->profit << '\n';
			  out.close();
			  cout << "保存信息成功" << endl;
			  cout << "排序完成！" << endl;
			  _getch();
			  return;
	}
	}
}


void Goodsmessage::Save()       //﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌保存商品信息到文件函数﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌
{
	out.open("supermarket.txt");
	for (Goods *p = Head->Next; p != End; p = p->Next)
		out << p->name << "\t" << p->kind << "\t" << p->Id << "\t" << p->buyprice << "\t" << p->saleprice << "\t" << p->amount << "\t" << p->place << "\t" << p->brand << "\t" << p->profit << '\n';

	out.close();
	cout << "保存信息成功" << endl;
}


int main()
{
	cout << "\t\t" << endl;
	for (int i = 0; i<3; i++)
		cout << "\t\t￠\t\t\t\t\t\t￠" << endl; cout << "\t\t￠★★★★【欢迎进入超市商品管理系统】★★★★￠" << endl;
	for (int i = 0; i<3; i++)
		cout << "\t\t￠\t\t\t\t\t\t￠" << endl;
	cout << "\t\t$$\n" << endl;;
	Goodsmessage Grade;
	cout << "\t\t\t\t按任意键开始……";
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
