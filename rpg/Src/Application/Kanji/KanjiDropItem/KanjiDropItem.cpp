#include "KanjiDropItem.h"
#include ".././../Asset/AssetManager.h"

void C_KanjiDropItem::Init()
{
	m_spModel = C_AssetManager::Instance().GetModel("Hi");

	m_mWorld = Math::Matrix::CreateTranslation(m_pos);
}

void C_KanjiDropItem::Update()
{
}

void C_KanjiDropItem::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}

