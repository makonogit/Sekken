#include "Fade.h"

int Fade::mState;
extern DWORD gDeltaTime;

//コンストラクタ
Fade::Fade()
{
	color = { 0.0f,0.0f,0.0f,1.0f };
	camera = { 0.0f,0.0f,1.0f };

	LoadTexture(L"assets/Test.png", &mpTexture);
	LoadTexture(L"assets/images/UI/TeamLogo.png", &mTeamLogoTex);
	
	mSprite = new Sprite(camera);
	mSprite->SetTexture(mpTexture);
	mSprite->mSize.x = 2.8f;
	mSprite->mSize.y = 2.0f;
	mSprite->mCenter.y = 0.0f;
	mSprite->mCenter.x = 0.0f;
	mSprite->SetColor(color);				//色の指定

	mTeamLogo = new Sprite(camera);
	mTeamLogo->SetTexture(mTeamLogoTex);
	mTeamLogo->mSize.x = 1.4f;
	mTeamLogo->mSize.y = 1.0f;
	mTeamLogo->mCenter.y = 0.0f;
	mTeamLogo->mCenter.x = 0.0f;
	//mTeamLogo->SetColor(color);				//色の指定
	
	mState = NONE_FADE;						//現在の状態をなにもしていないに設定

}

//デストラクタ
Fade::~Fade()
{
	delete mTeamLogo;
	delete mSprite;
	COM_SAFE_RELEASE(mpTexture);
	COM_SAFE_RELEASE(mTeamLogoTex);
}

//フェードイン
void Fade::FadeIn(void)
{
	if (mState == FADE_OUT_END || mState == NONE_FADE) {
		mState = FADE_IN;
	}
}

void Fade::FadeOut(void)
{
	if (mState == FADE_IN_END || mState == NONE_FADE) {
		mState = FADE_OUT;
	}
}

//描画
void Fade::Draw()
{
	mSprite->Draw();
	mTeamLogo->Draw();
}

//更新
void Fade::Update()
{

	//状態ごとにフェードイン・アウトする
	switch (mState)
	{
	case NONE_FADE:
		break;
	case FADE_IN:
		
		if (mTeamLogo->mColor.a <= 0.0f) {
			mSprite->mColor.a -= 0.0007f * gDeltaTime;
		}

		mTeamLogo->mColor.a -= 0.0004f * gDeltaTime;
		if (mSprite->mColor.a <= 0.0f) {//フェードが終了していたらなにもしていない状態にする
			mState = FADE_IN_END;
		}

		break;
	case FADE_OUT:
		
		if (mTeamLogo->mColor.a >= 1.0f) {
			mSprite->mColor.a += 0.0007f * gDeltaTime;
		}
		mTeamLogo->mColor.a += 0.0004f * gDeltaTime;
		if (mSprite->mColor.a >= 1.0f) {//フェードが終了していたらなにもしていない状態にする
			mState = FADE_OUT_END;
		}

		break;
	default:
		break;
	}
	
	
	mSprite->Update();
	mTeamLogo->Update();
	
}
