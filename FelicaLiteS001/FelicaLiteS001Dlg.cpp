
// FelicaLiteS001Dlg.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "FelicaLiteS001.h"
#include "FelicaLiteS001Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// �A�v���P�[�V�����̃o�[�W�������Ɏg���� CAboutDlg �_�C�A���O

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �_�C�A���O �f�[�^
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

// ����
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


// CFelicaLiteS001Dlg �_�C�A���O



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


// CFelicaLiteS001Dlg ���b�Z�[�W �n���h���[

BOOL CFelicaLiteS001Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// "�o�[�W�������..." ���j���[���V�X�e�� ���j���[�ɒǉ����܂��B

	// IDM_ABOUTBOX �́A�V�X�e�� �R�}���h�͈͓̔��ɂȂ���΂Ȃ�܂���B
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

	// ���̃_�C�A���O�̃A�C�R����ݒ肵�܂��B�A�v���P�[�V�����̃��C�� �E�B���h�E���_�C�A���O�łȂ��ꍇ�A
	//  Framework �́A���̐ݒ�������I�ɍs���܂��B
	SetIcon(m_hIcon, TRUE);			// �傫���A�C�R���̐ݒ�
	SetIcon(m_hIcon, FALSE);		// �������A�C�R���̐ݒ�

	// TODO: �������������ɒǉ����܂��B

	// LOGFONT�\���̂̐ݒ�
	LOGFONT log_font;
	log_font.lfWeight = 4;
	log_font.lfHeight = 18;
	log_font.lfWidth = 18;
	// (����)
	::strcpy(log_font.lfFaceName, "Yu Gothic UI");

	// CreateFontIndirect�֐��𗘗p����CFont�N���X�𐶐�
	CFont font;
	font.CreateFontIndirect(&log_font);
	
	// SetFont�֐��ŃR���g���[���փt�H���g�����t
	GetDlgItem(IDC_EDIT1)->SetFont(&font, TRUE);

	/*
	SetBkMode(this->hDC, OPAQUE);		// �w�i��h��Ԃ�
	SetTextColor(hDC, RGB(255, 0, 0));	// �e�L�X�g�̐F
	SetBkColor(hDC, RGB(192, 192, 192));	// �e�L�X�g��������Ă��镔���̃e�L�X�g�̔w�i�̐F
	return (LRESULT)m_hBrush_BkColor;	// �e�L�X�g��������Ă��Ȃ������̔w�i�̐F
	*/



	return TRUE;  // �t�H�[�J�X���R���g���[���ɐݒ肵���ꍇ�������ATRUE ��Ԃ��܂��B
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

// �_�C�A���O�ɍŏ����{�^����ǉ�����ꍇ�A�A�C�R����`�悷�邽�߂�
//  ���̃R�[�h���K�v�ł��B�h�L�������g/�r���[ ���f�����g�� MFC �A�v���P�[�V�����̏ꍇ�A
//  ����́AFramework �ɂ���Ď����I�ɐݒ肳��܂��B

void CFelicaLiteS001Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �`��̃f�o�C�X �R���e�L�X�g

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// �N���C�A���g�̎l�p�`�̈���̒���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �A�C�R���̕`��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ���[�U�[���ŏ��������E�B���h�E���h���b�O���Ă���Ƃ��ɕ\������J�[�\�����擾���邽�߂ɁA
//  �V�X�e�������̊֐����Ăяo���܂��B
HCURSOR CFelicaLiteS001Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFelicaLiteS001Dlg::OnBnClickedWrite()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B

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
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	char *po = (char *)malloc(sizeof(char) * 5120);
	FelicaRW *fRW = new FelicaRW(po);
	fRW->FelicaRW_main(NULL, NULL, true);

	mEdit.SetWindowTextA((LPCTSTR)po);

	delete(fRW);
	free(po);
}
