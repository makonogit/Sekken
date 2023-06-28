#include "Babble.h"

extern DWORD gDeltaTime;

//<><><><><><><><><><><><><><><><><><>
// �֐����FBabblr
// �����F�R���X�g���N�^
//<><><><><><><><><><><><><><><><><><>
Babble::Babble(XMFLOAT3 & _Camera):StaticObject(_Camera)
{
	this->SetSize(0.15f, 0.15f);
	this->active = false;
	//this->mSprite->SetTexture(mBabbleTex);
	fBabbleTime = 0.0f;

}

//<><><><><><><><><><><><><><><><><><>
// �֐����F~Babble
// �����F�f�X�g���N�^
//<><><><><><><><><><><><><><><><><><>
Babble::~Babble()
{

}

//<><><><><><><><><><><><><><><><><><>
// �֐����FUpdate
// �����F�X�V
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
// �֐����FBabbleSet
// �����F�A�̈ʒu�Z�b�g
//<><><><><><><><><><><><><><><><><><>
void Babble::BabbleSet(XMFLOAT2 pos)
{
	if (active == false) {
		//�������炵�ĕ\��
		this->mSprite->mCenter.x = pos.x + (rand() % (3 - (-3 + 1)) + -3) * 0.01f;
		this->mSprite->mCenter.y = pos.y + (rand() % (3 - (-3 + 1)) + -3) * 0.01f;
		this->active = true;
	}

	BubbleAngle = rand() % 2;
	
}
