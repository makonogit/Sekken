//======================================================================================
// ���O�FAnimObject.h
// �����F�����I�u�W�F�N�g
//======================================================================================
#pragma once
#include "GameObject.h"
#include "AnimSprite.h"
#include "HitCircle.h"
#include "Sound.h"

class AnimObject :
	public GameObject
{
private:
	
public:
	// �\���@�\
	AnimSprite* mAnimObject;
	HitCircle* mHit;

	AnimObject(XMFLOAT3& _Camera);	//�R���X�g���N�^
	~AnimObject();	//�f�X�g���N�^

};

//======================================================================================
// �S���ҁF		�����S
// ��������F�@ 2022-12-01
// �`�[�����F	����	
//======================================================================================