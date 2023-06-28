//=============================================================================
//
// サウンド処理 [xa2.cpp]
//
//=============================================================================

#include "Sound.h"


PARAM g_param[SOUND_LABEL_MAX] =
{
	//BGM読み込み
	{"assets/BGM/Title/TitleBGM.wav", true},					// タイトルBGM（ループさせるのでtrue設定）
	{"assets/BGM/Result/ResultBGM.wav", true},					//　リザルトBGM（ループさせるのでtrue設定）
	{"assets/BGM/Select/BathroomBGM(short).wav", true},			// バスルームBGM(short)（ループさせるのでtrue設定）
	{"assets/BGM/Select/EntranceBGM(short).wav", true},			// 玄関BGM(short)（ループさせるのでtrue設定）
	{"assets/BGM/Select/TableBGM(short).wav", true},			// テーブルBGM(short)（ループさせるのでtrue設定）
	{"assets/BGM/Stage/BathroomBGM(long).wav", true},			// バスルームBGM(long)（ループさせるのでtrue設定）
	{"assets/BGM/Stage/EntranceBGM(long).wav", true},			// 玄関BGM(long)（ループさせるのでtrue設定）
	{"assets/BGM/Stage/TableBGM(long).wav", true},				// テーブルBGM(long)（ループさせるのでtrue設定）
	//ゲームフェードSE読み込み
	{"assets/SE/GameFade/Dog_SOUND.wav", false},  				// 犬のフェードSE（ループしないのでfalse設定）
	{"assets/SE/GameFade/Foam_SOUND.wav", false},  				// 泡のフェードSE（ループしないのでfalse設定）
	//ゲームメインSE読み込み
	{"assets/SE/GameMain/BubbleFly.wav", false},  				// 泡が飛ぶときのSE（ループしないのでfalse設定）
	{"assets/SE/GameMain/BubbleRupture.wav", false},  			// 泡が破裂した時のSE（ループしないのでfalse設定）
	{"assets/SE/GameMain/CatCry.wav", false},  					// 猫鳴き声SE（ループしないのでfalse設定）
	{"assets/SE/GameMain/CatRunAway.wav", false},  				// 猫が逃げる時のSE（ループしないのでfalse設定）
	{"assets/SE/GameMain/CatSurprise.wav", false},				// 猫が驚くときのSE（ループしないのでfalse設定）
	{"assets/SE/GameMain/CatWalk.wav", false},  				// 猫が歩くときのSE（ループしないのでfalse設定）
	{"assets/SE/GameMain/Curve.wav", false},  					// フリスビーカーブSE（ループしないのでfalse設定）
	{"assets/SE/GameMain/DirtCatWalk.wav", false},  			// 汚れの上を歩く時の猫のSE（ループしないのでfalse設定）
	{"assets/SE/GameMain/DogCry.wav", false},  					// 犬鳴き声SE（ループしないのでfalse設定）
	{"assets/SE/GameMain/DogJump.wav", false},  				// 犬ジャンプSE（ループしないのでfalse設定）
	{"assets/SE/GameMain/DogNotice.wav", false},  				// 犬気づくSE（ループしないのでfalse設定）
	{"assets/SE/GameMain/DuckRobotFeet.wav", false},			// アヒルロボット足音SE（ループしないのでfalse設定）
	{"assets/SE/GameMain/FlyAway.wav", false},  				// フリスビー飛んでいくSE（ループしないのでfalse設定）
	{"assets/SE/GameMain/GoronCat.wav", false},  				// 猫ゴロンSE（ループしないのでfalse設定）
	{"assets/SE/GameMain/HalfTimelimit.wav", false},  			// 残り半分SE（ループしないのでfalse設定）
	{"assets/SE/GameMain/JumpOver.wav", false},  				// 犬ジャンプSE（ループしないのでfalse設定）
	{"assets/SE/GameMain/Reducer.wav", false},  				// フリスビー減速SE（ループしないのでfalse設定）
	{"assets/SE/GameMain/RobotFeet.wav", false},  				// ロボット足音SE（ループしないのでfalse設定）
	{"assets/SE/GameMain/Run.wav", false},  					// 走るSE（ループしないのでfalse設定）
	{"assets/SE/GameMain/Slide.wav", false},  					// 滑るSE（ループしないのでfalse設定）
	{"assets/SE/GameMain/Throw.wav", false},  					// フリスビー投げるSE（ループしないのでfalse設定）
	{"assets/SE/GameMain/Timelimit.wav", false},  				// 10秒前SE（ループしないのでfalse設定）
	{"assets/SE/GameMain/Walk.wav", false},  					// 歩くSE（ループしないのでfalse設定）
	//ゲームリザルトSE読み込み
	{"assets/SE/GameResult/Applause_SOUND(A).wav", false},  	// ランクＡSE（ループしないのでfalse設定）
	{"assets/SE/GameResult/Applause_SOUND(B).wav", false},  	// ランクＢSE（ループしないのでfalse設定）
	{"assets/SE/GameResult/Applause_SOUND(C).wav", false},  	// ランクＣSE（ループしないのでfalse設定）
	{"assets/SE/GameResult/Applause_SOUND(S).wav", false},  	// ランクＳSE（ループしないのでfalse設定）
	{"assets/SE/GameResult/Cracker_SOUND.wav", false},  		// クラッカーSE（ループしないのでfalse設定）
	{"assets/SE/GameResult/Gauge_UP_SOUND.wav", false},  		// ゲージアップSE（ループしないのでfalse設定）
	{"assets/SE/GameResult/Rank_SOUND.wav", false},  			// シンバルSE（ループしないのでfalse設定）
	//システムSE
	{"assets/SE/System/Cancel_SOUND.wav", false},  				// キャンセルSE（ループしないのでfalse設定）
	{"assets/SE/System/Cursor_SOUND.wav", false},  				// カーソルSE（ループしないのでfalse設定）
	{"assets/SE/System/Decision_SOUND.wav", false},				// 選択音SE（ループしないのでfalse設定）
	//ピカピカ音	
	{"assets/SE/GameMain/CatchShiny.wav", false},  				// フリスビーキャッチ(ピカピカ)SE（ループしないのでfalse設定）
	{"assets/SE/GameMain/Shiny.wav", false},  					// ピカピカSE（ループしないのでfalse設定）

};

