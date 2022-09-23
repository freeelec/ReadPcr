
// ReadPcrDlg.h : 헤더 파일
//

#pragma once


// CReadPcrDlg 대화 상자
class CReadPcrDlg : public CDialogEx
{
	BOOL FileBrowse(CString& sPath);
	int LoadPCR(int nSerial, BOOL bFromShare);	// return : 2(Failed), 1(정상), -1(Align Error, 노광불량), -2(Lot End)
	void ResetMkInfo(int nAoi);	// 0 : AOI-Up , 1 : AOI-Dn , 2 : AOI-UpDn

// 생성입니다.
public:
	CReadPcrDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_READPCR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
