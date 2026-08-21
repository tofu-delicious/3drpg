#pragma once
#include "../ObjectBase.h"

class C_Ground:public C_ObjectBase
{
public:
	
	C_Ground(){}
	~C_Ground(){}

	void Init()		override;
	void Update()	override;
	void DrawLit()	override;

private:

};