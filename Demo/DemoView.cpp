
// DemoView.cpp : CDemoView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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

// CDemoView ����/����

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
	// TODO:  �ڴ˴���ӹ������
	
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
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CFormView::PreCreateWindow(cs);
}

void CDemoView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	//��ʼ�����ڿؼ�
	m_myComm.put__CommPort(1); // ѡ��COM7
	m_myComm.put_InBufferSize(1024); // ���ջ�����
	m_myComm.put_OutBufferSize(1024); // ���ͻ�����
	m_myComm.put_InputLen(0); // ���ý��ջ��������ݳ���Ϊ0����ʾȫ����ȡ
	m_myComm.put_InputMode(1); // �Զ����Ʒ�ʽ��д����
	m_myComm.put_RThreshold(1); // ���ջ�������1�������ַ�ʱ�������������ݵ�OnComm�¼�
	m_myComm.put_Settings(_T("9600,n,8,1"));// ������9600����У�飬����λ8��ֹͣλ1

	//������Ͽ��ʼ��
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

// CDemoView ���

#ifdef _DEBUG
void CDemoView::AssertValid() const
{
	CFormView::AssertValid();
}

void CDemoView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CDemoDoc* CDemoView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDemoDoc)));
	return (CDemoDoc*)m_pDocument;
}
#endif //_DEBUG

// CDemoView ��Ϣ�������

void CDemoView::OnBnClickedOpen()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (OpenDevice() == 0)
	{
		UpdateData(TRUE);///DDX �ؼ�->����
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
		AfxMessageBox(_T("�豸��ʧ��"));
	}
}


void CDemoView::OnBnClickedClose()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	KillTimer(1);
	CloseDevice();
}


void CDemoView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CByteArray SendData;
	BYTE SendData2[8];
	BYTE bytes[2];
	CByteArray SendDataPACK;
	UINT16 CRC;
	ReadOneData(&m_dblDataShow);//�����ȡ
	m_SendData = m_dblDataShow;

#if 1
	//��doubleת����8λ16����
	BYTE *p = (BYTE*)&m_SendData;
	SendData.RemoveAll(); // ���������
	SendData.SetSize(sizeof(double)); // �����ڴ�ռ�
	for (int k = 0; k<sizeof(double); k++)   /// ��Ч����
	{
		SendData[k] = *p++;
		SendData2[k] = SendData[k];
	}
#endif

	//����CRC16У����
	CRC = CRC16(SendData2, 8);
	bytes[0] = (byte)(0xff & CRC);
	bytes[1] = (byte)((0xff00 & CRC) >> 8);
	m_nTest.Format(_T("%X %X"), bytes[0],bytes[1]);

	//���ݴ��
	SendDataPACK.SetSize(sizeof(double)+4);
	SendDataPACK[0] = 0x01;// ���ݰ�ͷ
	SendDataPACK[1] = sizeof(double);//��Ч���ݳ���
	for (int i = 0; i < 8; i++)//��Ч����
	{
		SendDataPACK[i + 2] = SendData[i];
	}
	SendDataPACK[10] = bytes[0];//У��λ��λ
	SendDataPACK[11] = bytes[1];//У��λ��λ

	UpdateData(FALSE);

	//�����ݴӴ��ڷ���
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
	// TODO: �ڴ˴������Ϣ����������

}


void CDemoView::OnBnClickedSeropen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);//�򿪴���
	int nPortNO = 0;
	CString szBaudRate;

	//���ö˿ں�
	nPortNO = m_PortNO.GetCurSel() + 1;
	m_myComm.put_CommPort(nPortNO);

	//���ò�����n:��У�� o:��У�� e:żУ��
	szBaudRate.Format(_T("%d, n, 8, 1"), m_nBaudRate);
	m_myComm.put_Settings(szBaudRate);

	if (!m_myComm.get_PortOpen())//�������û�д�
	{
		m_myComm.put_PortOpen(TRUE);//�򿪴���
		AfxMessageBox(_T("���ڴ򿪳ɹ�"));
	}
}


void CDemoView::OnBnClickedSerclose()//�رմ���
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�رմ���
	if (m_myComm.get_PortOpen())
	{
		m_myComm.put_PortOpen(FALSE);
		AfxMessageBox(_T("���ڳɹ��رգ�"));
	}
	else
	{
		AfxMessageBox(_T("���ڴ��ڹر�״̬��"));
	}
}

UINT16 CDemoView::CRC16(BYTE *ptr, int len)//CRC16У������㺯��
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
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nSBCode)
	{
	case SB_LINEUP://����΢��
		pScrollBar->SetScrollPos(pScrollBar->GetScrollPos() - 0.5);
		break;
	case SB_LINEDOWN://����΢��
		pScrollBar->SetScrollPos(pScrollBar->GetScrollPos() + 0.5);
	}
	CFormView::OnHScroll(nSBCode, nPos, pScrollBar);
}
