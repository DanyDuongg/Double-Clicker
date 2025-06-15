#pragma once
#include <iostream>
#include <string>
#include <atomic>
#include <thread>
extern std::atomic<bool> isActive;
extern std::atomic<bool> isLeft;
extern std::atomic<bool> isRight;
extern std::atomic<bool> isBoth;
extern std::atomic<bool> isToggle;
extern std::atomic<bool> isToggleLeft;
extern std::atomic<bool> isToggleRight;
extern std::atomic<int> leftDebounceClick;
extern std::atomic<int> rightDebounceClick;


extern int hobar1;
extern int hobar2;
extern int hobar3;
extern int hobar4;
extern int hobar5;
extern int hobar6;
extern int hobar7;
extern int hobar8;
extern int hobar9;

extern int soption1;
extern int soption2;
extern int soption3;
extern int soption4;
extern int soption5;
extern int soption6;
extern int soption7;
extern int soption8;
extern int soption9;

extern int inventoryKey;
