#pragma once

#include <Windows.h>
#include <string>
#include <iostream>
#include <unordered_map>
#include "vars.h"

int getKeyBind(std::string keybind);
void sitimulateClick(bool setting);
void doubleClick(std::atomic<bool>& isActive,int hobar1, int hobar2, int hobar3, int hobar4, int hobar5, int hobar6, int hobar7, int hobar8, int hobar9,int inventoryKey);