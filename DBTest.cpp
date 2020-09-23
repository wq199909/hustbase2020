#include "DBTest.h"
#include "QU_Manager.h"
#include "SYS_Manager.h"
#include <direct.h>
#include <iostream>
#pragma warning(disable : 4996)
//update by zjh 20191224 解决GetNextRec前未申请空间问题
int TableTest(
	char tabname[][20],
	int *tabnum,
	char colname[][20][20],
	int colnum[],
	AttrType coltype[][20],
	int collength[][20],
	int coloffset[][20],
	int iscolindex[][20],
	char indexname[][20][20],
	char *temppath
)
{
	RM_FileHandle fileHandle, colfilehandle;
	fileHandle.bOpen = 0;
	colfilehandle.bOpen = 0;
	RM_FileScan FileScan1, FileScan2;
	FileScan1.bOpen = 0;
	FileScan2.bOpen = 0;
	RM_Record rec1, rec2;
	Con condition;
	RC rc;

	int i = 0, j = 0;
	char table[512], column[512];
	if (!strcmp(temppath, "")) {
		return -1;
	}
	else {
		strcpy(table, temppath);
		strcpy(column, temppath);
		strcat(table, "\\SYSTABLES");
		strcat(column, "\\SYSCOLUMNS");
	}

	rc = RM_OpenFile(table, &fileHandle);//去SYSTABLES表中获取表名
	if (rc != SUCCESS) {
		return -1;
	}
	rc = RM_OpenFile(column, &colfilehandle);//去SYSCOLUMNS表中获取列名
	if (rc != SUCCESS) {
		return -1;
	}
	rc = OpenScan(&FileScan1, &fileHandle, 0, NULL);
	if (rc != SUCCESS) {
		return -1;
	}
	rec1.pData = new char[25];//25=SIZE_SYS_TABLE
	memset(rec1.pData, 0, 25);
	rec2.pData = new char[76];//76=SIZE_SYS_COLUMNS
	memset(rec2.pData, 0, 76);
	while (GetNextRec(&FileScan1, &rec1) == SUCCESS)
	{
		strcpy(tabname[i], rec1.pData);
		condition.bLhsIsAttr = 1;
		condition.bRhsIsAttr = 0;
		condition.LattrLength = strlen(tabname[i]);
		condition.RattrLength = strlen(tabname[i]);
		condition.LattrOffset = 0;
		condition.attrType = chars;
		condition.compOp = EQual;
		condition.Rvalue = tabname[i];
		rc = OpenScan(&FileScan2, &colfilehandle, 1, &condition);
		if (rc != SUCCESS) {
			return -1;
		}
		RC rc;
		while ((rc = GetNextRec(&FileScan2, &rec2)) == SUCCESS)
		{
			strcpy(colname[i][j], rec2.pData + 21);
			memcpy(&coltype[i][j], rec2.pData + 42, sizeof(AttrType));
			memcpy(&collength[i][j], rec2.pData + 46, sizeof(int));
			memcpy(&coloffset[i][j], rec2.pData + 50, sizeof(int));
			if (*(rec2.pData + 54) == '1') {
				iscolindex[i][j] = 1;
				strcpy(indexname[i][j], rec2.pData + 55);
			}
			else {
				iscolindex[i][j] = 0;
				strcpy(indexname[i][j], "\0");
			}

			j++;
		}
		colnum[i] = j;
		j = 0;
		i++;
		FileScan2.bOpen = 0;
	}
	*tabnum = i;
	rc = RM_CloseFile(&fileHandle);
	if (rc != SUCCESS) {
		return -1;
	}
	rc = RM_CloseFile(&colfilehandle);
	if (rc != SUCCESS) {
		return -1;
	}
	return 1;
}

