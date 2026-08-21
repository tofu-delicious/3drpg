#include "GameScene.h"
#include"../SceneManager.h"
#include "../../GameObject/Ground/Ground.h"
#include "../../GameObject/Charactor/Player/Player.h"

void GameScene::Event()
{
	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}
}

void GameScene::Init()
{
	//地面
	auto pGround = std::make_shared<C_Ground>();
	pGround->Init();
	m_objList.push_back(pGround);

	//プレイヤー
	auto pPlayer = std::make_shared<C_Player>();
	pPlayer->Init();
	m_objList.push_back(pPlayer);
}
