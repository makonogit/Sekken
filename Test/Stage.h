//======================================================================================
// 名前：Stage.h
// 説明：各ステージのベース
//======================================================================================
#pragma once
#include "Player.h"
#include "Dog.h"
#include "Cat.h"
#include "MiniMap.h"
#include "Frisbee.h"
#include "Dirt.h"
#include "Floor.h"
#include "SceneManager.h"
#include "Babble.h"
#include  <math.h>
#include "Robot.h"

#define FontU_Size 1.0f / 5.0f
#define FontV_Size 1.0f / 2.0f

#define BABBLMAX 50			//泡最大数
#define BLOCKMAX 3			//障害物最大数
#define sqr(n) ((n)*(n))	//距離計算用

#define ZOOMMAX 0.000001f	//カメラのズーム

//イベント
enum Ivent {
	NONE_IVENT,		//なんのイベントでもない
	DOG_IVENT,		//犬のイベント
	CAT_IVENT,		//猫のイベント
	IVENT_END
};

class Stage 
{
protected:

	Cat* mCat;								//猫
	Dog* mDog;								//犬
	Player* mPlayer;						//プレイヤー
	Frisbee* mFrisbee;						//フリスビー
	Floor* mFloor;							//床
	Robot* mRobot;							//ロボット
	StaticObject* mBlock[BLOCKMAX];			//障害物(3種類の障害物)
	HitSquare* mBlockHit[BLOCKMAX];			//障害物の当たり

	Babble* mBabble[BABBLMAX];				//泡
	int BabbleNum;			
	
	//StaticObject* mObj[3];					//障害物(3種類)

	XMFLOAT3 mCamera;						//カメラ
	StaticObject* mBackGround;				//背景
	ID3D11ShaderResourceView* mBgTex;		//背景テクスチャ用変数

	ID3D11ShaderResourceView* mTimeBackTex;	//時間背景用変数
	StaticObject* mTimeBack;				//時間表示用
	ID3D11ShaderResourceView* mNumTex[10];	//時間テクスチャ用変数
	StaticObject* mTime[4];					//時間表示用
	ID3D11ShaderResourceView* mCatMarkTex;	//猫マーカーテクスチャ
	StaticObject* mCatMark;					//猫マーカー

	HitSquare* mRobotHit;					//ロボットの当たり


	float fTime = 900000.0f;				//制限時間計測(ミリ秒)
	float fCatTime = 0.0f;					//猫が出現する時間
	float VibrationTime = 0.0f;				//振動する時間
	bool mSound[5] = { false };

	int ClearNum;							//汚れていない数
	int mMapInfo[STAGE_HIGHT][STAGE_WIDTH];		//ステージ情報

	float fCameraZoom;		//カメラズーム率
	float fDogCryTime = 0.0f;		//犬が鳴く時間

private:
	
public:

	int Score;								//スコア
	bool TimeActive = true;					//制限時間終了しているかどうか
	MiniMap* mMiniMap;						//ミニマップ
	SOUND_LABEL mBGMSound;					// BGMのラベルの変数

	void DrawTime(float Num);				//時間表示(ミリ秒で受け取る)

	void DrawMiniMap(void);		//ミニマップの表示
	void CameraSet(void);		//カメラの制御

	virtual void Update();	    //更新
	virtual void Draw();		//描画

};

