#pragma once
#include "../CharaBase.h"
#include "../../Camera/CameraBase.h"

class C_Player :public C_CharaBase
{

public:

	C_Player(){}
	~C_Player()		override{}

	void Init()		override;
	void Update()	override;
	void DrawLit()	override;

	//移動処理
	void MovePlayer();

	//行列処理
	void UpdateMatrix();

	// カメラをセット
	void SetCamera(const std::shared_ptr<CameraBase>& camera)
	{
		m_wpCamera = camera;
	}

private:

	std::weak_ptr<CameraBase> m_wpCamera;

};