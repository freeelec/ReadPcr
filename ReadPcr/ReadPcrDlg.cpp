
// ReadPcrDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "ReadPcr.h"
#include "ReadPcrDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CReadPcrDlg 대화 상자



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


// CReadPcrDlg 메시지 처리기

BOOL CReadPcrDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CReadPcrDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
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
	dlg.m_ofn.lStructSize = sizeof(OPENFILENAME) + 12; // +12를 Win2k Style로 다이얼로그 박스가 Open됨.

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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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

int CReadPcrDlg::LoadPCR(int nSerial, BOOL bFromShare)	// return : 2(Failed), 1(정상), -1(Align Error, 노광불량), -2(Lot End)
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
		strFileData.Format(_T("PCR파일이 설정되지 않았습니다."));
		AfxMessageBox(strFileData);
		return(2);
	}

	if (!m_pPcr[0])
	{
		strFileData.Format(_T("PCR[0]관련 메모리가 할당되지 않았습니다."));
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
		strFileData.Format(_T("PCR[Up] 파일이 존재하지 않습니다.\r\n%s"), sPath);
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

	// Error Code											// 1(정상), -1(Align Error, 노광불량), -2(Lot End)
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

	m_pPcr[0][nIdx]->Init(nSerial, nTotDef); // 제품시리얼, Shot내 총불량 피스수

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

	return (1); // 1(정상)
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
