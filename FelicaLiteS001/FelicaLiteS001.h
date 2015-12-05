
// FelicaLiteS001.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです。
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CFelicaLiteS001App:
// このクラスの実装については、FelicaLiteS001.cpp を参照してください。
//

class CFelicaLiteS001App : public CWinApp
{
public:
	CFelicaLiteS001App();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CFelicaLiteS001App theApp;