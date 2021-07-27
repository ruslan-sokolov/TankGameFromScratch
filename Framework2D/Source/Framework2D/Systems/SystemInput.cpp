#include "PCH_Framework.h"
#include "SystemInput.h"

namespace Framework2D {

	// Static
	std::unordered_map<int, std::vector<SystemInput::InputCbFn>> SystemInput::KeyPressedCbs;
	std::unordered_map<int, std::vector<SystemInput::InputCbFn>> SystemInput::KeyReleasedCbs;

}
