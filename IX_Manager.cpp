#include "IX_Manager.h"

RC CreateIndex(const char * fileName, AttrType attrType, int attrLength)
{
	return RC();
}

RC OpenIndex(const char * fileName, IX_IndexHandle * indexHandle)
{
	return RC();
}

RC CloseIndex(IX_IndexHandle * indexHandle)
{
	return RC();
}

RC InsertEntry(IX_IndexHandle * indexHandle, void * pData, const RID * rid)
{
	return RC();
}

RC DeleteEntry(IX_IndexHandle * indexHandle, void * pData, const RID * rid)
{
	return RC();
}

RC OpenIndexScan(IX_IndexScan *indexScan,IX_IndexHandle *indexHandle,CompOp compOp,char *value){
	return SUCCESS;
}

RC IX_GetNextEntry(IX_IndexScan *indexScan,RID * rid){
	return SUCCESS;
}

RC CloseIndexScan(IX_IndexScan *indexScan){
		return SUCCESS;
}

RC GetIndexTree(char *fileName, Tree *index){
		return SUCCESS;
}


