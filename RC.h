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
	PF_OPEN_TOO_MANY_FILES,	//add by hzh 20200112
	PF_ILLEGAL_FILE_ID,		//add by hzh 20200112
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

	DB_EXIST,			//���ݿ��Ѵ���
	DB_NOT_EXIST,		//���ݿⲻ����
	NO_DB_OPENED,		//���ݿ�δ��

	TABLE_NOT_EXIST,	//������
	TABLE_EXIST,		//���Ѵ���
	TABLE_NAME_ILLEGAL,	//�����Ƿ�

	FLIED_NOT_EXIST,	//�ֶβ�����
	FLIED_EXIST,		//�ֶ��Ѵ���add by xmy 20191216
	FIELD_NAME_ILLEGAL,	//�ֶ����Ƿ�
	FIELD_MISSING,		//����ֵ�е��ֶβ���
	FIELD_REDUNDAN,		//����ֵ�е��ֶ�̫��
	FIELD_TYPE_MISMATCH,//����ֵ���ֶ����Ͳ�ƥ��

	RECORD_NOT_EXIST,	//��һ�������ڵļ�¼����ɾ��ʱ

	INDEX_NAME_REPEAT,	//�������ظ�
	INDEX_EXIST,		//��ָ���ֶ����Ѵ�������
	INDEX_NOT_EXIST,	//����������
	INDEX_NAME_ILLEGAL,	//�������Ƿ�add by xmy 20191216

	//���·�������Autotest����ʹ��
	ABNORMAL_EXIT,			//�쳣�˳�
	DATABASE_FAILED,		//���ݿⴴ����ɾ��ʧ��
	TABLE_CREATE_REPEAT,	//���ظ�����
	TABLE_CREATE_FAILED,	//������ʧ��
	TABLE_COLUMN_ERROR,		//����/����/������/�г��ȴ���
	TABLE_ROW_ERROR,		//��������
	TABLE_DELETE_FAILED,	//��ɾ��ʧ��
	INCORRECT_QUERY_RESULT,	//��ѯ�������
	INDEX_CREATE_FAILED,	//��������ʧ��
	INDEX_DELETE_FAILED,	//����ɾ��ʧ��
	GET_INDEX_TREE_FAILED,	//��ȡ������ʧ��
	ILLEGAL_INDEX_TREE		//��������Ԥ�ڲ�һ��
	
	/*�������������룬�����һ�п�ʼ��ӣ���Ҫ��ǰ����룬����AutoTest�����жϴ���*/

}RC;

#endif
