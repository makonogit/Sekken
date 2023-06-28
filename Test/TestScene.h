#pragma once
#include"Fade.h"
#include"Sprite.h"

class TestScene
{
private:

	Fade* mFade;							//�t�F�[�h�p
	ID3D11ShaderResourceView* TestTexture;	//�e�N�X�`��
	XMFLOAT3 camera;						//�J�������W
	Sprite* TestSprite;						//�e�X�g�p�X�v���C�g
	Sprite* TestFrisbe;						//�e�X�g�p�t���X�r�[
	float OldStickPos_x;					//�X�e�B�b�N�̑O�̍��W
	float OldStickPos_y;					

	bool StickTrigger;						//�X�e�B�b�N1�����

public:

	TestScene(void);						//�R���X�g���N�^
	~TestScene(void);						//�f�X�g���N�^
	void Draw(void);						//�`��
	void Update(void);						//�X�V

};

