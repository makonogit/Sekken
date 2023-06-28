#include "MiniMap.h"

//<><><><><><><><><><><><><><><><><><>
// 関数名：MiniMap
// 役割：コンストラクタ
//<><><><><><><><><><><><><><><><><><>
MiniMap::MiniMap(Dirt * _Dirt[][STAGE_WIDTH], StaticObject *_Block[])
{
	//テクスチャ読み込み
	LoadTexture(L"assets/images/UI/Minimap/Map_character.png", &mPlayerPosTex);
	LoadTexture(L"assets/images/UI/Minimap/Map_dog.png", &mDogPosTex);
	LoadTexture(L"assets/Test.png", &mCatPosTex);
	LoadTexture(L"assets/images/UI/Minimap/Map_dirt.png", &mDirtPosTex);
	LoadTexture(L"assets/Test.png", &mBlockPosTex);
	LoadTexture(L"assets/images/UI/Minimap/Map.png", &mMiniMapTex);
	//LoadTexture(L"assets/GameMain/Camera_Range.png", &mCamera_RangeTex);

	//インスタンス生成
	mPlayerPos = new StaticObject(camera);
	mPlayerPos->mSprite->SetTexture(mPlayerPosTex);
	//mPlayerPos->mSprite->SetColor(Red);
	mPlayerPos->SetSize(0.1f,0.1f);

	mDogPos = new StaticObject(camera);
	mDogPos->mSprite->SetTexture(mDogPosTex);
	//mDogPos->mSprite->SetColor(Green);
	mDogPos->SetSize(0.1f, 0.1f);

	mCatPos = new StaticObject(camera);
	mCatPos->mSprite->SetTexture(mDogPosTex);
	mCatPos->mSprite->SetColor(Red);
	mCatPos->SetSize(0.1f, 0.1f);

	for (int i = 0; i < STAGE_HIGHT; i++) {
		for (int j = 0; j < STAGE_WIDTH; j++) {
			mDirtPos[i][j] = new StaticObject(camera);
			mDirtPos[i][j]->mSprite->SetTexture(mDirtPosTex);
			mDirtPos[i][j]->mSprite->SetColor(Green);
			mDirtPos[i][j]->SetSize(_Dirt[i][j]->mSprite->mSize.x / (MAP_SIZE * 1.7f), _Dirt[i][j]->mSprite->mSize.y / (MAP_SIZE * 2.7f));
			mDirtPos[i][j]->SetPosition(_Dirt[i][j]->mSprite->mCenter.x / (MAP_SIZE * 1.8f), _Dirt[i][j]->mSprite->mCenter.y / (MAP_SIZE * 2.2f));
			mDirtPos[i][j]->SetActive(_Dirt[i][j]->active);
		}
	}
	
	for (int i = 0; i < 3; i++) {
		mBlockPos[i] = new StaticObject(camera);
		mBlockPos[i]->mSprite->SetTexture(mBlockPosTex);
		//mBlockPos[i]->SetSize(0.1f, 0.1f);
		mBlockPos[i]->SetSize(_Block[i]->mSprite->mSize.x / (MAP_SIZE * 2.8f), _Block[i]->mSprite->mSize.y / (MAP_SIZE * 2.8f));
		mBlockPos[i]->SetPosition(_Block[i]->mSprite->mCenter.x / (MAP_SIZE * 2), _Block[i]->mSprite->mCenter.y / (MAP_SIZE * 2));
		mBlockPos[i]->mSprite->SetColor(Red);
	}

	mMiniMap = new StaticObject(camera);
	mMiniMap->mSprite->SetTexture(mMiniMapTex);
	mMiniMap->SetSize(2.8f / MAP_SIZE, 2.0f / MAP_SIZE);	

	mBack = new StaticObject(camera);
	mBack->mSprite->SetTexture(mBlockPosTex);
	mBack->mSprite->SetColor(color);
	mBack->SetSize(2.8f, 2.0f);	//全画面

	/*mCamera_Range = new StaticObject(camera);
	mCamera_Range->mSprite->SetTexture(mCamera_RangeTex);
	mCamera_Range->SetSize((2.8f / 2.0f) / MAP_SIZE, (2.0f / 2) / MAP_SIZE);
*/
	active = false;

}

//<><><><><><><><><><><><><><><><><><>
// 関数名：~MiniMap
// 役割：デストラクタ
//<><><><><><><><><><><><><><><><><><>
MiniMap::~MiniMap()
{
	//メモリ解放
	delete mPlayerPos;
	delete mDogPos;
	delete mCatPos;
	delete mMiniMap;
	delete mBack;
	//delete mCamera_Range;
	for (int i = 0; i < 3; i++) {
		delete mBlockPos[i];
	}

	for (int i = 0; i < STAGE_HIGHT; i++) {
		for (int j = 0; j < STAGE_WIDTH; j++) {
			delete mDirtPos[i][j];
		}
	}

	COM_SAFE_RELEASE(mPlayerPosTex);
	COM_SAFE_RELEASE(mDogPosTex);
	COM_SAFE_RELEASE(mCatPosTex);
	COM_SAFE_RELEASE(mDirtPosTex);
	COM_SAFE_RELEASE(mBlockPosTex);
	COM_SAFE_RELEASE(mMiniMapTex);
//	COM_SAFE_RELEASE(mCamera_RangeTex);
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：SetActive
// 役割：アクティブ状態のセット
//<><><><><><><><><><><><><><><><><><>
void MiniMap::SetActive(bool _active)
{
	active = _active;
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：Update
// 役割：更新
//<><><><><><><><><><><><><><><><><><>
void MiniMap::Update()
{

	mBack->Update();
	mMiniMap->Update();
	mDogPos->Update();
	mCatPos->Update();
	mPlayerPos->Update();
	//mCamera_Range->Update();

	for (int i = 0; i < STAGE_HIGHT; i++) {
		for (int j = 0; j < STAGE_WIDTH; j++) {
			mDirtPos[i][j]->Update();
		}
	}


	for (int i = 0; i < 3; i++) {
		mBlockPos[i]->Update();
	}

	//mCamera_Range->mSprite->mCenter.x = mPlayerPos->mSprite->mCenter.x;
	//mCamera_Range->mSprite->mCenter.y = mPlayerPos->mSprite->mCenter.y;

}

//<><><><><><><><><><><><><><><><><><>
// 関数名：Draw
// 役割：描画
//<><><><><><><><><><><><><><><><><><>
void MiniMap::Draw()
{
	if (active) {	//アクティブな時だけ描画
		mBack->Draw();
		mMiniMap->Draw();
		
		for (int i = 0; i < STAGE_HIGHT; i++) {
			for (int j = 0; j < STAGE_WIDTH; j++) {
				mDirtPos[i][j]->Draw();
			}
		}

		for (int i = 0; i < 3; i++) {
			mBlockPos[i]->Draw();
		}
	
		mDogPos->Draw();
		mCatPos->Draw();
		mPlayerPos->Draw();
	}
}
