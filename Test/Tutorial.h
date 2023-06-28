#pragma once

#include "Stage.h"
#include "Select.h"

class Tutorial :
	public Stage
{
private:

	//��Q���̃e�N�X�`��
	ID3D11ShaderResourceView* mChopStick_BlueTex;	//����(��)
	ID3D11ShaderResourceView* mChopStick_PinkTex;	//����(�s���N)

	StaticObject* mBlock4;		//���̃X�e�[�W����


	//�^�X�N�̃e�N�X�`��
	ID3D11ShaderResourceView* mWalkTaskTex;		//���s�^�X�N�e�N�X�`��
	ID3D11ShaderResourceView* mSetTaskTex;		//�\���^�X�N�e�N�X�`��
	ID3D11ShaderResourceView* mAngleTaskTex;	//�p�x�^�X�N�e�N�X�`��
	ID3D11ShaderResourceView* mThrowTaskTex;	//������^�X�N�e�N�X�`��
	ID3D11ShaderResourceView* mCurveTaskTex;	//�J�[�u�^�X�N�e�N�X�`��

	ID3D11ShaderResourceView* mPauseTex;		//�|�[�Y�e�N�X�`��

	ID3D11ShaderResourceView* mWASDKeyTex[2];			//WASD�L�[�e�N�X�`��
	ID3D11ShaderResourceView* mXY_ButtonTex[2];			//XY�{�^���e�N�X�`��
	ID3D11ShaderResourceView* mB_ButtonTex[2];			//B�{�^���e�N�X�`��
	ID3D11ShaderResourceView* mEscape_KeyTex[2];		//Escape�L�[�e�N�X�`��
	ID3D11ShaderResourceView* mSpeace_KeyTex[2];		//Speace�L�[�e�N�X�`��
	ID3D11ShaderResourceView* mTriggerTex[2];	//�g���K�[�e�N�X�`��
	ID3D11ShaderResourceView* mStickTex[2];		//�X�e�B�b�N�e�N�X�`��
	ID3D11ShaderResourceView* mMousePointTex;	//�}�E�X�|�C���^�e�N�X�`��
	ID3D11ShaderResourceView* mMouseTex[3];		//�}�E�X�e�N�X�`��

	ID3D11ShaderResourceView* mDogIvent_KeyTex;		//���C�x���g�e�N�X�`��(�L�[�{�[�h)
	ID3D11ShaderResourceView* mCatIvent_KeyTex;		//�L�C�x���g�e�N�X�`��(�L�[�{�[�h)
	ID3D11ShaderResourceView* mDogIvent_ButtonTex;	//���C�x���g�e�N�X�`��(�R���g���[���[)
	ID3D11ShaderResourceView* mCatIvent_ButtonTex;	//�L�C�x���g�e�N�X�`��(�R���g���[���[)

	StaticObject* mWalk_KeyUI;		//���s(WASD)
	StaticObject* mSet_KeyUI;		//�Z�b�g(Speace[0])
	StaticObject* mCurve_UI;		//�J�[�u(Mouse[0~2])
	StaticObject* mAngle_KeyUI;		//�p�x(MousePoint)
	StaticObject* mThrow_KeyUI;		//����(Speace[1])
	StaticObject* mPause_KeyUI;		//�|�[�Y(Escape[0])
	
	StaticObject* mWalk_TaskUI;			//���s�^�X�NUI
	StaticObject* mSet_TaskUI;			//�t���X�r�[�Z�b�g�^�X�NUI
	StaticObject* mAngle_TaskUI;		//�p�x�^�X�NUI
	StaticObject* mThrow_TaskUI;		//�p�x�^�X�NUI
	StaticObject* mCurve_TaskUI;		//�J�[�u�^�X�NUI
	StaticObject* mPauseUI;				//�|�[�YUI
	
	StaticObject* mIvent_UI;			//�C�x���gUI
	Ivent mDogIvent_State;
	Ivent mCatIvent_State;
	int mInput;		//���͏��

	//�}�E�X�̍��W
	int MouseX = 0;
	int MouseY = 0;

public:



	Tutorial();				//�R���X�g���N�^
	~Tutorial();			//�f�X�g���N�^

	void KeyLoad();			//�L�[�{�[�h���͂̏ꍇ�̏�����
	void ButtonLoad();		//�{�^�����͂̏ꍇ�̏�����
	void Task_Set();				//�^�X�N�o�[�̈ʒu�ݒ�
	Ivent Ivent_Set(Ivent IventNum);	//�C�x���g�J�n����
	void Hit();						//�����蔻��
	void Catch();					//�L���b�`
	void Update() override;			//�X�V
	void Draw() override;			//�`��
};
