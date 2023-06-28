//======================================================================================
// ���O�FInput
// �����F�L�[�{�[�h�A�}�E�X�ƃR���g���[���[�̏�Ԃ�����
//======================================================================================

//------------------------------------
//		include
//------------------------------------

#include "Input.h"


//------------------------------------
//		�����N�w��
//------------------------------------

#pragma comment (lib,"xinput.lib")// �Q�[���p�b�h�̃C���v�b�g

//------------------------------------
//		�O���[�o���ϐ��錾
//------------------------------------

Input* gpInput;

//------------------------------------
//		�v���g�^�C�v�錾
//------------------------------------

void Rfresh();// ���t���b�V��

//------------------------------------
//		�֐�
//------------------------------------


//<><><><><><><><><><><><><><><><><><>
// �֐����F���t���b�V���֐�
// �����FmOldKeyState��mOldGamePadButton�̍X�V����
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//<><><><><><><><><><><><><><><><><><>
void Rfresh()
{
	// �Q�[�����[�v�̍Ō�Ō��݂̃L�[��Ԃ�gOldKeyState�ɕۑ�
	memcpy_s(gpInput->mOldKeyState, sizeof(gpInput->mOldKeyState),
		gpInput->mKeyState, sizeof(gpInput->mKeyState));

	gpInput->mKeyCount = 0;// ���Z�b�g
	for (int i = 0; i < KEY_MAX; i++)
	{
		gpInput->mKeyCount += (int)gpInput->mKeyState[i];// �����ꂽ���𐔂���
	}
	
	// ���݂̃Q�[���p�b�h�̏�Ԃ�mOldGamePadButton�ɕۑ�
	gpInput->mOldGamePadButton = gpInput->mGamePadState.Gamepad;
}


//<><><><><><><><><><><><><><><><><><>
// �֐����F�����������֐�
// �����FInput�\���̂̓��I�m�ۂ�����
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//<><><><><><><><><><><><><><><><><><>
void Input_Init()
{
	gpInput = (Input*)malloc(sizeof(Input));
	for (int i = 0; i < KEY_MAX; i++)
	{
		gpInput->mKeyState[i] = false;// ������
	}
	ZeroMemory(&gpInput->mGamePadState, sizeof(XINPUT_STATE));
	ZeroMemory(&gpInput->vibration, sizeof(XINPUT_VIBRATION));
}


//<><><><><><><><><><><><><><><><><><>
// �֐����F�A�b�v�f�[�g�֐�
// �����FInput�\���̂̏�Ԃ��X�V����
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//<><><><><><><><><><><><><><><><><><>
void Input_Update()
{
	Rfresh();
	XInputGetState(0, &gpInput->mGamePadState);// �Q�[���p�b�h�̏�Ԃ��擾����
	
}


//<><><><><><><><><><><><><><><><><><>
// �֐����F�����[�X�֐�
// �����F���I�m�ۂ���Input�\���̂��������
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//<><><><><><><><><><><><><><><><><><>
void Input_Release()
{
	free(gpInput);
}


//<><><><><><><><><><><><><><><><><><>
// �֐����F�Z�b�g�}�E�X�|�W�V�����֐�
// �����F�}�E�X�J�[�\���̍��W��ݒ肷��
// �����Flong �}�E�X�̍��W
// �߂�l�F�Ȃ�
//<><><><><><><><><><><><><><><><><><>
void Input_SetMousePos(long mousepos)
{
	// ���ʃr�b�g���擾����
	gpInput->mMousePosition_X = mousepos & 0x0000ffff;
	// ��ʃr�b�g���擾����
	gpInput->mMousePosition_Y = (mousepos & 0xffff0000) >> 16;
}


//<><><><><><><><><><><><><><><><><><>
// �֐����F�Z�b�g�L�[�_�E���֐�
// �����F�����ꂽ�L�[��ݒ肷��
// �����Fint �����ꂽ�L�[
// �߂�l�F�Ȃ�
//<><><><><><><><><><><><><><><><><><>
void Input_SetKeyDown(int key)
{
	gpInput->mKeyState[key] = true;
}


