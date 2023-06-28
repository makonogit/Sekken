#pragma once
#include "StaticObject.h"

class Babble :
	public StaticObject
{
private:
	
	//StaticObject SubBubble;
	float fBabbleTime;					//�A�������܂ł̎���
	int BubbleAngle;					//�A�̌���

public:

	Babble(XMFLOAT3 & _Camera);	//�R���X�g���N�^
	~Babble();					//�f�X�g���N�^
	void Update() override;		//�X�V
	void BabbleSet(XMFLOAT2 pos);	//�A�̈ʒu�Z�b�g

};

