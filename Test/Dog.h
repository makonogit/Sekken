//======================================================================================
// ���O�FDog.h
// �����F���̃w�b�_�[�t�@�C��
//======================================================================================
#pragma once

//------------------------------------
//		include
//------------------------------------

#include"Input.h"// ��ԏて���Ԓ���
#include"AnimObject.h"
#include "HitCircle.h"//�~�̓����蔻��
#include "Fade_Bubble.h"
//------------------------------------
//		define
//------------------------------------

//#define PI (3.14159265359f)

//------------------------------------
//		�񋓌^
//------------------------------------

enum DogStateID
{
	DOG_NONE=0,
	DOG_WALK,// �ʏ���
	DOG_RUN,// �t���X�r�[��ǂ�������
	DOG_WAIT,//	�v���C���[�̑O�ő҂�
	DOG_RETURN,// �����Ԃ��Ă���
	DOG_BE_CARRYED,//�����A�q���ɉ^�΂��
};
 
//------------------------------------
//		�N���X
//------------------------------------

class Dog : public AnimObject
{
private:
	ID3D11ShaderResourceView* mWalkTexture;			// ���e�N�X�`��
	ID3D11ShaderResourceView* mRunTexture;			// ���e�N�X�`��
	XMFLOAT2* mTarget;
	XMFLOAT2 mSpeedSlip;
	XMFLOAT2 mResistance;// ��R��
	float mWaitTime;
	float mTime;
	float mRunSpeed;
	float mAngle;
	float mOldAngle;

	void Walk(void);
	void Run(void);
	void BeCarryed(void);

	//void Return(void);
public:
	Dog(XMFLOAT3 &_Camera);	// �R���X�g���N�^
	~Dog(); // �f�X�g���N�^
	DogStateID mState;


	HitCircle* mCatchArea;//�t���X�r�[���L���b�`���邠���蔻��
	HitCircle* mCatchBubbleArea;//�t���X�r�[���L���b�`���邠���蔻��
	HitCircle* mMissArea;//�t���X�r�[���~�X���邠���蔻��
	HitCircle* mCircle;//���̑̂̂����蔻��
	bool mSlip;


	void Update()override;
	//bool CatchResult(HitCircle*);
	void SetResistance(XMFLOAT2);// ��R�͂̌v�Z
	void ChangeState(DogStateID);
	void SetTarget(XMFLOAT2*);
};


//======================================================================================
// �S���ҁF		���쒼�o
// �`�[�����F	����	
//======================================================================================