#pragma once
#include"StaticObject.h"
#include"HitCircle.h"

#define STAGE_HIGHT 30
#define STAGE_WIDTH 40

class Dirt : public StaticObject
{
private:

public:
	HitCircle* mHitCircle;
	HitSquare* mHitSpuare;

	bool mHitDog;

	Dirt(XMFLOAT3 &_Camera);	//�R���X�g���N�^
	~Dirt();	//�f�X�g���N�^
	//void Update() override;	//�X�V
};