#ifdef _XBOX //Big-Endian
#define fourccRIFF 'RIFF'
#define fourccDATA 'data'
#define fourccFMT 'fmt '
#define fourccWAVE 'WAVE'
#define fourccXWMA 'XWMA'
#define fourccDPDS 'dpds'
#endif
#ifndef _XBOX //Little-Endian
#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT ' tmf'
#define fourccWAVE 'EVAW'
#define fourccXWMA 'AMWX'
#define fourccDPDS 'sdpd'
#endif


//-----------------------------------------------------------------
//    グローバル変数
//-----------------------------------------------------------------
IXAudio2               *g_pXAudio2 = NULL;
IXAudio2MasteringVoice *g_pMasteringVoice = NULL;
IXAudio2SourceVoice    *g_pSourceVoice[SOUND_LABEL_MAX];

WAVEFORMATEXTENSIBLE	g_wfx[SOUND_LABEL_MAX];			// WAVフォーマット
XAUDIO2_BUFFER			g_buffer[SOUND_LABEL_MAX];
BYTE					*g_DataBuffer[SOUND_LABEL_MAX];

//-----------------------------------------------------------------
//    プロトタイプ宣言
//-----------------------------------------------------------------
HRESULT FindChunk(HANDLE, DWORD, DWORD&, DWORD&);
HRESULT ReadChunkData(HANDLE, void*, DWORD, DWORD);

