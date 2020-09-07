#include "RM_Manager.h"
#include "str.h"


RC OpenScan(RM_FileScan *rmFileScan, RM_FileHandle *fileHandle, int conNum, Con *conditions)//³õÊ¼»¯É¨Ãè
{
	return FAIL;
}

RC CloseScan(RM_FileScan* rmFileScan) {
	return FAIL;
}
RC GetNextRec(RM_FileScan *rmFileScan, RM_Record *rec)
{
	return FAIL;
}

RC GetRec(RM_FileHandle *fileHandle, RID *rid, RM_Record *rec)
{
	return FAIL;
}

RC InsertRec(RM_FileHandle *fileHandle, char *pData, RID *rid)
{
	return FAIL;
}

RC DeleteRec(RM_FileHandle *fileHandle, const RID *rid)
{
	return FAIL;
}

RC UpdateRec(RM_FileHandle *fileHandle, const RM_Record *rec)
{
	return FAIL;
}

RC RM_CreateFile(char *fileName, int recordSize)
{
	return FAIL;
}

RC RM_OpenFile(char *fileName, RM_FileHandle *fileHandle)
{
	return FAIL;
}

RC RM_CloseFile(RM_FileHandle *fileHandle)
{
	return FAIL;
}