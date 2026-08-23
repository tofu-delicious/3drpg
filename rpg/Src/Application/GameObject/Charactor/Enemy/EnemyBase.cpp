#include "EnemyBase.h"
#include "../../../Kanji/KanjiDropSelector/KanjiDropSelector.h"

void C_EnemyBase::DecideBodyKanji(const C_KanjiUsageHistory& a_history)
{
	m_bodyKanji = C_KanjiDropSelector::Select(a_history);
}
