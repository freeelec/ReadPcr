
// ReadPcrDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "ReadPcr.h"
#include "ReadPcrDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CReadPcrDlg ��ȭ ����



CReadPcrDlg::CReadPcrDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_READPCR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CReadPcrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CReadPcrDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CReadPcrDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CReadPcrDlg �޽��� ó����

BOOL CReadPcrDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CReadPcrDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CReadPcrDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CReadPcrDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BOOL CReadPcrDlg::FileBrowse(CString& sPath)
{
	sPath = _T("");

	/* Load from file */
	CString FilePath;
	CFileFind finder;
	CString SrchPath, strTitleMsg, strErrMsg;

	CWaitCursor mCursor;

	CString DirPath[10];
	CString strWorkDir;
	BOOL bResult;

	CString strMcNum;
	int nAoiMachineNum = 0;

	// File Open Filter 
	static TCHAR BASED_CODE szFilter[] = _T("Mst Files (*.mst)|*.mst|All Files (*.*)|*.*||");

	// CFileDialog 
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);

	// Win2k Style FileDialog Box
	dlg.m_ofn.lStructSize = sizeof(OPENFILENAME) + 12; // +12�� Win2k Style�� ���̾�α� �ڽ��� Open��.

													   // Open Directory
	TCHAR strPrevDir[MAX_PATH];
	DWORD dwLength = GetCurrentDirectory(MAX_PATH, strPrevDir);
	strWorkDir = strPrevDir;
	dlg.m_ofn.lpstrInitialDir = strWorkDir;

	bResult = 0;

	// Dialog Open
	if (dlg.DoModal() == IDOK)
	{
		sPath = FilePath = dlg.GetPathName();
		return TRUE;
	}

	return FALSE;
}

void CReadPcrDlg::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString sPath;
	int nPos, nSerial;

	if (!FileBrowse(sPath))
		return;
	GetDlgItem(IDC_STATIC_PATH)->SetWindowText(sPath);

	CString sTemp, sSerial;
	nPos = sPath.ReverseFind('.');
	sTemp = sPath.Left(nPos);
	nPos = sPath.ReverseFind('\\');
	sSerial = sTemp.Right(nPos+1);
	nSerial = _tstoi(sSerial);

	//CString sData;
	//if (!LoadStripRgnFromCam(sPath, sData))
	//	AfxMessageBox(_T("LoadStripRgnFromCam failed!"));
	//GetDlgItem(IDC_EDIT1)->SetWindowText(sData);
}

