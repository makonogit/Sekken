#include "Dirt.h"

//<><><><><><><><><><><><><><><><><><>
// 関数名：Dirt
// 役割：コンストラクタ
//<><><><><><><><><><><><><><><><><><>

Dirt::Dirt(XMFLOAT3 &_Camera):StaticObject(_Camera)
{
	//初期化
	//mDirt->mSprite->SetTexture(mDirtTexture);
	SetSize(0.116f,0.132f);
	XMFLOAT2 gap = { 0.0f,0.0f };

	mHitSpuare = new HitSquare(&mSprite->mCenter, mSprite->mSize, gap, 0);

	mHitCircle = new HitCircle(&mSprite->mCenter,0.05f);
	mHitDog = false;
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：~Dirt
// 役割：デストラクタ
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
// 担当者：		井上想哉
// 最終更新日： 12/21
// チーム名：	黒棺
//======================================================================================