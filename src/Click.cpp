
#include "click.h"


std::unordered_map<std::string, int> keyCode = {
	{"LEFTMOUSE",VK_LBUTTON},{"LEFTCLICK",VK_LBUTTON},{"RIGHTCLICK",VK_RBUTTON},
	{"MIDLEMOUSE", VK_MBUTTON},
	{"MARCO2", VK_XBUTTON1},
	{"MARCO1", VK_XBUTTON2},
	{"F1", VK_F1}, {"F2", VK_F2}, {"F3", VK_F3}, {"F4", VK_F4}, {"F5", VK_F5},
	{"A", 'A'}, {"B", 'B'}, {"C", 'C'}, {"D", 'D'}, {"E", 'E'}, {"F", 'F'},
	{"G", 'G'}, {"H", 'H'}, {"I", 'I'}, {"J", 'J'}, {"K", 'K'}, {"L", 'L'},
	{"M", 'M'}, {"N", 'N'}, {"O", 'O'}, {"P", 'P'}, {"Q", 'Q'}, {"R", 'R'},
	{"S", 'S'}, {"T", 'T'}, {"U", 'U'}, {"V", 'V'}, {"W", 'W'}, {"X", 'X'},
	{"Y", 'Y'}, {"Z", 'Z'},  {"TAB", VK_TAB}, {"CONTROL",VK_LCONTROL},{"SHIFT",VK_SHIFT},
	{"0", '0'}, {"1", '1'}, {"2", '2'}, {"3", '3'}, {"4", '4'}, {"5", '5'},
	{"6", '6'}, {"7", '7'}, {"8", '8'}, {"9", '9'},
	{"SPACE", VK_SPACE}, {"ENTER", VK_RETURN}
};

int getKeyBind(std::string keybind)
{
	for (auto& c : keybind)
	{
		c = toupper(c);
	}
	auto keySet = keyCode.find(keybind);
	if (keySet != keyCode.end())
	{
		return keySet->second;
	}
	return 0;

}
// i have to think again about my c++ knowledge after done this
void sitimulateClick(bool setting)
{
	INPUT input = { 0 };
	if (leftDebounceClick == 2 && setting)
	{
		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		SendInput(1, &input, sizeof(input));

		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
		SendInput(1, &input, sizeof(input));

		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		SendInput(1, &input, sizeof(input));

		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
		SendInput(1, &input, sizeof(input));
	}

	if (rightDebounceClick == 2 && !setting)
	{
		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
		SendInput(1, &input, sizeof(input));

		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
		SendInput(1, &input, sizeof(input));

		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
		SendInput(1, &input, sizeof(input));

		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
		SendInput(1, &input, sizeof(input));
	}

	if (leftDebounceClick == 3 && setting)
	{
		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		SendInput(1, &input, sizeof(input));

		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
		SendInput(1, &input, sizeof(input));

		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		SendInput(1, &input, sizeof(input));

		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
		SendInput(1, &input, sizeof(input));

		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		SendInput(1, &input, sizeof(input));

		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
		SendInput(1, &input, sizeof(input));
	}

	if (rightDebounceClick == 3 && !setting)
	{
		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
		SendInput(1, &input, sizeof(input));

		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
		SendInput(1, &input, sizeof(input));

		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
		SendInput(1, &input, sizeof(input));

		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
		SendInput(1, &input, sizeof(input));

		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
		SendInput(1, &input, sizeof(input));

		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
		SendInput(1, &input, sizeof(input));
	}

	if (leftDebounceClick == 4 && setting)
	{
		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		SendInput(1, &input, sizeof(input));

		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
		SendInput(1, &input, sizeof(input));

		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		SendInput(1, &input, sizeof(input));

		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
		SendInput(1, &input, sizeof(input));

		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		SendInput(1, &input, sizeof(input));

		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
		SendInput(1, &input, sizeof(input));

		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		SendInput(1, &input, sizeof(input));

		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
		SendInput(1, &input, sizeof(input));
	}

	if (rightDebounceClick == 4 && !setting)
	{
		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
		SendInput(1, &input, sizeof(input));

		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
		SendInput(1, &input, sizeof(input));

		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
		SendInput(1, &input, sizeof(input));

		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
		SendInput(1, &input, sizeof(input));

		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
		SendInput(1, &input, sizeof(input));

		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
		SendInput(1, &input, sizeof(input));

		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
		SendInput(1, &input, sizeof(input));

		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
		SendInput(1, &input, sizeof(input));
	}
}



