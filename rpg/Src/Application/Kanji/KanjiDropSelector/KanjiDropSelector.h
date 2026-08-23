#pragma once
#include "../KanjiDefine/KanjiDefine.h"
#include "../KanjiUsageHistory/KanjiUsageHistory.h"

class C_KanjiDropSelector
{
public:
	//未使用の漢字があればその中から抽選、無ければ全漢字から抽選
	static KanjiID Select(const C_KanjiUsageHistory& a_history);
};