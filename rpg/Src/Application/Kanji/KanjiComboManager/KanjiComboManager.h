//多様性コンボ
#pragma once
#include "../KanjiDefine/KanjiDefine.h"

class C_KanjiComboManager
{
public:

	C_KanjiComboManager(){}
	~C_KanjiComboManager(){}

	//直近の漢字と今回の漢字が同じかどうかの判定処理
	void OnUseKanji(KanjiID a_kanji);
	
	float GetScoreMultiplier()const { return m_scoreMultiplier; }

private:

	KanjiID m_lastUsedKanji   = KanjiID::None;
	int		m_comboCount	  = 0;
	float	m_scoreMultiplier = 1.0f;

};