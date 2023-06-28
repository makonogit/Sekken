//======================================================================================
//	���O�FAnimSprite.h
//  �����F�����X�v���C�g
//======================================================================================
#pragma once
#include "Sprite.h"

//�ړ�����
enum DIRECTION
{
	D_DOWN, D_LEFT, D_RIGHT, D_UP
};

class AnimSprite :
	public Sprite
{
private:
	
public:
	
	static constexpr int nAnimTable[] = { 0,1,2,1,-1 };		//�A�j���[�V�����e�[�u��
	DIRECTION mDirection = D_LEFT;							//�L�����̌���
	float fAnimSpeed = 0.001f;								//�A�j���[�V�������x
	float fAnimCnt = 0.0f;									//�A�j���[�V�����v�Z�p

	void Update() override;			//�X�V
	AnimSprite(XMFLOAT3& _Camera);	//���R���X�g���N�^���Ăяo��
};


//======================================================================================
// �S���ҁF		�����S
// ��������F�@ 2022-12-01
// �`�[�����F	����	
//======================================================================================