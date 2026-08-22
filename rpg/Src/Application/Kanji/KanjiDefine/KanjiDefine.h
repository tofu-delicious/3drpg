//各部首・つくり・部首とつくりによって作成できる漢字を列挙しているクラス
#pragma once

//部首
enum class RadicalID
{
	None = -1,
	Hi,				//火偏
};

//つくり
enum class ElementID
{
	None = -1,
	Chou,			//丁
};

//完成する漢字
enum class KanjiID
{
	None = -1,
	Tou,			//灯
};

//「部首 + つくり → 漢字」のレシピ
struct KanjiRecipe
{
	RadicalID radical;
	ElementID element;
	KanjiID	  kanji;
};