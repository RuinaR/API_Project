#pragma once
class Scene abstract
{
public:
	virtual void Init() abstract;
	virtual void Release() abstract;
	virtual void Start() abstract;

	//마우스 클릭 이벤트
	virtual void LBtnDown() abstract;
	virtual void RBtnDown() abstract;
	virtual void LBtnUp() abstract;
	virtual void RBtnUp() abstract;
};

