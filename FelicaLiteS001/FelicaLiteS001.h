
// FelicaLiteS001.h : PROJECT_NAME �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH �ɑ΂��Ă��̃t�@�C�����C���N���[�h����O�� 'stdafx.h' ���C���N���[�h���Ă�������"
#endif

#include "resource.h"		// ���C�� �V���{��


// CFelicaLiteS001App:
// ���̃N���X�̎����ɂ��ẮAFelicaLiteS001.cpp ���Q�Ƃ��Ă��������B
//

class CFelicaLiteS001App : public CWinApp
{
public:
	CFelicaLiteS001App();

// �I�[�o�[���C�h
public:
	virtual BOOL InitInstance();

// ����

	DECLARE_MESSAGE_MAP()
};

extern CFelicaLiteS001App theApp;