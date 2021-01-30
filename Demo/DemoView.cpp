
// DemoView.cpp : CDemoView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Demo.h"
#endif

#include "DemoDoc.h"
#include "DemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif




// CDemoView

IMPLEMENT_DYNCREATE(CDemoView, CFormView)

BEGIN_MESSAGE_MAP(CDemoView, CFormView)
	ON_BN_CLICKED(IDC_OPEN, &CDemoView::OnBnClickedOpen)
	ON_BN_CLICKED(IDC_CLOSE, &CDemoView::OnBnClickedClose)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_SEROPEN, &CDemoView::OnBnClickedSeropen)
	ON_BN_CLICKED(IDC_SERCLOSE, &CDemoView::OnBnClickedSerclose)

	//(IDC_CSH, &CDemoView::OnBnClickedCSH)

	ON_WM_HSCROLL()
END_MESSAGE_MAP()

// CDemoView 构造/析构

CDemoView::CDemoView()
	: CFormView(CDemoView::IDD)
	, m_dblDataShow(0)
	, m_nWaveStyle(0)
	, m_pAmp(1)
	, m_pFreq(2.00)
	, m_pPhase(0.00)
	, m_pDuty(0.5)
	, m_nBaudRate(9600)
	, m_nTest(_T(""))
	, m_pSampFreq(100)
{
	// TODO:  在此处添加构造代码
	
}

CDemoView::~CDemoView()
{
}

void CDemoView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DATASHOW, m_dblDataShow);
	DDX_Radio(pDX, IDC_SIN, m_nWaveStyle);
	DDX_Text(pDX, IDC_PAMP, m_pAmp);
	DDX_Text(pDX, IDC_PFREQ, m_pFreq);
	DDX_Text(pDX, IDC_PPHASE, m_pPhase);
	DDX_Text(pDX, IDC_PDUTY, m_pDuty);
	DDX_Control(pDX, IDC_MSCOMM, m_myComm);
	DDX_Control(pDX, IDC_PORTNO, m_PortNO);
	DDX_Text(pDX, IDC_BAUDRATE, m_nBaudRate);
	DDX_Text(pDX, IDC_TEST, m_nTest);
	DDX_Text(pDX, IDC_PSAMPFREQ, m_pSampFreq);

}

BOOL CDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CFormView::PreCreateWindow(cs);
}

void CDemoView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	//初始化串口控件
	m_myComm.put__CommPort(1); // 选择COM7
	m_myComm.put_InBufferSize(1024); // 接收缓冲区
	m_myComm.put_OutBufferSize(1024); // 发送缓冲区
	m_myComm.put_InputLen(0); // 设置接收缓冲区数据长度为0，表示全部读取
	m_myComm.put_InputMode(1); // 以二进制方式读写数据
	m_myComm.put_RThreshold(1); // 接收缓冲区有1个以上字符时将引发接收数据的OnComm事件
	m_myComm.put_Settings(_T("9600,n,8,1"));// 波特率9600，无校验，数据位8，停止位1

	//串口组合框初始化
	m_PortNO.AddString(_T("COM1"));
	m_PortNO.AddString(_T("COM2"));
	m_PortNO.AddString(_T("COM3"));
	m_PortNO.AddString(_T("COM4"));
	m_PortNO.AddString(_T("COM5"));
	m_PortNO.AddString(_T("COM6"));
	m_PortNO.AddString(_T("COM7"));
	m_PortNO.AddString(_T("COM8"));
	m_PortNO.SetCurSel(6);
}

// CDemoView 诊断

#ifdef _DEBUG
void CDemoView::AssertValid() const
{
	CFormView::AssertValid();
}

void CDemoView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CDemoDoc* CDemoView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDemoDoc)));
	return (CDemoDoc*)m_pDocument;
}
#endif //_DEBUG

// CDemoView 消息处理程序

void CDemoView::OnBnClickedOpen()
{
	// TODO:  在此添加控件通知处理程序代码
	if (OpenDevice() == 0)
	{
		UpdateData(TRUE);///DDX 控件->变量
		switch (m_nWaveStyle)
		{
		case 0:
			SetSignalPara(m_nWaveStyle, m_pAmp, m_pFreq, m_pPhase);
			break;
		case 1:
			SetSignalPara(m_nWaveStyle, m_pAmp, m_pFreq, m_pPhase);
			SetSWDuty(m_pDuty);
			break;
		case 2:
			SetSignalPara(m_nWaveStyle, m_pAmp , m_pFreq, m_pPhase);
			break;
		}
		///SetSignalPara(0, 1.00, 2.00, 0.00);
		SetSampPara(m_pSampFreq);
		SetTimer(1, 100, NULL);		
	}
	else
	{
		AfxMessageBox(_T("设备打开失败"));
	}
}


