// FelicaRW.cpp : 実装ファイル
//

#include "stdafx.h"
#include "FelicaLiteS001.h"
#include "FelicaRW.h"

#pragma warning(disable : 4996)

// FelicaRW

IMPLEMENT_DYNAMIC(FelicaRW, CWnd)

FelicaRW::FelicaRW()
{
}

FelicaRW::FelicaRW(char *po)
{
	this->po = po;
}

FelicaRW::~FelicaRW()
{
}


BEGIN_MESSAGE_MAP(FelicaRW, CWnd)
END_MESSAGE_MAP()



// FelicaRW メッセージ ハンドラー


bool FelicaRW::PrintNfcLastErr(char* pFuncName)
{
	unsigned long pErrInfo[2];
	bool bSuccess;

	bSuccess = felicalib_nfc_get_last_error(pErrInfo);
	if (bSuccess)
	{
		printf("%s でエラー発生 [%x, %x].\n",
			pFuncName,
			pErrInfo[0],    // NFCアクセスライブラリエラーコード
			pErrInfo[1]);   // ドライバエラーコード
	}
	else
	{
		printf("%s でエラー発生. エラー情報取得失敗.\n",
			pFuncName);
	}

	return true;
}

bool FelicaRW::PrintHex(unsigned char *pBuf, int iLen) {

	char buf[16]; 
	for (int i = 0; i < iLen; i++)
	{
		sprintf(buf, "%02x ", pBuf[i]);
		strcat(po, buf);
	}
	sprintf(buf, "%s", "\r\n");
	strcat(po, buf);

	return true;
}

bool FelicaRW::MyPolling(unsigned short usSystemCode,
	unsigned char pIDm[IDM_SIZE]) {
	bool bSuccess;

	// Polling コマンドの組み立て
	unsigned char pCom[] = {
		0x00,           // データ長
		0x00,           // コマンドコード
		0x00, 0x00,     // システムコード
		0x00,           // リクエストコード
		0x00            // タイムスロット
	};
	unsigned char pRes[512];

	unsigned short usComLen = sizeof(pCom);
	unsigned short usResLen = sizeof(pRes);

	pCom[0] = sizeof(pCom);

	pCom[2] = usSystemCode >> 8;
	pCom[3] = usSystemCode & 0xFF;

	// コマンドの発行
	bSuccess = felicalib_nfc_thru(pCom, usComLen, pRes, &usResLen);
	if (!bSuccess)
	{
		PrintNfcLastErr("felicalib_nfc_thru(polling)");
		return false;
	}

	// レスポンスのチェック
	if (usResLen != 1 + 1 + 8 + 8)
	{
		printf("polling のレスポンス長 %d が不正 #1\n", usResLen);
		return false;
	}
	if (pRes[0] != 1 + 1 + 8 + 8)
	{
		printf("polling のレスポンス長 %d が不正 #2\n", pRes[0]);
		return false;
	}
	if (pRes[1] != 0x01)
	{
		printf("polling のレスポンスコード %d が不正\n", pRes[1]);
		return false;
	}

	// IDm のコピー
	memcpy_s(pIDm, IDM_SIZE, &pRes[2], IDM_SIZE);

	return true;
}

/*
bSuccess = MyWriteWithoutEncryption(
pIDm,                       // Polling コマンドで取得した IDm IN
SERVICE_CODE_RW,            // サービスコード IN
pBlockNum[iBlockCount],     // ブロック番号 IN
pDataR);                    // 読み出したデータの格納場所 OUT
*/

bool FelicaRW::MyWriteWithoutEncryption(unsigned char *pIDm,
	unsigned short usServiceCode,
	unsigned char ucBlockOffset,
	unsigned char *pDataW) {
	bool bSuccess;

	// Write Without Encryption コマンドの組み立て
	unsigned char pCom[] = {
		0x00,                                           // データ長
		0x08,                                           // コマンドコード
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // IDm
		0x01,                                           // サービス数
		0x00, 0x00,                                     // サービスコード
		0x01,                                           // ブロック数
		0x00, 0x00, 0x00,                               // ブロック
		'A', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'H'
		/*
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 任意のデータ
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  // 任意のデータ
		*/
	};

	unsigned char pRes[512];

	unsigned short usComLen = sizeof(pCom);
	unsigned short usResLen = sizeof(pRes);

	pCom[0] = sizeof(pCom);

	memcpy_s(&pCom[2], sizeof(pCom) - 2, pIDm, IDM_SIZE);

	pCom[11] = usServiceCode & 0xFF;
	pCom[12] = usServiceCode >> 8;

	pCom[15] = ucBlockOffset;

	memcpy_s(&pCom[17], sizeof(pCom) - 17, pDataW, BLOCK_SIZE);

	// コマンドの発行
	bSuccess = felicalib_nfc_thru(pCom, usComLen, pRes, &usResLen);
	if (!bSuccess)
	{
		PrintNfcLastErr("felicalib_nfc_thru(write without encryption)");
		return false;
	}

	// レスポンスのチェック
	if (usResLen != 1 + 1 + 8 + 1 + 1)
	{
		printf("write w/o enc のレスポンス長 %d が不正 #1\n", usResLen);
		return false;
	}
	if (pRes[0] != 1 + 1 + 8 + 1 + 1)
	{
		printf("write w/o enc のレスポンス長 %d が不正 #2\n", pRes[0]);
		return false;
	}
	if (pRes[1] != 0x09)
	{
		printf("write w/o enc のレスポンスコード %d が不正\n", pRes[1]);
		return false;
	}
	if (pRes[10] != 0x00)
	{
		printf("write w/o enc のステータスフラグが [%02x, %02x] のエラー\n", pRes[10], pRes[11]);
		return false;
	}

	return true;
}

