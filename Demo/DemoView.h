
// DemoView.h : CDemoView ��Ľӿ�
//

#pragma once

#include "resource.h"
#include "MyDLL.h"
#include "mscomm.h"
#include "afxwin.h"

class CDemoView : public CFormView
{
protected: // �������л�����
	CDemoView();
	DECLARE_DYNCREATE(CDemoView)

public:
	enum{ IDD = IDD_DEMO_FORM };

// ����
public:
	CDemoDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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
	double m_SendData; ///���ͳ�������
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

#ifndef _DEBUG  // DemoView.cpp �еĵ��԰汾
inline CDemoDoc* CDemoView::GetDocument() const
   { return reinterpret_cast<CDemoDoc*>(m_pDocument); }
#endif

