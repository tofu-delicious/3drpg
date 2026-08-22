#include "ElementEnemy.h"
#include "../../../../Asset/AssetManager.h"

void C_ElementEnemy::Init()
{
	m_spModel = C_AssetManager::Instance().GetModel("ElementEnemy");
	m_mWorld = Math::Matrix::CreateScale(17.0f) * Math::Matrix::CreateTranslation(Math::Vector3{ 5.0f,0.0f,10.0f });
}

void C_ElementEnemy::Update()
{}

void C_ElementEnemy::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}
