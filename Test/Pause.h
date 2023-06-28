#pragma once
//======================================================================================
// 名前：Pause.h
// 説明：ポーズ画面
//======================================================================================
#include "SceneManager.h"

class Pause :
	public Scene
{
private:

	//選択中のID
	typedef enum {
		RETURN,
		REPLAY,
		TITLE_BACK
	};

	ID3D11ShaderResourceView* mBackTex;				//背景テクスチャ
	ID3D11ShaderResourceView* mUIContinueTex;				//UIテクスチャ
	ID3D11ShaderResourceView* mUIRestartTex;				//UIテクスチャ
	ID3D11ShaderResourceView* mUITitleBackTex;				//UIテクスチャ
	StaticObject* mBack;		//背景
	StaticObject* mReturnUI;	//ゲームに戻るUI
	StaticObject* mTitleUI;		//タイトル画面UI
	StaticObject* mReplayUI;	//やり直しUI
	//StaticObject* mPauselogo;	//ポーズロゴ
	XMFLOAT3 camera;			//カメラ
	Sprite::RGBA color;			//背景色

	Sprite::RGBA Normal;		//暗く
	Sprite::RGBA Black;	//通常
	Sprite::RGBA Blue;	//青


	int SelectID;		//選択ID

public:

	Pause();	//コンストラクタ
	~Pause();	//デストラクタ

	void Update() override;	//更新
	void Draw() override;	//描画

	int SceneSelect();		//シーン選択

};

