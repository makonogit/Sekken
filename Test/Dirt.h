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

	Dirt(XMFLOAT3 &_Camera);	//コンストラクタ
	~Dirt();	//デストラクタ
	//void Update() override;	//更新
};