// i think hardcode is good if minecraft default inventory is 9 slots
// hardcode provide better performance in this instead of for loop
void doubleClick( std::atomic<bool>& isActive,int hobar1,int hobar2,int hobar3,int hobar4,int hobar5,int hobar6,int hobar7,int hobar8,int hobar9,int inventoryKey)
{
	if (isLeft)
	{
		while (isActive)
		{
			if (GetAsyncKeyState(hobar1) & 0x8000)
			{
				if (soption1 == 0)
				{
					isToggle = true;
				}

				if (soption1 == 1)
				{
					isToggle = true;
				}

				if (soption1 == 2)
				{
					isToggle = false;
				}
			}

			if (GetAsyncKeyState(hobar2) & 0x8000)
			{
				if (soption2 == 0)
				{
					isToggle = true;
				}

				if (soption2 == 1)
				{
					isToggle = true;
				}

				if (soption2 == 2)
				{
					isToggle = false;
				}
			}

			if (GetAsyncKeyState(hobar3) & 0x8000)
			{
				if (soption3 == 0)
				{
					isToggle = true;
				}

				if (soption3 == 1)
				{
					isToggle = true;
				}

				if (soption3 == 2)
				{
					isToggle = false;
				}
			}

			if (GetAsyncKeyState(hobar4) & 0x8000)
			{
				if (soption4 == 0)
				{
					isToggle = true;
				}

				if (soption4 == 1)
				{
					isToggle = true;
				}

				if (soption4 == 2)
				{
					isToggle = false;
				}
			}

			if (GetAsyncKeyState(hobar5) & 0x8000)
			{
				if (soption5 == 0)
				{
					isToggle = true;
				}

				if (soption5 == 1)
				{
					isToggle = true;
				}

				if (soption5 == 2)
				{
					isToggle = false;
				}
			}

			if (GetAsyncKeyState(hobar6) & 0x8000)
			{
				if (soption6 == 0)
				{
					isToggle = true;
				}

				if (soption6 == 1)
				{
					isToggle = true;
				}

				if (soption6 == 2)
				{
					isToggle = false;
				}
			}

			if (GetAsyncKeyState(hobar7) & 0x8000)
			{
				if (soption7 == 0)
				{
					isToggle = true;
				}

				if (soption7 == 1)
				{
					isToggle = true;
				}

				if (soption7 == 2)
				{
					isToggle = false;
				}
			}

			if (GetAsyncKeyState(hobar8) & 0x8000)
			{
				if (soption8 == 0)
				{
					isToggle = true;
				}

				if (soption8 == 1)
				{
					isToggle = true;
				}

				if (soption8 == 2)
				{
					isToggle = false;
				}
			}

			if (GetAsyncKeyState(hobar9) & 0x8000)
			{
				if (soption9 == 0)
				{
					isToggle = true;
				}

				if (soption9 == 1)
				{
					isToggle = true;
				}

				if (soption9 == 2)
				{
					isToggle = false;
				}
			}

			if (GetAsyncKeyState(inventoryKey) & 0x8000)
			{
				isToggle = false;
			}

			if (GetAsyncKeyState('L') & 0x8000)
			{
				isToggle = !isToggle;
				Sleep(500);
			}
			if (isToggle && GetAsyncKeyState(VK_LBUTTON) & 0x8000)
			{
				sitimulateClick(true);
				Sleep(1);
			}
			Sleep(10);
		}
	}

	if (isRight)
	{
		while (isActive)
		{
			if (GetAsyncKeyState(hobar1) & 0x8000)
			{
				if (soption1 == 0)
				{
					isToggle = true;
				}

				if (soption1 == 1)
				{
					isToggle = true;
				}

				if (soption1 == 2)
				{
					isToggle = false;
				}
			}

			if (GetAsyncKeyState(hobar2) & 0x8000)
			{
				if (soption2 == 0)
				{
					isToggle = true;
				}

				if (soption2 == 1)
				{
					isToggle = true;
				}

				if (soption2 == 2)
				{
					isToggle = false;
				}
			}

			if (GetAsyncKeyState(hobar3) & 0x8000)
			{
				if (soption3 == 0)
				{
					isToggle = true;
				}

				if (soption3 == 1)
				{
					isToggle = true;
				}

				if (soption3 == 2)
				{
					isToggle = false;
				}
			}

			if (GetAsyncKeyState(hobar4) & 0x8000)
			{
				if (soption4 == 0)
				{
					isToggle = true;
				}

				if (soption4 == 1)
				{
					isToggle = true;
				}

				if (soption4 == 2)
				{
					isToggle = false;
				}
			}

			if (GetAsyncKeyState(hobar5) & 0x8000)
			{
				if (soption5 == 0)
				{
					isToggle = true;
				}

				if (soption5 == 1)
				{
					isToggle = true;
				}

				if (soption5 == 2)
				{
					isToggle = false;
				}
			}

			if (GetAsyncKeyState(hobar6) & 0x8000)
			{
				if (soption6 == 0)
				{
					isToggle = true;
				}

				if (soption6 == 1)
				{
					isToggle = true;
				}

				if (soption6 == 2)
				{
					isToggle = false;
				}
			}

			if (GetAsyncKeyState(hobar7) & 0x8000)
			{
				if (soption7 == 0)
				{
					isToggle = true;
				}

				if (soption7 == 1)
				{
					isToggle = true;
				}

				if (soption7 == 2)
				{
					isToggle = false;
				}
			}

			if (GetAsyncKeyState(hobar8) & 0x8000)
			{
				if (soption8 == 0)
				{
					isToggle = true;
				}

				if (soption8 == 1)
				{
					isToggle = true;
				}

				if (soption8 == 2)
				{
					isToggle = false;
				}
			}

			if (GetAsyncKeyState(hobar9) & 0x8000)
			{
				if (soption9 == 0)
				{
					isToggle = true;
				}

				if (soption9 == 1)
				{
					isToggle = true;
				}

				if (soption9 == 2)
				{
					isToggle = false;
				}
			}

			if (GetAsyncKeyState(inventoryKey) & 0x8000)
			{
				isToggle = false;
			}

			if (GetAsyncKeyState('L') & 0x8000)
			{
				isToggle = !isToggle;
				Sleep(500);
			}

			if (isToggle && GetAsyncKeyState(VK_RBUTTON) & 0x8000)
			{
				sitimulateClick(false);
				Sleep(1);
			}
			Sleep(10);
		}
	}

	if (isBoth)
	{
		while (isActive)
		{
			if (GetAsyncKeyState(hobar1) & 0x8000)
			{
				if (soption1 == 0)
				{
					isToggleLeft = true;
					isToggleRight = false;
				}

				if (soption1 == 1)
				{
					isToggleLeft = false;
					isToggleRight = true;
				}

				if (soption1 == 2)
				{
					isToggleLeft = false;
					isToggleRight = false;
				}
			}

			if (GetAsyncKeyState(hobar2) & 0x8000)
			{
				if (soption2 == 0)
				{
					isToggleLeft = true;
					isToggleRight = false;
				}

				if (soption2 == 1)
				{
					isToggleLeft = false;
					isToggleRight = true;
				}

				if (soption2 == 2)
				{
					isToggleLeft = false;
					isToggleRight = false;
				}
			}

			if (GetAsyncKeyState(hobar3) & 0x8000)
			{
				if (soption3 == 0)
				{
					isToggleLeft = true;
					isToggleRight = false;
				}

				if (soption3 == 1)
				{
					isToggleLeft = false;
					isToggleRight = true;
				}

				if (soption3 == 2)
				{
					isToggleLeft = false;
					isToggleRight = false;
				}
			}

			if (GetAsyncKeyState(hobar4) & 0x8000)
			{
				if (soption4== 0)
				{
					isToggleLeft = true;
					isToggleRight = false;
				}

				if (soption4 == 1)
				{
					isToggleLeft = false;
					isToggleRight = true;
				}

				if (soption4 == 2)
				{
					isToggleLeft = false;
					isToggleRight = false;
				}
			}

			if (GetAsyncKeyState(hobar5) & 0x8000)
			{
				if (soption5 == 0)
				{
					isToggleLeft = true;
					isToggleRight = false;
				}

				if (soption5 == 1)
				{
					isToggleLeft = false;
					isToggleRight = true;
				}

				if (soption5 == 2)
				{
					isToggleLeft = false;
					isToggleRight = false;
				}
			}

			if (GetAsyncKeyState(hobar6) & 0x8000)
			{
				if (soption6== 0)
				{
					isToggleLeft = true;
					isToggleRight = false;
				}

				if (soption6 == 1)
				{
					isToggleLeft = false;
					isToggleRight = true;
				}

				if (soption6 == 2)
				{
					isToggleLeft = false;
					isToggleRight = false;
				}
			}

			if (GetAsyncKeyState(hobar7) & 0x8000)
			{
				if (soption7 == 0)
				{
					isToggleLeft = true;
					isToggleRight = false;
				}

				if (soption7 == 1)
				{
					isToggleLeft = false;
					isToggleRight = true;
				}

				if (soption7 == 2)
				{
					isToggleLeft = false;
					isToggleRight = false;
				}
			}

			if (GetAsyncKeyState(hobar8) & 0x8000)
			{
				if (soption8 == 0)
				{
					isToggleLeft = true;
					isToggleRight = false;
				}

				if (soption8 == 1)
				{
					isToggleLeft = false;
					isToggleRight = true;
				}

				if (soption8 == 2)
				{
					isToggleLeft = false;
					isToggleRight = false;
				}
			}

			if (GetAsyncKeyState(hobar9) & 0x8000)
			{
				if (soption9 == 0)
				{
					isToggleLeft = true;
					isToggleRight = false;
				}

				if (soption9 == 1)
				{
					isToggleLeft = false;
					isToggleRight = true;
				}

				if (soption9 == 2)
				{
					isToggleLeft = false;
					isToggleRight = false;
				}
			}

			if (GetAsyncKeyState(inventoryKey) & 0x8000)
			{
				isToggleLeft = false;
				isToggleRight = false;
			}

			if (GetAsyncKeyState('L') & 0x8000)
			{
				isToggleLeft = !isToggleLeft;
				isToggleRight = !isToggleRight;
				Sleep(500);
			}

			if (isToggleLeft && GetAsyncKeyState(VK_LBUTTON) & 0x8000)
			{
				sitimulateClick(true);
				Sleep(1);
			}

			if (isToggleRight && GetAsyncKeyState(VK_RBUTTON) & 0x8000)
			{
				sitimulateClick(false);
				Sleep(1);
			}
			Sleep(10);
			

		}
		
		
	}
}
