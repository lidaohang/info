//链表
typedef struct _LINK_NODE
{
	int data;
	struct _LINK_NODE* next;
}LINK_NODE;

//创建链表
LINK_NODE* alloca_node(int value)
{
	LINK_NODE *pLinkNode = NULL;
	pLinkNode = (LINK_NODE*)malloc(sizeof(LINK_NODE));
	
	pLinkNode->data = value;
	pLinkNode->next = NULL;
	return pLinkNode;
}

//delete link
void delete_node(LINK_NODE **pLinkNode)
{
	LINK_NODE **pNext;
	
	if ( NULL == pLinkNode || NULL == *pLinkNode)
		return NULL;
		
	pNext = &(*pLinkNode)->next;
	free(*pLinkNode);
	delete_node(pNext);
}

//插入链表
STATUS _add_data(LINK_NODE** pNode, LINK_NODE* pDataNode)
{
	if(NULL == *pNode) 
	{
		*pNode = pDataNode;
		return TRUE;
	}
	
	return _add_data(&(*pNode)->next,pDataNode);
}

STATUS add_data(const LINK_NODE** pNode, int value)
{
	LINK_NODE* pDataNode;
	if(NULL == *pNode)
		return FALSE;
		
	pDataNode = alloca_node(value);
	assert(NULL != pDataNode);
	return _add_data(LINK_NODE**)pNode,pDataNode);
}

//删除链表
STATUS _delete_data(LINK_NODE** pNode, int value)
{
	LINK_NODE* pLinkNode;
	if(NULL == (*pNode)->next)
		return FALSE;
		
	pLinkNode = (*pNode)->next;
	if(value == pLinkNode->data) {
		(*pNode)->next = pLinkNode->next;
		free(pLinkNode);
		return TRUE;
	} else {
		return _delete_data(&(*pNode)->next,value);
	}
}

STATUS delete_data(LINK_NODE** pNode, int value)
{
	LINK_NODE* pLinkNode;
	if(NULL == pNode || NULL == *pNode)
		return FALSE;
	
	if(value == (*pNode)->data) {
		pLinkNode = *pNode;
		*pNode = pLinkNode->next;
		free(pLinkNode);
		return TRUE;
	}
	
	return _delete_data(pNode,value);
}

//查找链表 
LINK_NODE* find_data(const LINK_NODE* pLinkNode, int value)
{
	if( NULL == pLinkNode )
		return NULL;
		
	if( value == pLinkNode->data )
		return (LINK_NODE*)pLinkNode;
	
	return find_data(pLinkNode->next,value);
}

//打印链表
void print_node(const LINK_NODE* pLinkNode)
{
	if(pLinkNode){
		printf("%d\n",pLinkNode->data);
		print_node(pLinkNode->next);
	}	
}

//count
int count_node(const LINK_NODE* pLinkNode) 
{
	if( NULL == pLinkNode)
		return 0;
	
	return 1 + count_node(pLinkNode->next);
}



//判断单链表是否有环(思路：一个步长1，一个步长2，n圈之后如果有环，必定相遇)
int circle(LINK_NODE *node)
{
	int slow = node;
	int last = node;
	while(last != NULL && last->next != NULL) {
		slow = slow->next;
		last = last->next->next;
		if(slow == last)
			return 1;
	}
	return 0;
}

//判断两个单链表是否相交(思路：如果两个单链表相交必定是Y字形，只需要把长的链表先走多的这部分，然后让两个链表一步一步走，如果相交必定相遇)
int get_link_len(LINK_NODE* node)
{
	int count = 0;
	if(node == NULL)
		return count;
	return get_link_len(node->next) + 1;	
}
int check(LINK_NODE* nodeA,LINK_NODE* nodeB)
{
	int lenA = get_link_len(nodeA);
	int lenB = get_link_len(nodeB);
	if(lenA>lenB) {
		for(int i=0;i<lenA-lenB;++i)
			nodeA=nodeA->next;
	}else {
		for(int i=0;i<lenB-lenA;++i,)
			nodeB=nodeB->next;
	}
	for(nodeA && nodeB && nodeA != nodeB){
		nodeA=nodeA->next;
		nodeB=nodeB->next;
	}
	return nodeA == nodeB ? 1 : 0;
}



//使用三个指针遍历单链表，逐个链接点进行反转。
Node * ReverseList(Node *head)
{
	Node *p1,*p2,*p3;
	if(head==NULL||*head==NULL)
	return head;
	p1=head;
	p2=p1->next;
	while(p2)             //注意条件
	{
		p3=p2->next;	      //要改变p2->next的指针，所以必须先保留p2->next	     
		p2->next=p1;
		p1=p2;		      //循环往后
		p2=p3;
	}
	head->next=NULL;   //原先的head已经变成tail，别忘了置空，只有到这步才能置空
	*head=p1;
	return head;
}
