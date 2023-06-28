//======================================================================================
// 名前：Frisbee.h
// 説明：フリスビーのヘッダーファイル
//======================================================================================
#pragma once

//------------------------------------
//		include
//------------------------------------

#include"Input.h"//※順番注意
#include "StaticObject.h"
#include "HitCircle.h"
#include "Sound.h"
//------------------------------------
//		列挙型
//------------------------------------

enum FrisbeeStateID
{
	FRISBEE_DROP = 0,		// 落ちた時
	FRISBEE_FRY,
	FRISBEE_HOLD,
};

enum CharHoldFrisbee
{
	DONT_HOLD = 0,
	HOLD_PLAYER,
	HOLD_DOG,
};

//------------------------------------
//		クラス
//------------------------------------

class Frisbee :
	public StaticObject
{
private:
	ID3D11ShaderResourceView* mTexture;			// フリスビーテクスチャ
	ID3D11ShaderResourceView* mShadowTexture;	// フリスビーの影テクスチャ
public:
	HitCircle* mCircle;
	StaticObject* mShadow;
	FrisbeeStateID mState;
	CharHoldFrisbee mHold;
	float mMiniSize;// 最小サイズ
	float mAngle;// 進行方向
	float mRate;// 速度率
	float mSpeed;// 速度
	bool mSound = false;	//サウンド状態を格納する変数

	Frisbee(XMFLOAT3 &);// コンストラクタ
	~Frisbee();// デストラクタ
	
	void SetReserve(XMFLOAT2,float);// 投げる準備
	void Fry();
	void Drop();
	void Update()override;// 更新処理
	void ChangeState(FrisbeeStateID);
	void Catch(CharHoldFrisbee);

	//void Collide();
};

//======================================================================================
// 担当者：		中川直登
// チーム名：	黒棺	
//======================================================================================