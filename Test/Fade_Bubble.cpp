#include "Fade_Bubble.h"

extern DWORD gDeltaTime;
int Fade_Bubble::mState = NONE_FADE;

//<><><><><><><><><><><><><><><><><><>
// 関数名：Fade_Bubble
// 役割：コンストラクタ
//<><><><><><><><><><><><><><><><><><>
Fade_Bubble::Fade_Bubble()
{
	camera = { 0.0f,0.0f,1.0f };	//カメラ
	
	//テクスチャ読み込み
	LoadTexture(L"assets/images/BackGround/FadeBubble.png", &mpTexture);
	LoadTexture(L"assets/Test.png", &BackTexture);

	//フェード用オブジェクトの初期化
	for (int i = 0; i < 2; i++) {
		Babble[i] = new StaticObject(camera);
		Babble[i]->mSprite->SetTexture(mpTexture);
		Babble[i]->SetSize(2.8f, 2.0f);
	}
	
	//	それぞれの座標を指定(四隅)
	Babble[0]->SetPosition( 0.0f, -2.0f);
	Babble[1]->SetPosition( 0.0f, -2.0f);
	//画像を反転
	float Revers = Babble[1]->mSprite->mUV.w;
	Babble[1]->mSprite->mUV.w = Babble[1]->mSprite->mUV.x;
	Babble[1]->mSprite->mUV.x = Revers;

	//背景の初期化
	color = { 1.0f,1.0f,1.0f,0.0f };
	Back = new Sprite(camera);
	Back->SetTexture(BackTexture);
	Back->mSize = { 2.8f,2.0f };
	Back->SetColor(color);

	Fade_Bubble::mState = NONE_FADE;
	fTime = 0.0f;
	Sound_Init(SOUND_LABEL_SE001);
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：~Fade_Bubble
// 役割：デストラクタ
//<><><><><><><><><><><><><><><><><><>
Fade_Bubble::~Fade_Bubble()
{
	Sound_Uninit(SOUND_LABEL_SE001);
	delete Back;
	for (int i = 0; i < 4; i++) {
		delete Babble[i];
	}
	COM_SAFE_RELEASE(BackTexture);
	COM_SAFE_RELEASE(mpTexture);

}

void Fade_Bubble::FadeIn(void)
{
	if (Fade_Bubble::mState == FADE_OUT_END || Fade_Bubble::mState == NONE_FADE) {
		mState = FADE_IN;
	}
}

void Fade_Bubble::FadeOut(void)
{
	if (Fade_Bubble::mState == FADE_IN_END || Fade_Bubble::mState == NONE_FADE) {
		Play(SOUND_LABEL_SE001);
		mState = FADE_OUT;
	}
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：Update
// 役割：更新
//<><><><><><><><><><><><><><><><><><>
void Fade_Bubble::Update()
{
	fTime += gDeltaTime;

	//状態ごとにフェードイン・アウトする
	switch (Fade_Bubble::mState)
	{
	case NONE_FADE:
		break;
	case FADE_IN:

		//泡画像を上にあげる
		if (Babble[0]->mSprite->mCenter.y < 2.0f || Babble[1]->mSprite->mCenter.y < 2.0f) {
			Babble[0]->mSprite->mCenter.y += 0.0015f * gDeltaTime;
			Babble[1]->mSprite->mCenter.y += 0.0015f * gDeltaTime;

		}
		/*if (Babble[1]->mSprite->mCenter.x < 1.5f || Babble[3]->mSprite->mCenter.x < 1.5f) {
			Babble[1]->mSprite->mCenter.x += 0.0005f;
			Babble[3]->mSprite->mCenter.x += 0.0005f;
			Babble[1]->mSprite->mCenter.y -= 0.0005f;
			Babble[3]->mSprite->mCenter.y += 0.0005f;
		}*/
		else {
			Babble[0]->mSprite->mCenter.y = -2.0f;
			Babble[1]->mSprite->mCenter.y = -2.0f;
			Fade_Bubble::mState = FADE_IN_END;
		}

		//背景を透明にする
		if (Back->mColor.a >= 0.0f) {
			Back->mColor.a -= 0.0006f * gDeltaTime;
		}

		break;
	case FADE_OUT:
		
		//泡を画面の中心まで移動させる
		if (Babble[0]->mSprite->mCenter.y < 0.0f || Babble[1]->mSprite->mCenter.y < 0.0f) {
			Babble[0]->mSprite->mCenter.y += 0.0015f * gDeltaTime;
			Babble[1]->mSprite->mCenter.y += 0.0015f * gDeltaTime;

		}
		/*if (Babble[0]->mSprite->mCenter.x < -0.5f || Babble[2]->mSprite->mCenter.x < -0.5f) {
			Babble[0]->mSprite->mCenter.x += 0.0005f;
			Babble[2]->mSprite->mCenter.x += 0.0005f;
			Babble[0]->mSprite->mCenter.y += 0.0005f;
			Babble[2]->mSprite->mCenter.y -= 0.0005f;

		}
		if (Babble[1]->mSprite->mCenter.x > 0.5f || Babble[3]->mSprite->mCenter.x > 0.5f) {
			Babble[1]->mSprite->mCenter.x -= 0.0005f;
			Babble[3]->mSprite->mCenter.x -= 0.0005f;
			Babble[1]->mSprite->mCenter.y += 0.0005f;
			Babble[3]->mSprite->mCenter.y -= 0.0005f;
		}*/
		else {
			Fade_Bubble::mState = FADE_OUT_END;
		}
		//画面を白くする
		if (Back->mColor.a <= 1.0f) {
			Back->mColor.a += 0.0006f * gDeltaTime;
		}

		break;
	default:
		break;
	}

	if (fTime >= 0.5f * 1000.0f) {
		if (Babble[0]->active) {
			Babble[0]->SetActive(false);
			Babble[1]->SetActive(true);
		}
		else {
			Babble[0]->SetActive(true);
			Babble[1]->SetActive(false);
		}
		fTime = 0.0f;
	}
	//スプライトの更新
	Back->Update();
	for (int i = 0; i < 2; i++) {
		Babble[i]->Update();
	}

	
}

//<><><><><><><><><><><><><><><><><><>
// 関数名：Draw
// 役割：描画
//<><><><><><><><><><><><><><><><><><>
void Fade_Bubble::Draw()
{
	Back->Draw();

	for (int i = 0; i < 2; i++) {
		Babble[i]->Draw();
	}
}


//======================================================================================
// 担当者：		菅眞心
// 制作日時：　 2022-12-01
// チーム名：	黒棺	
//======================================================================================