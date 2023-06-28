#include "Stage.h"

extern DWORD gDeltaTime;

//<><><><><><><><><><><><><><><><><><>
// �֐����FDrawTime
// �����F���Ԃ̕\��
// �����F�~���b�P�ʂ̎���
//<><><><><><><><><><><><><><><><><><>
void Stage::DrawTime(float Num)
{
	int Min = Num / 60000;					//����
	int Sec = (Num - (Min * 60000)) / 1000;	//�b��

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
// �֐����FDrawMiniMap
// �����F�~�j�}�b�v�̕\��
//<><><><><><><><><><><><><><><><><><>
void Stage::DrawMiniMap(void)
{
	//BACK�{�^���������Ă���Ԃ����~�j�}�b�v��\��
	if (Input_GetButtonDown(BACK)) {
		mMiniMap->SetActive(TRUE);
	}
	else {
		mMiniMap->SetActive(FALSE);
	}

	if (mMiniMap->active) {

		//--------�~�j�}�b�v�̍��W���w�肷��-----------
		//�v���C���[
		mMiniMap->mPlayerPos->mSprite->mCenter.x = mPlayer->mAnimObject->mCenter.x / (MAP_SIZE * 1.62f);
		mMiniMap->mPlayerPos->mSprite->mCenter.y = mPlayer->mAnimObject->mCenter.y / (MAP_SIZE * 1.9f);

		//�L
		mMiniMap->mCatPos->mSprite->mCenter.x = mCat->mAnimObject->mCenter.x / (MAP_SIZE * 1.62f);
		mMiniMap->mCatPos->mSprite->mCenter.y = mCat->mAnimObject->mCenter.y / (MAP_SIZE * 1.9f);

		//��
		mMiniMap->mDogPos->mSprite->mCenter.x = mDog->mAnimObject->mCenter.x / (MAP_SIZE * 1.62f);
		mMiniMap->mDogPos->mSprite->mCenter.y = mDog->mAnimObject->mCenter.y / (MAP_SIZE * 1.62f);

	}
}

//<><><><><><><><><><><><><><><><><><>
// �֐����FCameraSet
// �����F�J�����ʒu�̐���
//<><><><><><><><><><><><><><><><><><>
void Stage::CameraSet(void)
{
	//�J�������W���v���C���[�̈ړ��ɍ��킹��
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
	


	//�J�����̈ړ�����
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
// �֐����FUpdate
// �����F�X�V
//<><><><><><><><><><><><><><><><><><>
void Stage::Update()
{
	//�~�j�}�b�v�\������Ă����瑼�̍X�V�͌Ă΂Ȃ�
	if (mMiniMap->active) {
		mMiniMap->Update();
	}
	else {

		mBackGround->Update();
		mFloor->Update();		//���̍X�V

		if ((Fade_Bubble::mState == FADE_IN_END || Fade_Bubble::mState == NONE_FADE)) {
			fTime -= gDeltaTime;	//���Ԍv��
		}
		if (mCat->Appearance == false)
		{
			fCatTime += gDeltaTime;
		}

		mDog->Update();			//���̍X�V

		//--------------------------------------
		//����̓����蔻��
		//--------------------------------------
		for (int i = 0; i < STAGE_HIGHT; i++){
			for (int j = 0; j < STAGE_WIDTH; j++){

				//�X�R�A�v�Z
				if (!mFloor->mDirt[i][j]->active) {
					ClearNum++;
				}
			
				//----------------------------
				//�t���X�r�[�Ɖ���̓�����
				//----------------------------
		
				// ���Ɖ���
				if (mDog->mCircle->CheckHit(mFloor->mDirt[i][j]->mHitSpuare) && mDog->mState == DOG_RUN)
				{
					mFloor->mBubble[i][j]->BabbleSet(mFloor->mDirt[i][j]->mSprite->mCenter);
					mFloor->mDirt[i][j]->mHitDog = true;
				}

				//----------------------
				//�L�Ɖ���̓�����
				//----------------------
				if (mCat->mHit->CheckHit(mFloor->mDirt[i][j]->mHitSpuare) == true) {
					if (mFloor->mDirt[i][j]->active) 
					{	 //��������Ă�����
						mCat->SetDirtState(CatDirtState::DIRT);
					}
					else if (mCat->Appearance)//��������Ă��Ȃ�������
					{
						mFloor->mDirt[i][j]->SetActive(true);
					}
				}

				//�Q�]�񂾎��̉���
				if (mCat->mLieDownHit->CheckHit(mFloor->mDirt[i][j]->mHitSpuare) == true)
				{
					if (mFloor->mDirt[i][j]->active) 
					{	//��������Ă�����
						mCat->SetDirtState(CatDirtState::DIRT);	
					}
					else if (mCat->Appearance)//��������Ă��Ȃ�������
					{
						mFloor->mDirt[i][j]->SetActive(true);
					}
				}

				//�J�����ϐ���Ǝ��Ŏ����Ă��邽�ߖ�����W���X�V���Ă���
				mFloor->mDirt[i][j]->mSprite->mCamera = mBackGround->mSprite->mCamera;

				mMapInfo[i][j] = mFloor->mDirt[i][j]->active;
				mFloor->SetDirtTex(mMapInfo, i, j);	//����e�N�X�`��
			
			}
		}
		
		//�X�R�A�v�Z
		Score = ((float)ClearNum / (float)(STAGE_HIGHT*STAGE_WIDTH)) * 100;
		ClearNum = 0;

		//-------------------------------
		//�t���X�r�[�̏���
		//-------------------------------
		if (mPlayer->mState == PLAYER_THROW && mFrisbee->mHold != HOLD_DOG)
		{

			if (mFrisbee->mState == FRISBEE_FRY)
			{
				mCat->SetTarget(&mFrisbee->mSprite->mCenter);		//�L���ǂ�������
				
				if (mDog->mState != DOG_BE_CARRYED)// �A�q���ɂ��܂��Ă��Ȃ���
				{
					mDog->SetTarget(&mFrisbee->mSprite->mCenter);		// �t���X�r�[��ǂ�������
				}
			}
			else if (!(mDog->mCircle->CheckHit(mPlayer->mCircle)))	// 
			{
				mCat->SetTarget(NULL);
				if (mDog->mState != DOG_BE_CARRYED)// �A�q���ɂ��܂��Ă��Ȃ���
				{
					mDog->SetTarget(&mPlayer->mAnimObject->mCenter);	// �v���C���[�Ɍ�����
				}
			}
			else
			{
				if (mDog->mState != DOG_BE_CARRYED)// �A�q���ɂ��܂��Ă��Ȃ���
				{
					mDog->ChangeState(DOG_WAIT);
				}
			}
		}


		//�����͈͂Ō���(�L�G�ցG`)���
		if (mDog->mCatchArea->CheckHit(mFrisbee->mCircle) && mFrisbee->mState == FRISBEE_FRY) {
			fDogCryTime += gDeltaTime;
			//5�b�Ɉ���
			if (fDogCryTime > 0.4f * 1000) {
				Play(SOUND_LABEL_SE010);
				fDogCryTime = 0.0f;
			}
		}

		//�L���͂������Ƃ�
		if (mCat->mHit->CheckHit(mFrisbee->mCircle)) {
			mFrisbee->ChangeState(FRISBEE_DROP);
			mFrisbee->Catch(DONT_HOLD);
			mCat->SetTarget(NULL);
		}

		// �L���b�`�ł��邩�ǂ���
		if (mDog->mMissArea->CheckHit(mFrisbee->mCircle) && mFrisbee->mState == FRISBEE_FRY)
		{
			
			
			// �҂�

			if (mDog->mState != DOG_BE_CARRYED)// �A�q���ɂ��܂��Ă��Ȃ���
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

			//-------------------------------------�L�̒ǂ��z��
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
			
				//�A������
				mFloor->OffBubble();
				VibrationTime = 0.5f * 1000;	//�U�����Ԃ�ݒ�

				// ����	
				if (mDog->mCatchArea->CheckHit(mFrisbee->mCircle)&& mDog->mState != DOG_BE_CARRYED) {
					
					if (GetSoundState(SOUND_LABEL_SE035) == FALSE)
					{
						Play(SOUND_LABEL_SE035);
					}

					//�L�����ꂢ�ɂȂ�
					if (mDog->mCatchBubbleArea->CheckHit(mCat->mHit)) {	//�L��������
						Input_SetVibration(40000, 40000);	//�U��������
						
						if (GetSoundState(SOUND_LABEL_SE005) == FALSE)
						{
							Play(SOUND_LABEL_SE005);
						}

						mCat->nDirtState = CatDirtState::CLEARN;
						mCat->SetAppearance(false);
						mDog->mCatchBubbleArea->mRadius = 0.5f;	//���̖A�����蔻��̔��a
					}
					else
					{
						Stop(SOUND_LABEL_SE005);
					}

					if (!mDog->mCatchBubbleArea->CheckHit(mCat->mHit)) {	//�L�����Ȃ�������
						Input_SetVibration(5000, 5000);	//�U��������
						mDog->mCatchBubbleArea->mRadius = 0.25f;	//���̖A�����蔻��̔��a
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

					mDog->SetTarget(&mPlayer->mAnimObject->mCenter);// �v���C���[�Ɍ�����
					mDog->ChangeState(DOG_RETURN);
					mFloor->Clean();
				}
				else
				{
					// �~�X
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
			//�A������
			mFloor->OffBubble();
			mFloor->Miss();
		}

		// �v���C���[�Ƀt���X�r�[��Ԃ�
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
	
		// �������邩
		if (mFloor->OnSlipperyFloor(mDog->mCircle))
		{
			mDog->mSlip = true;
		}

		// �v���C���[�����邩
		//�����Ƃ��ׂ�A�����Ɠ�����H
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

			bool Active = false;// �}�[�J�[��\�����邽�߂̕ϐ�

			if (mCat->mSprite->mCenter.x > mCamera.x + 1.25f)// �E
			{
				Active = true;
				mCatMark->mSprite->mCenter.x = mCamera.x + 1.15f;
			}
			else if (mCat->mSprite->mCenter.x < mCamera.x - 1.25f)// ��
			{
				Active = true;
				mCatMark->mSprite->mCenter.x = mCamera.x - 1.15f;
			}

			if (mCat->mSprite->mCenter.y > mCamera.y + 0.9f)// ��
			{
				Active = true;
				mCatMark->mSprite->mCenter.y = mCamera.y + 0.9f;
			}
			else if (mCat->mSprite->mCenter.y < mCamera.y - 0.9f)// ��
			{
				Active = true;
				mCatMark->mSprite->mCenter.y = mCamera.y - 0.9;
			}
			mCatMark->SetActive(Active);	//�}�[�J�[��\��

		}
		else
		{
			mCatMark->SetActive(false);	//�}�[�J�[���\��
		}

		mPlayer->Update();

		// �������t���X�r�[�ƃv���C���[�̂����蔻��
		if (mFrisbee->mCircle->CheckHit(mPlayer->mCircle)
			&& mFrisbee->mState == FRISBEE_DROP)
		{
			mFrisbee->ChangeState(FRISBEE_HOLD);
			mFrisbee->Catch(HOLD_PLAYER);
		}

		//---------------------------
		//�v���C���[���L�ɋ߂Â�����
		//---------------------------
		//�v���C���[�Ƃ̋��������߂�
		float Distance = sqrt(sqr(mPlayer->mAnimObject->mCenter.x - mCat->mAnimObject->mCenter.x)
			+ sqr(mPlayer->mAnimObject->mCenter.y - mCat->mAnimObject->mCenter.y));

		if (Distance < 1.0f && mCat->GetState() == CatState::WALK && mCat->GetState() != CatState::LIEDOWN)
		{//��苗���߂Â�����ҋ@
			mCat->ChangeState(CatState::WAIT);
		}
		if (Distance < 0.5f && mCat->GetState() == CatState::WAIT)
		{//�߂Â��������瑖����
			mCat->ChangeState(CatState::RUN);
		}
		if (Distance > 1.5f && mCat->GetState() == CatState::RUN)
		{//�v���C���[���痣�ꂽ�����
			mCat->ChangeState(CatState::WALK);
		}

		mFrisbee->Update();
		
		for (int i = 0; i < BABBLMAX; i++) {
			mBabble[i]->Update();
		}

		//�L���o�����Ă��鎞�����X�V
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
		
		DrawTime(fTime);	//���ԕ`��


		//���Ԃ�UI�ʒu����
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
	//��Q���̓�����
	//-----------------

	for (int i = 0; i < BLOCKMAX; i++) 
	
	{
		//�L�Ƃ̓�����
		if (mCat->mHit->CheckHit(mBlockHit[i]))
		{
			mCat->ChangeState(CatState::JUMP);
		}
		else if (mCat->GetState() == CatState::JUMP) {
			mCat->ChangeState(CatState::WALK);

		}

		//�t���X�r�[�Ƃ̓�����
		if ((mFrisbee->mCircle->CheckHit(mBlockHit[i])
			&& mFrisbee->mState == FRISBEE_FRY))
		{
			mFrisbee->ChangeState(FRISBEE_DROP);
		}

		//�v���C���[�Ƃ̓�����
		if (mPlayer->mHit->CheckHit(mBlockHit[i]))
		{
			mPlayer->SetResistance(mBlock[i]->mSprite->mCenter);
		}
		//���Ƃ̓�����
		if (mDog->mHit->CheckHit(mBlockHit[i]))
		{
			mDog->SetResistance(mBlock[i]->mSprite->mCenter);
		}
		mBlock[i]->Update();
	}
	
	mCatMark->Update();	//�L�̃}�[�J�[
	DrawMiniMap();	//�~�j�}�b�v�\��
	CameraSet();	//�J�����̐���

	//�������Ԃ��c��10�b�ɂȂ�����SE�𗬂�
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

	//�������Ԃ�0�ȉ��ŃX�R�A�󂯓n�����ăV�[���J��(GameMain.cpp)
	if (fTime < 0) {
		Stop(SOUND_LABEL_SE023);
		Stop(SOUND_LABEL_SE021);
		Stop(SOUND_LABEL_SE007);
		Stop(SOUND_LABEL_SE019);
		TimeActive = false;
	}

}


//<><><><><><><><><><><><><><><><><><>
// �֐����FDraw
// �����F�`��
//<><><><><><><><><><><><><><><><><><>
void Stage::Draw()
{

	mBackGround->Draw();
	mFloor->Draw();				//��
	
	for (int i = 0; i < BLOCKMAX; i++) 
	{
		mBlock[i]->Draw();
	}

	mFrisbee->mShadow->Draw();	//�t���X�r�[

	mDog->Draw();				//��

	mFrisbee->Draw();


	mPlayer->Draw();			//�v���C���[
	mPlayer->mMark->Draw();

	if (mCat->Appearance == true) {
		mCat->Draw();				//�L
	}

	for (int i = 0; i < BABBLMAX; i++)
	{	//�A
		mBabble[i]->Draw();
	}

	
	mTimeBack->Draw();
	for (int i = 0; i < 4; i++)
	{	//����
		mTime[i]->Draw();
	}

	mMiniMap->Draw();			//�~�j�}�b�v
	mCatMark->Draw();

}
