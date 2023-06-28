#pragma once
#include "Stage.h"
class Table_Stage :
	public Stage
{
private:

	//障害物のテクスチャ
	ID3D11ShaderResourceView* mStickTex;//箸
	ID3D11ShaderResourceView* mPlateTex;//皿
	ID3D11ShaderResourceView* mCupTex;	//カップ

	StaticObject* mChopstick[2];// 箸


	HitCircle* mBlockHitCircle[2];// 皿とカップ
public:

	Table_Stage();	//コンストラクタ
	~Table_Stage();	//デストラクタ

	void Update() override;	//更新
	void Draw() override;	//描画
};

