#pragma once
//======================================================================================
// ���O�FPause.h
// �����F�|�[�Y���
//======================================================================================
#include "SceneManager.h"

class Pause :
	public Scene
{
private:

	//�I�𒆂�ID
	typedef enum {
		RETURN,
		REPLAY,
		TITLE_BACK
	};

	ID3D11ShaderResourceView* mBackTex;				//�w�i�e�N�X�`��
	ID3D11ShaderResourceView* mUIContinueTex;				//UI�e�N�X�`��
	ID3D11ShaderResourceView* mUIRestartTex;				//UI�e�N�X�`��
	ID3D11ShaderResourceView* mUITitleBackTex;				//UI�e�N�X�`��
	StaticObject* mBack;		//�w�i
	StaticObject* mReturnUI;	//�Q�[���ɖ߂�UI
	StaticObject* mTitleUI;		//�^�C�g�����UI
	StaticObject* mReplayUI;	//��蒼��UI
	//StaticObject* mPauselogo;	//�|�[�Y���S
	XMFLOAT3 camera;			//�J����
	Sprite::RGBA color;			//�w�i�F

	Sprite::RGBA Normal;		//�Â�
	Sprite::RGBA Black;	//�ʏ�
	Sprite::RGBA Blue;	//��


	int SelectID;		//�I��ID

public:

	Pause();	//�R���X�g���N�^
	~Pause();	//�f�X�g���N�^

	void Update() override;	//�X�V
	void Draw() override;	//�`��

	int SceneSelect();		//�V�[���I��

};

