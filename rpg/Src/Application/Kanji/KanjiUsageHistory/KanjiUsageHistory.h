#pragma once
#include "../KanjiDefine/KanjiDefine.h"

//プレイヤーが今プレイで使用（消費）した漢字の履歴
//敵の出現時ドロップ抽選で「未使用優先」を判定するために参照される
class C_KanjiUsageHistory
{
public:
	void MarkUsed(KanjiID a_kanji)
	{
		if (!IsUsed(a_kanji))
		{
			m_usedList.push_back(a_kanji);
		}
	}

	bool IsUsed(KanjiID a_kanji) const
	{
		return std::find(m_usedList.begin(), m_usedList.end(), a_kanji) != m_usedList.end();
	}

	void ResetForNewPlay() { m_usedList.clear(); }	//1プレイ限りでリセット

private:
	std::vector<KanjiID> m_usedList;
};