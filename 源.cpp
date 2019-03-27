#include <iostream>
#include "singlenode.h"
#include<map>
#include<cmath>
using namespace std;

singlenode* CreateNode(int nValue)//ÿ����һ���ڵ㣬������ָ�붼ָ��
{
	singlenode* pNode = new singlenode();

	pNode->m_Value = nValue;
	pNode->m_Next = nullptr;

	return pNode;
}
void PrintList(singlenode* pHead)
{
	singlenode* pNode = pHead;
	while (pNode != nullptr)
	{
		printf("The value of this node is: %d.\n", pNode->m_Value);
		if (pNode->m_Next != nullptr)
			cout << "The value of its next is: " << pNode->m_Next->m_Value << endl;
		pNode = pNode->m_Next;
	}
}
void BuildNodes(singlenode* pNode, singlenode* pNext)
{
	if (pNode != nullptr)
	{
		pNode->m_Next = pNext;
	}
}
singlenode* getcirclenode(singlenode* head)//�õ��뻷�ڵ㷨һ�� ��ϣ������
{
	singlenode *ptr = head;
	map<singlenode*, int>  lmap;
	while (ptr != nullptr)
	{
		if (lmap.find(ptr) != lmap.end()){
			return ptr;
		}else{
			lmap.insert(make_pair(ptr, 1));
		}
		ptr = ptr->m_Next;
	}
}
singlenode* getcirclenode2(singlenode* head)//�õ��뻷�ڵ�ķ�������������ָ�����������������غϣ���ص���ͷ����Ϊ��һ�������������ཻʱ�������뻷�ڵ� ��ѧ
{
	if (head == nullptr || head->m_Next == nullptr)
		return nullptr;
	singlenode* sptr = head->m_Next;
	singlenode* fptr = head->m_Next->m_Next;
	int num = 0;
	while (sptr!=fptr)
	{
		if (fptr->m_Next == nullptr || fptr->m_Next->m_Next == nullptr)
			return nullptr;
		fptr = fptr->m_Next->m_Next;
		sptr = sptr->m_Next;
	}
	fptr = head;
	while (fptr != sptr)
	{
		fptr = fptr->m_Next;
		sptr = sptr->m_Next;
	}
	return sptr;
}
//�������������

singlenode* No_node(singlenode* head1, singlenode* head2)//�ж������޻���������ཻ����
{
	//******************************************************************************
	//��һ�ַ����ǰ�head1ȫ�����ڹ�ϣ���Ȼ�����head2���жϵ�ǰ�ڵ��Ƿ��ڹ�ϣ����
	//singlenode *ptr1 = head1;
	//singlenode *ptr2 = head2;
	//map<singlenode*, int> lmap;
	//while (ptr1!=nullptr)
	//{
	//	lmap.insert(make_pair(ptr1, 1));
	//	ptr1 = ptr1->m_Next;
	//}
	//while (ptr2 != nullptr)
	//{
	//	if (lmap.find(ptr2) != lmap.end())
	//		return ptr2;
	//	ptr2 = ptr2->m_Next;
	//}
	//return nullptr;
	//*************************************************************************************
	//�ڶ��ַ���   �����õ����������β�ڵ� �����β�ڵ㲻�ȣ�ֱ�Ӳ��뽻������ Ȼ���ó�����������һ�����ȳ��Ȳ�ֵ��Ȼ��һ���ߣ��õ��ĵ�һ���ڵ�����ཻ�ڵ�
	singlenode *ptr1 = head1;
	singlenode *ptr2 = head2;
	int length1 = 0;
	int length2 = 0;
	while (ptr1->m_Next!= nullptr)
	{
		length1++;
		ptr1 = ptr1->m_Next;//�õ���һ��β�ڵ�
	}
	while (ptr2->m_Next != nullptr)
	{
		length2++;
		ptr2 = ptr2->m_Next;//�õ��ڶ���β�ڵ�
	}
	if (ptr1 != ptr2)
		return nullptr;
	ptr1 = head1;
	ptr2 = head2;
	int diff = abs(length1 - length2);
	if (length1 > length2)
	{
		while (diff){
			ptr1 = ptr1->m_Next;
			diff--;
		}
	}else{
		while (diff){
			ptr2 = ptr2->m_Next;
			diff--;
		}
	}
	while (ptr1 != ptr2)
	{
		ptr1 = ptr1->m_Next;
		ptr2 = ptr2->m_Next;
	}
	return ptr1;
}


singlenode* Both_node(singlenode* head1, singlenode*loop1, singlenode* head2, singlenode*loop2)
{
	singlenode* r_next1 = loop1->m_Next;
	singlenode* r_next2 = loop2->m_Next;
	if (loop1 == loop2)
	{
		loop1->m_Next = nullptr;
		loop2->m_Next = nullptr;
		return No_node(head1, head2);
		loop1->m_Next = r_next1;
		loop2->m_Next = r_next2;//���Ͻڵ�
	}

		//��һ��\ /
		//		O
	singlenode* ptr = loop1->m_Next;
	while (loop1 != ptr)
	{
		if (ptr == loop2)
			//return loop2;
			return loop1;//����loop1������1�Ͻ���loop2������2�Ͻ�
		ptr = ptr->m_Next;
	}
	//�ڶ��� 6 6
	return nullptr;
}


