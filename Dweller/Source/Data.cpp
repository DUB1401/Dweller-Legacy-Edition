#include "Data.h"

//---> LayoutAnswer
//========================================================================================================================//

// Очистка контейнера.
void LayoutAnswer::Clear() {
	from.clear();
	to.clear();
}

// Проверка на пустоту.
bool LayoutAnswer::Empty() {
	if (from == "" && to == "") return true;
	return false;
}

// Задаёт новое значение, если оно не пустое.
void LayoutAnswer::Assign(LayoutAnswer Value) {
	if (!Value.Empty()) {
		from = Value.from;
		to = Value.to;
	}
}