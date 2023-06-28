//======================================================================================
// ���O�FSprite
// �����F�|���S���̕\��
//======================================================================================
#pragma once


//------------------------------------
//		include
//------------------------------------
#include <Windows.h>
#include <DirectXMath.h>
#include"WICTextureLoader.h"
#include "Direct3d.h"

using namespace DirectX;


//------------------------------------
//		�}�N����`
//------------------------------------

// �Ȃ�


//------------------------------------
//		�N���X
//------------------------------------

class Sprite
{
protected:

public:


	// �����N���X�����̃N���X���Ŏg����N���X

	// �F��\���\����
	struct RGBA
	{
		float r, g, b, a;
	};

	// ���_�f�[�^�p�̍\����
	struct VERTEX2D
	{
		float x, y;	// ���_�̍��W�i�ʒu�j
		float u, v;	// �e�N�X�`����UV���W
		RGBA color; // ���_�̐F
	};

	//�@���_�o�b�t�@�p�̕ϐ�
	ID3D11Buffer* mpVertexBuffer;
	//�@�ǂݍ��񂾃e�N�X�`����ێ����邽�߂̕ϐ�
	ID3D11ShaderResourceView* mpTexture;

	XMFLOAT2 mCenter;
	XMFLOAT2 mSize;
	XMFLOAT4 mUV;
	XMFLOAT3& mCamera;
	//float mAngle;	// �p�x

	RGBA mColor;

	virtual void Update();
	void Draw();	// �`�揈��
	void SetColor(RGBA color);// ���_�̐F��ݒ肷��֐�
	void SetTexture(ID3D11ShaderResourceView* pTexture);

	Sprite(XMFLOAT3& _Camera);	// �R���X�g���N�^
	~Sprite();	// �f�X�g���N�^


};


//======================================================================================
// �S���ҁF		���쒼�o
// �`�[�����F	����	
//======================================================================================