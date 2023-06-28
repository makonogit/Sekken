//======================================================================================
// 名前：Dog.h
// 説明：犬のヘッダーファイル
//======================================================================================
#pragma once

//------------------------------------
//		include
//------------------------------------

#include"Input.h"// 一番上※順番注意
#include"AnimObject.h"
#include "HitCircle.h"//円の当たり判定
#include "Fade_Bubble.h"
//------------------------------------
//		define
//------------------------------------

//#define PI (3.14159265359f)

//------------------------------------
//		列挙型
//------------------------------------

enum DogStateID
{
	DOG_NONE=0,
	DOG_WALK,// 通常状態
	DOG_RUN,// フリスビーを追っかける
	DOG_WAIT,//	プレイヤーの前で待つ
	DOG_RETURN,// 犬が返ってくる
	DOG_BE_CARRYED,//犬がアヒルに運ばれる
};
 
//------------------------------------
//		クラス
//------------------------------------

class Dog : public AnimObject
{
private:
	ID3D11ShaderResourceView* mWalkTexture;			// 犬テクスチャ
	ID3D11ShaderResourceView* mRunTexture;			// 犬テクスチャ
	XMFLOAT2* mTarget;
	XMFLOAT2 mSpeedSlip;
	XMFLOAT2 mResistance;// 抵抗力
	float mWaitTime;
	float mTime;
	float mRunSpeed;
	float mAngle;
	float mOldAngle;

	void Walk(void);
	void Run(void);
	void BeCarryed(void);

	//void Return(void);
public:
	Dog(XMFLOAT3 &_Camera);	// コンストラクタ
	~Dog(); // デストラクタ
	DogStateID mState;


	HitCircle* mCatchArea;//フリスビーをキャッチするあたり判定
	HitCircle* mCatchBubbleArea;//フリスビーをキャッチするあたり判定
	HitCircle* mMissArea;//フリスビーをミスするあたり判定
	HitCircle* mCircle;//犬の体のあたり判定
	bool mSlip;


	void Update()override;
	//bool CatchResult(HitCircle*);
	void SetResistance(XMFLOAT2);// 抵抗力の計算
	void ChangeState(DogStateID);
	void SetTarget(XMFLOAT2*);
};


//======================================================================================
// 担当者：		中川直登
// チーム名：	黒棺	
//======================================================================================