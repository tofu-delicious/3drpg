#include "EnemySpawner.h"
#include "../../../../main.h"
#include "../../../../Scene/SceneManager.h"
#include "../../Enemy/RadicalEnemy/RadicalEnemy.h"

void C_EnemySpawner::Init()
{
	//経過時間を0にリセットしている
	m_elapsedTime = 0.0f;
	//最初の1体がInit直後に出現するようタイマーを0にしている
	m_spawnTimer = 0.0f;
}

void C_EnemySpawner::Update()
{
	//60秒経過済みなら以降の生成処理を行わずに抜ける
	if (m_elapsedTime >= m_kGameDuration) { return; }

	//このフレームで進んだ時間を取得している
	const float _deltaTime = Application::Instance().GetDeltaTime();

	//ゲーム開始からの経過時間に加算している
	m_elapsedTime += _deltaTime;
	//次の出現までのタイマーを減算している
	m_spawnTimer -= _deltaTime;

	//タイマーが0以下になったら出現処理を行う
	if (m_spawnTimer <= 0.0f)
	{
		//敵を1体生成している
		SpawnEnemy();
		//次の出現までのタイマーをリセットしている
		m_spawnTimer = m_kSpawnInterval;
	}
}

void C_EnemySpawner::SpawnEnemy()
{
	//敵1体分のインスタンスを生成している（現状は敵の種類が1種類のためRadicalEnemyを直接生成している）
	auto _pEnemy = std::make_shared<C_RadicalEnemy>();
	//敵の共通初期化を実行している
	_pEnemy->Init();

	//出現範囲内のX座標をランダムに決定している
	const float _spawnX = KdRandom::GetFloat(m_kSpawnRangeX_Min, m_kSpawnRangeX_Max);
	//出現範囲内のZ座標をランダムに決定している
	const float _spawnZ = KdRandom::GetFloat(m_kSpawnRangeZ_Min, m_kSpawnRangeZ_Max);
	//決定した座標を敵にセットしている(Y座標は地面の高さに合わせて0固定にしている)
	_pEnemy->SetPos(Math::Vector3{ _spawnX, 0.0f, _spawnZ });

	//保持しているプレイヤーの参照がまだ有効かを確認しつつ取得している
	if (auto _spPlayer = m_wpPlayer.lock())
	{
		//生成した敵に刻む漢字をプレイヤーの使用履歴から決定している
		_pEnemy->DecideBodyKanji(_spPlayer->GetKanjiUsageHistory());
	}

	//生成した敵を現在のシーンのオブジェクトリストに追加している
	SceneManager::Instance().AddObject(_pEnemy);
}