#include "MatrixFunctions.h"
#include <math.h>

Matrix Matrix_Create()
{
	Matrix matrix;
	memset(&matrix, 0, sizeof(matrix));
	matrix.M11 = 1;
	matrix.M22 = 1;
	matrix.M33 = 1;
	matrix.M44 = 1;
	
	return matrix;
}

Matrix Matrix_Multiply(Matrix* m1, Matrix* m2)
{
	Matrix matrix;
	
	// Row 1
	// Col 1
	matrix.M11 = (
		(m1->M11 * m2->M11) +
		(m1->M12 * m2->M21) +
		(m1->M13 * m2->M31) +
		(m1->M14 * m2->M41)
	);
	// Col 2
	matrix.M12 = (
		(m1->M11 * m2->M12) +
		(m1->M12 * m2->M22) +
		(m1->M13 * m2->M32) +
		(m1->M14 * m2->M42)
	);
	// Col 3
	matrix.M13 = (
		(m1->M11 * m2->M13) +
		(m1->M12 * m2->M23) +
		(m1->M13 * m2->M33) +
		(m1->M14 * m2->M43)
	);
	// Col 4
	matrix.M14 = (
		(m1->M11 * m2->M14) +
		(m1->M12 * m2->M24) +
		(m1->M13 * m2->M34) +
		(m1->M14 * m2->M44)
	);
	
	// Row 2
	// Col 1
	matrix.M11 = (
		(m1->M21 * m2->M11) +
		(m1->M22 * m2->M21) +
		(m1->M23 * m2->M31) +
		(m1->M24 * m2->M41)
	);
	// Col 2
	matrix.M12 = (
		(m1->M21 * m2->M12) +
		(m1->M22 * m2->M22) +
		(m1->M23 * m2->M32) +
		(m1->M24 * m2->M42)
	);
	// Col 3
	matrix.M13 = (
		(m1->M21 * m2->M13) +
		(m1->M22 * m2->M23) +
		(m1->M23 * m2->M33) +
		(m1->M24 * m2->M43)
	);
	// Col 4
	matrix.M14 = (
		(m1->M21 * m2->M14) +
		(m1->M22 * m2->M24) +
		(m1->M23 * m2->M34) +
		(m1->M24 * m2->M44)
	);
	
	// Row 3
	// Col 1
	matrix.M11 = (
		(m1->M31 * m2->M11) +
		(m1->M32 * m2->M21) +
		(m1->M33 * m2->M31) +
		(m1->M34 * m2->M41)
	);
	// Col 2
	matrix.M12 = (
		(m1->M31 * m2->M12) +
		(m1->M32 * m2->M22) +
		(m1->M33 * m2->M32) +
		(m1->M34 * m2->M42)
	);
	// Col 3
	matrix.M13 = (
		(m1->M31 * m2->M13) +
		(m1->M32 * m2->M23) +
		(m1->M33 * m2->M33) +
		(m1->M34 * m2->M43)
	);
	// Col 4
	matrix.M14 = (
		(m1->M31 * m2->M14) +
		(m1->M32 * m2->M24) +
		(m1->M33 * m2->M34) +
		(m1->M34 * m2->M44)
	);
	
	// Row 4
	// Col 1
	matrix.M11 = (
		(m1->M41 * m2->M11) +
		(m1->M42 * m2->M21) +
		(m1->M43 * m2->M31) +
		(m1->M44 * m2->M41)
	);
	// Col 2
	matrix.M12 = (
		(m1->M41 * m2->M12) +
		(m1->M42 * m2->M22) +
		(m1->M43 * m2->M32) +
		(m1->M44 * m2->M42)
	);
	// Col 3
	matrix.M13 = (
		(m1->M41 * m2->M13) +
		(m1->M42 * m2->M23) +
		(m1->M43 * m2->M33) +
		(m1->M44 * m2->M43)
	);
	// Col 4
	matrix.M14 = (
		(m1->M41 * m2->M14) +
		(m1->M42 * m2->M24) +
		(m1->M43 * m2->M34) +
		(m1->M44 * m2->M44)
	);
	
	return matrix;
}

void Matrix_ToTransform(Matrix* matrix, float* transform)
{
	transform[0] = matrix->M11;
	transform[1] = matrix->M12;
	transform[2] = matrix->M13;
	transform[3] = matrix->M14;
	transform[4] = matrix->M21;
	transform[5] = matrix->M22;
	transform[6] = matrix->M23;
	transform[7] = matrix->M24;
	transform[8] = matrix->M31;
	transform[9] = matrix->M32;
	transform[10] = matrix->M33;
	transform[11] = matrix->M34;
	transform[12] = matrix->M41;
	transform[13] = matrix->M42;
	transform[14] = matrix->M43;
	transform[15] = matrix->M44;
}

Matrix Matrix_CreateTranslation(float X, float Y, float Z)
{
	Matrix matrix = Matrix_Create();
	
	matrix.M41 = X;
	matrix.M42 = Y;
	matrix.M43 = Z;
	
	return matrix;
}

Matrix Matrix_CreateRotationZ(float Rotation)
{
	Matrix matrix = Matrix_Create();
	
	float
		val1 = cos(Rotation),
		val2 = sin(Rotation)
	;
	
	matrix.M11 = val1;
	matrix.M12 = val2;
	matrix.M21 = -val2;
	matrix.M22 = val1;
	
	return matrix;
}

Matrix Matrix_CreateScale(float X, float Y, float Z)
{
	Matrix matrix = Matrix_Create();
	
	matrix.M11 = X;
	matrix.M22 = Y;
	matrix.M33 = Z;
	
	return matrix;
}

Matrix Matrix_CreateFromCamera(Camera* camera)
{
	Matrix matrix = Matrix_Create();
	
	matrix.M11 = (2.0f / camera->resolution.X) * (camera->zoom.X);
	matrix.M14 = 0.0f - (2.0f / (camera->resolution.X / camera->position.X / camera->zoom.X));
	matrix.M22 = -(2.0f / camera->resolution.Y) * (camera->zoom.Y);
	matrix.M24 = 0.0f + (2.0f / (camera->resolution.Y / camera->position.Y / camera->zoom.Y));
	matrix.M33 = 1;
	matrix.M44 = 1;
	
	return matrix;
}
