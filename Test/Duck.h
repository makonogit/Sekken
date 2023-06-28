//======================================================================================
// ���O�FDuck.h
// �����F�A�q���̃w�b�_�[�t�@�C��
//======================================================================================
#pragma once

//------------------------------------
//		include
//------------------------------------

#include "AnimObject.h"
#include "HitCircle.h"//�~�̓����蔻��

//------------------------------------
//		�񋓌^
//------------------------------------
enum DuckStateID
{
	DUCK_NONE = 0,// �������Ȃ�
	DUCK_MOVE,// ����
	DUCK_CARRY,// ���������^��
	DUCK_CONFUSION,// �t���X�r�[�𓖂Ă�ꂽ��
};

//------------------------------------
//		class
//------------------------------------

class Duck :
	public AnimObject
{
private:
	ID3D11ShaderResourceView* mDuckTex;			// �A�q���e�N�X�`��
	XMFLOAT2 mResistance;// ��R��
	float mTime;

	void Move(void);// ����
	void Confusion(void);
public:
	HitCircle* mCircle;// �A�q���{�̂̂����蔻��
	DuckStateID mState;// ���
	float mAngle;

	Duck(XMFLOAT3 &_Camera);	// �R���X�g���N�^
	~Duck(); // �f�X�g���N�^

	void Update()override;	// �X�V
	void SetResistance(XMFLOAT2);// ��R�͂̌v�Z
	void ChangeState(DuckStateID _state);
};

//======================================================================================
// �S���ҁF		���쒼�o
// �`�[�����F	����	
//======================================================================================