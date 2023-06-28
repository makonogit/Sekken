//======================================================================================
// 名前：Sound.h
// 説明：サウンド
//======================================================================================
#ifndef _XAUDIO2_H_
#define _XAUDIO2_H_

#include <xaudio2.h>


// パラメータ構造体
typedef struct
{
	LPCSTR filename;	// 音声ファイルまでのパスを設定
	bool bLoop;			// trueでループ。通常BGMはture、SEはfalse。
} PARAM;

// サウンドファイル
typedef enum
{
	//BGM
	SOUND_LABEL_BGM000,			// タイトルBGM
	SOUND_LABEL_BGM001,			// リザルトBGM
	SOUND_LABEL_BGM002,			// バスルームBGM(short)
	SOUND_LABEL_BGM003,			// 玄関BGM(short)
	SOUND_LABEL_BGM004,			// テーブルBGM(short)
	SOUND_LABEL_BGM005,			// バスルームBGM(long)
	SOUND_LABEL_BGM006,			// 玄関BGM(long)
	SOUND_LABEL_BGM007,			// テーブルBGM(long)
	//ゲームフェードSE
	SOUND_LABEL_SE000,			// 犬のフェードSE
	SOUND_LABEL_SE001,			// 泡のフェードSE
	//ゲームメインSE
	SOUND_LABEL_SE002,			// 泡が飛ぶときのSE
	SOUND_LABEL_SE003,			// 泡が破裂した時のSE
	SOUND_LABEL_SE004,			// 猫鳴き声SE
	SOUND_LABEL_SE005,			// 猫が逃げる時のSE
	SOUND_LABEL_SE006,			// 猫が驚くときのSE
	SOUND_LABEL_SE007,			// 猫が歩くときのSE
	SOUND_LABEL_SE008,			// フリスビーカーブSE
	SOUND_LABEL_SE009,			// 汚れの上を歩く時の猫のSE
	SOUND_LABEL_SE010,			// 犬鳴き声SE
	SOUND_LABEL_SE011,			// 犬ジャンプSE
	SOUND_LABEL_SE012,			// 犬気づくSE
	SOUND_LABEL_SE013,			// アヒルロボット足音SE
	SOUND_LABEL_SE014,			// フリスビー飛んでいくSE
	SOUND_LABEL_SE015,			// 猫ゴロンSE
	SOUND_LABEL_SE016,			// 残り半分SE
	SOUND_LABEL_SE017,			// 犬ジャンプSE
	SOUND_LABEL_SE018,			// フリスビー減速SE
	SOUND_LABEL_SE019,			// ロボット足音SE
	SOUND_LABEL_SE020,			// 走るSE
	SOUND_LABEL_SE021,			// 滑るSE
	SOUND_LABEL_SE022,			// フリスビー投げるSE
	SOUND_LABEL_SE023,			// 10秒前SE
	SOUND_LABEL_SE024,			// 歩くSE
	//ゲームリザルトSE
	SOUND_LABEL_SE025,			// ランクＡSE
	SOUND_LABEL_SE026,			// ランクＢSE
	SOUND_LABEL_SE027,			// ランクＣSE
	SOUND_LABEL_SE028,			// ランクＳSE
	SOUND_LABEL_SE029,			// クラッカーSE
	SOUND_LABEL_SE030,			// ゲージアップSE
	SOUND_LABEL_SE031,			// シンバルSE
	//システムSE
	SOUND_LABEL_SE032,			// キャンセルSE
	SOUND_LABEL_SE033,			// カーソルSE
	SOUND_LABEL_SE034,			// 選択音SE
	//ピカピカ音
	SOUND_LABEL_SE035,			// フリスビーキャッチ(ピカピカ)SE
	SOUND_LABEL_SE036,			// ピカピカSE
	SOUND_LABEL_MAX,

} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

// ゲームループ開始前に呼び出すサウンドの初期化処理
HRESULT Sound_Initialize(void);

// 初期化
void Sound_Init(SOUND_LABEL label);

// 解放
void Sound_Uninit(SOUND_LABEL label);

// ゲームループ終了後に呼び出すサウンドの解放処理
void Sound_Release(void);

// 引数で指定したサウンドを再生する
void Play(SOUND_LABEL label);

// 引数で指定したサウンドを停止する
void Stop(SOUND_LABEL label);

// 引数で指定したサウンドの再生を再開する
void Resume(SOUND_LABEL label);

//　引数で指定した音量をセットする
void SetVolume(SOUND_LABEL label, float Volume);

//　引数で指定したサウンドが再生中かを返す
bool GetSoundState(SOUND_LABEL label);

#endif

//======================================================================================
// 担当者：		菅眞心
// 制作日時：　 2022-12-01
// チーム名：	黒棺	
//======================================================================================
