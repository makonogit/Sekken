#pragma once
#include "Stage.h"
class Room_Stage :
	public Stage
{
private:

	//障害物のテクスチャ
	ID3D11ShaderResourceView* mShoesTex;		//靴
	ID3D11ShaderResourceView* mLeatherShoesTex;	//革靴
	ID3D11ShaderResourceView* mSneakerShoesTex;	//スニーカー

	ID3D11ShaderResourceView* mRobotInfoTex;	//ロボット説明

	StaticObject* RobotInfoUI;

	float RobotInfoTime = 0.0f;

public:

	Room_Stage();	//コンストラクタ
	~Room_Stage();	//デストラクタ

	void Update() override;	//更新
	void Draw() override;	//描画
};

