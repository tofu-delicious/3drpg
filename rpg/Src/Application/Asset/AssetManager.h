//AssetManager.h
#pragma once

class C_AssetManager
{
public:
	
	~C_AssetManager(){}

	//テキストファイル読み込み処理
	void ReadFile(const std::string& a_fileName);

	//2Dポリゴンロード処理
	void LoadPolygon(const std::string& a_keyword, const std::string& a_filePath);

	//3Dモデルロード処理
	void LoadModel(const std::string& a_keyword, const std::string& a_filePath);

	//2Dテクスチャロード処理
	void LoadTex(const std::string& a_keyword, const std::string& a_filePath);

	//2Dポリゴン取得処理
	std::shared_ptr<KdSquarePolygon> GetPolygon(const std::string& a_keyword);

	//3Dモデル取得処理
	std::shared_ptr<KdModelData> GetModel(const std::string& a_keyword);

	//2Dテクスチャ取得処理
	std::shared_ptr<KdTexture> GetTex(const std::string& a_keyword);

private:

	C_AssetManager(){}

	std::unordered_map<std::string, std::shared_ptr<KdSquarePolygon>> m_polygonMap;	//2Dポリゴン格納マップ
	
	std::unordered_map<std::string, std::shared_ptr<KdModelData>> m_modelMap;		//3Dモデルデータ格納マップ

	std::unordered_map<std::string, std::shared_ptr<KdTexture>> m_texMap;			//2Dテクスチャ格納マップ

public:

	static C_AssetManager& Instance() {
		static C_AssetManager Instance;
		return Instance;
	}
};