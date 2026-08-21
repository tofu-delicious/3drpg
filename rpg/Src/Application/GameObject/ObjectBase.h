#pragma once 

class C_ObjectBase :public KdGameObject
{
public:
	C_ObjectBase(){}
	virtual ~C_ObjectBase()					override{}

	virtual void Init()				override{}
	virtual void Update()			override{}
	virtual void DrawLit()			override{}
	virtual void DrawSprite()		override{}

	//================ ゲッター =================
	Math::Vector3 GetPos()const override { return m_pos; }

	//================ セッター =================
	void SetPos(float a_posX = 0.0f, float a_posY = 0.0f, float a_posZ = 0.0f) { m_pos = Math::Vector3{ a_posX,a_posY,a_posZ }; }	//各軸ごとに値を指定したいとき
	void SetPos(const Math::Vector3& a_pos) { m_pos = a_pos; }	//X・Y・Z軸一気に座標を指定させたいとき

protected:

	//============= インスタンス ================
	std::shared_ptr<KdSquarePolygon> m_spPolygon = nullptr;		//2Dポリゴン用：きちんと実体化して使うこと！
	std::shared_ptr<KdModelData>	 m_spModel = nullptr;		//3Dモデル用：きちんと実体化して使うこと！
	std::shared_ptr<KdModelWork>	 m_spModelWork = nullptr;	//3Dモデルアニメーション用：きちんと実体化して使うこと！

	//=============== 状態フラグ ================
	bool m_isDebugOpen = false;

	//================ 動的変数 =================
	Math::Vector3 m_pos = {};			//座標
	Math::Color m_color = { 1,1,1,1 };	//色
	float m_radiusX = 0.0f;				//X軸方向の半径
	float m_radiusY = 0.0f;;			//Y軸方向の半径
	float m_scale = 1.0f;				//X・Y・Z軸共通の拡縮
	float m_scaleX = 1.0f;				//X軸方向の拡縮
	float m_scaleY = 1.0f;				//Y軸方向の拡縮
	float m_scaleZ = 1.0f;				//Z軸方向の拡縮
	float m_rotate = 0.0f;				//回転角度
	float m_alpha = 0.0f;				//不透明度
	float m_fadeStep = 0.0f;			//フェード用
	bool m_isActive = true;				//true 表示　false 非表示
};