#pragma once
#include "StaticObject.h"

class Babble :
	public StaticObject
{
private:
	
	//StaticObject SubBubble;
	float fBabbleTime;					//泡が割れるまでの時間
	int BubbleAngle;					//泡の向き

public:

	Babble(XMFLOAT3 & _Camera);	//コンストラクタ
	~Babble();					//デストラクタ
	void Update() override;		//更新
	void BabbleSet(XMFLOAT2 pos);	//泡の位置セット

};

