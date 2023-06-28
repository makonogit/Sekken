//======================================================================================
// ���O�FFade.h
// �����F�t�F�[�h
//======================================================================================
#pragma once
#include"Sprite.h"
#include"System.h"

//�t�F�[�h�̏��
typedef enum{
	NONE_FADE,	//�Ȃɂ����Ă��Ȃ�
	FADE_IN,	//�t�F�[�h�C����
	FADE_OUT,	//�t�F�[�h�A�E�g��
	FADE_IN_END,	//�t�F�[�h�C���I��
	FADE_OUT_END,	//�t�F�[�h�A�E�g�I��
	
}FadeState;

typedef enum {
	NOMAL_FADE,		//���ʂ̃t�F�[�h
	BUBBLE_FADE,	//�A�̃t�F�[�h
	DOGRUN_FADE,	//���̃t�F�[�h
	NONE_TYPE,
}Fade_Type;

class Fade
{
protected:
	
	ID3D11ShaderResourceView* mpTexture;	//�e�N�X�`���p�ϐ�
	ID3D11ShaderResourceView* mTeamLogoTex;	//�`�[�����S
	Sprite::RGBA color;						//�|���S���̐F
	XMFLOAT3 camera;						//�J�������W

private:

	Sprite* mSprite;						//�t�F�[�h�p�X�v���C�g
	Sprite* mTeamLogo;						//�`�[�����S
	
public:

	Fade();			//�R���X�g���N�^
	~Fade();		//�f�X�g���N�^

	static void FadeIn(void);			//�t�F�[�h�C��
	static void FadeOut(void);			//�t�F�[�h�A�E�g
	virtual void Update();		//�X�V
	virtual void Draw();		//�`��

	static int mState;		//���݂̏�Ԃ�����ϐ�

};

//======================================================================================
// �S���ҁF		�����S
// ��������F�@ 2022-12-01
// �`�[�����F	����	
//======================================================================================
