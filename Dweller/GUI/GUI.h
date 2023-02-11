#pragma once

namespace DUBGUI {

	// Базовые свойства всех объектов GUI.
	class ObjectGUI {
	public:

		// Статусы объекта GUI.
		enum class Status { Normal = 0, Hover, Active, Clicked };

	};

	// Дополнительные свойства текстурируемых объектов GUI.
	class TexturedObjectGUI : public ObjectGUI {
	public:

		// Направление разбивки текстуры.
		enum class SlicingOrientation { Vertical, Horizontal };

		// Варианты разбики текстуры.
		enum class SlicingType { Single = 1, Double, Triple };

	};

}