#include "Data.h"

//---> LayoutAnswer
//=======================================================================================================================//

//������� ����������.
void LayoutAnswer::Clear() {
	from.clear();
	to.clear();
}

//�������� �� �������.
bool LayoutAnswer::Empty() {
	if (from == "" && to == "") return true;
	return false;
}

//����� ����� ��������, ���� ��� �� ������.
void LayoutAnswer::Assign(LayoutAnswer Value) {
	if (!Value.Empty()) {
		from = Value.from;
		to = Value.to;
	}
}