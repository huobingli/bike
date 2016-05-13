// FrameDispDataUI.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "station_3.h"
#include "FrameDispDataUI.h"
#include "afxdialogex.h"
#include"StationInfo.h"



// FrameDispDataUI �Ի���

IMPLEMENT_DYNAMIC(FrameDispDataUI, CDialogEx)

FrameDispDataUI::FrameDispDataUI(CWnd* pParent /*=NULL*/)
	: CDialogEx(FrameDispDataUI::IDD, pParent)
{
	m_pBLLDisplay = new CFrameBLLDisplay();
	EnableAutomation();

}

FrameDispDataUI::~FrameDispDataUI()
{
}

void FrameDispDataUI::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CDialogEx::OnFinalRelease();
}

void FrameDispDataUI::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, ListCtrl1);
	DDX_Control(pDX, IDC_LIST2, ListCtrl2);
	DDX_Control(pDX, IDC_LIST3, ListCtrl3);

	DDX_Control(pDX, IDC_Station, Station1);
	DDX_Control(pDX, IDC_Station2, Station2);
	DDX_Control(pDX, IDC_COMBO1, ComboBox1);
}


BEGIN_MESSAGE_MAP(FrameDispDataUI, CDialogEx)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &FrameDispDataUI::OnNMDblclkList1)
	ON_BN_CLICKED(IDC_BUTTON1, &FrameDispDataUI::OnBnClickedButton1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, &FrameDispDataUI::OnLvnItemchangedList2)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST3, &FrameDispDataUI::OnLvnItemchangedList3)
	ON_STN_CLICKED(IDC_Station2, &FrameDispDataUI::OnStnClickedStation2)
	ON_STN_CLICKED(IDC_Station, &FrameDispDataUI::OnStnClickedStation)
	ON_CBN_SELCHANGE(IDC_COMBO1, &FrameDispDataUI::OnCbnSelchangeCombo1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST1, &FrameDispDataUI::OnNMCustomdrawList1)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(FrameDispDataUI, CDialogEx)
END_DISPATCH_MAP()

// ע��: ������� IID_IFrameDispDataUI ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {CF87E42C-C38A-4A99-ABE3-74CD51F1E4B3}
static const IID IID_IFrameDispDataUI =
{ 0xCF87E42C, 0xC38A, 0x4A99, { 0xAB, 0xE3, 0x74, 0xCD, 0x51, 0xF1, 0xE4, 0xB3 } };

BEGIN_INTERFACE_MAP(FrameDispDataUI, CDialogEx)
	INTERFACE_PART(FrameDispDataUI, IID_IFrameDispDataUI, Dispatch)
END_INTERFACE_MAP()


// FrameDispDataUI ��Ϣ�������
BOOL FrameDispDataUI::OnInitDialog()
{
	
	//m_BLLControllerDisplay->showData();

	CDialogEx::OnInitDialog();
	ListCtrl1.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE);

	ListCtrl1.InsertColumn(0, _T("    "), LVCFMT_LEFT, 60, -1);
	for (int i = 1; i < 51; i++)
	{
		ListCtrl1.InsertColumn(i, _T("վ��"), LVCFMT_LEFT, 60, -1);
	}


	for (int j = 0; j < 50; j++)
	{
		ListCtrl1.InsertItem(j, _T("վ��"));
	}
	for (int i = 0; i <50; i++)
		for (int j = 1; j < 51; j++)
		{
		if (i == j - 1)
			ListCtrl1.SetItemText(i, j, _T("0"));
		else
			ListCtrl1.SetItemText(i, j, _T("1"));
		}



	ListCtrl1.SetItemText(0, 1, _T("100"));

	


	/*******************************************************/

	ListCtrl2.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	
	ListCtrl2.InsertColumn(1, _T("����վ��"), LVCFMT_LEFT, 60, -1);
	ListCtrl2.InsertColumn(2, _T("���ʱ��"), LVCFMT_LEFT, 60, -1);
	ListCtrl2.InsertColumn(3, _T("��Сʱ��"), LVCFMT_LEFT, 60, -1);
	ListCtrl2.InsertColumn(4, _T("��������"), LVCFMT_LEFT, 60, -1);
	ListCtrl2.InsertColumn(5, _T("�軹���"), LVCFMT_LEFT, 60, -1);
	



	/*******************************************************/

	ListCtrl3.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	ListCtrl3.InsertColumn(1, _T("����վ��"), LVCFMT_LEFT, 60, -1);
	ListCtrl3.InsertColumn(2, _T("���ʱ��"), LVCFMT_LEFT, 60, -1);
	ListCtrl3.InsertColumn(3, _T("��Сʱ��"), LVCFMT_LEFT, 60, -1);
	ListCtrl3.InsertColumn(4, _T("��������"), LVCFMT_LEFT, 60, -1);
	ListCtrl3.InsertColumn(5, _T("�軹���"), LVCFMT_LEFT, 60, -1);

	/*******************************************************/
	





	return true;
}

