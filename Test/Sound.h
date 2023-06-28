//======================================================================================
// ���O�FSound.h
// �����F�T�E���h
//======================================================================================
#ifndef _XAUDIO2_H_
#define _XAUDIO2_H_

#include <xaudio2.h>


// �p�����[�^�\����
typedef struct
{
	LPCSTR filename;	// �����t�@�C���܂ł̃p�X��ݒ�
	bool bLoop;			// true�Ń��[�v�B�ʏ�BGM��ture�ASE��false�B
} PARAM;

// �T�E���h�t�@�C��
typedef enum
{
	//BGM
	SOUND_LABEL_BGM000,			// �^�C�g��BGM
	SOUND_LABEL_BGM001,			// ���U���gBGM
	SOUND_LABEL_BGM002,			// �o�X���[��BGM(short)
	SOUND_LABEL_BGM003,			// ����BGM(short)
	SOUND_LABEL_BGM004,			// �e�[�u��BGM(short)
	SOUND_LABEL_BGM005,			// �o�X���[��BGM(long)
	SOUND_LABEL_BGM006,			// ����BGM(long)
	SOUND_LABEL_BGM007,			// �e�[�u��BGM(long)
	//�Q�[���t�F�[�hSE
	SOUND_LABEL_SE000,			// ���̃t�F�[�hSE
	SOUND_LABEL_SE001,			// �A�̃t�F�[�hSE
	//�Q�[�����C��SE
	SOUND_LABEL_SE002,			// �A����ԂƂ���SE
	SOUND_LABEL_SE003,			// �A���j�􂵂�����SE
	SOUND_LABEL_SE004,			// �L����SE
	SOUND_LABEL_SE005,			// �L�������鎞��SE
	SOUND_LABEL_SE006,			// �L�������Ƃ���SE
	SOUND_LABEL_SE007,			// �L�������Ƃ���SE
	SOUND_LABEL_SE008,			// �t���X�r�[�J�[�uSE
	SOUND_LABEL_SE009,			// ����̏��������̔L��SE
	SOUND_LABEL_SE010,			// ������SE
	SOUND_LABEL_SE011,			// ���W�����vSE
	SOUND_LABEL_SE012,			// ���C�Â�SE
	SOUND_LABEL_SE013,			// �A�q�����{�b�g����SE
	SOUND_LABEL_SE014,			// �t���X�r�[���ł���SE
	SOUND_LABEL_SE015,			// �L�S����SE
	SOUND_LABEL_SE016,			// �c�蔼��SE
	SOUND_LABEL_SE017,			// ���W�����vSE
	SOUND_LABEL_SE018,			// �t���X�r�[����SE
	SOUND_LABEL_SE019,			// ���{�b�g����SE
	SOUND_LABEL_SE020,			// ����SE
	SOUND_LABEL_SE021,			// ����SE
	SOUND_LABEL_SE022,			// �t���X�r�[������SE
	SOUND_LABEL_SE023,			// 10�b�OSE
	SOUND_LABEL_SE024,			// ����SE
	//�Q�[�����U���gSE
	SOUND_LABEL_SE025,			// �����N�`SE
	SOUND_LABEL_SE026,			// �����N�aSE
	SOUND_LABEL_SE027,			// �����N�bSE
	SOUND_LABEL_SE028,			// �����N�rSE
	SOUND_LABEL_SE029,			// �N���b�J�[SE
	SOUND_LABEL_SE030,			// �Q�[�W�A�b�vSE
	SOUND_LABEL_SE031,			// �V���o��SE
	//�V�X�e��SE
	SOUND_LABEL_SE032,			// �L�����Z��SE
	SOUND_LABEL_SE033,			// �J�[�\��SE
	SOUND_LABEL_SE034,			// �I����SE
	//�s�J�s�J��
	SOUND_LABEL_SE035,			// �t���X�r�[�L���b�`(�s�J�s�J)SE
	SOUND_LABEL_SE036,			// �s�J�s�JSE
	SOUND_LABEL_MAX,

} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

// �Q�[�����[�v�J�n�O�ɌĂяo���T�E���h�̏���������
HRESULT Sound_Initialize(void);

// ������
void Sound_Init(SOUND_LABEL label);

// ���
void Sound_Uninit(SOUND_LABEL label);

// �Q�[�����[�v�I����ɌĂяo���T�E���h�̉������
void Sound_Release(void);

// �����Ŏw�肵���T�E���h���Đ�����
void Play(SOUND_LABEL label);

// �����Ŏw�肵���T�E���h���~����
void Stop(SOUND_LABEL label);

// �����Ŏw�肵���T�E���h�̍Đ����ĊJ����
void Resume(SOUND_LABEL label);

//�@�����Ŏw�肵�����ʂ��Z�b�g����
void SetVolume(SOUND_LABEL label, float Volume);

//�@�����Ŏw�肵���T�E���h���Đ�������Ԃ�
bool GetSoundState(SOUND_LABEL label);

#endif

//======================================================================================
// �S���ҁF		�����S
// ��������F�@ 2022-12-01
// �`�[�����F	����	
//======================================================================================
