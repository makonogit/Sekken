//======================================================================================
// 名前：Fade_Dogrun.h
// 説明：犬のフェード
//犬のテクスチャは仮で使っていたものなので変更してください
//======================================================================================

#pragma once
#include "Fade.h"
#include"StaticObject.h"
#include"AnimObject.h"

class Fade_Dogrun :public Fade
{
private:
	ID3D11ShaderResourceView* BackTexture;	//テクスチャ用変数
	StaticObject* Back[2];	//背景
	//StaticObject* Dogrun;	//犬
	AnimObject* Dogrun;
	
	int fiFlg,feFlg;	//フェードイン状態格納用変数

public:
	Fade_Dogrun();		//コンストラクタ
	~Fade_Dogrun();		//デストラクタ

	static void FadeIn(void);			//フェードイン
	static void FadeOut(void);			//フェードアウト
	void Update();		//更新
	void Draw();		//描画

	static int mState;		//現在の状態を入れる変数
};

//======================================================================================
// 担当者：		井上想哉
// 制作日時：　 2022-12-05
// チーム名：	黒棺	
//======================================================================================