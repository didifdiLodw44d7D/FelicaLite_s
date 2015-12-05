
// FelicaLiteS001Dlg.h : ヘッダー ファイル
//

#pragma once
#include "afxcmn.h"
#include "FelicaRW.h"
#include "afxwin.h"

#pragma warning(disable:4996)

// CFelicaLiteS001Dlg ダイアログ
class CFelicaLiteS001Dlg : public CDialogEx
{
// コンストラクション
public:
	CFelicaLiteS001Dlg(CWnd* pParent = NULL);	// 標準コンストラクター

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FELICALITES001_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedWrite();
	afx_msg void OnBnClickedRead();
	CEdit mEdit;
};


