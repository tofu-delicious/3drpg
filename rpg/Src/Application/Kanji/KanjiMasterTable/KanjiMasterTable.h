#pragma once
#include "../KanjiDefine/KanjiDefine.h"

//全漢字のマスタデータ一覧（KanjiID::Noneは含まない）
extern const std::vector<KanjiMasterData> KanjiMasterTable;

//KanjiIDからマスタデータを検索する（見つからなければnullptr）
const KanjiMasterData* FindKanjiMaster(KanjiID a_kanji);

//マスタに登録されている全KanjiIDの一覧を取得（ドロップ抽選の母集団に使用
std::vector<KanjiID> GetAllKanjiIDList();