//<><><><><><><><><><><><><><><><><><>
// �֐����F�Z�b�g�L�[�A�b�v�֐�
// �����F�������L�[��ݒ肷��
// �����Fint �������L�[
// �߂�l�F�Ȃ�
//<><><><><><><><><><><><><><><><><><>
void Input_SetKeyUp(int key)
{
	gpInput->mKeyState[key] = false;
}


//<><><><><><><><><><><><><><><><><><>
// �֐����F�Z�b�g�o�C�u���[�V�����֐�
// �����F�o�C�u���[�V������ݒ肷��B�����ӁF�A���ŌĂԂƃR���g���[���̐ڑ����ؒf�����̂ŉ�������΍��͍����ł�
// �����Fint �E�̉�]���x, int ���̉�]���x
// �߂�l�F�Ȃ�
//<><><><><><><><><><><><><><><><><><>
void Input_SetVibration(int rightSpeed, int leftSpeed)
{
	if(gpInput->vibration.wLeftMotorSpeed != leftSpeed && gpInput->vibration.wRightMotorSpeed != rightSpeed)
	{
		gpInput->vibration.wLeftMotorSpeed = leftSpeed;// 0�`65535�̊ԂŎg��
		gpInput->vibration.wRightMotorSpeed = rightSpeed;// 0�`65535�̊ԂŎg��
		XInputSetState(0, &gpInput->vibration);// �U��
	}
}


//<><><><><><><><><><><><><><><><><><>
// �֐����F�Q�b�g�L�[�_�E���֐�
// �����F�L�[��������Ă��邩���ʂ���
// �����Fint ���ʂ������L�[
// �߂�l�Fbool�@true ������Ă���@false ������ĂȂ�
//<><><><><><><><><><><><><><><><><><>
bool Input_GetKeyDown(int key)
{
	return gpInput->mKeyState[key];
}


//<><><><><><><><><><><><><><><><><><>
// �֐����F�Q�b�g�L�[�g���K�[�֐�
// �����F�L�[�������ꂽ�u�Ԃ𔻕ʂ���
// �����Fint ���ʂ������L�[
// �߂�l�Fbool�@true �������u�ԁ@false ����ȊO
//<><><><><><><><><><><><><><><><><><>
bool Input_GetKeyTrigger(int key)
{
	return  (gpInput->mKeyState[key] == TRUE )&& (gpInput->mOldKeyState[key] == FALSE);
}

//<><><><><><><><><><><><><><><><><><>
// �֐����F�Q�b�g�}�E�X�|�YX�֐�
// �����F�}�E�X�̈ʒu���擾
// �����F�i�V
// �߂�l�Fint 
//<><><><><><><><><><><><><><><><><><>
int Input_GetMousePosX(void)
{
	return gpInput->mMousePosition_X;
}

//<><><><><><><><><><><><><><><><><><>
// �֐����F�Q�b�g�}�E�X�|�YX�֐�
// �����F�}�E�X�̈ʒu���擾
// �����F�i�V
// �߂�l�Fint 
//<><><><><><><><><><><><><><><><><><>
int Input_GetMousePosY(void)
{
	return gpInput->mMousePosition_Y;
}


//<><><><><><><><><><><><><><><><><><>
// �֐����F�Q�b�g�{�^���_�E���֐�
// �����F�{�^����������Ă��邩���ʂ���
// �����FGAMEPAD_BUTTON�@���ʂ������{�^��
// �߂�l�Fbool�@true ������Ă���@false ������ĂȂ�
//<><><><><><><><><><><><><><><><><><>
bool Input_GetButtonDown(GAMEPAD_BUTTON num)
{
	return gpInput->mGamePadState.Gamepad.wButtons & num;
}


//<><><><><><><><><><><><><><><><><><>
// �֐����F�Q�b�g�{�^���g���K�[�֐�
// �����F�{�^���̉����ꂽ�u�Ԃ𔻕ʂ���
// �����FGAMEPAD_BUTTON�@���ʂ������{�^��
// �߂�l�Fbool�@true �������u�ԁ@false ����ȊO
//<><><><><><><><><><><><><><><><><><>
bool Input_GetButtonTrigger(GAMEPAD_BUTTON num)
{
	return ((gpInput->mGamePadState.Gamepad.wButtons & num) && !(gpInput->mOldGamePadButton.wButtons & num));
}


