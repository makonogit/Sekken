#pragma once

#include "Stage.h"
#include "Select.h"

class Tutorial :
	public Stage
{
private:

	//障害物のテクスチャ
	ID3D11ShaderResourceView* mChopStick_BlueTex;	//お箸(青)
	ID3D11ShaderResourceView* mChopStick_PinkTex;	//お箸(ピンク)

	StaticObject* mBlock4;		//このステージ限定


	//タスクのテクスチャ
	ID3D11ShaderResourceView* mWalkTaskTex;		//歩行タスクテクスチャ
	ID3D11ShaderResourceView* mSetTaskTex;		//構えタスクテクスチャ
	ID3D11ShaderResourceView* mAngleTaskTex;	//角度タスクテクスチャ
	ID3D11ShaderResourceView* mThrowTaskTex;	//投げるタスクテクスチャ
	ID3D11ShaderResourceView* mCurveTaskTex;	//カーブタスクテクスチャ

	ID3D11ShaderResourceView* mPauseTex;		//ポーズテクスチャ

	ID3D11ShaderResourceView* mWASDKeyTex[2];			//WASDキーテクスチャ
	ID3D11ShaderResourceView* mXY_ButtonTex[2];			//XYボタンテクスチャ
	ID3D11ShaderResourceView* mB_ButtonTex[2];			//Bボタンテクスチャ
	ID3D11ShaderResourceView* mEscape_KeyTex[2];		//Escapeキーテクスチャ
	ID3D11ShaderResourceView* mSpeace_KeyTex[2];		//Speaceキーテクスチャ
	ID3D11ShaderResourceView* mTriggerTex[2];	//トリガーテクスチャ
	ID3D11ShaderResourceView* mStickTex[2];		//スティックテクスチャ
	ID3D11ShaderResourceView* mMousePointTex;	//マウスポインタテクスチャ
	ID3D11ShaderResourceView* mMouseTex[3];		//マウステクスチャ

	ID3D11ShaderResourceView* mDogIvent_KeyTex;		//犬イベントテクスチャ(キーボード)
	ID3D11ShaderResourceView* mCatIvent_KeyTex;		//猫イベントテクスチャ(キーボード)
	ID3D11ShaderResourceView* mDogIvent_ButtonTex;	//犬イベントテクスチャ(コントローラー)
	ID3D11ShaderResourceView* mCatIvent_ButtonTex;	//猫イベントテクスチャ(コントローラー)

	StaticObject* mWalk_KeyUI;		//歩行(WASD)
	StaticObject* mSet_KeyUI;		//セット(Speace[0])
	StaticObject* mCurve_UI;		//カーブ(Mouse[0~2])
	StaticObject* mAngle_KeyUI;		//角度(MousePoint)
	StaticObject* mThrow_KeyUI;		//投擲(Speace[1])
	StaticObject* mPause_KeyUI;		//ポーズ(Escape[0])
	
	StaticObject* mWalk_TaskUI;			//歩行タスクUI
	StaticObject* mSet_TaskUI;			//フリスビーセットタスクUI
	StaticObject* mAngle_TaskUI;		//角度タスクUI
	StaticObject* mThrow_TaskUI;		//角度タスクUI
	StaticObject* mCurve_TaskUI;		//カーブタスクUI
	StaticObject* mPauseUI;				//ポーズUI
	
	StaticObject* mIvent_UI;			//イベントUI
	Ivent mDogIvent_State;
	Ivent mCatIvent_State;
	int mInput;		//入力情報

	//マウスの座標
	int MouseX = 0;
	int MouseY = 0;

public:



	Tutorial();				//コンストラクタ
	~Tutorial();			//デストラクタ

	void KeyLoad();			//キーボード入力の場合の初期化
	void ButtonLoad();		//ボタン入力の場合の初期化
	void Task_Set();				//タスクバーの位置設定
	Ivent Ivent_Set(Ivent IventNum);	//イベント開始処理
	void Hit();						//あたり判定
	void Catch();					//キャッチ
	void Update() override;			//更新
	void Draw() override;			//描画
};
