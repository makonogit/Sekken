#pragma once
#include "AnimObject.h"
#include "HitSquare.h"

//�������W{0.0f,-1.9f}

class Robot : public AnimObject
{
private:
	ID3D11ShaderResourceView* mRobotTexture;			// ���{�b�g�e�N�X�`��
	float fMoveSpeed;									//�X�s�[�h
	float fAngle;										//�ړ��p�x
	bool mState;
	HitSquare* mRobotHit;								//���{�b�g�̓�����


public:
	Robot(XMFLOAT3 &_Camera);		//�R���X�g���N�^
	~Robot();		//�f�X�g���N�^

	void Move();
	void Update()override;
	
};