//<><><><><><><><><><><><><><><><><><>
// �֐����F�Q�b�g���t�g�X�e�B�b�N�]�֐�
// �����FL�X�e�B�b�N�̇]�̓��͂�1.0f�`0,0f�͈̔͂ŕԂ�
// �����F�Ȃ�
// �߂�l�Ffloat 1.0f�`0,0f�͈̔�
//<><><><><><><><><><><><><><><><><><>
float Input_GetLeftStick_X(void)
{
	float LX = (float)gpInput->mGamePadState.Gamepad.sThumbLX / 32767;
	LX = ((LX * LX) > 0.002f ? LX : 0.0f);
	return LX;
}

//<><><><><><><><><><><><><><><><><><>
// �֐����F�Q�b�g���t�g�X�e�B�b�N�x�֐�
// �����FL�X�e�B�b�N�̂x�̓��͂�1.0f�`0,0f�͈̔͂ŕԂ�
// �����F�Ȃ�
// �߂�l�Ffloat 1.0f�`0,0f�͈̔�
//<><><><><><><><><><><><><><><><><><>
float Input_GetLeftStick_Y(void)
{
	float LY = (float)gpInput->mGamePadState.Gamepad.sThumbLY / 32767;
	LY = ((LY * LY) > 0.002f ? LY : 0.0f);
	return  LY;
}

//<><><><><><><><><><><><><><><><><><>
// �֐����F�Q�b�g���C�g�X�e�B�b�N�]�֐�
// �����F�q�X�e�B�b�N�̂w�̓��͂�1.0f�`0,0f�͈̔͂ŕԂ�
// �����F�Ȃ�
// �߂�l�Ffloat 1.0f�`0,0f�͈̔�
//<><><><><><><><><><><><><><><><><><>
float Input_GetRightStick_X(void)
{
	float RX = (float)gpInput->mGamePadState.Gamepad.sThumbRX / 32767;
	RX = ((RX * RX) > 0.0025f ? RX : 0);
	return  RX;
}

//<><><><><><><><><><><><><><><><><><>
// �֐����F�Q�b�g���t�g�X�e�B�b�N�x�֐�
// �����FL�X�e�B�b�N�̂x�̓��͂�1.0f�`0,0f�͈̔͂ŕԂ�
// �����F�Ȃ�
// �߂�l�Ffloat 1.0f�`0,0f�͈̔�
//<><><><><><><><><><><><><><><><><><>
float Input_GetRightStick_Y(void)
{
	float RY = (float)gpInput->mGamePadState.Gamepad.sThumbRY / 32767;
	RY = ((RY * RY) > 0.0025f ? RY : 0);
	return  RY;
}

//<><><><><><><><><><><><><><><><><><>
// �֐����F�Q�b�g���t�g�g���K�[�{�^���֐�
// �����FLT�g���K�[�̓��͂�0�`255�͈̔͂ŕԂ�
// �����F�Ȃ�
// �߂�l�Fint 0�`255
//<><><><><><><><><><><><><><><><><><>
int Input_GetLTButton(void)
{
	return (int)gpInput->mGamePadState.Gamepad.bLeftTrigger;
}

//<><><><><><><><><><><><><><><><><><>
// �֐����F�Q�b�g���C�g�g���K�[�{�^���֐�
// �����FRT�g���K�[�̓��͂�0�`255�͈̔͂ŕԂ�
// �����F�Ȃ�
// �߂�l�Fint 0�`255
//<><><><><><><><><><><><><><><><><><>
int Input_GetRTButton(void)
{
	return (int)gpInput->mGamePadState.Gamepad.bRightTrigger;
}


//======================================================================================
// �N���X�F		AT12E224
// �o�Ȕԍ��F	16
// �S���ҁF		���쒼�o
// �`�[�����F	����	
//======================================================================================