#pragma once

#include"SceneManager.h"

#define GAGEMAX 1.25f	//ゲージの最大サイズ

class Result :
	public Scene
{
private:

	XMFLOAT3 camera = { 0.0f,0.0f,1.0f };	//カメラ座標

	ID3D11ShaderResourceView* mBgTex;			//背景テクスチャ用変数
	ID3D11ShaderResourceView* mReplayUITex;		//リプレイテクスチャ
	ID3D11ShaderResourceView* mReturnUITex;		//ステージ選択テクスチャ用
	ID3D11ShaderResourceView* mScoreUITex[4];	//スコアテクスチャ用(C~S)

	ID3D11ShaderResourceView* mScoreGageFreamTex;		//スコアゲージ枠テクスチャ用
	ID3D11ShaderResourceView* mScoreGageBackTex;		//スコアゲージ背景テクスチャ用
	ID3D11ShaderResourceView* mScoreGageTex;			//スコアゲージテクスチャ用

	ID3D11ShaderResourceView* mCrackerTex;				//クラッカーテクスチャ用
	ID3D11ShaderResourceView* mCracker_PaperTex;		//クラッカーの紙？テクスチャ用

	StaticObject* mBg;						//背景
	
	StaticObject* mReplayUI;				//リプレイUI
	StaticObject* mReturnUI;				//ステージ選択UI
	StaticObject* mScoreUI;					//スコアUI

	StaticObject* mScoreGageFream;			//スコアゲージの枠
	StaticObject* mScoreGageBack;			//スコアゲージの背景
	StaticObject* mScoreGage;				//スコアゲージ

	StaticObject* mCracker_Left;				//クラッカー左
	StaticObject* mCracker_Right;				//クラッカー右
	StaticObject* mCracker_Paper_Left;			//クラッカーの紙?左
	StaticObject* mCracker_Paper_Right;			//クラッカーの紙?右

	float fRevers;			//反転用
	float fWeight;			//重力加速(クラッカーのアニメーション用)


	static int nScore;		//スコア
	int ScoreLank = 0;		//スコアランク
	bool GageState = true;	//ゲージの状態
	int nSceneNum = 0;		//シーン番号
	bool mSound = false;
	float mSETime;

	XMFLOAT2 SelectSize;	//選択中のUIのサイズ

public:
	
	Result();	//コンストラクタ
	~Result();	//デストラクタ

	void Update() override;	//更新
	void Draw() override;	//描画
	void SceneSelect();		//シーン選択
	bool ScoreGageAnim();	//スコアゲージのアニメーション(true:アニメーション中　false:アニメーション終了)
	void Cracker_Anim();	//クラッカーアニメーション
	static void GetScore(int Score);	//スコアの受け取り
	
};

