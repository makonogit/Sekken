#pragma once
#include "Stage.h"
class Room_Stage :
	public Stage
{
private:

	//��Q���̃e�N�X�`��
	ID3D11ShaderResourceView* mShoesTex;		//�C
	ID3D11ShaderResourceView* mLeatherShoesTex;	//�v�C
	ID3D11ShaderResourceView* mSneakerShoesTex;	//�X�j�[�J�[

	ID3D11ShaderResourceView* mRobotInfoTex;	//���{�b�g����

	StaticObject* RobotInfoUI;

	float RobotInfoTime = 0.0f;

public:

	Room_Stage();	//�R���X�g���N�^
	~Room_Stage();	//�f�X�g���N�^

	void Update() override;	//�X�V
	void Draw() override;	//�`��
};

