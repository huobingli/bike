#pragma once
#include "afxcmn.h"
#include "FrameBLLDisplay.h"
#include "afxwin.h"


// FrameDispDataUI 对话框

class FrameDispDataUI : public CDialogEx
{
	DECLARE_DYNAMIC(FrameDispDataUI)

public:
	FrameDispDataUI(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~FrameDispDataUI();

	virtual void OnFinalRelease();
	//CString iTimeID;
// 对话框数据
	enum { IDD = IDD_DispData };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	CListCtrl ListCtrl1;
	CListCtrl ListCtrl2;
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);

private:
	CFrameBLLDisplay *m_pBLLDisplay;
public:
	afx_msg void OnBnClickedButton1();
	CListCtrl ListCtrl3;
	CListBox ListBox1;
	CListBox ListBox2;
	CStatic Station1;
	CStatic Station2;
	afx_msg void OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedList3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnStnClickedStation2();
	afx_msg void OnStnClickedStation();
	CComboBox ComboBox1;
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnNMCustomdrawList1(NMHDR *pNMHDR, LRESULT *pResult);
};
