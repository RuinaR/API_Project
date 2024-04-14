#pragma once
class Scene abstract
{
public:
	virtual void Init() abstract;
	virtual void Release() abstract;
	virtual void Start() abstract;

	//���콺 Ŭ�� �̺�Ʈ
	virtual void LBtnDown() abstract;
	virtual void RBtnDown() abstract;
	virtual void LBtnUp() abstract;
	virtual void RBtnUp() abstract;
};

