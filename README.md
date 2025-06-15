## Double-Clicker
Aim to entrance your Minecraft  gameplay 

## Feature
- Make your mouse double click for both click (can be customize)
- Setting keybind with their function (Useful for your gameplay, all keys are sereprated)
- Load/Save config load your previous config to save your time

## Supported platform
- Window 10/11 (64-bit processors only)

## Credits
- Credits to https://github.com/xy8q for his/her design in https://github.com/ocornut/imgui/issues/707

## Some notes
```keymap
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
```
- You have to type the exact same as the keys in this keymap in oder to get it worked.
- Lowercase and uppercase is accepted
- The debounce time is brutal make sure you adjust it careful, reccommend to use 2, use max in your own risk:)
- I'm kind of lazy to debug all the error that could possiblity happen make sure to fill all the input.
- Feel free to pull request or fork this repo if you find any improvements.
  
