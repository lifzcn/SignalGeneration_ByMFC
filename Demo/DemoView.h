
// DemoView.h : CDemoView 类的接口
//

#pragma once

#include "resource.h"
#include "MyDLL.h"
#include "mscomm.h"
#include "afxwin.h"

class CDemoView : public CFormView
{
protected: // 仅从序列化创建
	CDemoView();
	DECLARE_DYNCREATE(CDemoView)

public:
	enum{ IDD = IDD_DEMO_FORM };

// 特性
public:
	CDemoDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedClose();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	double m_dblDataShow;
	int m_nWaveStyle;
	double m_pAmp;
	CScrollBar m_pAmp1;

	double m_pFreq;
	double m_pPhase;
	double m_pDuty;
	double m_SendData; ///发送出的数据
	CMscomm m_myComm;
	DECLARE_EVENTSINK_MAP()
	void OnCommMscomm();
	afx_msg void OnBnClickedSeropen();
	afx_msg void OnBnClickedSerclose();
	CComboBox m_PortNO;
	int m_nBaudRate;
	///double m_nTest;
	CString m_nTest;
	UINT16 CRC16(BYTE *ptr, int len);
	int m_pSampFreq;


//	afx_msg void OnBnClickedCSH();

	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnChangeBaudrate();
};

#ifndef _DEBUG  // DemoView.cpp 中的调试版本
inline CDemoDoc* CDemoView::GetDocument() const
   { return reinterpret_cast<CDemoDoc*>(m_pDocument); }
#endif

