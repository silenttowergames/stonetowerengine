#pragma once

#include "Camera.h"

Camera Camera_Create();
void Camera_LoadInto(Camera* camera, void* dest);
