
// FelicaLiteS001Dlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "FelicaLiteS001.h"
#include "FelicaLiteS001Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
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


// CFelicaLiteS001Dlg ダイアログ



CFelicaLiteS001Dlg::CFelicaLiteS001Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FELICALITES001_DIALOG, pParent)
	//, mEditbox(_T(""))
	//, mInputValue(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFelicaLiteS001Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, mEdit);
	DDX_Control(pDX, IDC_EDIT2, mInputBox);
	DDX_Control(pDX, IDC_COMBO1, mBlock);
}

BEGIN_MESSAGE_MAP(CFelicaLiteS001Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CFelicaLiteS001Dlg::OnBnClickedWrite)
	ON_BN_CLICKED(IDC_BUTTON2, &CFelicaLiteS001Dlg::OnBnClickedRead)
END_MESSAGE_MAP()


// CFelicaLiteS001Dlg メッセージ ハンドラー

BOOL CFelicaLiteS001Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// "バージョン情報..." メニューをシステム メニューに追加します。

	// IDM_ABOUTBOX は、システム コマンドの範囲内になければなりません。
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

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。

	// LOGFONT構造体の設定
	LOGFONT log_font;
	log_font.lfWeight = 4;
	log_font.lfHeight = 18;
	log_font.lfWidth = 18;
	// (中略)
	::strcpy(log_font.lfFaceName, "Yu Gothic UI");

	// CreateFontIndirect関数を利用してCFontクラスを生成
	CFont font;
	font.CreateFontIndirect(&log_font);
	
	// SetFont関数でコントロールへフォントを割付
	GetDlgItem(IDC_EDIT1)->SetFont(&font, TRUE);

	/*
	SetBkMode(this->hDC, OPAQUE);		// 背景を塗りつぶし
	SetTextColor(hDC, RGB(255, 0, 0));	// テキストの色
	SetBkColor(hDC, RGB(192, 192, 192));	// テキストが書かれている部分のテキストの背景の色
	return (LRESULT)m_hBrush_BkColor;	// テキストが書かれていない部分の背景の色
	*/



	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

void CFelicaLiteS001Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CFelicaLiteS001Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CFelicaLiteS001Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFelicaLiteS001Dlg::OnBnClickedWrite()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。

	CString str;
	mInputBox.GetWindowTextA(str);

	char *p = new char[16+1];
	memset(p, 0, 16+1);
	strcpy(p, str);

	CString blockNum;
	mBlock.GetWindowTextA(blockNum);
	int iBlock = _ttoi(blockNum.GetBuffer(0));

	char *po = (char *)malloc(sizeof(char) * 5120);
	FelicaRW *fRW = new FelicaRW(po);
	fRW->FelicaRW_main(iBlock, (unsigned char*)p, false);

	mEdit.SetWindowTextA((LPCTSTR)po);

	delete[] p;
	delete(fRW);
	free(po);
}


void CFelicaLiteS001Dlg::OnBnClickedRead()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	char *po = (char *)malloc(sizeof(char) * 5120);
	FelicaRW *fRW = new FelicaRW(po);
	fRW->FelicaRW_main(NULL, NULL, true);

	mEdit.SetWindowTextA((LPCTSTR)po);

	delete(fRW);
	free(po);
}
