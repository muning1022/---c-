
singlenode* getcirclenode(singlenode* head)//得到入环节点法一： 哈希表做法
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
singlenode* getcirclenode2(singlenode* head)//得到入环节点的法二：定义两个指针的做法。如果快慢重合，快回到开头，改为走一个，当他们再相交时，就是入环节点 玄学
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
//这个是主程序了

singlenode* No_node(singlenode* head1, singlenode* head2)//判断两个无环单链表的相交问题
{
	//******************************************************************************
	//第一种方法是把head1全部存在哈希表里，然后遍历head2，判断当前节点是否在哈希表里
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
	//第二种方法   遍历得到两个链表的尾节点 ，如果尾节点不等，直接不想交，否则 然后让长的链表先走一个长度长度插值，然后一起走，得到的第一个节点就是相交节点
	singlenode *ptr1 = head1;
	singlenode *ptr2 = head2;
	int length1 = 0;
	int length2 = 0;
	while (ptr1->m_Next!= nullptr)
	{
		length1++;
		ptr1 = ptr1->m_Next;//得到第一个尾节点
	}
	while (ptr2->m_Next != nullptr)
	{
		length2++;
		ptr2 = ptr2->m_Next;//得到第二个尾节点
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


singlenode* Both_node(singlenode* head1, singlenode*loop1, singlenode* head2, singlenode*loop2)//判断两个环形链表的相交情况
{
	singlenode* r_next1 = loop1->m_Next;
	singlenode* r_next2 = loop2->m_Next;
	if (loop1 == loop2)
	{
		loop1->m_Next = nullptr;
		loop2->m_Next = nullptr;
		return No_node(head1, head2);
		loop1->m_Next = r_next1;
		loop2->m_Next = r_next2;//续上节点
	}

		//第一种\ /
		//		O
	singlenode* ptr = loop1->m_Next;
	while (loop1 != ptr)
	{
		if (ptr == loop2)
			//return loop2;
			return loop1;//这里loop1离子链1较近，loop2离子链2较近
		ptr = ptr->m_Next;
	}
	//第二种 6 6
	return nullptr;
}


singlenode* GetInsertNode(singlenode* head1, singlenode* head2)
{
	singlenode* loop1 = getcirclenode2(head1);
	singlenode* loop2 = getcirclenode2(head2);
	if (loop1 == nullptr&&loop2 == nullptr)
	{
		return No_node(head1,head2);//两个都没有环
	}
	if (loop1 != nullptr&&loop2 != nullptr)
	{
		return Both_node(head1,loop1,head2,loop2);//两个都有环
	}
	return nullptr;//一环一线不可能相交
}
