#ifndef STR_H_H
#define STR_H_H
#define MAX_NUM 20
#define MAX_REL_NAME 20
#define MAX_ATTR_NAME 20
#define MAX_ERROR_MESSAGE 20
#define MAX_DATA 50

/*
�ļ�: str.h
����: the definition of sqls' structs
*/
#include<stdlib.h>
#include<string.h>
#include "RC.h"	//add by xmy 20200823 to unify retune code

//���Խṹ��
typedef struct  {
  char *relName;     // relation name (may be NULL) ����
  char *attrName;    // attribute name              ������
}RelAttr;

typedef enum {
	EQual,			//"="			0
	LEqual,			//"<="          1         
	NEqual,			//"<>"			2       
	LessT,			//"<"			3            
	GEqual,			//">="			4         
	GreatT,			//">"           5    
	NO_OP
}CompOp;

//����ֵ����
typedef enum {
		chars,
		ints,
		floats
}AttrType;
//����ֵ
typedef struct _Value Value;
struct _Value{
	AttrType type;     // type of value               
	void     *data;    // value    
};

typedef struct  _Condition Condition;
struct  _Condition{
  int     bLhsIsAttr;   // TRUE if left-hand side is an attribute 1ʱ���������ұ������ԣ�0ʱ��������ֵ
  Value   lhsValue;		// left-hand side value if bLhsIsAttr = FALSE 
  RelAttr lhsAttr;      // left-hand side attribute                     
  CompOp  op;           // comparison operator                          
  int     bRhsIsAttr;   // TRUE if right-hand side is an attribute 1ʱ���������ұ������ԣ�0ʱ��������ֵ
                        //   and not a value
  RelAttr rhsAttr;      // right-hand side attribute if bRhsIsAttr = TRUE �ұߵ�����
  Value   rhsValue;     // right-hand side value if bRhsIsAttr = FALSE 

};

//struct of select
typedef struct {
	int nSelAttrs;              	//Length of attrs in Select clause
	RelAttr *selAttrs[MAX_NUM];			//attrs in Select clause
	int nRelations;								//Length of relations in Fro clause
	char *relations[MAX_NUM];			//relations in From clause
	int nConditions;							//Length of conditions in Where clause 
	Condition conditions[MAX_NUM];//conditions in Where clause
}selects;

//struct of insert 
typedef struct {
	char *relName;				//Relation to insert into 
	int nValues;					//Length of values
	Value values[MAX_NUM];//values to insert
}inserts;

//struct of delete 
typedef struct {
	char *relName;										//Relation to delete from
	int nConditions;									//Length of conditions in Where clause 
	  Condition conditions[MAX_NUM];	//conditions in Where clause
}deletes;

//struct of update 
typedef struct {
	char *relName;					//Relation to update
	char *attrName;					//Attribute to update
	Value value;						//update value
	int nConditions;				//Length of conditions in Where clause 
	 Condition conditions[MAX_NUM];	// conditions in Where clause
}updates;

//struct of AttrInfo  
typedef struct _AttrInfo AttrInfo;
struct _AttrInfo{
	char *attrName;		//Attribute name
	AttrType attrType;		//Type of attribute
	int attrLength;		//Length of attribute
};
//struct of craete_table
typedef struct {
	char *relName;		//Relation name
	int attrCount;		//Length of attribute 
	AttrInfo attributes[MAX_NUM];	//attributes 
}createTable;

//struct of drop_table  
typedef struct {
	char *relName;		//Relation name
}dropTable;

//struct of create_index  
typedef struct {
	char *indexName;	// Index name
	char *relName;		// Relation name
	char *attrName;		// Attribute name
}createIndex;

//struct of  drop_index  
typedef struct {
	char *indexName;		// Index name

}dropIndex;

//union of sql_structs
union sqls{
	 selects sel;
	 inserts ins;
	 deletes del;
	 updates upd;
	 createTable cret;
	 dropTable drt;
	 createIndex crei;
	 dropIndex dri;
	 char *errors;
};


// struct of flag and sql_struct
typedef struct {
	int flag;	/*match to the sqls 0--error;1--select;2--insert;3--update;4--delete;5--create table;6--drop table;7--create index;8--drop index;9--help;10--exit;*/
 	union sqls sstr;
}sqlstr;

/* deleted by xmy 20200823 to unify return code
#ifndef RC_HH
#define RC_HH
typedef enum{
	SUCCESS,
	SQL_SYNTAX,
	PF_EXIST,
	PF_FILEERR,
	PF_INVALIDNAME,
	PF_WINDOWS,
	PF_FHCLOSED,
	PF_FHOPEN,
	PF_PHCLOSED,
	PF_PHOPEN,
	PF_NOBUF,
	PF_EOF,
	PF_INVALIDPAGENUM,
	PF_NOTINBUF,
	PF_PAGEPINNED,
	RM_FHCLOSED,
	RM_FHOPENNED,
	RM_INVALIDRECSIZE,
	RM_INVALIDRID,
	RM_FSCLOSED,
	RM_NOMORERECINMEM,
	RM_FSOPEN,
	IX_IHOPENNED,
	IX_IHCLOSED,
	IX_INVALIDKEY,
	IX_NOMEM,
	RM_NOMOREIDXINMEM,
	IX_EOF,
	IX_SCANCLOSED,
	IX_ISCLOSED,
	IX_NOMOREIDXINMEM,
	IX_SCANOPENNED,
	FAIL,

	DB_EXIST,
	DB_NOT_EXIST,
	NO_DB_OPENED,

	TABLE_NOT_EXIST,
	TABLE_EXIST,
	TABLE_NAME_ILLEGAL,

	FLIED_NOT_EXIST,
	FIELD_NAME_ILLEGAL,
	FIELD_MISSING,
	FIELD_REDUNDAN,
	FIELD_TYPE_MISMATCH,

	RECORD_NOT_EXIST,

	INDEX_NAME_REPEAT,
	INDEX_EXIST,
	INDEX_NOT_EXIST,
	INDEX_CREATE_FAILED,
	INDEX_DELETE_FAILED,

	INCORRECT_QUERY_RESULT,
	ABNORMAL_EXIT,

	TABLE_CREATE_REPEAT,
	TABLE_CREATE_FAILED,
	TABLE_COLUMN_ERROR,
	TABLE_ROW_ERROR,
	TABLE_DELETE_FAILED,

	DATABASE_FAILED
}RC;
#endif
*/

#ifdef __cplusplus
extern "C"{
	sqlstr * get_sqlstr();
	RC parse(char* st,sqlstr* sqln);
};
#endif
#endif
