#include "Camera.h"

Camera::Camera(int w, int h, float corner, DirectX::XMFLOAT3 scale)
{
	this->w = w;
	this->h = h;
	this->corner = corner;
	this->scale = scale;
	scene_h.push_back(S1H);
	scene_h.push_back(S2H);
	scene_h.push_back(S3H);
	scene_h.push_back(S4H);
	scene_w.push_back(S1W);
	scene_w.push_back(S2W);
	scene_w.push_back(S3W);
	scene_w.push_back(S4W);
	current_scene_h = scene_h.at(0);
	current_scene_w = scene_w.at(0);
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
	LatTruc(cam_y);
	if (cam_x < w / 2)
		cam_x = w / 2;
	if (cam_y < h / 2)
		cam_y = h / 2;
	if (cam_x > current_scene_w - w / 2)
		cam_x = current_scene_w - w / 2;
	if (cam_y > current_scene_h - h / 2)
		cam_y = current_scene_h - h / 2;

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






