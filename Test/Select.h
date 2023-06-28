//======================================================================================
// 名前：Select.h
// 説明：ステージ選択画面
//======================================================================================
#pragma once
#include "SceneManager.h"

#define MAXSTAGE 3	//最大ステージ数

//選択ステージのID
enum STAGETID {
	ROOM_STAGE,
	BATH_STAGE,
	TABLE_STAGE,
	TUTORIAL_STAGE,
};

class Select : 
	public Scene
{
private:

	//回転状態
	enum RotaState {
		LEFT_ROTA,
		RIGHT_ROTA,
		NONE_ROTA
	};

	int StageID[MAXSTAGE];						//ステージIDの並び順
	static int SelectStageID;					//選択中のステージID
	static int mInput;							//入力情報

	int Rota;									//回転状態
	int Stage_Info;								//ステージ詳細表示
	bool Stage_Dicision;						//ステージ決定しているか

	ID3D11ShaderResourceView* mBgTex;				//背景テクスチャ
	ID3D11ShaderResourceView* mTableObjTex;			//テーブルテクスチャ
	ID3D11ShaderResourceView* mBathObjTex;			//風呂テクスチャ
	ID3D11ShaderResourceView* mRoomObjTex;			//部屋テクスチャ
	ID3D11ShaderResourceView* mStartUITex;			//スタートボタンテクスチャ
	ID3D11ShaderResourceView* mCancelUITex;			//キャンセルボタンテクスチャ
	ID3D11ShaderResourceView* mDifficultyUITex;			//難易度UIテクスチャ
	ID3D11ShaderResourceView* mDifficultyBackUITex;			//難易度UIテクスチャ
	ID3D11ShaderResourceView* mRankUITex[4];			//難易度UIテクスチャ
	ID3D11ShaderResourceView* mRankBackUITex;			//難易度UIテクスチャ
	ID3D11ShaderResourceView* mTutorialUITex;			//チュートリアルテクスチャ
	ID3D11ShaderResourceView* mStageNameBackTex;		//ステージ名称UIテクスチャ
	ID3D11ShaderResourceView* mTableNameUITex;		//テーブル名称UIテクスチャ
	ID3D11ShaderResourceView* mBathNameUITex;		//お風呂場名称UIテクスチャ
	ID3D11ShaderResourceView* mRoomNameUITex;		//玄関名称UIテクスチャ
	ID3D11ShaderResourceView* mLevelFontTex;		//難易度UIテクスチャ
	ID3D11ShaderResourceView* mTimeLimitTex;		//制限時間テクスチャ
	ID3D11ShaderResourceView* mSelectTex;			//『ステージ選択』
	ID3D11ShaderResourceView* mSelectBackTex;		//背景

	StaticObject* mBg;								//背景
	StaticObject* mObject[MAXSTAGE];				//ゲームオブジェクト
	StaticObject* mStartUI;							//開始UI
	StaticObject* mCancelUI;						//キャンセルUI
	StaticObject* mTutorialUI;						//チュートリアルUI
	StaticObject* mDifficultyUI;							//難易度UI
	StaticObject* mDifficultyBackUI;							//難易度UI
	StaticObject* mRankUI;							//制限時間時間UI
	StaticObject* mRankBackUI;							//制限時間時間UI
	StaticObject* mStageNameUI;						//ステージ名称UI
	StaticObject* mStageNameBackUI;						//ステージ名称UI
	StaticObject* mSelectUI;						//『ステージ選択』
	StaticObject* mSelectBackUI;					//背景

	XMFLOAT3 camera = { 0.0f,0.0f,1.0f };			//カメラ座標

	int BGMChange = false;
	SOUND_LABEL BGM;
	SOUND_LABEL OldBGM;
	float mBGMTime;

	Sprite::RGBA Red = { 1.0f,0.0f,0.0f,1.0f };		//テスト用赤
	Sprite::RGBA White = { 1.0f,1.0f,1.0f,1.0f };	//テスト用白

public:

	Select();						//コンストラクタ
	~Select();						//デストラクタ
	//ステージIDを取得する
	static int GetStageID(void);	
	//入力情報を取得する　0:コントローラー　1:キーボード
	static int GetInput(void);
	//ステージ選択
	void StageSelect(void);
	//ステージ詳細
	void StageInfo(void);
	//更新
	void Update(void) override;			
	//更新
	void Draw(void) override;			

};

//======================================================================================
// 担当者：		菅眞心
// 制作日時：　 2022-12-01
// チーム名：	黒棺	
//======================================================================================