bool FelicaRW::MyReadWithoutEncryption(unsigned char *pIDm,
	unsigned short usServiceCode,
	unsigned char ucBlockOffset,
	unsigned char *pDataR) {
	bool bSuccess;

	// Read Without Encryption コマンドの組み立て
	unsigned char pCom[] = {
		0x00,                                           // データ長
		0x06,                                           // コマンドコード
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // IDm
		0x01,                                           // サービス数
		0x00, 0x00,                                     // サービスコード
		0x01,                                           // ブロック数
		0x00, 0x00, 0x00                                // ブロック
	};

	unsigned char pRes[512];

	unsigned short usComLen = sizeof(pCom);
	unsigned short usResLen = sizeof(pRes);

	pCom[0] = sizeof(pCom);

	memcpy_s(&pCom[2], sizeof(pCom) - 2, pIDm, IDM_SIZE);

	pCom[11] = usServiceCode & 0xFF;
	pCom[12] = usServiceCode >> 8;

	pCom[15] = ucBlockOffset;

	// コマンドの発行
	bSuccess = felicalib_nfc_thru(pCom, usComLen, pRes, &usResLen);
	if (!bSuccess)
	{
		PrintNfcLastErr("felicalib_nfc_thru(read without encryption)");
		return false;
	}

	// レスポンスのチェック
	if (usResLen < 1 + 1 + 8 + 1 + 1)
	{
		printf("read w/o enc のレスポンス長 %d が不正 #1\n", usResLen);
		return false;
	}
	if (pRes[0] < 1 + 1 + 8 + 1 + 1)
	{
		printf("read w/o enc のレスポンス長 %d が不正 #2\n", pRes[0]);
		return false;
	}
	if (pRes[1] != 0x07)
	{
		printf("read w/o enc のレスポンスコード %d が不正\n", pRes[1]);
		return false;
	}
	if (pRes[10] != 0x00)
	{
		printf("read w/o enc のステータスフラグが [%02x, %02x] のエラー\n", pRes[10], pRes[11]);
		return false;
	}

	// 読み出したデータのコピー
	memcpy_s(pDataR, BLOCK_SIZE, &pRes[13], BLOCK_SIZE);

	return true;
}

