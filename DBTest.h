#ifndef DBTEST_H_H
#define DBTEST_H_H
#include "IX_Manager.h"
#include "PF_Manager.h"
#include "RM_Manager.h"
#include "str.h"
#include "RC.h"

int TableTest(char tabname[][20],int *tabnum,char colname[][20][20],int colnum[],AttrType coltype[][20],int collength[][20],int coloffset[][20],int iscolindex[][20],char indexname[][20][20],char *temppath);
int TableContent(int *colNum, int *rowNum, AttrType colType[20], char unit[][20][100],char *dbname,char *tablename);
#endif