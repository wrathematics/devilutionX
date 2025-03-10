#pragma once

#ifdef VIRTUAL_GAMEPAD

#include <functional>

#include "controls/controller_buttons.h"
#include "engine/circle.hpp"
#include "engine/point.hpp"
#include "engine/rectangle.hpp"

namespace devilution {

struct VirtualDirectionPad {
	Circle area;
	Point position;
	bool isUpPressed;
	bool isDownPressed;
	bool isLeftPressed;
	bool isRightPressed;

	VirtualDirectionPad()
	    : area({ { 0, 0 }, 0 })
	    , position({ 0, 0 })
	    , isUpPressed(false)
	    , isDownPressed(false)
	    , isLeftPressed(false)
	    , isRightPressed(false)
	{
	}

	void UpdatePosition(Point touchCoordinates);
	void Deactivate();
};

struct VirtualButton {
	bool isHeld;
	bool didStateChange;
	std::function<bool()> isUsable;

	VirtualButton()
	    : isHeld(false)
	    , didStateChange(false)
	    , isUsable([]() { return true; })
	{
	}

	virtual bool Contains(Point point) = 0;
	void Deactivate();
};

struct VirtualMenuButton : VirtualButton {
	Rectangle area;

	VirtualMenuButton()
	    : area({ { 0, 0 }, { 0, 0 } })
	{
	}

	bool Contains(Point point) override
	{
		return area.Contains(point);
	}
};

struct VirtualPadButton : VirtualButton {
	Circle area;

	VirtualPadButton()
	    : area({ { 0, 0 }, 0 })
	{
	}

	bool Contains(Point point) override
	{
		return area.Contains(point);
	}
};

struct VirtualMenuPanel {
	VirtualMenuButton charButton;
	VirtualMenuButton questsButton;
	VirtualMenuButton inventoryButton;
	VirtualMenuButton mapButton;
	Rectangle area;

	VirtualMenuPanel()
	    : area({ { 0, 0 }, { 0, 0 } })
	{
	}

	void Deactivate();
};

struct VirtualGamepad {
	VirtualMenuPanel menuPanel;
	VirtualDirectionPad directionPad;
	VirtualPadButton standButton;

	VirtualPadButton primaryActionButton;
	VirtualPadButton secondaryActionButton;
	VirtualPadButton spellActionButton;
	VirtualPadButton cancelButton;

	VirtualPadButton healthButton;
	VirtualPadButton manaButton;

	bool isActive;

	VirtualGamepad()
	{
	}

	void Deactivate();
};

void InitializeVirtualGamepad();
void ActivateVirtualGamepad();
void DeactivateVirtualGamepad();

extern VirtualGamepad VirtualGamepadState;

} // namespace devilution

#endif
