#pragma once
#include <memory>
namespace Game {
	//�@�q�������p�{���~���z �q�p�x���r���z �{�|�p���� �������������~�y��. 
	class State :public std::enable_shared_from_this<State>
	{
	public:
		using Ptr = std::shared_ptr<State>;
	protected:
		virtual void OnStart() = 0;
		virtual void OnEnd() = 0;
	public:
		void Deactivate();
		void Activate();
		virtual void Update(float dt) = 0;
		//�R�����������~�y�u �}���w�u�� �}�u�~���������� ���� �r�r���t�� �y�|�y �p�r�����}�p���y���u���{�y �����y �{�p�{�y��-���� �����|���r�y����. �O�q�u ���y�����p���y�y ���q���p�q�p�����r�p�������� �r �}�p���y�~�u �������������~�y�z, �~�� �t�|�� �r���������z �u�z �~�u���q�����t�y�}�� �x�~�p���� - �r�������|�~�u�~�� �|�y �����|���r�y�u ���}�u�~�� �������������~�y��.
		virtual bool AwaitsChange() = 0;
	};

}