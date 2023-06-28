#pragma once
#include "Stage.h"
#include "Duck.h"

class Bath_Stage :
	public Stage
{
private:
	//��Q���̃e�N�X�`��
	ID3D11ShaderResourceView* mSoapTex;		//�Ό�
	ID3D11ShaderResourceView* mBottleTex;	//�{�g��
	ID3D11ShaderResourceView* mSpongeTex;	//�X�|���W

	ID3D11ShaderResourceView* mDuckTex;	//����
	StaticObject* mDuckUI;		//�A�q���̐���
	Duck* mDuck;

	float DuckInfoTime = 0.0f;

public:

	Bath_Stage();		//�R���X�g���N�^
	~Bath_Stage();		//�f�X�g���N�^

	void Update() override;	//�X�V
	void Draw() override;	//�`��
};

