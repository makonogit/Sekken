//======================================================================================
// ���O�FPlayer.h
// �����F�v���C���[�̃w�b�_�[�t�@�C��
//======================================================================================
#pragma once

//------------------------------------
//		include
//------------------------------------

#include"Input.h"// ��ԏて���Ԓ���
#include "Frisbee.h"// �t���X�r�[
#include"AnimObject.h"
#include "HitCircle.h"//�~�̓����蔻��
#include "Fade_Bubble.h"
//------------------------------------
//		�񋓌^
//------------------------------------

enum PlayerStateID
{
	PLAYER_DONT_MOVE = 0,	// �����Ȃ����������Ȃ�
	PLAYER_MOVE,			// �ړ�����Ƃ�
	PLAYER_THROW,			// �����鏀���ƃt���X�r�[��������܂�
};

//------------------------------------
//		�N���X
//------------------------------------

class Player : public AnimObject
{
private:

	
	ID3D11ShaderResourceView* mPlayerTex;			// �ړ��e�N�X�`��
	ID3D11ShaderResourceView* mPlayerTexThrow;		// ������e�N�X�`��
	ID3D11ShaderResourceView* mMarkTex;		// ������e�N�X�`��

	void Move();	// �ړ�����
	void Throw();	// �t���X�r�[�𓊂��鏈��
public:
	// �����o�[�ϐ�
	bool mHitCount;
	HitCircle* mCircle;// �����蔻��
	PlayerStateID mState; // �v���C���[�̏�ԕϐ�
	Frisbee* mpFrisbee;// �t���X�r�[�̃|�C���^
	StaticObject* mMark;// ����������̖ڈ�
	XMFLOAT2 mSpeed;
	XMFLOAT2 mSpeedSlip;
	float mThrowAngle;// ���������
	XMFLOAT2 mResistance;// ��R��
	float fWalkSETime;
	// �����o�[�֐�

	Player(XMFLOAT3 &_Camera, Frisbee* _Fris);	// �R���X�g���N�^
	~Player();					// �f�X�g���N�^
	
	void Update()override;	// �X�V
	void Slip();
	void SetResistance(XMFLOAT2);// ��R�͂̌v�Z
	void ChangeState(PlayerStateID);
};

//======================================================================================
// �S���ҁF		���쒼�o
// �`�[�����F	����	
//======================================================================================