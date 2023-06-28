#pragma once
#include "AnimObject.h"
#include "StaticObject.h"
#include "Fade_Bubble.h"

//猫の状態
typedef enum{
	CNONE,
	WAIT,		//止まる
	WALK,		//歩く
	RUN,		//走る
	LIEDOWN,	//寝転ぶ
	JUMP,		//ジャンプ
}CatState;

//猫の汚れ状態
typedef enum {
	CLEARN,		//きれい
	DIRT,		//汚い
}CatDirtState;

class Cat : public AnimObject
{
private:

	ID3D11ShaderResourceView* mCatTex;			//猫テクスチャ
	ID3D11ShaderResourceView* mDirtCatTex;		//汚れ猫テクスチャ
	ID3D11ShaderResourceView* mCatLieDownTex;	//寝転ぶテクスチャ
	ID3D11ShaderResourceView* mCatJampTex;		//ジャンプテクスチャ

	StaticObject* mStaticObj;					//アニメーションしないオブジェクト

	int nMove;					//ランダム移動
	CatState nState;			//状態

	XMFLOAT2* fTarget;			//追いかける対象

	float fAngle;				//移動角度
	float fMoveSpeed;			//スピード
	float fTime;				//時間
	float fCatDownTime;			//寝転ぶ時間

public:

	bool Appearance;			//出現しているかのフラグ

	CatDirtState nDirtState;	//汚れ状態
	HitCircle* mLieDownHit;		//寝転んでいる時のあたり判定
	HitCircle* mBlockAreaHit;	//妨害するエリアのあたり判定

	Cat(XMFLOAT3 &_Camera);		//コンストラクタ
	~Cat();						//デストラクタ

	void Update() override;	//更新
	void Draw();			//描画

	void Move();							//移動
	void LieDown();							//寝転ぶ
	void Run();								//走る
	void Jump();							//ジャンプ

	void Wait();			//停止

	void SetTarget(XMFLOAT2* _target);		//追いかける対象を指定
	void ChangeState(CatState _state);		//状態遷移
	CatState GetState(void);				//現在の状態を渡す
	void SetDirtState(CatDirtState _state);	//汚れの状態をセット
	void SetAppearance(bool _appearance);	//出現する場所をセット
	void OutSideRun(XMFLOAT2* _Pos);		//画面外に出ていく
};

