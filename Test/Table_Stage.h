#pragma once
#include "Stage.h"
class Table_Stage :
	public Stage
{
private:

	//��Q���̃e�N�X�`��
	ID3D11ShaderResourceView* mStickTex;//��
	ID3D11ShaderResourceView* mPlateTex;//�M
	ID3D11ShaderResourceView* mCupTex;	//�J�b�v

	StaticObject* mChopstick[2];// ��


	HitCircle* mBlockHitCircle[2];// �M�ƃJ�b�v
public:

	Table_Stage();	//�R���X�g���N�^
	~Table_Stage();	//�f�X�g���N�^

	void Update() override;	//�X�V
	void Draw() override;	//�`��
};

