#define CAMERA_H

#include <DirectXMath.h>
#include "Tank.h"


class Camera
{
public:
	Camera(int w, int h, float corner, DirectX::XMFLOAT3 scale);
	~Camera();

	void Follow(CTank* following);
	void Update();
	void Unfollow();
	bool IsFollowing() const;
	void SetTransform(LPDIRECT3DDEVICE9 device) const;
	D3DVECTOR GetPosition();

private:
	int w;
	int h;
	D3DVECTOR pos;
	float corner;

	D3DXMATRIX Matrix;
	D3DXMATRIX orthoMatrix;
	D3DXMATRIX iMatrix;
	DirectX::XMFLOAT3 scale;

	CTank* following;
};
