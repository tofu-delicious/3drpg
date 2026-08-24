#include "KanjiMasterTable.h"

//全漢字のマスタデータ（漢字名、漢字属性、スコア値）
const std::vector<KanjiMasterData> KanjiMasterTable =
{
	{KanjiID::Hi,	KanjiAttribute::Fire,	100,	"Model_Hi"},	//火
	{KanjiID::Mizu,	KanjiAttribute::Water,	100,	"Model_Mizu"},	//水
	{KanjiID::Wood,	KanjiAttribute::Wood,	100,	"Model_Ki"},	//木
	{KanjiID::Tsuki,KanjiAttribute::None,	100,	"Model_Tsuki"},	//月
};

const KanjiMasterData* FindKanjiMaster(KanjiID a_kanji)
{
	for (const auto& _data : KanjiMasterTable)
	{
		if (_data.id == a_kanji)
		{
			return &_data;
		}
	}
	return nullptr;
}

std::vector<KanjiID> GetAllKanjiIDList()
{
	std::vector<KanjiID> _list;
	_list.reserve(KanjiMasterTable.size());

	for (const auto& _data : KanjiMasterTable)
	{
		_list.push_back(_data.id);
	}
	return _list;
}
