#pragma once

namespace DUBGUI {

	class ObjectGUI {
	public:

		// Статусы объекта GUI.
		enum class Status { Normal = 0, Hover, Active, Clicked };

		// Направление разбивки текстуры.
		enum class SlicingOrientation { Vertical, Horizontal };

		// Варианты разбики текстуры.
		enum class SlicingType { Single = 1, Double, Triple };

	};

}