void CDemoView::OnBnClickedClose()
{
	// TODO:  在此添加控件通知处理程序代码
	KillTimer(1);
	CloseDevice();
}


void CDemoView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CByteArray SendData;
	BYTE SendData2[8];
	BYTE bytes[2];
	CByteArray SendDataPACK;
	UINT16 CRC;
	ReadOneData(&m_dblDataShow);//单点读取
	m_SendData = m_dblDataShow;

#if 1
	//将double转换成8位16进制
	BYTE *p = (BYTE*)&m_SendData;
	SendData.RemoveAll(); // 清空数据区
	SendData.SetSize(sizeof(double)); // 分配内存空间
	for (int k = 0; k<sizeof(double); k++)   /// 有效数据
	{
		SendData[k] = *p++;
		SendData2[k] = SendData[k];
	}
#endif

	//计算CRC16校验码
	CRC = CRC16(SendData2, 8);
	bytes[0] = (byte)(0xff & CRC);
	bytes[1] = (byte)((0xff00 & CRC) >> 8);
	m_nTest.Format(_T("%X %X"), bytes[0],bytes[1]);

	//数据打包
	SendDataPACK.SetSize(sizeof(double)+4);
	SendDataPACK[0] = 0x01;// 数据包头
	SendDataPACK[1] = sizeof(double);//有效数据长度
	for (int i = 0; i < 8; i++)//有效数据
	{
		SendDataPACK[i + 2] = SendData[i];
	}
	SendDataPACK[10] = bytes[0];//校验位低位
	SendDataPACK[11] = bytes[1];//校验位高位

	UpdateData(FALSE);

	//将数据从串口发出
	if (m_myComm.get_PortOpen())
	{
		m_myComm.put_Output(COleVariant(SendDataPACK));
	}

	CFormView::OnTimer(nIDEvent);
}
BEGIN_EVENTSINK_MAP(CDemoView, CFormView)
	ON_EVENT(CDemoView, IDC_MSCOMM, 1, CDemoView::OnCommMscomm, VTS_NONE)
END_EVENTSINK_MAP()

void CDemoView::OnCommMscomm()
{
	// TODO: 在此处添加消息处理程序代码

}


void CDemoView::OnBnClickedSeropen()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);//打开串口
	int nPortNO = 0;
	CString szBaudRate;

	//设置端口号
	nPortNO = m_PortNO.GetCurSel() + 1;
	m_myComm.put_CommPort(nPortNO);

	//设置波特率n:无校验 o:奇校验 e:偶校验
	szBaudRate.Format(_T("%d, n, 8, 1"), m_nBaudRate);
	m_myComm.put_Settings(szBaudRate);

	if (!m_myComm.get_PortOpen())//如果串口没有打开
	{
		m_myComm.put_PortOpen(TRUE);//打开串口
		AfxMessageBox(_T("串口打开成功"));
	}
}


void CDemoView::OnBnClickedSerclose()//关闭串口
{
	// TODO: 在此添加控件通知处理程序代码
	//关闭串口
	if (m_myComm.get_PortOpen())
	{
		m_myComm.put_PortOpen(FALSE);
		AfxMessageBox(_T("串口成功关闭！"));
	}
	else
	{
		AfxMessageBox(_T("串口处于关闭状态！"));
	}
}

UINT16 CDemoView::CRC16(BYTE *ptr, int len)//CRC16校验码计算函数
{
	unsigned char i;
	UINT16 crc = 0xFFFF;
	if (len == 0) 
	{
		len = 1;
	}
	while (len--) 
	{
		crc ^= *ptr;
		for (i = 0; i<8; i++)
		{
			if (crc & 1) 
			{
				crc >>= 1;
				crc ^= 0xA001;
			}
			else 
			{
				crc >>= 1;
			}
		}
		ptr++;
	}
	return(crc);
}

void CDemoView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	switch (nSBCode)
	{
	case SB_LINEUP://向上微调
		pScrollBar->SetScrollPos(pScrollBar->GetScrollPos() - 0.5);
		break;
	case SB_LINEDOWN://向下微调
		pScrollBar->SetScrollPos(pScrollBar->GetScrollPos() + 0.5);
	}
	CFormView::OnHScroll(nSBCode, nPos, pScrollBar);
}