//update by zjh 20191224 解决GetNextRec前未申请空间、colType应提前初始化问题
int TableContent(int *colNum, int *rowNum, AttrType colType[20], char unit[][20][100], char *dbname, char *tablename)
{
	RM_FileHandle fileHandle;
	fileHandle.bOpen = 0;
	RC rc;
	RM_Record rec;
	RM_FileScan FileScan;
	FileScan.bOpen = 0;
	Con condition;
	*rowNum = 0;
	char tabname[20][20];
	char colname[20][20][20];
	AttrType coltype[20][20];
	int tabnum, colnum[20];
	int collength[20][20];
	int coloffset[20][20];
	int iscolix[20][20];
	char indexname[20][20][20];
	int i, j, k = 0;
	char path[512];
	strcpy(path, dbname);
	strcat(path, "\\SYSTABLES");
	rc = RM_OpenFile(path, &fileHandle);//去SYSTABLES表中获取表名
	if (rc != SUCCESS)
	{
		return -1;
	}
	condition.bLhsIsAttr = 1;
	condition.bRhsIsAttr = 0;
	condition.LattrOffset = 0;
	condition.LattrLength = 20;
	condition.RattrLength = 20;
	condition.attrType = chars;
	condition.compOp = EQual;
	condition.Rvalue = tablename;

	rc = OpenScan(&FileScan, &fileHandle, 1, &condition);
	if (rc != SUCCESS) {
		return -1;
	}
	rec.pData = new char[76];//76=SIZE_SYS_COLUMNS
	rc = GetNextRec(&FileScan, &rec);
	if (rc != SUCCESS)//点击的不是表名，不做显示处理
	{
		rc = RM_CloseFile(&fileHandle);
		if (rc != SUCCESS)
			return -1;
	}
	rc = RM_CloseFile(&fileHandle);
	if (rc != SUCCESS) {
		return -1;
	}


	int rc1 = TableTest(tabname, &tabnum, colname, colnum, coltype, collength, coloffset, iscolix, indexname, dbname);

	for (i = 0; i < tabnum; i++)
	{
		if (strcmp(tablename, tabname[i]) == 0)
			break;
	}
	fileHandle.bOpen = 0;
	char temp1[100];
	strcpy(temp1, dbname);
	strcat(temp1, "\\");
	strcat(temp1, tablename);
	rc = RM_OpenFile(temp1, &fileHandle);
	if (rc != SUCCESS) {
		return -1;
	}
	FileScan.bOpen = 0;
	rc = OpenScan(&FileScan, &fileHandle, 0, NULL);
	if (rc != SUCCESS) {
		return -1;
	}
	if (!rec.pData) {
		rec.pData = new char[76];//76=SIZE_SYS_COLUMNS
	}
	*colNum = colnum[i];
	for (j = 0; j < colnum[i]; j++)
	{
		//memcpy(&colType[j],&(coltype[i][j]),sizeof(AttrType));
		colType[j] = coltype[i][j];
	}
	while (GetNextRec(&FileScan, &rec) == SUCCESS)
	{
		for (j = 0; j < colnum[i]; j++)
		{
			if (coltype[i][j] == chars)
			{
				char temp[21];
				memcpy(temp, rec.pData + coloffset[i][j], collength[i][j]);
				strcpy((unit)[*rowNum][j], temp);
			}
			else if (coltype[i][j] == ints)
			{
				int temp;
				memcpy(&temp, rec.pData + coloffset[i][j], sizeof(int));
				char buff[64];
				sprintf(buff, "%d", temp);
				strcpy((unit)[*rowNum][j], buff);
			}
			else if (coltype[i][j] == floats)
			{
				float temp;
				memcpy(&temp, rec.pData + coloffset[i][j], sizeof(float));
				char buff[64];
				sprintf(buff, "%f", temp);
				strcpy((unit)[*rowNum][j], buff);
			}
		}
		(*rowNum)++;
	}
	rc = RM_CloseFile(&fileHandle);
	if (rc != SUCCESS) {
		return -1;
	}
	return 1;
}
