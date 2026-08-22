//無属性漢字のレベルアップ：レベルごとに個別の追加効果
#pragma once
#include "../KanjiDefine/KanjiDefine.h"

class C_KanjiLevelManager
{
public:
	C_KanjiLevelManager(){}
	~C_KanjiLevelManager(){}

	//同じ無属性漢字を拾う度Lv + 1
	void OnPickUp(KanjiID a_kanji);

	//レベル取得
	int GetLevel(KanjiID a_kanji) const;

	//ゲーム終了時にレベルアップ情報を削除
	void ResetForNewPlay() { m_levelMap.clear(); }

private:

	std::unordered_map<KanjiID, int> m_levelMap;

};