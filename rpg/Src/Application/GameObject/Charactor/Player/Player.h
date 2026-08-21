#pragma once
#include "../CharaBase.h"

class C_Player :public C_CharaBase
{

public:

	C_Player(){}
	~C_Player()		override{}

	void Init()		override;
	void Update()	override;
	void DrawLit()	override;

private:

};