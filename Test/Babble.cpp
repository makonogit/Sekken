#include "Babble.h"

extern DWORD gDeltaTime;

//<><><><><><><><><><><><><><><><><><>
// 関数名：Babblr
// 役割：コンストラクタ
//<><><><><><><><><><><><><><><><><><>
Babble::Babble(XMFLOAT3 & _Camera):StaticObject(_Camera)
{
	this->SetSize(0.15f, 0.15f);
	this->active = false;
	//this->mSprite->SetTexture(mBabbleTex);
	fBabbleTime = 0.0f;

}

//<><><><><><><><><><><><><><><><><><>
// 関数名：~Babble
// 役割：デストラクタ
//<><><><><><><><><><><><><><><><><><>
Babble::~Babble()
{

}

//<><><><><><><><><><><><><><><><><><>
// 関数名：Update
// 役割：更新
//<><><><><><><><><><><><><><><><><><>
void Babble::Update()
{
	fBabbleTime += gDeltaTime;

	//this->mSprite->mCenter.y = BubblePos.y + (rand() % (10 - (-10 + 1)) + -10) * 0.01f;

	if (BubbleAngle == 0) {
		if (fBabbleTime >= 1.0f * 1000) {
			this->mSprite->mCenter.x -= 0.00001f * gDeltaTime;
			this->mSprite->mCenter.y += 0.00001f * gDeltaTime;
			fBabbleTime = 0.0f;
		}
		else {
			this->mSprite->mCenter.x += 0.00001f * gDeltaTime;
			this->mSprite->mCenter.y -= 0.00001f * gDeltaTime;
		}
	}
	else {
		if (fBabbleTime <= 1.0f * 1000) {
			this->mSprite->mCenter.x -= 0.00001f * gDeltaTime;
			this->mSprite->mCenter.y += 0.00001f * gDeltaTime;
			fBabbleTime = 0.0f;
		}
		else {
			this->mSprite->mCenter.x += 0.00001f * gDeltaTime;
			this->mSprite->mCenter.y -= 0.00001f * gDeltaTime;
		}
	}


	StaticObject::Update();
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：BabbleSet
// 役割：泡の位置セット
//<><><><><><><><><><><><><><><><><><>
void Babble::BabbleSet(XMFLOAT2 pos)
{
	if (active == false) {
		//少しずらして表示
		this->mSprite->mCenter.x = pos.x + (rand() % (3 - (-3 + 1)) + -3) * 0.01f;
		this->mSprite->mCenter.y = pos.y + (rand() % (3 - (-3 + 1)) + -3) * 0.01f;
		this->active = true;
	}

	BubbleAngle = rand() % 2;
	
}
