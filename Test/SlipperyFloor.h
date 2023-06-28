//======================================================================================
// ���O�FSlipperyFloor.h
// �����F�҂��҂��̏��̃w�b�_�[�t�@�C��
//======================================================================================
#pragma once

//------------------------------------
//		include
//------------------------------------

#include "AnimObject.h"
#include "HitSquare.h"

#define MAP_WIDTH 2.8f
#define MAP_HIGHT 2.0f

//------------------------------------
//		�N���X
//------------------------------------

class SlipperyFloor :
	public AnimObject
{
private:
	//ID3D11ShaderResourceView* mTexture;			// �҂��҂����̃e�N�X�`������������v��Ȃ�
	float mlimitTime;// ���Ŏ���
	float mTime;// �o�ߎ���
public:
	HitSquare* mSquare;// �����蔻��

	SlipperyFloor(XMFLOAT3 &);// �R���X�g���N�^
	~SlipperyFloor();// �f�X�g���N�^

	void Update()override;// �X�V����
	void SetLimitTime(float);// �������Ԑݒ茓�A�N�e�B�u��
};

//======================================================================================
// �S���ҁF		���쒼�o
// �`�[�����F	����	
//======================================================================================