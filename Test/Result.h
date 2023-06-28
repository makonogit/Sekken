#pragma once

#include"SceneManager.h"

#define GAGEMAX 1.25f	//�Q�[�W�̍ő�T�C�Y

class Result :
	public Scene
{
private:

	XMFLOAT3 camera = { 0.0f,0.0f,1.0f };	//�J�������W

	ID3D11ShaderResourceView* mBgTex;			//�w�i�e�N�X�`���p�ϐ�
	ID3D11ShaderResourceView* mReplayUITex;		//���v���C�e�N�X�`��
	ID3D11ShaderResourceView* mReturnUITex;		//�X�e�[�W�I���e�N�X�`���p
	ID3D11ShaderResourceView* mScoreUITex[4];	//�X�R�A�e�N�X�`���p(C~S)

	ID3D11ShaderResourceView* mScoreGageFreamTex;		//�X�R�A�Q�[�W�g�e�N�X�`���p
	ID3D11ShaderResourceView* mScoreGageBackTex;		//�X�R�A�Q�[�W�w�i�e�N�X�`���p
	ID3D11ShaderResourceView* mScoreGageTex;			//�X�R�A�Q�[�W�e�N�X�`���p

	ID3D11ShaderResourceView* mCrackerTex;				//�N���b�J�[�e�N�X�`���p
	ID3D11ShaderResourceView* mCracker_PaperTex;		//�N���b�J�[�̎��H�e�N�X�`���p

	StaticObject* mBg;						//�w�i
	
	StaticObject* mReplayUI;				//���v���CUI
	StaticObject* mReturnUI;				//�X�e�[�W�I��UI
	StaticObject* mScoreUI;					//�X�R�AUI

	StaticObject* mScoreGageFream;			//�X�R�A�Q�[�W�̘g
	StaticObject* mScoreGageBack;			//�X�R�A�Q�[�W�̔w�i
	StaticObject* mScoreGage;				//�X�R�A�Q�[�W

	StaticObject* mCracker_Left;				//�N���b�J�[��
	StaticObject* mCracker_Right;				//�N���b�J�[�E
	StaticObject* mCracker_Paper_Left;			//�N���b�J�[�̎�?��
	StaticObject* mCracker_Paper_Right;			//�N���b�J�[�̎�?�E

	float fRevers;			//���]�p
	float fWeight;			//�d�͉���(�N���b�J�[�̃A�j���[�V�����p)


	static int nScore;		//�X�R�A
	int ScoreLank = 0;		//�X�R�A�����N
	bool GageState = true;	//�Q�[�W�̏��
	int nSceneNum = 0;		//�V�[���ԍ�
	bool mSound = false;
	float mSETime;

	XMFLOAT2 SelectSize;	//�I�𒆂�UI�̃T�C�Y

public:
	
	Result();	//�R���X�g���N�^
	~Result();	//�f�X�g���N�^

	void Update() override;	//�X�V
	void Draw() override;	//�`��
	void SceneSelect();		//�V�[���I��
	bool ScoreGageAnim();	//�X�R�A�Q�[�W�̃A�j���[�V����(true:�A�j���[�V�������@false:�A�j���[�V�����I��)
	void Cracker_Anim();	//�N���b�J�[�A�j���[�V����
	static void GetScore(int Score);	//�X�R�A�̎󂯎��
	
};

