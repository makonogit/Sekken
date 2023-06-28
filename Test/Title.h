//======================================================================================
// ���O�FTitle.h
// �����F�^�C�g�����
//======================================================================================
#pragma once
#include"SceneManager.h"

class Title :
	public Scene
{
private:

	ID3D11ShaderResourceView* backTexture;					//�w�i�e�N�X�`��
	StaticObject* backObject;								//�w�i�I�u�W�F�N�g

	ID3D11ShaderResourceView* titleTexture;					//�^�C�g�����S�e�N�X�`��
	StaticObject* titleObject;								//�^�C�g�����S�I�u�W�F�N�g

	ID3D11ShaderResourceView* charaTexture;					//�L�����N�^�[�e�N�X�`��
	StaticObject* charaObject;								//�L�����N�^�[�I�u�W�F�N�g

	ID3D11ShaderResourceView* dogTexture;					//���e�N�X�`��
	StaticObject* dogObject;								//���I�u�W�F�N�g

	ID3D11ShaderResourceView* startTexture;					//�X�^�[�g�e�N�X�`��
	ID3D11ShaderResourceView* startTexture2;				//�X�^�[�g�e�N�X�`��2
	StaticObject* startObject;								//�X�^�[�g�I�u�W�F�N�g

	ID3D11ShaderResourceView* endTexture;					//�G���h�e�N�X�`��
	ID3D11ShaderResourceView* endTexture2;					//�G���h�e�N�X�`��2
	StaticObject* endObject;								//�G���h�I�u�W�F�N�g

	XMFLOAT3 camera = { 0.0f,0.0f,1.0f };				//�J�������W

	bool mBgmPlay = false;	//BGM

public:

	Title();			//�R���X�g���N�^
	~Title();			//�f�X�g���N�^

	void Draw(void) override;	//�`��
	void Update(void) override;	//�X�V

};

//======================================================================================
// �S���ҁF		�ɓ�
// ��������F�@ 2022-12-01
// �`�[�����F	����	
//======================================================================================
