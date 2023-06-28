//======================================================================================
// ���O�FInput
// �����F�L�[�{�[�h�A�}�E�X�ƃR���g���[���[�̏�Ԃ�����
//======================================================================================
#pragma once

//------------------------------------
//		include
//------------------------------------

#include <Windows.h>// memcpy�p

//�����ӁFWindows.h��������Xinput.h��u������
#include <Xinput.h>

//------------------------------------
//		�}�N����`
//------------------------------------

#define KEY_MAX 256

//------------------------------------
//		�񋓌^
//------------------------------------

// �Q�[���p�b�h�̃{�^���̎��ʔԍ�
enum GAMEPAD_BUTTON:unsigned int 
{
	NONE		= 0x0000,
	UP			= 0x0001,
	DOWN		= 0x0002,
	LEFT		= 0x0004,
	RIGHT		= 0x0008,

	START		= 0x0010,
	BACK		= 0X0020,
	LEFT_STICK	= 0x0040,
	RIGHT_STICK	= 0x0080,

	LB			= 0x0100,
	RB			= 0x0200,
	A			= 0x1000,
	B			= 0x2000,
	X			= 0x4000,
	Y			= 0x8000,
};
//------------------------------------
//		�\����
//------------------------------------

typedef struct Input
{
	bool mKeyState[KEY_MAX];// ���݂̃L�[�{�[�h�̏��
	bool mOldKeyState[KEY_MAX];// �ߋ��̃L�[�{�[�h�̏��

	//bool GamePad;
	XINPUT_STATE mGamePadState;// �R���g���[���[�̏�Ԃ�����(1����)
	XINPUT_GAMEPAD mOldGamePadButton;// �ߋ��̏�Ԃ�����
	XINPUT_VIBRATION vibration;// �o�C�u���[�V����
	//float vibrationTime;

	int mMousePosition_X, mMousePosition_Y;// �}�E�X�̈ʒu������
	int mKeyCount;
	
}Input;

//------------------------------------
//		�v���g�^�C�v�錾
//------------------------------------

void Input_Init();// ����������
void Input_Update();// �X�V����
void Input_Release();// �������

// Set

void Input_SetMousePos(long mousepos);// �}�E�X�J�[�\���̈ʒu���Z�b�g����
void Input_SetKeyDown(int key);// �L�[�������ꂽ���̏���
void Input_SetKeyUp(int key);// �L�[�𗣂������̏���
void Input_SetVibration(int rightSpeed, int leftSpeed);// �o�C�u���[�V�����̐ݒ�

// Get

bool Input_GetKeyDown(int key);// �L�[��������Ă��邪
bool Input_GetKeyTrigger(int key);// �L�[�������ꂽ�u��

int Input_GetMousePosX(void);// �}�E�X��X���W�@���ǉ����܂���
int Input_GetMousePosY(void);// �}�E�X��X���W�@���ǉ����܂���

bool Input_GetButtonDown(GAMEPAD_BUTTON num);// �Q�[���p�b�h�̃{�^����������Ă��邪
bool Input_GetButtonTrigger(GAMEPAD_BUTTON num);// �Q�[���p�b�h�̃{�^���������ꂽ�u��
float Input_GetLeftStick_X(void);// L�X�e�B�b�N�̇]�̒l��Ԃ�
float Input_GetLeftStick_Y(void);// L�X�e�B�b�N�̂x�̒l��Ԃ�
float Input_GetRightStick_X(void);// �q�X�e�B�b�N�̇]�̒l��Ԃ�
float Input_GetRightStick_Y(void);// �q�X�e�B�b�N�̂x�̒l��Ԃ�
int Input_GetLTButton(void);// LT�{�^���̒l��Ԃ�0�`255
int Input_GetRTButton(void);// RT�{�^���̒l��Ԃ�0�`255

//======================================================================================
// �N���X�F		AT12E224
// �o�Ȕԍ��F	16
// �S���ҁF		���쒼�o
// �`�[�����F	����	
//======================================================================================