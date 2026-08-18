//AssetManager.cpp
#include "AssetManager.h"

void C_AssetManager::ReadFile(const std::string& a_fileName)
{
	//ファイルを読み込みモードで開く
	std::ifstream file(a_fileName);
	//1行分のテキストを一時的に保存するための変数
	std::string line;
	//ファイルから1行ずつ読み込む処理
	while (std::getline(file, line))
	{
		std::istringstream ss(line);	//読み込んだ1行を空白区切りで分解
		std::string asset;				//読み込んだデータが「Polygon」か「Model」かを判別
		std::string keyword;
		std::string path;				//読み込んだパス

		//空白区切りで各値を取り出し、そのデータを変数に格納する処理（左から順に）
		ss >> asset >> keyword >> path;

		if (asset == "Polygon") LoadPolygon(keyword, path);
		else if (asset == "Model") LoadModel(keyword, path);
		else if (asset == "Texture") LoadTex(keyword, path);
	}
}

void C_AssetManager::LoadPolygon(const std::string& a_keyword, const std::string& a_filePath)
{
	//ロード中のポリゴンが既にマップに存在していればリターン
	if (m_polygonMap.count(a_keyword) > 0)return;

	auto newPolygon = std::make_shared<KdSquarePolygon>();	//新規の領域を確保
	newPolygon->SetMaterial(a_filePath);					//引数のポリゴンをロード
	m_polygonMap[a_keyword] = newPolygon;					//ポリゴンマップに追加
}

void C_AssetManager::LoadModel(const std::string& a_keyword, const std::string& a_filePath)
{
	//ロード中のモデルが既にマップに存在していればリターン
	if (m_modelMap.count(a_keyword) > 0)return;

	auto newModel = std::make_shared<KdModelData>();		//新規の領域を確保
	newModel->Load(a_filePath);								//引数のモデルをロード
	m_modelMap[a_keyword] = newModel;						//モデルマップに追加
}

void C_AssetManager::LoadTex(const std::string& a_keyword, const std::string& a_filePath)
{
	//ロード中のテクスチャが既にマップに存在していればリターン
	if (m_texMap.count(a_keyword) > 0)return;

	auto newTex = std::make_shared<KdTexture>();
	newTex->Load(a_filePath);
	m_texMap[a_keyword] = newTex;
}

std::shared_ptr<KdSquarePolygon> C_AssetManager::GetPolygon(const std::string& a_keyword)
{
	//引数の「keyword」をマップ上で探索する
	auto it = m_polygonMap.find(a_keyword);
	//もしイテレータがend関数と等しければデータなし、そうでなければデータ発見
	if (it != m_polygonMap.end())
	{
		return it->second;
	}
	return nullptr;
}

std::shared_ptr<KdModelData> C_AssetManager::GetModel(const std::string& a_keyword)
{
	//引数の「keyword」をマップ上で探索する
	auto it = m_modelMap.find(a_keyword);
	//もしイテレータがend関数と等しければデータなし、そうでなければデータ発見
	if (it != m_modelMap.end())
	{
		return it->second;
	}
	return nullptr;
}

std::shared_ptr<KdTexture> C_AssetManager::GetTex(const std::string& a_keyword)
{
	auto it = m_texMap.find(a_keyword);

	if (it != m_texMap.end())
	{
		return it->second;
	}
	return nullptr;
}
