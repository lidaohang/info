
typedef struct _NODE {
	int data;
	struct _NODE* next;
}NODE;

typedef struct _HASH_TABLE {
	NODE* value[10];
}HASH_TABLE;

//创建hash表
HASH_TABLE* create_hash_table() {

	HASH_TALBE* pHashTb1 = (HASH_TABLE*)malloc(sizeof(HASH_TABLE));
	memset(pHahsTbl,0,sizeof(HASH_TABLE));
	return pHashTbl;
}

//find
NODE* find_data_in_hash(HASH_TALBLE* pHashTbl,int data){

	NODE* pNode;
	if(NULL == pHashTbl)
		return NULL;
	if(NULL == (pNode = pHashTbl->value[data %10]))
		return NULL;

	while(pNode) {
		if(data == pNode->data)
			return pNode;
		pNode = pNode->next;
	}
	return NULL;
}

//insert
STATUS insert_data_into_hash(HASH_TABLE* pHashTbl,int data) {
	
	NODE* pNode;
	if(NULL == pHashTbl)
		return FALSE;
		
	if(NULL == pHashTbl->value[data%10]) {
		pNode =(NODE*)malloc(sizeof(NODE));
		memset(pNode,0,sizeof(NODE));
		pNode->data=data;
		pHashTbl->value[data%10]=pNode;
		return TRUE;
	}
	
	if(NULL != find_data_in_hash(pHashTbl,data))
		return FALSE;
	
	pNode=pHashTbl->value[data%10];
	while(NULL != pNode->next)
		pNode=pNode->next;
		
	pNode->next=(NODE*)malloc(sizeof(NODE));
	memset(pNode->next,0,sizeof(NODE));
	pNode->next->data=data;
	return TRUE;
}

//删除hash
STATUS delete_data_from_hash(HASH_TABLE* pHashTbl,int data)
{
	NODE* pHead;
	NODE* pNode;
	if(NULL == pHashTbl || NULL == pHashTbl->value[data%10])
		return FALSE;
		
	if(NULL == find_data_in_hash(pHashTbl,data))
		return FALSE;
		
	if(pNode == pHashTbl->value[data%10]){
		pHashTbl->value[data%10]=pNode->next;
		free(pNode);
	}
	
	pHead = pHashTbl->value[data%10];
	while(pNode != pHead->next)
		pHead=phead->next;
	pHead->next=pNode->next;
	return TRUE;
}
