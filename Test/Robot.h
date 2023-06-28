#pragma once
#include "AnimObject.h"
#include "HitSquare.h"

//初期座標{0.0f,-1.9f}

class Robot : public AnimObject
{
private:
	ID3D11ShaderResourceView* mRobotTexture;			// ロボットテクスチャ
	float fMoveSpeed;									//スピード
	float fAngle;										//移動角度
	bool mState;
	HitSquare* mRobotHit;								//ロボットの当たり


public:
	Robot(XMFLOAT3 &_Camera);		//コンストラクタ
	~Robot();		//デストラクタ

	void Move();
	void Update()override;
	
};

