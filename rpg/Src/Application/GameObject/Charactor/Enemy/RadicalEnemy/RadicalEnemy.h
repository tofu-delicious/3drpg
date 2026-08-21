#pragma once
#include "../EnemyBase.h"

class C_RadicalEnemy:public C_EnemyBase
{
public:
	C_RadicalEnemy(){}
	~C_RadicalEnemy()		override{}

	void Init()				override;
	void Update()			override;
	void DrawLit()			override;

private:

};