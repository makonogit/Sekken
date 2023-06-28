//======================================================================================
// 名前：Player.h
// 説明：プレイヤーのヘッダーファイル
//======================================================================================
#pragma once

//------------------------------------
//		include
//------------------------------------

#include"Input.h"// 一番上※順番注意
#include "Frisbee.h"// フリスビー
#include"AnimObject.h"
#include "HitCircle.h"//円の当たり判定
#include "Fade_Bubble.h"
//------------------------------------
//		列挙型
//------------------------------------

enum PlayerStateID
{
	PLAYER_DONT_MOVE = 0,	// 動かないし何もしない
	PLAYER_MOVE,			// 移動するとき
	PLAYER_THROW,			// 投げる準備とフリスビーが落ちるまで
};

//------------------------------------
//		クラス
//------------------------------------

class Player : public AnimObject
{
private:

	
	ID3D11ShaderResourceView* mPlayerTex;			// 移動テクスチャ
	ID3D11ShaderResourceView* mPlayerTexThrow;		// 投げるテクスチャ
	ID3D11ShaderResourceView* mMarkTex;		// 投げるテクスチャ

	void Move();	// 移動処理
	void Throw();	// フリスビーを投げる処理
public:
	// メンバー変数
	bool mHitCount;
	HitCircle* mCircle;// あたり判定
	PlayerStateID mState; // プレイヤーの状態変数
	Frisbee* mpFrisbee;// フリスビーのポインタ
	StaticObject* mMark;// 投げる方向の目印
	XMFLOAT2 mSpeed;
	XMFLOAT2 mSpeedSlip;
	float mThrowAngle;// 投げる方向
	XMFLOAT2 mResistance;// 抵抗力
	float fWalkSETime;
	// メンバー関数

	Player(XMFLOAT3 &_Camera, Frisbee* _Fris);	// コンストラクタ
	~Player();					// デストラクタ
	
	void Update()override;	// 更新
	void Slip();
	void SetResistance(XMFLOAT2);// 抵抗力の計算
	void ChangeState(PlayerStateID);
};

//======================================================================================
// 担当者：		中川直登
// チーム名：	黒棺	
//======================================================================================