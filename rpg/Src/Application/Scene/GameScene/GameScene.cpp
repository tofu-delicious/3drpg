#include "GameScene.h"
#include"../SceneManager.h"
#include "../../GameObject/Ground/Ground.h"
#include "../../GameObject/Charactor/Player/Player.h"
#include "../../GameObject/Camera/TPSCamera/TPSCamera.h"
#include "../../GameObject/Charactor/Enemy/EnemySpawner/EnemySpawner.h"
#include "../../Kanji/KanjiDropItem/KanjiDropItem.h"
#include "../../GameObject/UI/KanjiStockUI/KanjiStockUI.h"

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
	auto _pGround = std::make_shared<C_Ground>();
	_pGround->Init();
	m_objList.push_back(_pGround);

	//プレイヤー
	auto _pPlayer = std::make_shared<C_Player>();
	_pPlayer->Init();
	m_objList.push_back(_pPlayer);

	//敵出現処理（60秒間、5秒間隔でランダムな座標に敵を出現させ続ける）
	auto _pEnemyS_pawner = std::make_shared<C_EnemySpawner>();
	_pEnemyS_pawner->Init();
	_pEnemyS_pawner->SetPlayer(_pPlayer);
	m_objList.push_back(_pEnemyS_pawner);

	//手持ち漢字UI
	auto _pKanjiStockUI = std::make_shared<C_KanjiStockUI>();
	_pKanjiStockUI->Init();
	_pKanjiStockUI->SetPlayer(_pPlayer);
	m_objList.push_back(_pKanjiStockUI);

	//TPSカメラ
	auto _pCamera = std::make_shared<TPSCamera>();
	_pCamera->Init();
	_pCamera->SetTarget(_pPlayer);			//Playerを追従ターゲットに設定
	_pCamera->RegistHitObject(_pGround);	//地面との当たり判定（めりこみ防止）
	_pPlayer->SetCamera(_pCamera);			//プレイヤーにカメラをセット（向き参照用）
	m_objList.push_back(_pCamera);

	//================ テスト ====================
	/*auto pKanji = std::make_shared<C_KanjiDropItem>();
	pKanji->Init();
	m_objList.push_back(pKanji);*/
}
