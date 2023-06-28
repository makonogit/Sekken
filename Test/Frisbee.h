//======================================================================================
// ���O�FFrisbee.h
// �����F�t���X�r�[�̃w�b�_�[�t�@�C��
//======================================================================================
#pragma once

//------------------------------------
//		include
//------------------------------------

#include"Input.h"//�����Ԓ���
#include "StaticObject.h"
#include "HitCircle.h"
#include "Sound.h"
//------------------------------------
//		�񋓌^
//------------------------------------

enum FrisbeeStateID
{
	FRISBEE_DROP = 0,		// ��������
	FRISBEE_FRY,
	FRISBEE_HOLD,
};

enum CharHoldFrisbee
{
	DONT_HOLD = 0,
	HOLD_PLAYER,
	HOLD_DOG,
};

//------------------------------------
//		�N���X
//------------------------------------

class Frisbee :
	public StaticObject
{
private:
	ID3D11ShaderResourceView* mTexture;			// �t���X�r�[�e�N�X�`��
	ID3D11ShaderResourceView* mShadowTexture;	// �t���X�r�[�̉e�e�N�X�`��
public:
	HitCircle* mCircle;
	StaticObject* mShadow;
	FrisbeeStateID mState;
	CharHoldFrisbee mHold;
	float mMiniSize;// �ŏ��T�C�Y
	float mAngle;// �i�s����
	float mRate;// ���x��
	float mSpeed;// ���x
	bool mSound = false;	//�T�E���h��Ԃ��i�[����ϐ�

	Frisbee(XMFLOAT3 &);// �R���X�g���N�^
	~Frisbee();// �f�X�g���N�^
	
	void SetReserve(XMFLOAT2,float);// �����鏀��
	void Fry();
	void Drop();
	void Update()override;// �X�V����
	void ChangeState(FrisbeeStateID);
	void Catch(CharHoldFrisbee);

	//void Collide();
};

//======================================================================================
// �S���ҁF		���쒼�o
// �`�[�����F	����	
//======================================================================================