//======================================================================================
// 名前：Sprite
// 説明：ポリゴンの表示
//======================================================================================
#pragma once


//------------------------------------
//		include
//------------------------------------
#include <Windows.h>
#include <DirectXMath.h>
#include"WICTextureLoader.h"
#include "Direct3d.h"

using namespace DirectX;


//------------------------------------
//		マクロ定義
//------------------------------------

// なし


//------------------------------------
//		クラス
//------------------------------------

class Sprite
{
protected:

public:


	// 内部クラス＝このクラス内で使えるクラス

	// 色を表す構造体
	struct RGBA
	{
		float r, g, b, a;
	};

	// 頂点データ用の構造体
	struct VERTEX2D
	{
		float x, y;	// 頂点の座標（位置）
		float u, v;	// テクスチャのUV座標
		RGBA color; // 頂点の色
	};

	//　頂点バッファ用の変数
	ID3D11Buffer* mpVertexBuffer;
	//　読み込んだテクスチャを保持するための変数
	ID3D11ShaderResourceView* mpTexture;

	XMFLOAT2 mCenter;
	XMFLOAT2 mSize;
	XMFLOAT4 mUV;
	XMFLOAT3& mCamera;
	//float mAngle;	// 角度

	RGBA mColor;

	virtual void Update();
	void Draw();	// 描画処理
	void SetColor(RGBA color);// 頂点の色を設定する関数
	void SetTexture(ID3D11ShaderResourceView* pTexture);

	Sprite(XMFLOAT3& _Camera);	// コンストラクタ
	~Sprite();	// デストラクタ


};


//======================================================================================
// 担当者：		中川直登
// チーム名：	黒棺	
//======================================================================================