void FrameDispDataUI::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int col = 0;
	int row = 0;
	row = pNMListView->iItem;
	col = pNMListView->iSubItem;
	CString str1;
	CString str2;
	str1.Format("%d",col);
	str2.Format("%d",row+1);
	ListCtrl2.SetItemText(0, 1, str1);
	ListCtrl2.SetItemText(0, 2, str2);


	GetDlgItem(IDC_Station)->SetWindowText("վ��" + str2);
	GetDlgItem(IDC_Station2)->SetWindowText("վ��" + str1);

	StationInfo  m_StationInfo;
	//��ʼ��
	/******************
	m_StationInfo.RecordNum1 = -1;
	m_StationInfo.RecordNum2 = -1;
	m_StationInfo.m_StationData1->maxtime = -1;
	m_StationInfo.m_StationData1->mintime = -1;
	m_StationInfo.m_StationData1->maxtime = -1;
	m_StationInfo.m_StationData1->OperatedTimes = -1;
	m_StationInfo.m_StationData1->rent = -1;
	m_StationInfo.m_StationData2->maxtime = -1;
	m_StationInfo.m_StationData2->mintime = -1;
	m_StationInfo.m_StationData2->maxtime = -1;
	m_StationInfo.m_StationData2->OperatedTimes = -1;
	m_StationInfo.m_StationData2->rent = -1;
	*******************/
	StationData *pt1,*pt2;
	pt1 = m_StationInfo.m_StationData1;
	pt2 = m_StationInfo.m_StationData2;

	//���ý���
	ListCtrl2.DeleteAllItems();
	int nCount = ListCtrl2.GetHeaderCtrl()->GetItemCount();
	for (int i = 0; i<nCount; i++)
	{
		ListCtrl2.DeleteColumn(0);
	}

	ListCtrl3.DeleteAllItems();
	int mCount = ListCtrl3.GetHeaderCtrl()->GetItemCount();
	for (int i = 0; i<mCount; i++)
	{
		ListCtrl3.DeleteColumn(0);
	}
	/*******************************************************/
	ListCtrl2.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	ListCtrl2.InsertColumn(1, _T("����վ��"), LVCFMT_LEFT, 60, -1);
	ListCtrl2.InsertColumn(2, _T("���ʱ��"), LVCFMT_LEFT, 60, -1);
	ListCtrl2.InsertColumn(3, _T("��Сʱ��"), LVCFMT_LEFT, 60, -1);
	ListCtrl2.InsertColumn(4, _T("��������"), LVCFMT_LEFT, 60, -1);
	ListCtrl2.InsertColumn(5, _T("�軹���"), LVCFMT_LEFT, 60, -1);

	/*******************************************************/

	ListCtrl3.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	ListCtrl3.InsertColumn(1, _T("����վ��"), LVCFMT_LEFT, 60, -1);
	ListCtrl3.InsertColumn(2, _T("���ʱ��"), LVCFMT_LEFT, 60, -1);
	ListCtrl3.InsertColumn(3, _T("��Сʱ��"), LVCFMT_LEFT, 60, -1);
	ListCtrl3.InsertColumn(4, _T("��������"), LVCFMT_LEFT, 60, -1);
	ListCtrl3.InsertColumn(5, _T("�軹���"), LVCFMT_LEFT, 60, -1);
	/*******************************************************/
	
		
	
