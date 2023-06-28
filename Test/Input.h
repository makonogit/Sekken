//======================================================================================
// 名前：Input
// 説明：キーボード、マウスとコントローラーの状態を持つ
//======================================================================================
#pragma once

//------------------------------------
//		include
//------------------------------------

#include <Windows.h>// memcpy用

//※注意：Windows.hよりも下にXinput.hを置くこと
#include <Xinput.h>

//------------------------------------
//		マクロ定義
//------------------------------------

#define KEY_MAX 256

//------------------------------------
//		列挙型
//------------------------------------

// ゲームパッドのボタンの識別番号
enum GAMEPAD_BUTTON:unsigned int 
{
	NONE		= 0x0000,
	UP			= 0x0001,
	DOWN		= 0x0002,
	LEFT		= 0x0004,
	RIGHT		= 0x0008,

	START		= 0x0010,
	BACK		= 0X0020,
	LEFT_STICK	= 0x0040,
	RIGHT_STICK	= 0x0080,

	LB			= 0x0100,
	RB			= 0x0200,
	A			= 0x1000,
	B			= 0x2000,
	X			= 0x4000,
	Y			= 0x8000,
};
//------------------------------------
//		構造体
//------------------------------------

typedef struct Input
{
	bool mKeyState[KEY_MAX];// 現在のキーボードの状態
	bool mOldKeyState[KEY_MAX];// 過去のキーボードの状態

	//bool GamePad;
	XINPUT_STATE mGamePadState;// コントローラーの状態を持つ(1つだけ)
	XINPUT_GAMEPAD mOldGamePadButton;// 過去の状態を持つ
	XINPUT_VIBRATION vibration;// バイブレーション
	//float vibrationTime;

	int mMousePosition_X, mMousePosition_Y;// マウスの位置を持つ
	int mKeyCount;
	
}Input;

//------------------------------------
//		プロトタイプ宣言
//------------------------------------

void Input_Init();// 初期化処理
void Input_Update();// 更新処理
void Input_Release();// 解放処理

// Set

void Input_SetMousePos(long mousepos);// マウスカーソルの位置をセットする
void Input_SetKeyDown(int key);// キーが押された時の処理
void Input_SetKeyUp(int key);// キーを離した時の処理
void Input_SetVibration(int rightSpeed, int leftSpeed);// バイブレーションの設定

// Get

bool Input_GetKeyDown(int key);// キーが押されているが
bool Input_GetKeyTrigger(int key);// キーが押された瞬間

int Input_GetMousePosX(void);// マウスのX座標　※追加しました
int Input_GetMousePosY(void);// マウスのX座標　※追加しました

bool Input_GetButtonDown(GAMEPAD_BUTTON num);// ゲームパッドのボタンが押されているが
bool Input_GetButtonTrigger(GAMEPAD_BUTTON num);// ゲームパッドのボタンが押された瞬間
float Input_GetLeftStick_X(void);// LスティックのⅩの値を返す
float Input_GetLeftStick_Y(void);// LスティックのＹの値を返す
float Input_GetRightStick_X(void);// ＲスティックのⅩの値を返す
float Input_GetRightStick_Y(void);// ＲスティックのＹの値を返す
int Input_GetLTButton(void);// LTボタンの値を返す0～255
int Input_GetRTButton(void);// RTボタンの値を返す0～255

//======================================================================================
// クラス：		AT12E224
// 出席番号：	16
// 担当者：		中川直登
// チーム名：	黒棺	
//======================================================================================