int FelicaRW::FelicaRW_main(int block, unsigned char* wData, bool read)
{
	strcpy(po, "IDm = ");

	bool bSuccess;
	unsigned char pIDm[IDM_SIZE];

	// ライブラリの初期化
	bSuccess = felicalib_nfc_initialize();
	if (!bSuccess)
	{
		PrintNfcLastErr("felicalib_nfc_initialize");
		goto L_End;
	}

	// ポートのオープン
	char szPort[16] = "";
	bSuccess = felicalib_nfc_open(szPort);
	if (!bSuccess)
	{
		PrintNfcLastErr("felicalib_nfc_open");
		goto L_Uninitialize;
	}
	printf("port=%s\n", szPort);

	// デバイスの補足とアクセス権の取得
	DEVICE_INFO *pInfo;
	bSuccess = felicalib_nfc_poll_and_start_dev_access(
		DEVICE_TYPE_NFC_18092_212K      // FeliCa 212kbps
		| DEVICE_TYPE_NFC_18092_424K,   // FeliCa 424kbps
		3000,                           // タイムアウト ms
		&pInfo);
	if (!bSuccess)
	{
		PrintNfcLastErr("felicalib_nfc_poll_and_start_dev_access");
		goto L_Close;
	}

	// IDm の表示
	DEVICE_DATA_NFC_18092_212_424K *pf;
	pf = (DEVICE_DATA_NFC_18092_212_424K *)pInfo->dev_info;
	printf("IDm=");
	PrintHex(pf->NFCID2, IDM_SIZE);

	// Polling コマンド発行
	bSuccess = MyPolling(SYSTEM_CODE, pIDm);
	if (!bSuccess)
	{
		goto L_StopDevAccess;
	}

	int pBlockNum[] =
	{
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
		0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e,
		0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
		0x88,
	};
	char *pBlockName[] =
	{
		"S_PAD0", "S_PAD1", "S_PAD2", "S_PAD3", "S_PAD4", "S_PAD5", "S_PAD6", "S_PAD7",
		"S_PAD8", "S_PAD9", "S_PAD10", "S_PAD11", "S_PAD12", "S_PAD13", "REG",
		"ID", "D_ID", "SER_C", "SYS_C", "CKV", "CK",
		"MC",
	};

	if (true == read)
	{
		for (int iBlockCount = 0; iBlockCount < sizeof(pBlockNum) / sizeof(int); iBlockCount++)
		{
			unsigned char pDataR[512];
			bSuccess = MyReadWithoutEncryption(
				pIDm,                       // Polling コマンドで取得した IDm
				SERVICE_CODE_RO,            // サービスコード
				pBlockNum[iBlockCount],     // ブロック番号
				pDataR);                    // 読み出したデータの格納場所

			printf("Block[%02x], %-7s=", pBlockNum[iBlockCount], pBlockName[iBlockCount]);
			if (!bSuccess)
			{
				printf("<error>\n");
				continue;
			}

			PrintHex(pDataR, BLOCK_SIZE);

			// 詳細な情報の表示
			if (pBlockNum[iBlockCount] == 0x82)
			{
				printf("                   ");
				printf("(DFC, Data Format Code=%02x %02x)\n", pDataR[8], pDataR[9]);
			}
			else if (pBlockNum[iBlockCount] == 0x83)
			{
				printf("                   ");
				printf("(IC種別=");
				if (pDataR[9] == 0xf0) { printf("FeliCa Lite)\n"); }
				else if (pDataR[9] == 0xf1) { printf("FeliCa Lite-S)\n"); }
				else { printf("?\n"); }
			}
			else if (pBlockNum[iBlockCount] == 0x88)
			{
				printf("                   ");
				printf("(");

				printf("1次発行=%s, ", (pDataR[2] == 0xff ? "未" : "済"));
				printf("2次発行=%s, ", (pDataR[1] & 0x80 ? "未" : "済"));

				printf("NFC=");
				if (pDataR[3] == 0x00) { printf("非対応)\n"); }
				else if (pDataR[3] == 0x01) { printf("対応)\n"); }
				else { printf("対応不明)\n"); }

				printf("                   ");
				printf("(");

				printf("MAC/認証=");
				if (pDataR[5] == 0x00 && pDataR[6] == 0x00 && pDataR[7] == 0x00 && pDataR[8] == 0x00
					&& pDataR[9] == 0x00 && pDataR[10] == 0x00 && pDataR[11] == 0x00 && pDataR[12] == 0x00)
				{
					printf("不要, ");
				}
				else
				{
					printf("要, ");
				}

				printf("全S_PAD RW=");
				if (pDataR[0] == 0xFF && (pDataR[1] & 0x3F) == 0x3F)
				{
					printf("可)\n");
				}
				else
				{
					printf("不可)\n");
				}
			}
		}
	}
	else
	{
		unsigned char pDataW[16] =
		{
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
		};

		MyWriteWithoutEncryption(
			pIDm,
			SERVICE_CODE_RW,		    	//usServiceCode,
			block,							//ucBlockOffset,
			wData);
	}

L_StopDevAccess:
	// デバイス使用権の解放
	bSuccess = felicalib_nfc_stop_dev_access(
		RE_NOTIFICATION_SAME_DEVICE);
	if (!bSuccess)
	{
		PrintNfcLastErr("felicalib_nfc_stop_dev_access");
	}

	// デバイス捕捉処理の停止
	bSuccess = felicalib_nfc_stop_poll_mode();
	if (!bSuccess)
	{
		PrintNfcLastErr("felicalib_nfc_stop_poll_mode");
	}

L_Close:
	// ポートのクローズ
	bSuccess = felicalib_nfc_close();
	if (!bSuccess)
	{
		PrintNfcLastErr("felicalib_nfc_close");
	}

L_Uninitialize:
	// ライブラリの終了処理
	bSuccess = felicalib_nfc_uninitialize();
	if (!bSuccess)
	{
		PrintNfcLastErr("felicalib_nfc_uninitialize");
	}

L_End:

	return 0;
}