/*****************************��ʾ***************************/
	int nIndex = ComboBox1.GetCurSel();
	CString TimeId;
	ComboBox1.GetLBText(nIndex, TimeId);
	TimeId = TimeId.Mid(9, 5);
	int TimeID = _ttoi(TimeId);
	if (m_pBLLDisplay->showInfo(m_StationInfo,row+1,col,TimeID))

	{
		m_StationInfo.m_StationData1 = pt1;
		m_StationInfo.m_StationData2 = pt2;
		
		for (int iCount = 1; iCount <= m_StationInfo.RecordNum1; iCount++)
		{
			str1.Format("%d", m_StationInfo.m_StationData1->getId());
			ListCtrl2.InsertItem(iCount, _T("վ��" + str1));
			str1.Format("%d", m_StationInfo.m_StationData1->getMaxtime());
			ListCtrl2.SetItemText(iCount-1, 1, str1);
			str1.Format("%d", m_StationInfo.m_StationData1->getMintime());
			ListCtrl2.SetItemText(iCount-1, 2, str1);
			str1.Format("%d", m_StationInfo.m_StationData1->getOperatedTimes());
			ListCtrl2.SetItemText(iCount-1, 3, str1);
			str1.Format("%d", m_StationInfo.m_StationData1->getRent());
			ListCtrl2.SetItemText(iCount-1, 4, str1);
			m_StationInfo.m_StationData1++;
		}

		for (int iCount = 2; iCount <= m_StationInfo.RecordNum2+1; iCount++)
		{
			str1.Format("%d", m_StationInfo.m_StationData2->getId());
			ListCtrl3.InsertItem(iCount, _T("վ��" + str1));
			str1.Format("%d", m_StationInfo.m_StationData2->getMaxtime());
			ListCtrl3.SetItemText(iCount-2, 1, str1);
			str1.Format("%d", m_StationInfo.m_StationData2->getMintime());
			ListCtrl3.SetItemText(iCount-2, 2, str1);
			str1.Format("%d", m_StationInfo.m_StationData2->getOperatedTimes());
			ListCtrl3.SetItemText(iCount-2, 3, str1);
			str1.Format("%d", m_StationInfo.m_StationData2->getRent());
			ListCtrl3.SetItemText(iCount-2, 4, str1);
			m_StationInfo.m_StationData2++;
		}

	}
	m_StationInfo.m_StationData1 = pt1;
	m_StationInfo.m_StationData2 = pt2;
	m_StationInfo.clearData();
	/**********/
	*pResult = 0;
}

//���ݻ�ȡ��ť
void FrameDispDataUI::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	int TimeIDSet[500];
	int TimeID_Num;
	int day_Num,day_Today,month, day, hour, minute;
	CString str_mon, str_d, str_h, str_min;
	CString str1;

	

	/********************************************/

	TimeID_Num = m_pBLLDisplay->GetTimeID(TimeIDSet);
	for (int iCount = 0; iCount < TimeID_Num; iCount++)
	{
		day_Num = TimeIDSet[iCount] / 72;
		day_Today = TimeIDSet[iCount] % 72;
		m_pBLLDisplay->getDate(day_Num, month, day);
		m_pBLLDisplay->getToday(day_Today, hour, minute);
		str1.Format("%d", TimeIDSet[iCount]);
		str_mon.Format("%d", month);
		str_d.Format("%d", day);
		str_h.Format("%d", hour);
		if (minute==1)
		 str_min="0-19";
		else if (minute==2)
			str_min = "20-39";
		else if (minute == 0)
			str_min = "30-59";
		
		ComboBox1.AddString("ʱ��ƬID:"+str1+"|"+str_mon+"��"+str_d+"��"+str_h+"ʱ"+str_min+"��");
	}
















	/****************************************************************/

	
 
}


void FrameDispDataUI::OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void FrameDispDataUI::OnLvnItemchangedList3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void FrameDispDataUI::OnStnClickedStation2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void FrameDispDataUI::OnStnClickedStation()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void FrameDispDataUI::OnCbnSelchangeCombo1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int nIndex = ComboBox1.GetCurSel();
	CString TimeId;
	ComboBox1.GetLBText(nIndex, TimeId);
	

	TimeId =TimeId.Mid(9, 5);
	int TimeID = _ttoi(TimeId);
	int *p_StationRelation;
	//	int **StationRelationSet;
	int StationNum = 0;
	CString str;
	p_StationRelation = m_pBLLDisplay->showData(StationNum,TimeID);
	//���ý���
	ListCtrl1.DeleteAllItems();
	int nCount = ListCtrl1.GetHeaderCtrl()->GetItemCount();
	for (int i = 0; i<nCount; i++)
	{
		ListCtrl1.DeleteColumn(0);
	}

	ListCtrl1.InsertColumn(0, _T("    "), LVCFMT_LEFT, 60, -1);
	for (int i = 1; i < StationNum + 1; i++)
	{
		str.Format("%d", i);
		ListCtrl1.InsertColumn(i, _T("վ��" + str), LVCFMT_LEFT, 60, -1);
	}
	for (int j = 0; j < StationNum; j++)
	{
		str.Format("%d", j + 1);
		ListCtrl1.InsertItem(j, _T("վ��" + str));
	}
	for (int kCount = 0, iCount = 0, jCount = 1; kCount < StationNum*StationNum; kCount++, iCount++)
	{
		if (iCount == StationNum)
		{
			iCount = 0;
			jCount++;
		}

		str.Format("%d", *p_StationRelation);
		ListCtrl1.SetItemText(iCount, jCount, _T(str));
		*p_StationRelation++;
	}
}


void FrameDispDataUI::OnNMCustomdrawList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}
