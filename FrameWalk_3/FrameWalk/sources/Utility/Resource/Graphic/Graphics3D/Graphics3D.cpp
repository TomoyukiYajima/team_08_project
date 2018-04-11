#include "Graphics3D.h"
#include "../../../../Math/MathHelper.h"

// ライトパラメータ
Light Graphics3D::light_;

void Graphics3D::initialize()
{
	// 描画先を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);
	// zバッファを有効にする
	enable_z_buffer();
	// zバッファの書き込みを行う
	enable_write_z_buffer();
	// デフォルトのライト設定
	light(Light());
	// ライティングを有効にする
	enable_lighting();
}

void Graphics3D::finalize()
{
}

void Graphics3D::clear()
{
	ClearDrawScreen();
}

void Graphics3D::clear_color(float r, float g, float b)
{
	SetBackgroundColor(int(r * 255), int(g * 255), int(b * 255));
}

void Graphics3D::viewport(int x, int y, int w, int h)
{
	MATRIX viewport_matrix;
	CreateViewportMatrix(&viewport_matrix, x + (w / 2.0f), y + (h / 2.0f), w, h);
	SetTransformToViewport(&viewport_matrix);
	SetDrawArea(x, y, x + w, y + h);
}

void Graphics3D::view_matrix(const Matrix & view)
{
	SetCameraViewMatrix(view);
}

void Graphics3D::projection_matrix(const Matrix & projection)
{
	SetupCamera_ProjectionMatrix(projection);
}

Matrix Graphics3D::view_matrix()
{
	return GetCameraViewMatrix();
}

Matrix Graphics3D::projection_matrix()
{
	return GetCameraProjectionMatrix();
}

void Graphics3D::light(const Light & light)
{
	switch (light.type)
	{
	case Light::Type::Directional: ChangeLightTypeDir(light.direction); break;
	case Light::Type::Point: 
		ChangeLightTypePoint(
			light.position, light.range, 
			light.attenuation0, light.attenuation1, light.attenuation2
			); 
		break;
	case Light::Type::Spot: 
		ChangeLightTypeSpot(
			light.position, light.direction, 
			MathHelper::ToRadius(light.out_angle), MathHelper::ToRadius(light.in_angle),
			light.range, light.attenuation0, light.attenuation1, light.attenuation2); 
		break;
	}

	SetLightDifColor(GetColorF(light.diffuse.r, light.diffuse.g, light.diffuse.b, light.diffuse.a));
	SetLightSpcColor(GetColorF(light.specular.r, light.specular.g, light.specular.b, light.specular.a));
	SetLightAmbColor(GetColorF(light.ambient.r, light.ambient.g, light.ambient.b, light.ambient.a));
	light_ = light;
}

Light Graphics3D::light()
{
	return light_;
}

void Graphics3D::enable_lighting()
{
	SetLightEnable(TRUE);
}

void Graphics3D::disable_lighting()
{
	SetLightEnable(FALSE);
}

void Graphics3D::enable_z_buffer()
{
	SetUseZBuffer3D(TRUE);
}

void Graphics3D::disable_z_buffer()
{
	SetUseZBuffer3D(FALSE);
}

void Graphics3D::enable_write_z_buffer()
{
	SetWriteZBuffer3D(TRUE);
}

void Graphics3D::disable_write_z_buffer()
{
	SetWriteZBuffer3D(FALSE);
}

void Graphics3D::blend_mode(BlendMode mode, float a)
{

}
