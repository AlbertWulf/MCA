
// MCADoc.h : CMCADoc ��Ľӿ�
//


#pragma once


class CMCADoc : public CDocument
{
protected: // �������л�����
	CMCADoc();
	DECLARE_DYNCREATE(CMCADoc)

// ����
public:
	int m_Dot[1024];
	int num_channel ;
	int Data[1024];
	int lbtn_beg;
	int lbtn_end;
	int mouse_now;
	int m_nChannel;
	int m_nCount;
	int m_nDetailSum;
	int cha;
	int gap;
	int total_mouse_pos;
	int mult;//��¼��Ϊ�������̵��µļ�������
	int total_channel;
	CEdit m_EditChannel;
	//int m_nChannel;
	CEdit m_EditCount;
	CEdit m_EditDetailSum;
	
	
	
	


// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CMCADoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
