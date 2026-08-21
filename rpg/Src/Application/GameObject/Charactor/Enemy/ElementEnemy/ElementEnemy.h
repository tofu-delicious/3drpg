#pragma once
#include "../EnemyBase.h"

class C_ElementEnemy :public C_EnemyBase
{
public:
	C_ElementEnemy() {}
	~C_ElementEnemy()		override {}

	void Init()				override;
	void Update()			override;
	void DrawLit()			override;

private:

};