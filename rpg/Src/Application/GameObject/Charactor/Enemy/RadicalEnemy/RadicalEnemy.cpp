#include "RadicalEnemy.h"
#include "../../../../Asset/AssetManager.h"

void C_RadicalEnemy::Init()
{
	m_spModel = C_AssetManager::Instance().GetModel("RadicalEnemy");
	m_mWorld = Math::Matrix::CreateScale(17.0f) * Math::Matrix::CreateTranslation(Math::Vector3{ -5.0f,0.0f,10.0f });

	//仮：RadicalEnemyの弱点造成を水に設定
	SetWeekAttribute(KanjiAttribute::Water);
}

void C_RadicalEnemy::Update()
{}

void C_RadicalEnemy::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel,m_mWorld);
}