int CReadPcrDlg::LoadPCR(int nSerial, BOOL bFromShare)	// return : 2(Failed), 1(����), -1(Align Error, �뱤�ҷ�), -2(Lot End)
{
	FILE *fp;
	char FileD[200];
	size_t nFileSize, nRSize;
	char *FileData;
	CString strFileData;
	int nTemp, i;
	CString strHeaderErrorInfo, strModel, strLayer, strLot, strTotalBadPieceNum;
	CString strCamID, strPieceID, strBadPointPosX, strBadPointPosY, strBadName,
		strCellNum, strImageSize, strImageNum, strMarkingCode;

	if (nSerial <= 0)
	{
		strFileData.Format(_T("PCR������ �������� �ʾҽ��ϴ�."));
		AfxMessageBox(strFileData);
		return(2);
	}

	if (!m_pPcr[0])
	{
		strFileData.Format(_T("PCR[0]���� �޸𸮰� �Ҵ���� �ʾҽ��ϴ�."));
		AfxMessageBox(strFileData);
		return(2);
	}

	int nIdx;
	if (m_bNewLotShare[0] && (WorkingInfo.LastJob.bLotSep || m_bDoneChgLot))
		nIdx = GetPcrIdx0(nSerial, TRUE);
	else
		nIdx = GetPcrIdx0(nSerial);

	CString sPath;

#ifdef TEST_MODE
	sPath = PATH_PCR;	// for Test
#else
	if (bFromShare)
		sPath.Format(_T("%s%04d.pcr"), WorkingInfo.System.sPathVrsShareUp, nSerial);
	else
		sPath.Format(_T("%s%04d.pcr"), WorkingInfo.System.sPathVrsBufUp, nSerial);
#endif

	//strcpy(FileD, sPath);
	//_tcscpy(FileD, sPath);
	StringToChar(sPath, FileD);

	if ((fp = fopen(FileD, "r")) != NULL)
	{
		fseek(fp, 0, SEEK_END);
		nFileSize = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		/* Allocate space for a path name */
		//FileData = (char*)malloc( nFileSize );
		FileData = (char*)calloc(nFileSize + 1, sizeof(char));

		nRSize = fread(FileData, sizeof(char), nFileSize, fp);
		strFileData.Format(_T("%s"), CharToString(FileData));
		fclose(fp);
		free(FileData);
	}
	else
	{
		strFileData.Format(_T("PCR[Up] ������ �������� �ʽ��ϴ�.\r\n%s"), sPath);
		AfxMessageBox(strFileData);
		return(2);
	}

	if (!m_pPcr[0])
		return(2);
	if (!m_pPcr[0][nIdx])
		return(2);

	BOOL bResetMkInfo = FALSE;

	m_pPcr[0][nIdx]->m_nIdx = nIdx;							// m_nIdx : From 0 to nTot.....
	m_pPcr[0][nIdx]->m_nSerial = nSerial;

	// Error Code											// 1(����), -1(Align Error, �뱤�ҷ�), -2(Lot End)
	nTemp = strFileData.Find(',', 0);
	strHeaderErrorInfo = strFileData.Left(nTemp);
	strFileData.Delete(0, nTemp + 1);
	nFileSize = nFileSize - nTemp - 1;
	m_pPcr[0][nIdx]->m_nErrPnl = _tstoi(strHeaderErrorInfo);

	// Model
	nTemp = strFileData.Find(',', 0);
	strModel = strFileData.Left(nTemp);
	strFileData.Delete(0, nTemp + 1);
	nFileSize = nFileSize - nTemp - 1;
	m_pPcr[0][nIdx]->m_sModel = strModel;

	// Layer
	nTemp = strFileData.Find(',', 0);
	strLayer = strFileData.Left(nTemp);
	strFileData.Delete(0, nTemp + 1);
	nFileSize = nFileSize - nTemp - 1;
	m_pPcr[0][nIdx]->m_sLayer = strLayer;

	// Lot
	nTemp = strFileData.Find('\n', 0);
	strLot = strFileData.Left(nTemp);
	strFileData.Delete(0, nTemp + 1);
	nFileSize = nFileSize - nTemp - 1;
	m_pPcr[0][nIdx]->m_sLot = strLot;

	nTemp = strFileData.Find('\n', 0);
	strTotalBadPieceNum = strFileData.Left(nTemp);;
	strFileData.Delete(0, nTemp + 1);
	nFileSize = nFileSize - nTemp - 1;

	if (!strModel.IsEmpty() && !strLot.IsEmpty() && !strLayer.IsEmpty())
	{
		if (WorkingInfo.LastJob.sModelUp.IsEmpty() || WorkingInfo.LastJob.sLotUp.IsEmpty() || WorkingInfo.LastJob.sLayerUp.IsEmpty())
		{
			WorkingInfo.LastJob.sModelUp = strModel;
			WorkingInfo.LastJob.sLotUp = strLot;
			WorkingInfo.LastJob.sLayerUp = strLayer;

			if (!WorkingInfo.LastJob.bDualTest)
			{
				ResetMkInfo(0); // 0 : AOI-Up , 1 : AOI-Dn , 2 : AOI-UpDn
			}
		}
	}

	int nTotDef = _tstoi(strTotalBadPieceNum);

	m_pPcr[0][nIdx]->Init(nSerial, nTotDef); // ��ǰ�ø���, Shot�� �Ѻҷ� �ǽ���

	if (nTotDef > 0)
	{
		for (i = 0; i < nTotDef; i++)
		{
			// Cam ID
			nTemp = strFileData.Find(',', 0);
			strCamID = strFileData.Left(nTemp);
			strFileData.Delete(0, nTemp + 1);
			nFileSize = nFileSize - nTemp - 1;
			m_pPcr[0][nIdx]->m_nCamId = _tstoi(strCamID);

			// Piece Number
			nTemp = strFileData.Find(',', 0);
			strPieceID = strFileData.Left(nTemp);
			strFileData.Delete(0, nTemp + 1);
			nFileSize = nFileSize - nTemp - 1;
			m_pPcr[0][nIdx]->m_pDefPcs[i] = _tstoi(strPieceID);
			m_pPcr[0][nIdx]->m_pLayer[i] = 0; // Up

											  // BadPointPosX
			nTemp = strFileData.Find(',', 0);
			strBadPointPosX = strFileData.Left(nTemp);
			strFileData.Delete(0, nTemp + 1);
			nFileSize = nFileSize - nTemp - 1;
			m_pPcr[0][nIdx]->m_pDefPos[i].x = (long)_tstoi(strBadPointPosX);

			// BadPointPosY
			nTemp = strFileData.Find(',', 0);
			strBadPointPosY = strFileData.Left(nTemp);
			strFileData.Delete(0, nTemp + 1);
			nFileSize = nFileSize - nTemp - 1;
			m_pPcr[0][nIdx]->m_pDefPos[i].y = (long)_tstoi(strBadPointPosY);

			// BadName
			nTemp = strFileData.Find(',', 0);
			strBadName = strFileData.Left(nTemp);
			strFileData.Delete(0, nTemp + 1);
			nFileSize = nFileSize - nTemp - 1;
			m_pPcr[0][nIdx]->m_pDefType[i] = _tstoi(strBadName);

			// CellNum
			nTemp = strFileData.Find(',', 0);
			strCellNum = strFileData.Left(nTemp);
			strFileData.Delete(0, nTemp + 1);
			nFileSize = nFileSize - nTemp - 1;
			m_pPcr[0][nIdx]->m_pCell[i] = _tstoi(strCellNum);

			// ImageSize
			nTemp = strFileData.Find(',', 0);
			strImageSize = strFileData.Left(nTemp);
			strFileData.Delete(0, nTemp + 1);
			nFileSize = nFileSize - nTemp - 1;
			m_pPcr[0][nIdx]->m_pImgSz[i] = _tstoi(strImageSize);

			// ImageNum
			nTemp = strFileData.Find(',', 0);
			strImageNum = strFileData.Left(nTemp);
			strFileData.Delete(0, nTemp + 1);
			nFileSize = nFileSize - nTemp - 1;
			m_pPcr[0][nIdx]->m_pImg[i] = _tstoi(strImageNum);

			// strMarkingCode : -2 (NoMarking)
			nTemp = strFileData.Find('\n', 0);
			strMarkingCode = strFileData.Left(nTemp);
			strFileData.Delete(0, nTemp + 1);
			nFileSize = nFileSize - nTemp - 1;
			m_pPcr[0][nIdx]->m_pMk[i] = _tstoi(strMarkingCode);
		}
	}

	return (1); // 1(����)
				// 	return(m_pPcr[0][nIdx]->m_nErrPnl);
}

