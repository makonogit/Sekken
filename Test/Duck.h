//======================================================================================
// 名前：Duck.h
// 説明：アヒルのヘッダーファイル
//======================================================================================
#pragma once

//------------------------------------
//		include
//------------------------------------

#include "AnimObject.h"
#include "HitCircle.h"//円の当たり判定

//------------------------------------
//		列挙型
//------------------------------------
enum DuckStateID
{
	DUCK_NONE = 0,// 何もしない
	DUCK_MOVE,// 動く
	DUCK_CARRY,// 犬を持ち運ぶ
	DUCK_CONFUSION,// フリスビーを当てられた時
};

//------------------------------------
//		class
//------------------------------------

class Duck :
	public AnimObject
{
private:
	ID3D11ShaderResourceView* mDuckTex;			// アヒルテクスチャ
	XMFLOAT2 mResistance;// 抵抗力
	float mTime;

	void Move(void);// 動く
	void Confusion(void);
public:
	HitCircle* mCircle;// アヒル本体のあたり判定
	DuckStateID mState;// 状態
	float mAngle;

	Duck(XMFLOAT3 &_Camera);	// コンストラクタ
	~Duck(); // デストラクタ

	void Update()override;	// 更新
	void SetResistance(XMFLOAT2);// 抵抗力の計算
	void ChangeState(DuckStateID _state);
};

//======================================================================================
// 担当者：		中川直登
// チーム名：	黒棺	
//======================================================================================