singlenode* GetInsertNode(singlenode* head1, singlenode* head2)
{
	singlenode* loop1 = getcirclenode2(head1);
	singlenode* loop2 = getcirclenode2(head2);
	if (loop1 == nullptr&&loop2 == nullptr)
	{
		return No_node(head1,head2);//������û�л�
	}
	if (loop1 != nullptr&&loop2 != nullptr)
	{
		return Both_node(head1,loop1,head2,loop2);//�������л�
	}
	return nullptr;//һ��һ�߲������ཻ
}

void test01()
{
	//��һ���л�����,
	singlenode* pNode1 = CreateNode(1);
	singlenode* pNode2 = CreateNode(2);
	singlenode* pNode3 = CreateNode(3);
	singlenode* pNode4 = CreateNode(4);
	singlenode* pNode5 = CreateNode(5);
	BuildNodes(pNode1, pNode2);
	BuildNodes(pNode2, pNode3);
	BuildNodes(pNode3, pNode4);
	BuildNodes(pNode4, pNode5);
	BuildNodes(pNode5, pNode3);

	cout << "��ӡ��һ���ظ��ڵ�" << endl;
	cout<<getcirclenode(pNode1)->m_Value<<endl;
	//�ڶ����л�����,
	singlenode* pNode11 = CreateNode(13);
	singlenode* pNode21 = CreateNode(24);
	singlenode* pNode31 = CreateNode(35);
	singlenode* pNode41 = CreateNode(44);
	singlenode* pNode51 = CreateNode(65);
	BuildNodes(pNode11, pNode21);
	BuildNodes(pNode21, pNode31);
	BuildNodes(pNode31, pNode41);
	BuildNodes(pNode41, pNode51);
	BuildNodes(pNode51, pNode21);

	//cout << "��ӡ��һ���ظ��ڵ�" << endl;
	//cout << getcirclenode(pNode11)->m_Value << endl;

	//�������л�����,�����һ������\O/��
	singlenode* pNode12 = CreateNode(13);
	singlenode* pNode22 = CreateNode(24);
	singlenode* pNode32 = pNode3;
	singlenode* pNode42 = pNode4;
	singlenode* pNode52 = pNode5;
	BuildNodes(pNode12, pNode42);
	BuildNodes(pNode42, pNode32);
	BuildNodes(pNode32, pNode22);
	BuildNodes(pNode22, pNode52);
	BuildNodes(pNode52, pNode42);
	cout << "��ӡ��һ���ظ��ڵ�" << endl;
	cout << getcirclenode(pNode12)->m_Value << endl;
	//��һ���޻�����
	singlenode* pNodea = CreateNode(31);
	singlenode* pNodeb = CreateNode(25);
	singlenode* pNodec = CreateNode(37);
	singlenode* pNoded = CreateNode(49);
	singlenode* pNodee = CreateNode(45);
	BuildNodes(pNodea, pNodeb);
	BuildNodes(pNodeb, pNodec);
	BuildNodes(pNodec, pNoded);
	BuildNodes(pNoded, pNodee);
	BuildNodes(pNodee, nullptr);

	//�ڶ����޻��������������ཻ��
	singlenode* pNodea1 = CreateNode(15);
	singlenode* pNodeb1 = CreateNode(27);
	singlenode* pNodec1 = pNodec;
	singlenode* pNoded1 = pNoded;
	singlenode* pNodee1 = pNodee; 

	BuildNodes(pNodea1, pNodeb1);
	BuildNodes(pNodeb1, pNodec1);
	BuildNodes(pNodec1, pNoded1);
	BuildNodes(pNoded1, pNodee1);
	BuildNodes(pNodee1, nullptr);

	//�������޻����� (�����治�ཻ)
	singlenode* pNodea2 = CreateNode(100);
	singlenode* pNodeb2 = CreateNode(101);
	singlenode* pNodec2 = CreateNode(103);
	singlenode* pNoded2 = CreateNode(149);
	singlenode* pNodee2 = CreateNode(435);
	BuildNodes(pNodea2, pNodeb2);
	BuildNodes(pNodeb2, pNodec2);
	BuildNodes(pNodec2, pNoded2);
	BuildNodes(pNoded2, pNodee2);
	BuildNodes(pNodee2, nullptr);

	//�õ�������ཻ�ڵ�
	cout << "�õ�������ཻ�ڵ�" << endl;
	singlenode *res = GetInsertNode(pNode1, pNodea2);
	if (res == nullptr){
		cout << "���ཻ" << endl;
	}else{
		cout << res->m_Value << endl;
	}


	//cout << "��ӡ��һ���ظ��ڵ�" << endl;
	//cout<<getcirclenode(pNode1)->m_Value<<endl;
	//cout << getcirclenode2(pNode1)->m_Value << endl;
	//PrintList(pNode1);//�������Ҫ��ӡ�Ļ������ǳ���ѭ����ӡ��
}

int main()
{	
	test01();
	system("pause");
	return 0;
}