void CReadPcrDlg::ResetMkInfo(int nAoi) // 0 : AOI-Up , 1 : AOI-Dn , 2 : AOI-UpDn
{
	BOOL bDualTest = pDoc->WorkingInfo.LastJob.bDualTest;

	pView->m_nDebugStep = 500; pView->DispThreadTick();
	// CamMst Info...
	pDoc->GetCamPxlRes();

	//if(!pDoc->m_pReelMap)
	//	InitReelmap();

	if (nAoi == 0 || nAoi == 2)
	{
		pView->m_nDebugStep = 501; pView->DispThreadTick();
		if (!bDualTest)
		{
			m_bDrawGL = FALSE;
			if (m_pDlgMenu01)
				m_pDlgMenu01->ResetMkInfo();
		}
		pView->m_nDebugStep = 502; pView->DispThreadTick();
		if (IsLastJob(0)) // Up
		{
			pView->m_nDebugStep = 503; pView->DispThreadTick();
			pDoc->m_MasterDB.Init(
				pDoc->WorkingInfo.System.sPathCamSpecDir,
				pDoc->WorkingInfo.LastJob.sModelUp,
				pDoc->WorkingInfo.LastJob.sLayerUp,
				_T(""));
			//pDoc->m_Master[0].Init(
			//	pDoc->WorkingInfo.System.sPathCamSpecDir,
			//	pDoc->WorkingInfo.LastJob.sModelUp,
			//	pDoc->WorkingInfo.LastJob.sLayerUp,
			//	_T(""), FALSE);
			pView->m_nDebugStep = 504; pView->DispThreadTick();
			pDoc->m_MasterDB.m_bUse = pDoc->m_MasterDB.LoadMstInfo();
			pDoc->m_MasterDB.WriteStripPieceRegion_Text(pDoc->WorkingInfo.System.sPathOldFile, pDoc->WorkingInfo.LastJob.sLotUp);
			//pDoc->m_Master[0].LoadMstInfo();
			//pDoc->m_Master[0].WriteStripPieceRegion_Text(pDoc->WorkingInfo.System.sPathOldFile, pDoc->WorkingInfo.LastJob.sLotUp);
		}
		else
		{
			pView->ClrDispMsg();
			AfxMessageBox(_T("Error - IsLastJob(0)..."));
		}
		pView->m_nDebugStep = 505; pView->DispThreadTick();
		InitReelmapUp();
		pView->m_nDebugStep = 506; pView->DispThreadTick();
		SetAlignPosUp();

		pView->m_nDebugStep = 507; pView->DispThreadTick();
		if (m_pDlgMenu02)
		{
			m_pDlgMenu02->ChgModelUp();

			pView->m_nDebugStep = 508; pView->DispThreadTick();
			if (bDualTest)
				m_pDlgMenu02->ChgModelDn();
		}

		pView->m_nDebugStep = 509; pView->DispThreadTick();
		if (m_pDlgMenu01)
		{
			m_pDlgMenu01->InitCadImgUp();

			pView->m_nDebugStep = 510; pView->DispThreadTick();
			if (!bDualTest)
			{
				m_pDlgMenu01->InitGL();

				pView->m_nDebugStep = 511; pView->DispThreadTick();
				m_bDrawGL = TRUE;
				m_pDlgMenu01->RefreshRmap();
			}
		}
	}

	pView->m_nDebugStep = 512; pView->DispThreadTick();
	if (bDualTest)
	{
		if (nAoi == 1 || nAoi == 2)
		{
			pView->m_nDebugStep = 513; pView->DispThreadTick();
			m_bDrawGL = FALSE;
			if (m_pDlgMenu01)
				m_pDlgMenu01->ResetMkInfo();

			//ResetReelmap();

			pView->m_nDebugStep = 514; pView->DispThreadTick();
			//if (IsLastJob(1)) // Dn
			//{
			//	pView->m_nDebugStep = 515; pView->DispThreadTick();
			//	pDoc->m_Master[1].Init(
			//		pDoc->WorkingInfo.System.sPathCamSpecDir,
			//		pDoc->WorkingInfo.LastJob.sModelDn,
			//		pDoc->WorkingInfo.LastJob.sLayerDn,
			//		pDoc->WorkingInfo.LastJob.sLayerUp,
			//		FALSE);
			//	pView->m_nDebugStep = 516; pView->DispThreadTick();
			//	pDoc->m_Master[1].LoadMstInfo();
			//	pDoc->m_Master[1].WriteStripPieceRegion_Text(pDoc->WorkingInfo.System.sPathOldFile, pDoc->WorkingInfo.LastJob.sLotDn);
			//}
			//else
			//{
			//	AfxMessageBox(_T("Error - IsLastJob(1)..."));
			//}

			pView->m_nDebugStep = 517; pView->DispThreadTick();
			InitReelmapDn();
			pView->m_nDebugStep = 518; pView->DispThreadTick();
			SetAlignPosDn();

			pView->m_nDebugStep = 519; pView->DispThreadTick();
			if (m_pDlgMenu02)
				m_pDlgMenu02->ChgModelDn();

			pView->m_nDebugStep = 520; pView->DispThreadTick();
			if (m_pDlgMenu01)
			{
				m_pDlgMenu01->InitCadImgDn();
				pView->m_nDebugStep = 521; pView->DispThreadTick();
				m_pDlgMenu01->InitGL();
				pView->m_nDebugStep = 522; pView->DispThreadTick();
				m_bDrawGL = TRUE;
				m_pDlgMenu01->RefreshRmap();
			}

			// 		m_bDrawGL = TRUE;
		}
	}
	// 	else
	// 	{
	// 		if(m_pDlgMenu01)
	// 			m_pDlgMenu01->ResetMkInfo();
	// 	}
	pView->m_nDebugStep = 523; pView->DispThreadTick();
}