//<><><><><><><><><><><><><><><><><><>
// 関数名： Sound_Initialize
// 役割：サウンドの初期化
// 引数：なし
// 戻り値：HRESURT エラーの場合-1を返す
//<><><><><><><><><><><><><><><><><><>
HRESULT Sound_Initialize()
{
	HRESULT      hr;

	HANDLE               hFile;
	DWORD                dwChunkSize;
	DWORD                dwChunkPosition;
	DWORD                filetype;

	// ＣＯＭの初期化
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	/**** Create XAudio2 ****/
	hr = XAudio2Create(&g_pXAudio2, 0);		// 第二引数は､動作フラグ デバッグモードの指定(現在は未使用なので0にする)
	//hr=XAudio2Create(&g_pXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);		// 第三引数は、windowsでは無視
	if (FAILED(hr)) {
		CoUninitialize();
		return -1;
	}

	/**** Create Mastering Voice ****/
	hr = g_pXAudio2->CreateMasteringVoice(&g_pMasteringVoice);			// 今回はＰＣのデフォルト設定に任せている
	/*, XAUDIO2_DEFAULT_CHANNELS, XAUDIO2_DEFAULT_SAMPLERATE, 0, 0, NULL*/		// 本当６個の引数を持っている
	if (FAILED(hr)) {
		if (g_pXAudio2)	g_pXAudio2->Release();
		CoUninitialize();
		return -1;
	}

	/**** Initalize Sound ****/
	//for (int i = 0; i < SOUND_LABEL_MAX; i++)// 音声を一個ずつ初期化する
	//{
	//	memset(&g_wfx[i], 0, sizeof(WAVEFORMATEXTENSIBLE));// メモリー動的確保?
	//	memset(&g_buffer[i], 0, sizeof(XAUDIO2_BUFFER));// メモリー動的確保?

	//	// ファイル読込み？
	//	hFile = CreateFileA(g_param[i].filename, GENERIC_READ, FILE_SHARE_READ, NULL,
	//		OPEN_EXISTING, 0, NULL);
	//	if (hFile == INVALID_HANDLE_VALUE) {// エラー文？
	//		return HRESULT_FROM_WIN32(GetLastError());
	//	}
	//	if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER) {// エラー文？
	//		return HRESULT_FROM_WIN32(GetLastError());
	//	}

	//	//check the file type, should be fourccWAVE or 'XWMA'
	//	FindChunk(hFile, fourccRIFF, dwChunkSize, dwChunkPosition);
	//	ReadChunkData(hFile, &filetype, sizeof(DWORD), dwChunkPosition);
	//	if (filetype != fourccWAVE)		return S_FALSE;

	//	FindChunk(hFile, fourccFMT, dwChunkSize, dwChunkPosition);
	//	ReadChunkData(hFile, &g_wfx[i], dwChunkSize, dwChunkPosition);

	//	//fill out the audio data buffer with the contents of the fourccDATA chunk
	//	FindChunk(hFile, fourccDATA, dwChunkSize, dwChunkPosition);
	//	g_DataBuffer[i] = new BYTE[dwChunkSize];
	//	ReadChunkData(hFile, g_DataBuffer[i], dwChunkSize, dwChunkPosition);

	//	CloseHandle(hFile);

	//	// 	サブミットボイスで利用するサブミットバッファの設定
	//	g_buffer[i].AudioBytes = dwChunkSize;
	//	g_buffer[i].pAudioData = g_DataBuffer[i];
	//	g_buffer[i].Flags = XAUDIO2_END_OF_STREAM;
	//	if (g_param[i].bLoop)
	//		g_buffer[i].LoopCount = XAUDIO2_LOOP_INFINITE;
	//	else
	//		g_buffer[i].LoopCount = 0;

	//	g_pXAudio2->CreateSourceVoice(&g_pSourceVoice[i], &(g_wfx[i].Format));
	//}

	return hr;
}

