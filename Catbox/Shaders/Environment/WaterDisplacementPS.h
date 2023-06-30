#pragma once
#include "Assets\Shader.h"

class WaterDisplacementPS : public PixelShader
{
public:
	struct WaterDisplacementData
	{
		float WaveHeight = 0;
		float WaveSpeed = 0;
		float WaveScale = 0;
		float WaveAngle = 0;
	} myWaterDisplacementData;

	WaterDisplacementPS();
	std::shared_ptr<PixelShader> MakeInstance() override;
	void SetResource() override;
	void SetData() override;
	void SaveData() override;
	void LoadData() override;

private:

	void RenderInProperties() override;
	Catbox::CBuffer<WaterDisplacementData> myWaterDisplacementDataBuffer;
};