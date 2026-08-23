#include "KanjiDropSelector.h"
#include "../KanjiMasterTable/KanjiMasterTable.h"
//KdRandomはPch.h経由でグローバルに使用可能（既存コードの慣習に合わせ明示includeなし）

KanjiID C_KanjiDropSelector::Select(const C_KanjiUsageHistory& a_history)
{
	std::vector<KanjiID> _allList = GetAllKanjiIDList();

	//未使用の漢字だけを抽出
	std::vector<KanjiID> _unusedList;
	for (KanjiID _kanji : _allList)
	{
		if (!a_history.IsUsed(_kanji))
		{
			_unusedList.push_back(_kanji);
		}
	}

	//未使用があればそちらを優先、無ければ全体から抽選
	const std::vector<KanjiID>& _pool = !_unusedList.empty() ? _unusedList : _allList;

	if (_pool.empty())
	{
		return KanjiID::None;
	}

	int _index = KdRandom::GetInt(0, (int)_pool.size() - 1);
	return _pool[_index];
}