#pragma once

#include "Camera.h"
#include "Matrix.h"

Matrix Matrix_Create();
Matrix Matrix_Multiply(Matrix* m1, Matrix* m2);
void Matrix_ToTransform(Matrix* matrix, float* transform);
Matrix Matrix_CreateTranslation(float X, float Y, float Z);
Matrix Matrix_CreateRotationZ(float Rotation);
Matrix Matrix_CreateScale(float X, float Y, float Z);
Matrix Matrix_CreateFromCamera(Camera* camera);
