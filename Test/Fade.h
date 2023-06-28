//======================================================================================
// 名前：Fade.h
// 説明：フェード
//======================================================================================
#pragma once
#include"Sprite.h"
#include"System.h"

//フェードの状態
typedef enum{
	NONE_FADE,	//なにもしていない
	FADE_IN,	//フェードイン中
	FADE_OUT,	//フェードアウト中
	FADE_IN_END,	//フェードイン終了
	FADE_OUT_END,	//フェードアウト終了
	
}FadeState;

typedef enum {
	NOMAL_FADE,		//普通のフェード
	BUBBLE_FADE,	//泡のフェード
	DOGRUN_FADE,	//犬のフェード
	NONE_TYPE,
}Fade_Type;

class Fade
{
protected:
	
	ID3D11ShaderResourceView* mpTexture;	//テクスチャ用変数
	ID3D11ShaderResourceView* mTeamLogoTex;	//チームロゴ
	Sprite::RGBA color;						//ポリゴンの色
	XMFLOAT3 camera;						//カメラ座標

private:

	Sprite* mSprite;						//フェード用スプライト
	Sprite* mTeamLogo;						//チームロゴ
	
public:

	Fade();			//コンストラクタ
	~Fade();		//デストラクタ

	static void FadeIn(void);			//フェードイン
	static void FadeOut(void);			//フェードアウト
	virtual void Update();		//更新
	virtual void Draw();		//描画

	static int mState;		//現在の状態を入れる変数

};

//======================================================================================
// 担当者：		菅眞心
// 制作日時：　 2022-12-01
// チーム名：	黒棺	
//======================================================================================
