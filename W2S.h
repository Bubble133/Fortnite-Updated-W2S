{
	float FieldOfView;
	Vector3 Rotation;
	Vector3 Location;
};

typedef          __int64 ll;
typedef ll              int64;

Camera GetCamera(int64 a1)
{
	Camera FGC_Camera;
	int64 v1;
	int64 v6;
	int64 v7;
	int64 v8;

	v1 = driver.read<int64>(Localplayer + 0xd0);
	int64 v9 = driver.read<int64>(v1 + 0x10); // 0x10

	FGC_Camera.FieldOfView = 80.0f / (driver.read<double>(v9 + 0x680) / 1.19f); // 0x600

	FGC_Camera.Rotation.x = driver.read<double>(v9 + 0x7D0);
	FGC_Camera.Rotation.y = driver.read<double>(a1 + 0x148);

	uint64_t FGC_Pointerloc = driver.read<uint64_t>(Uworld + 0x100);
	FGC_Camera.Location = driver.read<Vector3>(FGC_Pointerloc);

	return FGC_Camera;
}


Vector3 ProjectWorldToScreen(Vector3 WorldLocation)
{
	Camera vCamera = GetCamera(Rootcomp);
	vCamera.Rotation.x = (asin(vCamera.Rotation.x)) * (180.0 / M_PI);


	D3DMATRIX tempMatrix = Matrix(vCamera.Rotation);

	Vector3 vAxisX = Vector3(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
	Vector3 vAxisY = Vector3(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
	Vector3 vAxisZ = Vector3(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);

	Vector3 vDelta = WorldLocation - vCamera.Location;
	Vector3 vTransformed = Vector3(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));

	if (vTransformed.z < 1.f)
		vTransformed.z = 1.f;

	return Vector3((Width / 2.0f) + vTransformed.x * (((Width / 2.0f) / tanf(vCamera.FieldOfView * (float)M_PI / 360.f))) / vTransformed.z, (Height / 2.0f) - vTransformed.y * (((Width / 2.0f) / tanf(vCamera.FieldOfView * (float)M_PI / 360.f))) / vTransformed.z, 0);
}
