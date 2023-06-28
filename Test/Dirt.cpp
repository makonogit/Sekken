#include "Dirt.h"

//<><><><><><><><><><><><><><><><><><>
// �֐����FDirt
// �����F�R���X�g���N�^
//<><><><><><><><><><><><><><><><><><>

Dirt::Dirt(XMFLOAT3 &_Camera):StaticObject(_Camera)
{
	//������
	//mDirt->mSprite->SetTexture(mDirtTexture);
	SetSize(0.116f,0.132f);
	XMFLOAT2 gap = { 0.0f,0.0f };

	mHitSpuare = new HitSquare(&mSprite->mCenter, mSprite->mSize, gap, 0);

	mHitCircle = new HitCircle(&mSprite->mCenter,0.05f);
	mHitDog = false;
}

//<><><><><><><><><><><><><><><><><><>
// �֐����F~Dirt
// �����F�f�X�g���N�^
//<><><><><><><><><><><><><><><><><><>
Dirt::~Dirt()
{
	delete mHitSpuare;
	delete mHitCircle;
	//COM_SAFE_RELEASE(mDirtTexture);
}

//void Dirt::Update()
//{
//	mSprite->Update();
//
//	StaticObject::Update();
//}

//void Dirt::Draw()
//{
//	if (active == true)
//	{
//		mSprite->Draw();
//	}
//}
//======================================================================================
// �S���ҁF		���z��
// �ŏI�X�V���F 12/21
// �`�[�����F	����
//======================================================================================