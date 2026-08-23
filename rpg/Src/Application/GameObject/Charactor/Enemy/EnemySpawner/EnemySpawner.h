#pragma once
#include "../EnemyBase.h"
#include "../../Player/Player.h"

//時間経過で敵を複数出現させる役割専用のクラス
class C_EnemySpawner : public C_EnemyBase
{
public:

	C_EnemySpawner() {}
	~C_EnemySpawner()	override {}

	void Init()			override;
	void Update()		override;

	//出現した敵に使用履歴を渡すため、参照するプレイヤーを外部から設定する
	void SetPlayer(const std::shared_ptr<C_Player>& a_pPlayer) { m_wpPlayer = a_pPlayer; }

private:

	//敵を1体生成し、現在のシーンに追加する
	void SpawnEnemy();

	std::weak_ptr<C_Player> m_wpPlayer;			//生成した敵にDecideBodyKanjiを呼ぶためのプレイヤー参照（所有権は持たない）

	float m_elapsedTime = 0.0f;					//ゲーム開始からの経過時間
	float m_spawnTimer = 0.0f;					//次の出現までのカウントダウンタイマー

	const float m_kGameDuration = 60.0f;		//敵を出現させ続ける時間(60秒)
	const float m_kSpawnInterval = 5.0f;		//敵を出現させる間隔(秒)

	const float m_kSpawnRangeX_Min = -10.0f;	//出現範囲 X座標の最小値
	const float m_kSpawnRangeX_Max = 10.0f;		//出現範囲 X座標の最大値
	const float m_kSpawnRangeZ_Min = 5.0f;		//出現範囲 Z座標の最小値
	const float m_kSpawnRangeZ_Max = 20.0f;		//出現範囲 Z座標の最大値
};