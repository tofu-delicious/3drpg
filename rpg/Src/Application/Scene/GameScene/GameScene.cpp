#include "GameScene.h"
#include"../SceneManager.h"
#include "../../GameObject/Ground/Ground.h"
#include "../../GameObject/Charactor/Player/Player.h"
#include "../../GameObject/Camera/TPSCamera/TPSCamera.h"

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

	//TPSカメラ
	auto pCamera = std::make_shared<TPSCamera>();
	pCamera->Init();
	pCamera->SetTarget(pPlayer);		//Playerを追従ターゲットに設定
	pCamera->RegistHitObject(pGround);	//地面との当たり判定（めりこみ防止）
	m_objList.push_back(pCamera);
}
