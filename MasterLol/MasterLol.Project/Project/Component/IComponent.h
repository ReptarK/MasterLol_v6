#pragma once
#include <vector>

#include "IGameService.h"

class IComponent {

private:
	std::vector<IGameService> mServices;

public:
	// For Menu
	bool mIsActive;
	const char* mTabName;

	IComponent(const char* tabName) {
		mTabName = tabName;
		mIsActive = false;
		mServices = std::vector<IGameService>();
	}

	virtual void RenderMenu() {}
};
