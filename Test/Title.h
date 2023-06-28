//======================================================================================
// 名前：Title.h
// 説明：タイトル画面
//======================================================================================
#pragma once
#include"SceneManager.h"

class Title :
	public Scene
{
private:

	ID3D11ShaderResourceView* backTexture;					//背景テクスチャ
	StaticObject* backObject;								//背景オブジェクト

	ID3D11ShaderResourceView* titleTexture;					//タイトルロゴテクスチャ
	StaticObject* titleObject;								//タイトルロゴオブジェクト

	ID3D11ShaderResourceView* charaTexture;					//キャラクターテクスチャ
	StaticObject* charaObject;								//キャラクターオブジェクト

	ID3D11ShaderResourceView* dogTexture;					//犬テクスチャ
	StaticObject* dogObject;								//犬オブジェクト

	ID3D11ShaderResourceView* startTexture;					//スタートテクスチャ
	ID3D11ShaderResourceView* startTexture2;				//スタートテクスチャ2
	StaticObject* startObject;								//スタートオブジェクト

	ID3D11ShaderResourceView* endTexture;					//エンドテクスチャ
	ID3D11ShaderResourceView* endTexture2;					//エンドテクスチャ2
	StaticObject* endObject;								//エンドオブジェクト

	XMFLOAT3 camera = { 0.0f,0.0f,1.0f };				//カメラ座標

	bool mBgmPlay = false;	//BGM

public:

	Title();			//コンストラクタ
	~Title();			//デストラクタ

	void Draw(void) override;	//描画
	void Update(void) override;	//更新

};

//======================================================================================
// 担当者：		伊東
// 制作日時：　 2022-12-01
// チーム名：	黒棺	
//======================================================================================
