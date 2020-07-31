#include "CameraFunctions.h"
#include "MatrixFunctions.h"

Camera Camera_Create(int resX, int resY)
{
	Camera camera;
	memset(&camera, 0, sizeof(Camera));
	camera.resolution.X = resX;
	camera.resolution.Y = resY;
	camera.zoom.X = 1;
	camera.zoom.Y = 1;
	
	return camera;
}

void Camera_LoadInto(Camera* camera, void* dest)
{
	Matrix matrix = Matrix_CreateFromCamera(camera);
	
	Matrix_ToTransform(&matrix, dest);
}
