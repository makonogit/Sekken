//======================================================================================
// 名前：Floor.h
// 説明：床のヘッダーファイル
//======================================================================================
#pragma once

#include "SlipperyFloor.h"
#include "Dirt.h"
#include "HitCircle.h"
#include "Babble.h"

#define STAGE_HIGHT 30
#define STAGE_WIDTH 40

class Floor
{
private:
	ID3D11ShaderResourceView* mSlipperyTexture;			// ぴかぴか床のテクスチャ
	ID3D11ShaderResourceView* mDirtTexture;				// 汚れテクスチャ
	ID3D11ShaderResourceView* mBabbleTex;				// 泡テクスチャ

	int BubbleNum;

public:
	
	SlipperyFloor* mSlippery[STAGE_HIGHT][STAGE_WIDTH];
	Dirt* mDirt[STAGE_HIGHT][STAGE_WIDTH];
	Babble* mBubble[STAGE_HIGHT][STAGE_WIDTH];

	Floor(XMFLOAT3 & ,int Stage[][STAGE_WIDTH]);
	~Floor();

	void Update();
	void Draw();
	bool OnSlipperyFloor(HitCircle*);
	void Clean();
	void Miss();
	void SetDirtTex(int _mapdata[][STAGE_WIDTH],int hight_num,int width_num);
	void OffBubble();
};


//======================================================================================
// 担当者：		中川直登
// チーム名：	黒棺	
//======================================================================================