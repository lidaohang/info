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


//二分查找(思路：一个low从0开始，一个high从指针长度开始,得到中间的长度跟value比较，如果大于value，在左边)
int search(int *a, int len, int value)
{
	int low = 0;
	int high = len - 1;
	for(low<=high) {
		int middle = (low+high)/2;
		if(a[middle] == value)
			return middle;
		else if(a[middle] > value) //左
			high = middle - 1;
		else //右
			low = middle + 1;
	}
	return -1;
}





/*
题目：
给出一棵排序二叉树根节点，将二叉树转化为有序的双向链表，只修改指针指向
显然这是个经典的题目，难点也不多，重在好好理解排序二叉树的特性和二叉树的递归性质。

解法:

思路：
排序二叉树既有特殊性left<root<right，同时又具备二叉树的递归性。
所以，将left和right子树分别转化完成后，root节点放在中间即可。
当需要转化left子树的时候
a)left == null，那么无需转化，head = root
b)left != null，那么head = leftHead；然后将left与root相接：root->left = leftTail, leftTail->right = root;

同样当需要转化right子树的时候
a)right = null，那么无需转化，tail = root;
b)right != null，那么tail = rightTail；然后将right与root相接: root->right = rightHead, rightHead->left = root;
*/
/*
将二叉排序树转化为有序的双向链表
*/
void converBitTreeToLinkedList(BitTree *root, BitTree *&head, BitTree *&tail)
{
    BitTree *lHead, *lTail, *rHead, *rTail;
    if(!root)
    {
        head = tail = null;
    }
    //转化左子树  
    if(!root->left)//左子树为空，简单的情况 
    {
        head = root;
    }
    else
    {
        //转化完左子树 
        converBitTreeToLinkedList(root->left, lHead, lTail);
        //获取整个双向链表的头部，最小的肯定在左子树 
        head = lHead;
        //将left与root相接 
        /*如何相接可能不好理解。首先，从root的两个分支中任意选一个指针(这里选的是left指针)指向left子树 
        （此时已经决定了转化右子树的时候只剩下一个分支可以用,这里剩下的是right指针）；然后根据递归的性质
        我们可以知道lTail也曾经是root节点，即left指针也已经被占用，所以应该用leftTail的右指针指向root 
        */ 
        root->left = lTail;
        lTail->right = root;
    }
    //转化右子树 
    if(!root->right)//右子树为空，简单的情况
    {
        tail = root;
    }
    else
    {
        //转化完右子树 
        converBitTreeToLinkedList(root->right, rHead, rTail);
        //获取整个双向链表的尾部，最大的肯定在右子树 
        tail = lTail;
        //将right与root相接 
        root->right = lHead;
        lHead->left = root;
    }
    return;
}
