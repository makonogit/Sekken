//======================================================================================
// 名前：Input
// 説明：キーボード、マウスとコントローラーの状態を持つ
//======================================================================================

//------------------------------------
//		include
//------------------------------------

#include "Input.h"


//------------------------------------
//		リンク指定
//------------------------------------

#pragma comment (lib,"xinput.lib")// ゲームパッドのインプット

//------------------------------------
//		グローバル変数宣言
//------------------------------------

Input* gpInput;

//------------------------------------
//		プロトタイプ宣言
//------------------------------------

void Rfresh();// リフレッシュ

//------------------------------------
//		関数
//------------------------------------


//<><><><><><><><><><><><><><><><><><>
// 関数名：リフレッシュ関数
// 役割：mOldKeyStateやmOldGamePadButtonの更新する
// 引数：なし
// 戻り値：なし
//<><><><><><><><><><><><><><><><><><>
void Rfresh()
{
	// ゲームループの最後で現在のキー状態をgOldKeyStateに保存
	memcpy_s(gpInput->mOldKeyState, sizeof(gpInput->mOldKeyState),
		gpInput->mKeyState, sizeof(gpInput->mKeyState));

	gpInput->mKeyCount = 0;// リセット
	for (int i = 0; i < KEY_MAX; i++)
	{
		gpInput->mKeyCount += (int)gpInput->mKeyState[i];// 押された数を数える
	}
	
	// 現在のゲームパッドの状態をmOldGamePadButtonに保存
	gpInput->mOldGamePadButton = gpInput->mGamePadState.Gamepad;
}


//<><><><><><><><><><><><><><><><><><>
// 関数名：初期化処理関数
// 役割：Input構造体の動的確保をする
// 引数：なし
// 戻り値：なし
//<><><><><><><><><><><><><><><><><><>
void Input_Init()
{
	gpInput = (Input*)malloc(sizeof(Input));
	for (int i = 0; i < KEY_MAX; i++)
	{
		gpInput->mKeyState[i] = false;// 初期化
	}
	ZeroMemory(&gpInput->mGamePadState, sizeof(XINPUT_STATE));
	ZeroMemory(&gpInput->vibration, sizeof(XINPUT_VIBRATION));
}


//<><><><><><><><><><><><><><><><><><>
// 関数名：アップデート関数
// 役割：Input構造体の状態を更新する
// 引数：なし
// 戻り値：なし
//<><><><><><><><><><><><><><><><><><>
void Input_Update()
{
	Rfresh();
	XInputGetState(0, &gpInput->mGamePadState);// ゲームパッドの状態を取得する
	
}


//<><><><><><><><><><><><><><><><><><>
// 関数名：リリース関数
// 役割：動的確保したInput構造体を解放する
// 引数：なし
// 戻り値：なし
//<><><><><><><><><><><><><><><><><><>
void Input_Release()
{
	free(gpInput);
}


//<><><><><><><><><><><><><><><><><><>
// 関数名：セットマウスポジション関数
// 役割：マウスカーソルの座標を設定する
// 引数：long マウスの座標
// 戻り値：なし
//<><><><><><><><><><><><><><><><><><>
void Input_SetMousePos(long mousepos)
{
	// 下位ビットを取得する
	gpInput->mMousePosition_X = mousepos & 0x0000ffff;
	// 上位ビットを取得する
	gpInput->mMousePosition_Y = (mousepos & 0xffff0000) >> 16;
}


//<><><><><><><><><><><><><><><><><><>
// 関数名：セットキーダウン関数
// 役割：押されたキーを設定する
// 引数：int 押されたキー
// 戻り値：なし
//<><><><><><><><><><><><><><><><><><>
void Input_SetKeyDown(int key)
{
	gpInput->mKeyState[key] = true;
}


//<><><><><><><><><><><><><><><><><><>
// 関数名：セットキーアップ関数
// 役割：離したキーを設定する
// 引数：int 離したキー
// 戻り値：なし
//<><><><><><><><><><><><><><><><><><>
void Input_SetKeyUp(int key)
{
	gpInput->mKeyState[key] = false;
}


//<><><><><><><><><><><><><><><><><><>
// 関数名：セットバイブレーション関数
// 役割：バイブレーションを設定する。※注意：連続で呼ぶとコントローラの接続が切断されるので何かしら対策を模索中です
// 引数：int 右の回転速度, int 左の回転速度
// 戻り値：なし
//<><><><><><><><><><><><><><><><><><>
void Input_SetVibration(int rightSpeed, int leftSpeed)
{
	if(gpInput->vibration.wLeftMotorSpeed != leftSpeed && gpInput->vibration.wRightMotorSpeed != rightSpeed)
	{
		gpInput->vibration.wLeftMotorSpeed = leftSpeed;// 0～65535の間で使う
		gpInput->vibration.wRightMotorSpeed = rightSpeed;// 0～65535の間で使う
		XInputSetState(0, &gpInput->vibration);// 振動
	}
}


