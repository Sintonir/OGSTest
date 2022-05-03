#pragma once
namespace Game {
	//�I�~���u�����u�z�� �t�|�� �r���p���u�~�y��, �������q�� �r RotateState �}���w�~�� �q���|�� �x�p�t�p���� �r���p���u�~�y�u ���p�x�~���}�y �����������q�p�}�y.
	class RotateInterface
	{
	public:
		virtual bool IsRotateActive() = 0;
		virtual void Start() = 0;
		virtual void Stop() = 0;
	};
}