void Sound_Init(SOUND_LABEL label)
{
	HANDLE               hFile;
	DWORD                dwChunkSize;
	DWORD                dwChunkPosition;
	DWORD                filetype;


	//int i = label;
	memset(&g_wfx[label], 0, sizeof(WAVEFORMATEXTENSIBLE));// メモリー動的確保?
	memset(&g_buffer[label], 0, sizeof(XAUDIO2_BUFFER));// メモリー動的確保?

	// ファイル読込み？
	hFile = CreateFileA(g_param[label].filename, GENERIC_READ, FILE_SHARE_READ, NULL,
		OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {// エラー文？
		//return HRESULT_FROM_WIN32(GetLastError());
	}
	if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER) {// エラー文？
		//return HRESULT_FROM_WIN32(GetLastError());
	}

	//check the file type, should be fourccWAVE or 'XWMA'
	FindChunk(hFile, fourccRIFF, dwChunkSize, dwChunkPosition);
	ReadChunkData(hFile, &filetype, sizeof(DWORD), dwChunkPosition);
	if (filetype != fourccWAVE) { /*return S_FALSE; */}

		FindChunk(hFile, fourccFMT, dwChunkSize, dwChunkPosition);
		ReadChunkData(hFile, &g_wfx[label], dwChunkSize, dwChunkPosition);

		//fill out the audio data buffer with the contents of the fourccDATA chunk
		FindChunk(hFile, fourccDATA, dwChunkSize, dwChunkPosition);
		g_DataBuffer[label] = new BYTE[dwChunkSize];
		ReadChunkData(hFile, g_DataBuffer[label], dwChunkSize, dwChunkPosition);

		CloseHandle(hFile);

		// 	サブミットボイスで利用するサブミットバッファの設定
		g_buffer[label].AudioBytes = dwChunkSize;
		g_buffer[label].pAudioData = g_DataBuffer[label];
		g_buffer[label].Flags = XAUDIO2_END_OF_STREAM;
		if (g_param[label].bLoop)
			g_buffer[label].LoopCount = XAUDIO2_LOOP_INFINITE;
		else
			g_buffer[label].LoopCount = 0;

		g_pXAudio2->CreateSourceVoice(&g_pSourceVoice[label], &(g_wfx[label].Format));

	
}