//<><><><><><><><><><><><><><><><><><>
// 関数名：ゲットキーダウン関数
// 役割：キーが押されているか判別する
// 引数：int 識別したいキー
// 戻り値：bool　true 押されている　false 押されてない
//<><><><><><><><><><><><><><><><><><>
bool Input_GetKeyDown(int key)
{
	return gpInput->mKeyState[key];
}


//<><><><><><><><><><><><><><><><><><>
// 関数名：ゲットキートリガー関数
// 役割：キーが押された瞬間を判別する
// 引数：int 識別したいキー
// 戻り値：bool　true 押した瞬間　false それ以外
//<><><><><><><><><><><><><><><><><><>
bool Input_GetKeyTrigger(int key)
{
	return  (gpInput->mKeyState[key] == TRUE )&& (gpInput->mOldKeyState[key] == FALSE);
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：ゲットマウスポズX関数
// 役割：マウスの位置を取得
// 引数：ナシ
// 戻り値：int 
//<><><><><><><><><><><><><><><><><><>
int Input_GetMousePosX(void)
{
	return gpInput->mMousePosition_X;
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：ゲットマウスポズX関数
// 役割：マウスの位置を取得
// 引数：ナシ
// 戻り値：int 
//<><><><><><><><><><><><><><><><><><>
int Input_GetMousePosY(void)
{
	return gpInput->mMousePosition_Y;
}


//<><><><><><><><><><><><><><><><><><>
// 関数名：ゲットボタンダウン関数
// 役割：ボタンが押されているか判別する
// 引数：GAMEPAD_BUTTON　識別したいボタン
// 戻り値：bool　true 押されている　false 押されてない
//<><><><><><><><><><><><><><><><><><>
bool Input_GetButtonDown(GAMEPAD_BUTTON num)
{
	return gpInput->mGamePadState.Gamepad.wButtons & num;
}


//<><><><><><><><><><><><><><><><><><>
// 関数名：ゲットボタントリガー関数
// 役割：ボタンの押された瞬間を判別する
// 引数：GAMEPAD_BUTTON　識別したいボタン
// 戻り値：bool　true 押した瞬間　false それ以外
//<><><><><><><><><><><><><><><><><><>
bool Input_GetButtonTrigger(GAMEPAD_BUTTON num)
{
	return ((gpInput->mGamePadState.Gamepad.wButtons & num) && !(gpInput->mOldGamePadButton.wButtons & num));
}


//<><><><><><><><><><><><><><><><><><>
// 関数名：ゲットレフトスティックⅩ関数
// 役割：LスティックのⅩの入力を1.0f～0,0fの範囲で返す
// 引数：なし
// 戻り値：float 1.0f～0,0fの範囲
//<><><><><><><><><><><><><><><><><><>
float Input_GetLeftStick_X(void)
{
	float LX = (float)gpInput->mGamePadState.Gamepad.sThumbLX / 32767;
	LX = ((LX * LX) > 0.002f ? LX : 0.0f);
	return LX;
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：ゲットレフトスティックＹ関数
// 役割：LスティックのＹの入力を1.0f～0,0fの範囲で返す
// 引数：なし
// 戻り値：float 1.0f～0,0fの範囲
//<><><><><><><><><><><><><><><><><><>
float Input_GetLeftStick_Y(void)
{
	float LY = (float)gpInput->mGamePadState.Gamepad.sThumbLY / 32767;
	LY = ((LY * LY) > 0.002f ? LY : 0.0f);
	return  LY;
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：ゲットライトスティックⅩ関数
// 役割：ＲスティックのＸの入力を1.0f～0,0fの範囲で返す
// 引数：なし
// 戻り値：float 1.0f～0,0fの範囲
//<><><><><><><><><><><><><><><><><><>
float Input_GetRightStick_X(void)
{
	float RX = (float)gpInput->mGamePadState.Gamepad.sThumbRX / 32767;
	RX = ((RX * RX) > 0.0025f ? RX : 0);
	return  RX;
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：ゲットレフトスティックＹ関数
// 役割：LスティックのＹの入力を1.0f～0,0fの範囲で返す
// 引数：なし
// 戻り値：float 1.0f～0,0fの範囲
//<><><><><><><><><><><><><><><><><><>
float Input_GetRightStick_Y(void)
{
	float RY = (float)gpInput->mGamePadState.Gamepad.sThumbRY / 32767;
	RY = ((RY * RY) > 0.0025f ? RY : 0);
	return  RY;
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：ゲットレフトトリガーボタン関数
// 役割：LTトリガーの入力を0～255の範囲で返す
// 引数：なし
// 戻り値：int 0～255
//<><><><><><><><><><><><><><><><><><>
int Input_GetLTButton(void)
{
	return (int)gpInput->mGamePadState.Gamepad.bLeftTrigger;
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：ゲットライトトリガーボタン関数
// 役割：RTトリガーの入力を0～255の範囲で返す
// 引数：なし
// 戻り値：int 0～255
//<><><><><><><><><><><><><><><><><><>
int Input_GetRTButton(void)
{
	return (int)gpInput->mGamePadState.Gamepad.bRightTrigger;
}


//======================================================================================
// クラス：		AT12E224
// 出席番号：	16
// 担当者：		中川直登
// チーム名：	黒棺	
//======================================================================================