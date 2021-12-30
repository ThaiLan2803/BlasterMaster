#define CAMERA_H

#include <DirectXMath.h>
#include "Tank.h"

#define S1H	484
#define S1W	300
#define S2H	496
#define S2W	1232
#define S3H	484
#define S3W	232
#define S4H	2000
#define S4W	496

class Camera
{
	vector<int> scene_h;
	vector<int> scene_w;
	int current_scene_h;
	int current_scene_w;
public:
	Camera(int w, int h, float corner, DirectX::XMFLOAT3 scale);
	~Camera();

	void Follow(CTank* following);
	void Update();
	void Unfollow();
	bool IsFollowing() const;
	void SetTransform(LPDIRECT3DDEVICE9 device) const;
	void LatTruc(float& y) {
		y = current_scene_h - y;
	}
	void SetSceneHeight(int i) {
		this->current_scene_h = scene_h.at(i - 1);
		this->current_scene_w = scene_w.at(i - 1);
	}
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