void Sound_Uninit(SOUND_LABEL label)
{
	if (g_pSourceVoice[label])
	{
		g_pSourceVoice[label]->Stop(0);
		g_pSourceVoice[label]->FlushSourceBuffers();
		g_pSourceVoice[label]->DestroyVoice();			// オーディオグラフからソースボイスを削除
		delete[]  g_DataBuffer[label];
	}
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：Sound_Release
// 役割：サウンドの削除、COMの破棄
// 引数：なし
// 戻り値：なし
//<><><><><><><><><><><><><><><><><><>
void Sound_Release(void)
{
	//for (int i = 0; i < SOUND_LABEL_MAX; i++)
	//{
	//	if (g_pSourceVoice[i])
	//	{
	//		g_pSourceVoice[i]->Stop(0);
	//		g_pSourceVoice[i]->FlushSourceBuffers();
	//		g_pSourceVoice[i]->DestroyVoice();			// オーディオグラフからソースボイスを削除
	//		delete[]  g_DataBuffer[i];
	//	}
	//}

	g_pMasteringVoice->DestroyVoice();

	if (g_pXAudio2) g_pXAudio2->Release();

	// ＣＯＭの破棄
	CoUninitialize();
}


//<><><><><><><><><><><><><><><><><><>
// 関数名：Play
// 役割：サウンドの再生
// 引数：サウンドハンドル
// 戻り値：なし
//<><><><><><><><><><><><><><><><><><>
void Play(SOUND_LABEL label)
{
	IXAudio2SourceVoice*& pSV = g_pSourceVoice[(int)label];

	if (pSV != nullptr)
	{
		pSV->DestroyVoice();
		pSV = nullptr;
	}

	// ソースボイス作成
	g_pXAudio2->CreateSourceVoice(&pSV, &(g_wfx[(int)label].Format));
	pSV->SubmitSourceBuffer(&(g_buffer[(int)label]));	// ボイスキューに新しいオーディオバッファーを追加

	// 再生
	pSV->Start(0);

}

//<><><><><><><><><><><><><><><><><><>
// 関数名：Stop
// 役割：サウンドの停止
// 引数：サウンドハンドル
// 戻り値：なし
//<><><><><><><><><><><><><><><><><><>
void Stop(SOUND_LABEL label)
{
	if (g_pSourceVoice[(int)label] == NULL) return;

	XAUDIO2_VOICE_STATE xa2state;
	g_pSourceVoice[(int)label]->GetState(&xa2state);
	if (xa2state.BuffersQueued)
	{
		g_pSourceVoice[(int)label]->Stop(0);
	}

}

//<><><><><><><><><><><><><><><><><><>
// 関数名：Resume
// 役割：停止したサウンド再生再開
// 引数：サウンドハンドル
// 戻り値：なし
//<><><><><><><><><><><><><><><><><><>
void Resume(SOUND_LABEL label)
{
	IXAudio2SourceVoice*& pSV = g_pSourceVoice[(int)label];
	pSV->Start();
}

//<><><><><><><><><><><><><><><><><><><><><><><><><><><>
// 関数名：SetVolume
// 役割：音量設定
// 引数：サウンドハンドル、ボリューム(1で通常、0で無音)
// 戻り値：なし
//<><><><><><><><><><><><><><><><><><><><><><><><><><><>
void SetVolume(SOUND_LABEL label, float Volume)
{
	IXAudio2SourceVoice*& pSV = g_pSourceVoice[(int)label];

	pSV->SetVolume(Volume);
}

//<><><><><><><><><><><><><><><><><><><><><><><><><><><>
// 関数名：GetSoundState
// 役割：サウンドの再生状態を取得する
// 引数：サウンドハンドル
// 戻り値：TRUE：再生中　FALSE：再生終了
//<><><><><><><><><><><><><><><><><><><><><><><><><><><>
bool GetSoundState(SOUND_LABEL label)
{
	XAUDIO2_VOICE_STATE state;
	IXAudio2SourceVoice*& pSV = g_pSourceVoice[(int)label];
	pSV->GetState(&state);

	//再生中ならtrueを返す
	if (state.BuffersQueued != FALSE) {
		return TRUE;
	}//　再生終了していればfalseを返す
	else{
		return FALSE;
	}

}


//=============================================================================
// ユーティリティ関数群
//=============================================================================
HRESULT FindChunk(HANDLE hFile, DWORD fourcc, DWORD & dwChunkSize, DWORD & dwChunkDataPosition)
{
	HRESULT hr = S_OK;
	if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_BEGIN))
		return HRESULT_FROM_WIN32(GetLastError());
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD bytesRead = 0;
	DWORD dwOffset = 0;
	while (hr == S_OK)
	{
		DWORD dwRead;
		if (0 == ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL))
			hr = HRESULT_FROM_WIN32(GetLastError());
		if (0 == ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL))
			hr = HRESULT_FROM_WIN32(GetLastError());
		switch (dwChunkType)
		{
		case fourccRIFF:
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			if (0 == ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL))
				hr = HRESULT_FROM_WIN32(GetLastError());
			break;
		default:
			if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT))
				return HRESULT_FROM_WIN32(GetLastError());
		}
		dwOffset += sizeof(DWORD) * 2;
		if (dwChunkType == fourcc)
		{
			dwChunkSize = dwChunkDataSize;
			dwChunkDataPosition = dwOffset;
			return S_OK;
		}
		dwOffset += dwChunkDataSize;
		if (bytesRead >= dwRIFFDataSize) return S_FALSE;
	}
	return S_OK;
}

HRESULT ReadChunkData(HANDLE hFile, void * buffer, DWORD buffersize, DWORD bufferoffset)
{
	HRESULT hr = S_OK;
	if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, bufferoffset, NULL, FILE_BEGIN))
		return HRESULT_FROM_WIN32(GetLastError());
	DWORD dwRead;
	if (0 == ReadFile(hFile, buffer, buffersize, &dwRead, NULL))
		hr = HRESULT_FROM_WIN32(GetLastError());
	return hr;
}
