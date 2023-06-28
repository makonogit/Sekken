#pragma once
#include"Fade.h"
#include"Sprite.h"

class TestScene
{
private:

	Fade* mFade;							//フェード用
	ID3D11ShaderResourceView* TestTexture;	//テクスチャ
	XMFLOAT3 camera;						//カメラ座標
	Sprite* TestSprite;						//テスト用スプライト
	Sprite* TestFrisbe;						//テスト用フリスビー
	float OldStickPos_x;					//スティックの前の座標
	float OldStickPos_y;					

	bool StickTrigger;						//スティック1回入力

public:

	TestScene(void);						//コンストラクタ
	~TestScene(void);						//デストラクタ
	void Draw(void);						//描画
	void Update(void);						//更新

};

