
// MCADoc.h : CMCADoc 类的接口
//


#pragma once


class CMCADoc : public CDocument
{
protected: // 仅从序列化创建
	CMCADoc();
	DECLARE_DYNCREATE(CMCADoc)

// 特性
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
	int mult;//记录因为超出量程导致的计数减半
	int total_channel;
	CEdit m_EditChannel;
	//int m_nChannel;
	CEdit m_EditCount;
	CEdit m_EditDetailSum;
	
	
	
	


// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CMCADoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
