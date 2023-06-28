//======================================================================================
// 名前：Sprite
// 説明：ポリゴンの表示
//======================================================================================

//------------------------------------
//		include
//------------------------------------
#include "Sprite.h"


//頂点更新
void Sprite::Update()
{
	VERTEX2D vx[6];
	
	vx[0] = { (mCenter.x - mSize.x / 2)*mCamera.z -mCamera.x ,  (mCenter.y - mSize.y / 2)* mCamera.z -mCamera.y , mUV.w , mUV.z ,mColor };	//左下
	vx[1] = { (mCenter.x - mSize.x / 2)*mCamera.z -mCamera.x ,  (mCenter.y + mSize.y / 2)* mCamera.z -mCamera.y , mUV.w , mUV.y ,mColor };	//左上
	vx[2] = { (mCenter.x + mSize.x / 2)*mCamera.z -mCamera.x ,  (mCenter.y - mSize.y / 2)* mCamera.z -mCamera.y , mUV.x , mUV.z ,mColor };	//右下
	vx[3] = { (mCenter.x + mSize.x / 2)*mCamera.z -mCamera.x ,  (mCenter.y + mSize.y / 2)* mCamera.z -mCamera.y , mUV.x , mUV.y ,mColor };	//右上
	vx[4] = vx[2];	//右下
	vx[5] = vx[1];	//左上
	
					//　Direct3D構造体にアクセスする
	DIRECT3D* d3d = Direct3D_Get();
	//　頂点データをVRAMに送る
	d3d->context->UpdateSubresource(mpVertexBuffer, 0, NULL, vx, 0, 0);
}

// 描画処理
void Sprite::Draw()
{
	//　Direct3D構造体にアクセスする
	DIRECT3D* d3d = Direct3D_Get();
	//　描画に称する頂点バッファを選択する
	UINT stride = sizeof(VERTEX2D);
	UINT offset = 0;

	//　ピクセルシェーダーにテクスチャを渡す
	d3d->context->PSSetShaderResources(0, 1, &mpTexture);

	//　ピクセルシェーダーにサンプラーを渡す
	d3d->context->PSSetSamplers(0, 1, &d3d->samplerPoint);


	d3d->context->IASetVertexBuffers(0, 1, &mpVertexBuffer,	//　選択する頂点バッファ
		&stride, &offset);


	//　描画命令
	d3d->context->Draw(6, 0); //　第一引数は頂点数
}

void Sprite::SetColor(RGBA color)
{
	mColor = color;
}

void Sprite::SetTexture(ID3D11ShaderResourceView * pTexture)
{
	mpTexture = pTexture;
}


// コンストラクタ
Sprite::Sprite(XMFLOAT3& _Camera):mCamera{_Camera}
{

	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = sizeof(VERTEX2D) * 6; // VRAMに確保するデータサイズ。通常は今から送る頂点データのサイズ。
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER; // 頂点バッファ作成をここで指定。
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;
	//　Direct3D構造体にアクセスする
	DIRECT3D* d3d = Direct3D_Get();
	// バッファ作成関数（デバイスクラスのメンバ関数）を呼び出し
	//												↓この変数に保存される
	d3d->device->CreateBuffer(&bufferDesc, NULL, &mpVertexBuffer);

	mCenter.x = 0.0f;
	mCenter.y = 0.0f;
	mSize.x = 1.0f;
	mSize.y = 1.0f;
	mUV.w = 0.0f;//左
	mUV.x = 1.0f;//右
	mUV.y = 0.0f;//上
	mUV.z = 1.0f;//下
	
	mColor = { 1.0f,1.0f,1.0f,1.0f };

}

// デストラクタ
Sprite::~Sprite()
{
	//　頂点バッファの解放
	COM_SAFE_RELEASE(mpVertexBuffer);

}


//======================================================================================
// 担当者：		中川直登
// チーム名：	黒棺	
//======================================================================================