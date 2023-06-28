#pragma once
#include "Stage.h"
#include "Duck.h"

class Bath_Stage :
	public Stage
{
private:
	//障害物のテクスチャ
	ID3D11ShaderResourceView* mSoapTex;		//石鹸
	ID3D11ShaderResourceView* mBottleTex;	//ボトル
	ID3D11ShaderResourceView* mSpongeTex;	//スポンジ

	ID3D11ShaderResourceView* mDuckTex;	//説明
	StaticObject* mDuckUI;		//アヒルの説明
	Duck* mDuck;

	float DuckInfoTime = 0.0f;

public:

	Bath_Stage();		//コンストラクタ
	~Bath_Stage();		//デストラクタ

	void Update() override;	//更新
	void Draw() override;	//描画
};

