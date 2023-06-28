#pragma once
#include "AnimObject.h"
#include "StaticObject.h"
#include "Fade_Bubble.h"

//�L�̏��
typedef enum{
	CNONE,
	WAIT,		//�~�܂�
	WALK,		//����
	RUN,		//����
	LIEDOWN,	//�Q�]��
	JUMP,		//�W�����v
}CatState;

//�L�̉�����
typedef enum {
	CLEARN,		//���ꂢ
	DIRT,		//����
}CatDirtState;

class Cat : public AnimObject
{
private:

	ID3D11ShaderResourceView* mCatTex;			//�L�e�N�X�`��
	ID3D11ShaderResourceView* mDirtCatTex;		//����L�e�N�X�`��
	ID3D11ShaderResourceView* mCatLieDownTex;	//�Q�]�ԃe�N�X�`��
	ID3D11ShaderResourceView* mCatJampTex;		//�W�����v�e�N�X�`��

	StaticObject* mStaticObj;					//�A�j���[�V�������Ȃ��I�u�W�F�N�g

	int nMove;					//�����_���ړ�
	CatState nState;			//���

	XMFLOAT2* fTarget;			//�ǂ�������Ώ�

	float fAngle;				//�ړ��p�x
	float fMoveSpeed;			//�X�s�[�h
	float fTime;				//����
	float fCatDownTime;			//�Q�]�Ԏ���

public:

	bool Appearance;			//�o�����Ă��邩�̃t���O

	CatDirtState nDirtState;	//������
	HitCircle* mLieDownHit;		//�Q�]��ł��鎞�̂����蔻��
	HitCircle* mBlockAreaHit;	//�W�Q����G���A�̂����蔻��

	Cat(XMFLOAT3 &_Camera);		//�R���X�g���N�^
	~Cat();						//�f�X�g���N�^

	void Update() override;	//�X�V
	void Draw();			//�`��

	void Move();							//�ړ�
	void LieDown();							//�Q�]��
	void Run();								//����
	void Jump();							//�W�����v

	void Wait();			//��~

	void SetTarget(XMFLOAT2* _target);		//�ǂ�������Ώۂ��w��
	void ChangeState(CatState _state);		//��ԑJ��
	CatState GetState(void);				//���݂̏�Ԃ�n��
	void SetDirtState(CatDirtState _state);	//����̏�Ԃ��Z�b�g
	void SetAppearance(bool _appearance);	//�o������ꏊ���Z�b�g
	void OutSideRun(XMFLOAT2* _Pos);		//��ʊO�ɏo�Ă���
};

