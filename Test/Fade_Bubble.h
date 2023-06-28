//======================================================================================
// 名前：Fade_Bubble.h
// 説明：泡のフェード
//背景の白は全部消えた方がいいかなと思ってやってるだけなのであとで消すかも
//======================================================================================
#pragma once
#include "Fade.h"
#include"StaticObject.h"

class Fade_Bubble :
	public Fade
{
private:
	ID3D11ShaderResourceView* BackTexture;	//テクスチャ用変数
	Sprite* Back;
	StaticObject* Babble[4];

	float fTime;
public:

	Fade_Bubble();	//コンストラクタ
	~Fade_Bubble();	//デストラクタ

	static void FadeIn(void);			//フェードイン
	static void FadeOut(void);			//フェードアウト
	void Update() override;	//更新
	void Draw() override;	//描画

	static int mState;		//現在の状態を入れる変数
};


//======================================================================================
// 担当者：		菅眞心
// 制作日時：　 2022-12-01
// チーム名：	黒棺	
//======================================================================================