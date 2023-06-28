#pragma once
//======================================================================================
// 名前：SceneManager.h
// 説明：シーン管理
//======================================================================================

//------------------------------------
//		include
//------------------------------------
#include"Scene.h"
#include"Fade.h"
#include"Fade_Bubble.h"
#include"Fade_Dogrun.h"
#include"System.h"

//------------------------------------
//		列挙型
//------------------------------------

enum SceneStateID
{
	NONE_SCENE = 0,
	TITLE,
	SELECT,
	GAME_MAIN,
	POSE,
	RESULT,
};
//------------------------------------
//		クラス
//------------------------------------
class SceneManager
{
private:
	
	static Scene* mScene;							//シーン
	static Fade* mFade[3];							//フェード用
	
public:
	static void Init(void);							//初期化
	static void Uninit(void);						
	static void SceneChange(SceneStateID scene,Fade_Type Fade_Name);	//シーン切替関数
	static int Update(void);						//更新
	static void Draw(void);							//描画
};


//======================================================================================
//担当者：菅眞心
//製作日：2022/11/25
//======================================================================================

