
// FelicaLiteS001Dlg.h : �w�b�_�[ �t�@�C��
//

#pragma once
#include "afxcmn.h"
#include "FelicaRW.h"
#include "afxwin.h"

#pragma warning(disable:4996)

// CFelicaLiteS001Dlg �_�C�A���O
class CFelicaLiteS001Dlg : public CDialogEx
{
// �R���X�g���N�V����
public:
	CFelicaLiteS001Dlg(CWnd* pParent = NULL);	// �W���R���X�g���N�^�[

// �_�C�A���O �f�[�^
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FELICALITES001_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �T�|�[�g


// ����
protected:
	HICON m_hIcon;

	// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedWrite();
	afx_msg void OnBnClickedRead();
	CEdit mEdit;
	CEdit mInputBox;
	CComboBox mBlock;
};


