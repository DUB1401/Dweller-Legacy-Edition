#pragma once

#include "../EvolvGen.h"

// ����� �� ����������� ����.
struct LayoutAnswer {
	//������ ������ �����.
	std::string from;
	//�� ����� ���� �������������.
	std::string to;
	//������� ����������.
	void Clear();
	//�������� �� �������.
	bool Empty();
	//����� ����� ��������, ���� ��� �� ������.
	void Assign(LayoutAnswer Value);
};