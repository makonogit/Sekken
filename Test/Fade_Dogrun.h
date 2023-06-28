//======================================================================================
// ���O�FFade_Dogrun.h
// �����F���̃t�F�[�h
//���̃e�N�X�`���͉��Ŏg���Ă������̂Ȃ̂ŕύX���Ă�������
//======================================================================================

#pragma once
#include "Fade.h"
#include"StaticObject.h"
#include"AnimObject.h"

class Fade_Dogrun :public Fade
{
private:
	ID3D11ShaderResourceView* BackTexture;	//�e�N�X�`���p�ϐ�
	StaticObject* Back[2];	//�w�i
	//StaticObject* Dogrun;	//��
	AnimObject* Dogrun;
	
	int fiFlg,feFlg;	//�t�F�[�h�C����Ԋi�[�p�ϐ�

public:
	Fade_Dogrun();		//�R���X�g���N�^
	~Fade_Dogrun();		//�f�X�g���N�^

	static void FadeIn(void);			//�t�F�[�h�C��
	static void FadeOut(void);			//�t�F�[�h�A�E�g
	void Update();		//�X�V
	void Draw();		//�`��

	static int mState;		//���݂̏�Ԃ�����ϐ�
};

//======================================================================================
// �S���ҁF		���z��
// ��������F�@ 2022-12-05
// �`�[�����F	����	
//======================================================================================