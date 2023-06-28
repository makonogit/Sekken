//=============================================================================
//
// �T�E���h���� [xa2.cpp]
//
//=============================================================================

#include "Sound.h"


PARAM g_param[SOUND_LABEL_MAX] =
{
	//BGM�ǂݍ���
	{"assets/BGM/Title/TitleBGM.wav", true},					// �^�C�g��BGM�i���[�v������̂�true�ݒ�j
	{"assets/BGM/Result/ResultBGM.wav", true},					//�@���U���gBGM�i���[�v������̂�true�ݒ�j
	{"assets/BGM/Select/BathroomBGM(short).wav", true},			// �o�X���[��BGM(short)�i���[�v������̂�true�ݒ�j
	{"assets/BGM/Select/EntranceBGM(short).wav", true},			// ����BGM(short)�i���[�v������̂�true�ݒ�j
	{"assets/BGM/Select/TableBGM(short).wav", true},			// �e�[�u��BGM(short)�i���[�v������̂�true�ݒ�j
	{"assets/BGM/Stage/BathroomBGM(long).wav", true},			// �o�X���[��BGM(long)�i���[�v������̂�true�ݒ�j
	{"assets/BGM/Stage/EntranceBGM(long).wav", true},			// ����BGM(long)�i���[�v������̂�true�ݒ�j
	{"assets/BGM/Stage/TableBGM(long).wav", true},				// �e�[�u��BGM(long)�i���[�v������̂�true�ݒ�j
	//�Q�[���t�F�[�hSE�ǂݍ���
	{"assets/SE/GameFade/Dog_SOUND.wav", false},  				// ���̃t�F�[�hSE�i���[�v���Ȃ��̂�false�ݒ�j
	{"assets/SE/GameFade/Foam_SOUND.wav", false},  				// �A�̃t�F�[�hSE�i���[�v���Ȃ��̂�false�ݒ�j
	//�Q�[�����C��SE�ǂݍ���
	{"assets/SE/GameMain/BubbleFly.wav", false},  				// �A����ԂƂ���SE�i���[�v���Ȃ��̂�false�ݒ�j
	{"assets/SE/GameMain/BubbleRupture.wav", false},  			// �A���j�􂵂�����SE�i���[�v���Ȃ��̂�false�ݒ�j
	{"assets/SE/GameMain/CatCry.wav", false},  					// �L����SE�i���[�v���Ȃ��̂�false�ݒ�j
	{"assets/SE/GameMain/CatRunAway.wav", false},  				// �L�������鎞��SE�i���[�v���Ȃ��̂�false�ݒ�j
	{"assets/SE/GameMain/CatSurprise.wav", false},				// �L�������Ƃ���SE�i���[�v���Ȃ��̂�false�ݒ�j
	{"assets/SE/GameMain/CatWalk.wav", false},  				// �L�������Ƃ���SE�i���[�v���Ȃ��̂�false�ݒ�j
	{"assets/SE/GameMain/Curve.wav", false},  					// �t���X�r�[�J�[�uSE�i���[�v���Ȃ��̂�false�ݒ�j
	{"assets/SE/GameMain/DirtCatWalk.wav", false},  			// ����̏��������̔L��SE�i���[�v���Ȃ��̂�false�ݒ�j
	{"assets/SE/GameMain/DogCry.wav", false},  					// ������SE�i���[�v���Ȃ��̂�false�ݒ�j
	{"assets/SE/GameMain/DogJump.wav", false},  				// ���W�����vSE�i���[�v���Ȃ��̂�false�ݒ�j
	{"assets/SE/GameMain/DogNotice.wav", false},  				// ���C�Â�SE�i���[�v���Ȃ��̂�false�ݒ�j
	{"assets/SE/GameMain/DuckRobotFeet.wav", false},			// �A�q�����{�b�g����SE�i���[�v���Ȃ��̂�false�ݒ�j
	{"assets/SE/GameMain/FlyAway.wav", false},  				// �t���X�r�[���ł���SE�i���[�v���Ȃ��̂�false�ݒ�j
	{"assets/SE/GameMain/GoronCat.wav", false},  				// �L�S����SE�i���[�v���Ȃ��̂�false�ݒ�j
	{"assets/SE/GameMain/HalfTimelimit.wav", false},  			// �c�蔼��SE�i���[�v���Ȃ��̂�false�ݒ�j
	{"assets/SE/GameMain/JumpOver.wav", false},  				// ���W�����vSE�i���[�v���Ȃ��̂�false�ݒ�j
	{"assets/SE/GameMain/Reducer.wav", false},  				// �t���X�r�[����SE�i���[�v���Ȃ��̂�false�ݒ�j
	{"assets/SE/GameMain/RobotFeet.wav", false},  				// ���{�b�g����SE�i���[�v���Ȃ��̂�false�ݒ�j
	{"assets/SE/GameMain/Run.wav", false},  					// ����SE�i���[�v���Ȃ��̂�false�ݒ�j
	{"assets/SE/GameMain/Slide.wav", false},  					// ����SE�i���[�v���Ȃ��̂�false�ݒ�j
	{"assets/SE/GameMain/Throw.wav", false},  					// �t���X�r�[������SE�i���[�v���Ȃ��̂�false�ݒ�j
	{"assets/SE/GameMain/Timelimit.wav", false},  				// 10�b�OSE�i���[�v���Ȃ��̂�false�ݒ�j
	{"assets/SE/GameMain/Walk.wav", false},  					// ����SE�i���[�v���Ȃ��̂�false�ݒ�j
	//�Q�[�����U���gSE�ǂݍ���
	{"assets/SE/GameResult/Applause_SOUND(A).wav", false},  	// �����N�`SE�i���[�v���Ȃ��̂�false�ݒ�j
	{"assets/SE/GameResult/Applause_SOUND(B).wav", false},  	// �����N�aSE�i���[�v���Ȃ��̂�false�ݒ�j
	{"assets/SE/GameResult/Applause_SOUND(C).wav", false},  	// �����N�bSE�i���[�v���Ȃ��̂�false�ݒ�j
	{"assets/SE/GameResult/Applause_SOUND(S).wav", false},  	// �����N�rSE�i���[�v���Ȃ��̂�false�ݒ�j
	{"assets/SE/GameResult/Cracker_SOUND.wav", false},  		// �N���b�J�[SE�i���[�v���Ȃ��̂�false�ݒ�j
	{"assets/SE/GameResult/Gauge_UP_SOUND.wav", false},  		// �Q�[�W�A�b�vSE�i���[�v���Ȃ��̂�false�ݒ�j
	{"assets/SE/GameResult/Rank_SOUND.wav", false},  			// �V���o��SE�i���[�v���Ȃ��̂�false�ݒ�j
	//�V�X�e��SE
	{"assets/SE/System/Cancel_SOUND.wav", false},  				// �L�����Z��SE�i���[�v���Ȃ��̂�false�ݒ�j
	{"assets/SE/System/Cursor_SOUND.wav", false},  				// �J�[�\��SE�i���[�v���Ȃ��̂�false�ݒ�j
	{"assets/SE/System/Decision_SOUND.wav", false},				// �I����SE�i���[�v���Ȃ��̂�false�ݒ�j
	//�s�J�s�J��	
	{"assets/SE/GameMain/CatchShiny.wav", false},  				// �t���X�r�[�L���b�`(�s�J�s�J)SE�i���[�v���Ȃ��̂�false�ݒ�j
	{"assets/SE/GameMain/Shiny.wav", false},  					// �s�J�s�JSE�i���[�v���Ȃ��̂�false�ݒ�j

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
//    �O���[�o���ϐ�
//-----------------------------------------------------------------
IXAudio2               *g_pXAudio2 = NULL;
IXAudio2MasteringVoice *g_pMasteringVoice = NULL;
IXAudio2SourceVoice    *g_pSourceVoice[SOUND_LABEL_MAX];

WAVEFORMATEXTENSIBLE	g_wfx[SOUND_LABEL_MAX];			// WAV�t�H�[�}�b�g
XAUDIO2_BUFFER			g_buffer[SOUND_LABEL_MAX];
BYTE					*g_DataBuffer[SOUND_LABEL_MAX];

//-----------------------------------------------------------------
//    �v���g�^�C�v�錾
//-----------------------------------------------------------------
HRESULT FindChunk(HANDLE, DWORD, DWORD&, DWORD&);
HRESULT ReadChunkData(HANDLE, void*, DWORD, DWORD);

//<><><><><><><><><><><><><><><><><><>
// �֐����F Sound_Initialize
// �����F�T�E���h�̏�����
// �����F�Ȃ�
// �߂�l�FHRESURT �G���[�̏ꍇ-1��Ԃ�
//<><><><><><><><><><><><><><><><><><>
HRESULT Sound_Initialize()
{
	HRESULT      hr;

	HANDLE               hFile;
	DWORD                dwChunkSize;
	DWORD                dwChunkPosition;
	DWORD                filetype;

	// �b�n�l�̏�����
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	/**** Create XAudio2 ****/
	hr = XAudio2Create(&g_pXAudio2, 0);		// �������ͤ����t���O �f�o�b�O���[�h�̎w��(���݂͖��g�p�Ȃ̂�0�ɂ���)
	//hr=XAudio2Create(&g_pXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);		// ��O�����́Awindows�ł͖���
	if (FAILED(hr)) {
		CoUninitialize();
		return -1;
	}

	/**** Create Mastering Voice ****/
	hr = g_pXAudio2->CreateMasteringVoice(&g_pMasteringVoice);			// ����͂o�b�̃f�t�H���g�ݒ�ɔC���Ă���
	/*, XAUDIO2_DEFAULT_CHANNELS, XAUDIO2_DEFAULT_SAMPLERATE, 0, 0, NULL*/		// �{���U�̈����������Ă���
	if (FAILED(hr)) {
		if (g_pXAudio2)	g_pXAudio2->Release();
		CoUninitialize();
		return -1;
	}

	/**** Initalize Sound ****/
	//for (int i = 0; i < SOUND_LABEL_MAX; i++)// �������������������
	//{
	//	memset(&g_wfx[i], 0, sizeof(WAVEFORMATEXTENSIBLE));// �������[���I�m��?
	//	memset(&g_buffer[i], 0, sizeof(XAUDIO2_BUFFER));// �������[���I�m��?

	//	// �t�@�C���Ǎ��݁H
	//	hFile = CreateFileA(g_param[i].filename, GENERIC_READ, FILE_SHARE_READ, NULL,
	//		OPEN_EXISTING, 0, NULL);
	//	if (hFile == INVALID_HANDLE_VALUE) {// �G���[���H
	//		return HRESULT_FROM_WIN32(GetLastError());
	//	}
	//	if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER) {// �G���[���H
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

	//	// 	�T�u�~�b�g�{�C�X�ŗ��p����T�u�~�b�g�o�b�t�@�̐ݒ�
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
	memset(&g_wfx[label], 0, sizeof(WAVEFORMATEXTENSIBLE));// �������[���I�m��?
	memset(&g_buffer[label], 0, sizeof(XAUDIO2_BUFFER));// �������[���I�m��?

	// �t�@�C���Ǎ��݁H
	hFile = CreateFileA(g_param[label].filename, GENERIC_READ, FILE_SHARE_READ, NULL,
		OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {// �G���[���H
		//return HRESULT_FROM_WIN32(GetLastError());
	}
	if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER) {// �G���[���H
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

		// 	�T�u�~�b�g�{�C�X�ŗ��p����T�u�~�b�g�o�b�t�@�̐ݒ�
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
		g_pSourceVoice[label]->DestroyVoice();			// �I�[�f�B�I�O���t����\�[�X�{�C�X���폜
		delete[]  g_DataBuffer[label];
	}
}

//<><><><><><><><><><><><><><><><><><>
// �֐����FSound_Release
// �����F�T�E���h�̍폜�ACOM�̔j��
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//<><><><><><><><><><><><><><><><><><>
void Sound_Release(void)
{
	//for (int i = 0; i < SOUND_LABEL_MAX; i++)
	//{
	//	if (g_pSourceVoice[i])
	//	{
	//		g_pSourceVoice[i]->Stop(0);
	//		g_pSourceVoice[i]->FlushSourceBuffers();
	//		g_pSourceVoice[i]->DestroyVoice();			// �I�[�f�B�I�O���t����\�[�X�{�C�X���폜
	//		delete[]  g_DataBuffer[i];
	//	}
	//}

	g_pMasteringVoice->DestroyVoice();

	if (g_pXAudio2) g_pXAudio2->Release();

	// �b�n�l�̔j��
	CoUninitialize();
}


//<><><><><><><><><><><><><><><><><><>
// �֐����FPlay
// �����F�T�E���h�̍Đ�
// �����F�T�E���h�n���h��
// �߂�l�F�Ȃ�
//<><><><><><><><><><><><><><><><><><>
void Play(SOUND_LABEL label)
{
	IXAudio2SourceVoice*& pSV = g_pSourceVoice[(int)label];

	if (pSV != nullptr)
	{
		pSV->DestroyVoice();
		pSV = nullptr;
	}

	// �\�[�X�{�C�X�쐬
	g_pXAudio2->CreateSourceVoice(&pSV, &(g_wfx[(int)label].Format));
	pSV->SubmitSourceBuffer(&(g_buffer[(int)label]));	// �{�C�X�L���[�ɐV�����I�[�f�B�I�o�b�t�@�[��ǉ�

	// �Đ�
	pSV->Start(0);

}

//<><><><><><><><><><><><><><><><><><>
// �֐����FStop
// �����F�T�E���h�̒�~
// �����F�T�E���h�n���h��
// �߂�l�F�Ȃ�
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
// �֐����FResume
// �����F��~�����T�E���h�Đ��ĊJ
// �����F�T�E���h�n���h��
// �߂�l�F�Ȃ�
//<><><><><><><><><><><><><><><><><><>
void Resume(SOUND_LABEL label)
{
	IXAudio2SourceVoice*& pSV = g_pSourceVoice[(int)label];
	pSV->Start();
}

//<><><><><><><><><><><><><><><><><><><><><><><><><><><>
// �֐����FSetVolume
// �����F���ʐݒ�
// �����F�T�E���h�n���h���A�{�����[��(1�Œʏ�A0�Ŗ���)
// �߂�l�F�Ȃ�
//<><><><><><><><><><><><><><><><><><><><><><><><><><><>
void SetVolume(SOUND_LABEL label, float Volume)
{
	IXAudio2SourceVoice*& pSV = g_pSourceVoice[(int)label];

	pSV->SetVolume(Volume);
}

//<><><><><><><><><><><><><><><><><><><><><><><><><><><>
// �֐����FGetSoundState
// �����F�T�E���h�̍Đ���Ԃ��擾����
// �����F�T�E���h�n���h��
// �߂�l�FTRUE�F�Đ����@FALSE�F�Đ��I��
//<><><><><><><><><><><><><><><><><><><><><><><><><><><>
bool GetSoundState(SOUND_LABEL label)
{
	XAUDIO2_VOICE_STATE state;
	IXAudio2SourceVoice*& pSV = g_pSourceVoice[(int)label];
	pSV->GetState(&state);

	//�Đ����Ȃ�true��Ԃ�
	if (state.BuffersQueued != FALSE) {
		return TRUE;
	}//�@�Đ��I�����Ă����false��Ԃ�
	else{
		return FALSE;
	}

}


//=============================================================================
// ���[�e�B���e�B�֐��Q
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
