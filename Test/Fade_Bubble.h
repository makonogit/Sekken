//======================================================================================
// ���O�FFade_Bubble.h
// �����F�A�̃t�F�[�h
//�w�i�̔��͑S�������������������ȂƎv���Ă���Ă邾���Ȃ̂ł��Ƃŏ�������
//======================================================================================
#pragma once
#include "Fade.h"
#include"StaticObject.h"

class Fade_Bubble :
	public Fade
{
private:
	ID3D11ShaderResourceView* BackTexture;	//�e�N�X�`���p�ϐ�
	Sprite* Back;
	StaticObject* Babble[4];

	float fTime;
public:

	Fade_Bubble();	//�R���X�g���N�^
	~Fade_Bubble();	//�f�X�g���N�^

	static void FadeIn(void);			//�t�F�[�h�C��
	static void FadeOut(void);			//�t�F�[�h�A�E�g
	void Update() override;	//�X�V
	void Draw() override;	//�`��

	static int mState;		//���݂̏�Ԃ�����ϐ�
};


//======================================================================================
// �S���ҁF		�����S
// ��������F�@ 2022-12-01
// �`�[�����F	����	
//======================================================================================