#pragma once
//======================================================================================
// 名前：MiniMap
// 説明：ミニマップ
//======================================================================================
#include"StaticObject.h"
#include"Dirt.h"

#define MAP_SIZE 1.2f	//ミニマップ縮小率
#define STAGE_HIGHT 30
#define STAGE_WIDTH 40

class MiniMap
{
private:
	
	ID3D11ShaderResourceView* mPlayerPosTex;		//プレイヤーテクスチャ
	ID3D11ShaderResourceView* mDogPosTex;			//犬テクスチャ
	ID3D11ShaderResourceView* mCatPosTex;			//猫テクスチャ
	ID3D11ShaderResourceView* mDirtPosTex;			//汚れテクスチャ
	ID3D11ShaderResourceView* mBlockPosTex;			//障害物テクスチャ
	ID3D11ShaderResourceView* mMiniMapTex;			//ミニマップテクスチャ
	ID3D11ShaderResourceView* mCamera_RangeTex;		//カメラ範囲テクスチャ


	XMFLOAT3 camera = { 0.0f,0.0f,1.0f };			//このクラスのカメラ
	Sprite::RGBA color = { 1.0f,1.0f,1.0f,1.0f };	//背景色
	Sprite::RGBA Red   = { 1.0f,0.0f,0.0f,0.5f };	//赤
	Sprite::RGBA Green = { 0.0f,1.0f,0.0f,0.5f };	//緑
	Sprite::RGBA Blue  = { 0.0f,0.0f,1.0f,0.5f };	//青

public:

	//GameMainで共有する
	StaticObject* mPlayerPos;		//プレイヤー
	StaticObject* mDogPos;			//犬
	StaticObject* mCatPos;			//猫
	StaticObject* mDirtPos[STAGE_HIGHT][STAGE_WIDTH];		//汚れ
	StaticObject* mBlockPos[3];		//障害物	
	StaticObject* mCamera_Range;	//カメラの範囲
	StaticObject* mMiniMap;			//ミニマップ
	StaticObject* mBack;			//背景


	bool active;	//アクティブ状態
	MiniMap(Dirt * _Dirt[][STAGE_WIDTH],StaticObject *_Block[]);					//コンストラクタ
	~MiniMap();						//デストラクタ
	void SetActive(bool _active);	//表示するか
	void Update();					//描画
	void Draw();					//更新

};

