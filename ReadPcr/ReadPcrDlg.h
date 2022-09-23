
// ReadPcrDlg.h : ��� ����
//

#pragma once


// CReadPcrDlg ��ȭ ����
class CReadPcrDlg : public CDialogEx
{
	BOOL FileBrowse(CString& sPath);
	int LoadPCR(int nSerial, BOOL bFromShare);	// return : 2(Failed), 1(����), -1(Align Error, �뱤�ҷ�), -2(Lot End)
	void ResetMkInfo(int nAoi);	// 0 : AOI-Up , 1 : AOI-Dn , 2 : AOI-UpDn

// �����Դϴ�.
public:
	CReadPcrDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_READPCR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
