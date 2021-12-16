#include "Camera.h"

Camera::Camera(int w, int h, float corner, DirectX::XMFLOAT3 scale)
{
	this->w = w;
	this->h = h;
	this->corner = corner;
	this->scale = scale;
	scene_h.push_back(344);
	scene_h.push_back(496);
	scene_h.push_back(304);
	scene_h.push_back(496);
	current_scene_h = scene_h.at(3);
	D3DXMatrixOrthoLH(&orthoMatrix, w, -h, 0.0f, 1.0f);
	D3DXMatrixIdentity(&iMatrix);
}

Camera::~Camera()
{

}

D3DVECTOR Camera::GetPosition() {
	return this->pos;
}

void Camera::SetTransform(LPDIRECT3DDEVICE9 gDevice) const
{
	gDevice->SetTransform(D3DTS_PROJECTION, &orthoMatrix);
	gDevice->SetTransform(D3DTS_WORLD, &iMatrix);
	gDevice->SetTransform(D3DTS_VIEW, &Matrix);
}

void Camera::Update()
{
	float cam_x = 0;
	float cam_y = 0;
	if (this->following)
	{
		this->following->GetPosition(cam_x, cam_y);
	}
	cam_y = current_scene_h - cam_y;
	this->Matrix = D3DXMATRIX(
		scale.x * cos(corner), scale.x * sin(corner), 0, 0,
		-scale.y * sin(corner), scale.y * cos(corner), 0, 0, 
		0, 0, scale.z, 0,
		-cam_x * scale.x * cos(corner) + cam_y * scale.y * sin(corner), -cam_x * scale.x * sin(corner) - cam_y * scale.y * cos(corner), 0, 1
	);

}

void Camera::Follow(CTank* following)
{
	this->following = following;
}

void Camera::Unfollow()
{
	this->following = nullptr;
}

bool Camera::IsFollowing() const
{
	return this->following != nullptr;
}






