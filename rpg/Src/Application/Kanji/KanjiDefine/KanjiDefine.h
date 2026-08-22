//各部首・つくり・部首とつくりによって作成できる漢字を列挙しているクラス
#pragma once
//漢字
enum class KanjiID
{
	None = -1,
	Tou,			//灯
};

//漢字の属性
enum class KanjiAttribute
{
	None = -1,		//無属性
	Fire,			//火属性
	Water,			//水属性
	Wood,			//木属性
	//今後追加・・・
};

//漢字データ
struct KanjiMasterData
{
	KanjiID			id;
	KanjiAttribute	attribute;	//Noneなら無属性漢字
	int				baseScore;	//スコア値
};

//部首（※未使用）
//enum class RadicalID
//{
//	None = -1,
//	Hi,				//火偏
//};
//
////つくり（※未使用）
//enum class ElementID
//{
//	None = -1,
//	Chou,			//丁
//};

//「部首 + つくり → 漢字」のレシピ
//struct KanjiRecipe
//{
//	RadicalID radical;
//	ElementID element;
//	KanjiID	  kanji;
//};