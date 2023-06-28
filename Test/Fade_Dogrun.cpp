#include "Fade_Dogrun.h"

extern DWORD gDeltaTime;
int Fade_Dogrun::mState = NONE_FADE;


//<><><><><><><><><><><><><><><><><><>
// 関数名：Fade_Dogrun
// 役割：コンストラクタ
//<><><><><><><><><><><><><><><><><><>
Fade_Dogrun::Fade_Dogrun()
{

	//変数の初期化
	fiFlg = 0;
	feFlg = 0;

	color = { 0.0f,0.0f,0.0f,1.0f };
	camera = { 0.0f,0.0f,1.0f };

	LoadTexture(L"assets/images/Character/Dog/Run_dog.png", &mpTexture);
	LoadTexture(L"assets/Test.png", &BackTexture);

	//フェード用オブジェクトの初期化
	Dogrun = new AnimObject(camera);
	Dogrun->mSprite->SetTexture(mpTexture);
	Dogrun->SetPosition(2.0f, -0.5f);
	Dogrun->SetSize(1.0f, 1.0f);
	Dogrun->mAnimObject->mDirection = D_LEFT;
	Dogrun->mAnimObject->fAnimSpeed = 0.01f;

	for (int i = 0; i < 2; i++)
	{
		Back[i] = new StaticObject(camera);
		Back[i]->mSprite->SetTexture(BackTexture);
		Back[i]->mSprite->SetColor(color);
		Back[i]->SetSize(2.8f,1.0f);

		if (i == 0)
		{
			Back[i]->SetPosition(2.75f, -0.5f);
		}
		else
		{
			Back[i]->SetPosition(-2.75f, 0.5f);

		}
	}
	Sound_Init(SOUND_LABEL_SE000);
	Fade_Dogrun::mState = NONE_FADE;
}

Fade_Dogrun::~Fade_Dogrun()
{
	Sound_Uninit(SOUND_LABEL_SE000);
	delete Dogrun;
	delete Back[0];
	delete Back[1];

}

void Fade_Dogrun::FadeIn(void)
{
	if (Fade_Dogrun::mState == FADE_OUT_END || Fade_Dogrun::mState == NONE_FADE) {
		Play(SOUND_LABEL_SE000);
		Fade_Dogrun::mState = FADE_IN;
	}
}

void Fade_Dogrun::FadeOut(void)
{
	if (Fade_Dogrun::mState == FADE_IN_END || Fade_Dogrun::mState == NONE_FADE) {
		Play(SOUND_LABEL_SE000);
		Fade_Dogrun::mState = FADE_OUT;
	}
}


//<><><><><><><><><><><><><><><><><><>
// 関数名：Update
// 役割：更新
//<><><><><><><><><><><><><><><><><><>
void Fade_Dogrun::Update()
{
	//状態ごとにフェードイン・アウトする
	switch (Fade_Dogrun::mState)
	{
	case NONE_FADE:
		break;
	case FADE_IN:
		
		//フェードイン用のポジションにセットする
		if (feFlg == 0)
		{
			Dogrun->SetPosition(1.8f, 0.5f);
			Back[0]->SetPosition(0.0f, 0.5f);
			Back[1]->SetPosition(0.0f, -0.5f);
			feFlg = 1;
		}

		//犬が右端に行くまで動かす
		if (feFlg == 1) {
			if (Back[0]->mSprite->mCenter.x >= -2.75f)
			{//背景を端まで移動
				Back[0]->mSprite->mCenter.x -= 0.002f * gDeltaTime;
			}
			if (Dogrun->mSprite->mCenter.x >= -2.75f) 
			{//犬を端まで移動
				Dogrun->mSprite->mCenter.x -= 0.002f * gDeltaTime;
			}

			//両方端まで移動したら次の処理
			if (Back[0]->mSprite->mCenter.x <= -2.75f && Dogrun->mSprite->mCenter.x <= -2.75f) {
				feFlg = 2;
			}
		}

		//画像のポジションを再セットし、次の処理へ
		if (feFlg == 2)
		{
			Dogrun->SetPosition(-1.8f, -0.5f);
			Dogrun->mAnimObject->mDirection = D_UP;
			feFlg = 3;
		}

		//犬が左端に行くまで動かす
		if (feFlg == 3) {
			
			if (Dogrun->mSprite->mCenter.x <= 2.75f)
			{//犬を端まで移動
				Dogrun->mSprite->mCenter.x += 0.002f * gDeltaTime;
			}
			if (Back[1]->mSprite->mCenter.x <= 2.75f) 
			{//背景を端まで移動
				Back[1]->mSprite->mCenter.x += 0.002f * gDeltaTime;
			}

			//両方端まで移動したらフェード終了
			if (Dogrun->mSprite->mCenter.x >= 2.75f && Back[1]->mSprite->mCenter.x >= 2.75f) 
			{
				Dogrun->mAnimObject->mDirection = D_LEFT;
				Fade_Dogrun::mState = FADE_IN_END;
				feFlg = 0;
			}
		}

		break;
	case FADE_OUT:

		//犬が左端に行くまで動かす
		if (Dogrun->mSprite->mCenter.x > -2.75f && Back[0]->mSprite->mCenter.x >= 0.0f &&fiFlg == 0)
		{
			Dogrun->mSprite->mCenter.x -= 0.002f * gDeltaTime;
			Back[0]->mSprite->mCenter.x -= 0.002f * gDeltaTime;
		}
		else if (fiFlg == 0)		//画面端に行ったら次の処理へ
		{
			fiFlg = 1;
		}

		//画像のポジションを再セットし、次の処理へ
		if (fiFlg == 1)
		{
			Dogrun->mAnimObject->mDirection = D_UP;
			Dogrun->SetPosition(-1.8f, 0.5f);
			fiFlg = 2;
		}

		//犬が右端に行くまで動かす
		if (Dogrun->mSprite->mCenter.x < 2.0f && Back[1]->mSprite->mCenter.x <= 0.0f && fiFlg == 2)
		{
			Dogrun->mSprite->mCenter.x += 0.002f * gDeltaTime;
			Back[1]->mSprite->mCenter.x += 0.002f * gDeltaTime;
		}
		else if (fiFlg == 2)		//画面端に行ったら次の処理へ
		{
			fiFlg = 3;
		}

		if (fiFlg == 3)		//フェードが終了していたらなにもしていない状態にする
		{
			Fade_Dogrun::mState = FADE_OUT_END;
			fiFlg = 0;
			Dogrun->SetPosition(1.8f, 0.5f);
			Dogrun->mAnimObject->mDirection = D_LEFT;
		}
		break;
	default:
		Fade_Dogrun::mState = NONE_FADE;
		break;
	}

	//スプライトの更新
	for (int i = 0; i < 2; i++) {
		Back[i]->Update();
	}

	Dogrun->Update();

}

//<><><><><><><><><><><><><><><><><><>
// 関数名：Update
// 役割：描画
//<><><><><><><><><><><><><><><><><><>
void Fade_Dogrun::Draw()
{
	for (int i = 0; i < 2; i++) {
		Back[i]->Draw();
	}

	Dogrun->Draw();
}

//======================================================================================
// 担当者：		井上想哉
// 制作日時：　 2022-12-05
// チーム名：	黒棺	
//======================================================================================