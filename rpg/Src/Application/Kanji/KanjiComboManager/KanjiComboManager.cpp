#include "KanjiComboManager.h"

void C_KanjiComboManager::OnUseKanji(KanjiID a_kanji)
{
	if (a_kanji == m_lastUsedKanji)
	{
		m_comboCount = 0;		//直近と同じ漢字 → 即座にリセット
	}
	else
	{
		m_comboCount++;			//直近と異なる字 → コンボ継続
	}

	m_lastUsedKanji = a_kanji;	//今回の漢字を直近の漢字として保存
	m_scoreMultiplier = 1.0f + m_comboCount * 0.1f;		//倍率の刻み幅は要調整
}
