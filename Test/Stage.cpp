#include "Stage.h"

extern DWORD gDeltaTime;

//<><><><><><><><><><><><><><><><><><>
// 関数名：DrawTime
// 役割：時間の表示
// 引数：ミリ秒単位の時間
//<><><><><><><><><><><><><><><><><><>
void Stage::DrawTime(float Num)
{
	int Min = Num / 60000;					//分数
	int Sec = (Num - (Min * 60000)) / 1000;	//秒数

	int Min_10 = Min / 10;
	int Min_1 = Min - (Min_10 * 10);
	int Sec_10 = Sec / 10;
	int Sec_1 = Sec - Sec_10 * 10;

	mTime[0]->mSprite->SetTexture(mNumTex[Min_10]);

	mTime[1]->mSprite->SetTexture(mNumTex[Min_1]);

	mTime[2]->mSprite->SetTexture(mNumTex[Sec_10]);

	mTime[3]->mSprite->SetTexture(mNumTex[Sec_1]);
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：DrawMiniMap
// 役割：ミニマップの表示
//<><><><><><><><><><><><><><><><><><>
void Stage::DrawMiniMap(void)
{
	//BACKボタンを押している間だけミニマップを表示
	if (Input_GetButtonDown(BACK)) {
		mMiniMap->SetActive(TRUE);
	}
	else {
		mMiniMap->SetActive(FALSE);
	}

	if (mMiniMap->active) {

		//--------ミニマップの座標を指定する-----------
		//プレイヤー
		mMiniMap->mPlayerPos->mSprite->mCenter.x = mPlayer->mAnimObject->mCenter.x / (MAP_SIZE * 1.62f);
		mMiniMap->mPlayerPos->mSprite->mCenter.y = mPlayer->mAnimObject->mCenter.y / (MAP_SIZE * 1.9f);

		//猫
		mMiniMap->mCatPos->mSprite->mCenter.x = mCat->mAnimObject->mCenter.x / (MAP_SIZE * 1.62f);
		mMiniMap->mCatPos->mSprite->mCenter.y = mCat->mAnimObject->mCenter.y / (MAP_SIZE * 1.9f);

		//犬
		mMiniMap->mDogPos->mSprite->mCenter.x = mDog->mAnimObject->mCenter.x / (MAP_SIZE * 1.62f);
		mMiniMap->mDogPos->mSprite->mCenter.y = mDog->mAnimObject->mCenter.y / (MAP_SIZE * 1.62f);

	}
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：CameraSet
// 役割：カメラ位置の制御
//<><><><><><><><><><><><><><><><><><>
void Stage::CameraSet(void)
{
	//カメラ座標をプレイヤーの移動に合わせる
	if (mFrisbee->mState != FRISBEE_FRY) {
		mBackGround->mSprite->mCamera.x = mPlayer->mAnimObject->mCenter.x;
		mBackGround->mSprite->mCamera.y = mPlayer->mAnimObject->mCenter.y;
	}
	
	if(mFrisbee->mHold == HOLD_DOG){
		mBackGround->mSprite->mCamera.x = mDog->mAnimObject->mCenter.x;
		mBackGround->mSprite->mCamera.y = mDog->mAnimObject->mCenter.y;
	}
	
	if(mFrisbee->mState == FRISBEE_FRY && mFrisbee->mHold != HOLD_DOG) {
		mBackGround->mSprite->mCamera.x = mFrisbee->mSprite->mCenter.x;
		mBackGround->mSprite->mCamera.y = mFrisbee->mSprite->mCenter.y;
	}
	


	//カメラの移動制限
	if (mBackGround->mSprite->mCamera.x < -1.0f) {
		mBackGround->mSprite->mCamera.x = -1.0f;
	}
	if (mBackGround->mSprite->mCamera.x > 1.0f) {
		mBackGround->mSprite->mCamera.x = 1.0f;
	}
	if (mBackGround->mSprite->mCamera.y < -1.0f) {
		mBackGround->mSprite->mCamera.y = -1.0f;
	}
	if (mBackGround->mSprite->mCamera.y > 1.0f) {
		mBackGround->mSprite->mCamera.y = 1.0f;
	}

	/*if (mPlayer->mState == PLAYER_THROW && mFrisbee->mState == FRISBEE_FRY)
	{
		if (fCameraZoom < ZOOMMAX) {
			fCameraZoom += 0.000001f*gDeltaTime;
		}
		mPlayer->SetSize(mPlayer->mSprite->mSize.x + fCameraZoom, mPlayer->mSprite->mSize.y + fCameraZoom);
		mDog->SetSize(mDog->mSprite->mSize.x + fCameraZoom, mDog->mSprite->mSize.y + fCameraZoom);
		mCat->SetSize(mCat->mSprite->mSize.x + fCameraZoom, mCat->mSprite->mSize.y + fCameraZoom);
		mFrisbee->SetSize(mFrisbee->mSprite->mSize.x + fCameraZoom, mFrisbee->mSprite->mSize.y + fCameraZoom);
		mBackGround->SetSize(mBackGround->mSprite->mSize.x + fCameraZoom, mBackGround->mSprite->mSize.y + fCameraZoom);

	}*/

}

//<><><><><><><><><><><><><><><><><><>
// 関数名：Update
// 役割：更新
//<><><><><><><><><><><><><><><><><><>
void Stage::Update()
{
	//ミニマップ表示されていたら他の更新は呼ばない
	if (mMiniMap->active) {
		mMiniMap->Update();
	}
	else {

		mBackGround->Update();
		mFloor->Update();		//床の更新

		if ((Fade_Bubble::mState == FADE_IN_END || Fade_Bubble::mState == NONE_FADE)) {
			fTime -= gDeltaTime;	//時間計測
		}
		if (mCat->Appearance == false)
		{
			fCatTime += gDeltaTime;
		}

		mDog->Update();			//犬の更新

		//--------------------------------------
		//汚れの当たり判定
		//--------------------------------------
		for (int i = 0; i < STAGE_HIGHT; i++){
			for (int j = 0; j < STAGE_WIDTH; j++){

				//スコア計算
				if (!mFloor->mDirt[i][j]->active) {
					ClearNum++;
				}
			
				//----------------------------
				//フリスビーと汚れの当たり
				//----------------------------
		
				// 犬と汚れ
				if (mDog->mCircle->CheckHit(mFloor->mDirt[i][j]->mHitSpuare) && mDog->mState == DOG_RUN)
				{
					mFloor->mBubble[i][j]->BabbleSet(mFloor->mDirt[i][j]->mSprite->mCenter);
					mFloor->mDirt[i][j]->mHitDog = true;
				}

				//----------------------
				//猫と汚れの当たり
				//----------------------
				if (mCat->mHit->CheckHit(mFloor->mDirt[i][j]->mHitSpuare) == true) {
					if (mFloor->mDirt[i][j]->active) 
					{	 //床が汚れていたら
						mCat->SetDirtState(CatDirtState::DIRT);
					}
					else if (mCat->Appearance)//床が汚れていなかったら
					{
						mFloor->mDirt[i][j]->SetActive(true);
					}
				}

				//寝転んだ時の汚れ
				if (mCat->mLieDownHit->CheckHit(mFloor->mDirt[i][j]->mHitSpuare) == true)
				{
					if (mFloor->mDirt[i][j]->active) 
					{	//床が汚れていたら
						mCat->SetDirtState(CatDirtState::DIRT);	
					}
					else if (mCat->Appearance)//床が汚れていなかったら
					{
						mFloor->mDirt[i][j]->SetActive(true);
					}
				}

				//カメラ変数を独自で持っているため毎回座標を更新している
				mFloor->mDirt[i][j]->mSprite->mCamera = mBackGround->mSprite->mCamera;

				mMapInfo[i][j] = mFloor->mDirt[i][j]->active;
				mFloor->SetDirtTex(mMapInfo, i, j);	//汚れテクスチャ
			
			}
		}
		
		//スコア計算
		Score = ((float)ClearNum / (float)(STAGE_HIGHT*STAGE_WIDTH)) * 100;
		ClearNum = 0;

		//-------------------------------
		//フリスビーの処理
		//-------------------------------
		if (mPlayer->mState == PLAYER_THROW && mFrisbee->mHold != HOLD_DOG)
		{

			if (mFrisbee->mState == FRISBEE_FRY)
			{
				mCat->SetTarget(&mFrisbee->mSprite->mCenter);		//猫が追いかける
				
				if (mDog->mState != DOG_BE_CARRYED)// アヒルにつかまっていない時
				{
					mDog->SetTarget(&mFrisbee->mSprite->mCenter);		// フリスビーを追いかける
				}
			}
			else if (!(mDog->mCircle->CheckHit(mPlayer->mCircle)))	// 
			{
				mCat->SetTarget(NULL);
				if (mDog->mState != DOG_BE_CARRYED)// アヒルにつかまっていない時
				{
					mDog->SetTarget(&mPlayer->mAnimObject->mCenter);	// プレイヤーに向かう
				}
			}
			else
			{
				if (mDog->mState != DOG_BE_CARRYED)// アヒルにつかまっていない時
				{
					mDog->ChangeState(DOG_WAIT);
				}
			}
		}


		//成功範囲で犬が(´；ω；`)ｳｩｩ
		if (mDog->mCatchArea->CheckHit(mFrisbee->mCircle) && mFrisbee->mState == FRISBEE_FRY) {
			fDogCryTime += gDeltaTime;
			//5秒に一回鳴く
			if (fDogCryTime > 0.4f * 1000) {
				Play(SOUND_LABEL_SE010);
				fDogCryTime = 0.0f;
			}
		}

		//猫がはたき落とす
		if (mCat->mHit->CheckHit(mFrisbee->mCircle)) {
			mFrisbee->ChangeState(FRISBEE_DROP);
			mFrisbee->Catch(DONT_HOLD);
			mCat->SetTarget(NULL);
		}

		// キャッチできるかどうか
		if (mDog->mMissArea->CheckHit(mFrisbee->mCircle) && mFrisbee->mState == FRISBEE_FRY)
		{
			
			
			// 待つ

			if (mDog->mState != DOG_BE_CARRYED)// アヒルにつかまっていない時
			{
				if (mDog->mCircle->CheckHit(mFrisbee->mCircle))
				{
					mDog->ChangeState(DOG_NONE);
				}
				else
				{
					mDog->ChangeState(DOG_RUN);
				}
			}

			//-------------------------------------猫の追い越し
			if(mFrisbee->mState == FRISBEE_FRY)
			{
				if (mCat->mHit->CheckHit(mFrisbee->mCircle))
				{
					mCat->ChangeState(CNONE);
				}
				else
				{
					mCat->ChangeState(RUN);
				}
			}
			//-----------------------------------------------------

			if (Input_GetButtonTrigger(B)|| Input_GetKeyTrigger(VK_SPACE))
			{
			
				//泡を消す
				mFloor->OffBubble();
				VibrationTime = 0.5f * 1000;	//振動時間を設定

				// 成功	
				if (mDog->mCatchArea->CheckHit(mFrisbee->mCircle)&& mDog->mState != DOG_BE_CARRYED) {
					
					if (GetSoundState(SOUND_LABEL_SE035) == FALSE)
					{
						Play(SOUND_LABEL_SE035);
					}

					//猫がきれいになる
					if (mDog->mCatchBubbleArea->CheckHit(mCat->mHit)) {	//猫がいたら
						Input_SetVibration(40000, 40000);	//振動させる
						
						if (GetSoundState(SOUND_LABEL_SE005) == FALSE)
						{
							Play(SOUND_LABEL_SE005);
						}

						mCat->nDirtState = CatDirtState::CLEARN;
						mCat->SetAppearance(false);
						mDog->mCatchBubbleArea->mRadius = 0.5f;	//犬の泡あたり判定の半径
					}
					else
					{
						Stop(SOUND_LABEL_SE005);
					}

					if (!mDog->mCatchBubbleArea->CheckHit(mCat->mHit)) {	//猫がいなかったら
						Input_SetVibration(5000, 5000);	//振動させる
						mDog->mCatchBubbleArea->mRadius = 0.25f;	//犬の泡あたり判定の半径
					}

					for (int i = 0; i < STAGE_HIGHT; i++) {
						for (int j = 0; j < STAGE_WIDTH; j++) {

							if (mDog->mCatchBubbleArea->CheckHit(mFloor->mDirt[i][j]->mHitSpuare))
							{
								mFloor->mDirt[i][j]->mHitDog = true;

							}
						}
					}
					
					mFrisbee->ChangeState(FRISBEE_HOLD);
					mFrisbee->Catch(HOLD_DOG);
					mCat->SetTarget(NULL);

					mDog->SetTarget(&mPlayer->mAnimObject->mCenter);// プレイヤーに向かう
					mDog->ChangeState(DOG_RETURN);
					mFloor->Clean();
				}
				else
				{
					// ミス
					mFrisbee->ChangeState(FRISBEE_DROP);
					mCat->SetTarget(NULL);
					
				}
			}
		}

		VibrationTime -= gDeltaTime;
		if (VibrationTime < 0.0f) {
			Input_SetVibration(0, 0);
		}
		
		
		if(mFrisbee->mState == FRISBEE_DROP)
		{
			//泡を消す
			mFloor->OffBubble();
			mFloor->Miss();
		}

		// プレイヤーにフリスビーを返す
		if (mDog->mState == DOG_RETURN && mDog->mCircle->CheckHit(mPlayer->mCircle))
		{
			mDog->ChangeState(DOG_WALK);
			mFrisbee->Catch(HOLD_PLAYER);
			mPlayer->ChangeState(PLAYER_MOVE);
		}
		if (mFrisbee->mState == FRISBEE_DROP&&mDog->mState != DOG_BE_CARRYED)
		{
			mDog->ChangeState(DOG_WALK);
		}
	
		// 犬が滑るか
		if (mFloor->OnSlipperyFloor(mDog->mCircle))
		{
			mDog->mSlip = true;
		}

		// プレイヤーが滑るか
		//ずっとすべる、ずっと当たり？
		if(mFloor->OnSlipperyFloor(mPlayer->mCircle))
		{
			mPlayer->Slip();
			if (mSound[0] == false)
			{
				Play(SOUND_LABEL_SE021);
				mSound[0] = true;
			}
		}
		else
		{
			Stop(SOUND_LABEL_SE021);
			mSound[0] = false;
		}

		if (mCat->Appearance)
		{
			mCatMark->mSprite->mCenter.x = mCat->mAnimObject->mCenter.x;
			mCatMark->mSprite->mCenter.y = mCat->mAnimObject->mCenter.y;

			bool Active = false;// マーカーを表示するための変数

			if (mCat->mSprite->mCenter.x > mCamera.x + 1.25f)// 右
			{
				Active = true;
				mCatMark->mSprite->mCenter.x = mCamera.x + 1.15f;
			}
			else if (mCat->mSprite->mCenter.x < mCamera.x - 1.25f)// 左
			{
				Active = true;
				mCatMark->mSprite->mCenter.x = mCamera.x - 1.15f;
			}

			if (mCat->mSprite->mCenter.y > mCamera.y + 0.9f)// 上
			{
				Active = true;
				mCatMark->mSprite->mCenter.y = mCamera.y + 0.9f;
			}
			else if (mCat->mSprite->mCenter.y < mCamera.y - 0.9f)// 下
			{
				Active = true;
				mCatMark->mSprite->mCenter.y = mCamera.y - 0.9;
			}
			mCatMark->SetActive(Active);	//マーカーを表示

		}
		else
		{
			mCatMark->SetActive(false);	//マーカーを非表示
		}

		mPlayer->Update();

		// 落ちたフリスビーとプレイヤーのあたり判定
		if (mFrisbee->mCircle->CheckHit(mPlayer->mCircle)
			&& mFrisbee->mState == FRISBEE_DROP)
		{
			mFrisbee->ChangeState(FRISBEE_HOLD);
			mFrisbee->Catch(HOLD_PLAYER);
		}

		//---------------------------
		//プレイヤーが猫に近づいた時
		//---------------------------
		//プレイヤーとの距離を求める
		float Distance = sqrt(sqr(mPlayer->mAnimObject->mCenter.x - mCat->mAnimObject->mCenter.x)
			+ sqr(mPlayer->mAnimObject->mCenter.y - mCat->mAnimObject->mCenter.y));

		if (Distance < 1.0f && mCat->GetState() == CatState::WALK && mCat->GetState() != CatState::LIEDOWN)
		{//一定距離近づいたら待機
			mCat->ChangeState(CatState::WAIT);
		}
		if (Distance < 0.5f && mCat->GetState() == CatState::WAIT)
		{//近づきすぎたら走り回る
			mCat->ChangeState(CatState::RUN);
		}
		if (Distance > 1.5f && mCat->GetState() == CatState::RUN)
		{//プレイヤーから離れたら歩く
			mCat->ChangeState(CatState::WALK);
		}

		mFrisbee->Update();
		
		for (int i = 0; i < BABBLMAX; i++) {
			mBabble[i]->Update();
		}

		//猫が出現している時だけ更新
		if (mCat->Appearance) {
			if (GetSoundState(SOUND_LABEL_SE004) == FALSE && mSound[1] == false)
			{
				Play(SOUND_LABEL_SE004);
				mSound[1] = true;
			}
			mCat->Update();
		}
		else
		{
			mSound[1] = false;
		}
		
		DrawTime(fTime);	//時間描画


		//時間のUI位置調整
		mTime[0]->mSprite->mCenter.x = mBackGround->mSprite->mCamera.x - 0.04f;
		mTime[1]->mSprite->mCenter.x = mBackGround->mSprite->mCamera.x - 0.04f + (0.088f - 0.01f);
		mTime[2]->mSprite->mCenter.x = mBackGround->mSprite->mCamera.x - 0.04f + (0.088f * 2 + 0.01f);
		mTime[3]->mSprite->mCenter.x = mBackGround->mSprite->mCamera.x - 0.04f + (0.088f * 3);
		for (int i = 0; i < 4; i++) {
			mTime[i]->mSprite->mCenter.y = mBackGround->mSprite->mCamera.y + 0.8f;
			mTime[i]->Update();
		}

		mTimeBack->mSprite->mCenter.x = mBackGround->mSprite->mCamera.x;
		mTimeBack->mSprite->mCenter.y = mBackGround->mSprite->mCamera.y + 0.8f;
		mTimeBack->Update();
	}

	//-----------------
	//障害物の当たり
	//-----------------

	for (int i = 0; i < BLOCKMAX; i++) 
	
	{
		//猫との当たり
		if (mCat->mHit->CheckHit(mBlockHit[i]))
		{
			mCat->ChangeState(CatState::JUMP);
		}
		else if (mCat->GetState() == CatState::JUMP) {
			mCat->ChangeState(CatState::WALK);

		}

		//フリスビーとの当たり
		if ((mFrisbee->mCircle->CheckHit(mBlockHit[i])
			&& mFrisbee->mState == FRISBEE_FRY))
		{
			mFrisbee->ChangeState(FRISBEE_DROP);
		}

		//プレイヤーとの当たり
		if (mPlayer->mHit->CheckHit(mBlockHit[i]))
		{
			mPlayer->SetResistance(mBlock[i]->mSprite->mCenter);
		}
		//犬との当たり
		if (mDog->mHit->CheckHit(mBlockHit[i]))
		{
			mDog->SetResistance(mBlock[i]->mSprite->mCenter);
		}
		mBlock[i]->Update();
	}
	
	mCatMark->Update();	//猫のマーカー
	DrawMiniMap();	//ミニマップ表示
	CameraSet();	//カメラの制御

	//制限時間が残り10秒になったらSEを流す
	if (fTime < 10000.0f)
	{
		if (GetSoundState(SOUND_LABEL_SE023) == FALSE)
		{
			SetVolume(SOUND_LABEL_SE023, 2.0f);
			Play(SOUND_LABEL_SE023);
		}
		if (GetSoundState(SOUND_LABEL_SE016) == FALSE && fTime > 9000.0f)
		{
			Play(SOUND_LABEL_SE016);
		}
	}

	//制限時間が0以下でスコア受け渡ししてシーン遷移(GameMain.cpp)
	if (fTime < 0) {
		Stop(SOUND_LABEL_SE023);
		Stop(SOUND_LABEL_SE021);
		Stop(SOUND_LABEL_SE007);
		Stop(SOUND_LABEL_SE019);
		TimeActive = false;
	}

}


//<><><><><><><><><><><><><><><><><><>
// 関数名：Draw
// 役割：描画
//<><><><><><><><><><><><><><><><><><>
void Stage::Draw()
{

	mBackGround->Draw();
	mFloor->Draw();				//床
	
	for (int i = 0; i < BLOCKMAX; i++) 
	{
		mBlock[i]->Draw();
	}

	mFrisbee->mShadow->Draw();	//フリスビー

	mDog->Draw();				//犬

	mFrisbee->Draw();


	mPlayer->Draw();			//プレイヤー
	mPlayer->mMark->Draw();

	if (mCat->Appearance == true) {
		mCat->Draw();				//猫
	}

	for (int i = 0; i < BABBLMAX; i++)
	{	//泡
		mBabble[i]->Draw();
	}

	
	mTimeBack->Draw();
	for (int i = 0; i < 4; i++)
	{	//時間
		mTime[i]->Draw();
	}

	mMiniMap->Draw();			//ミニマップ
	mCatMark->Draw();

}
