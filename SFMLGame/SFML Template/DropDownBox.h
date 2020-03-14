#pragma once
#include<vector>
#include<iostream>
#include "Button.h"
class DropDownBox
{
public:
		std::vector<Button*> options;
private:

	int currentSelectedIndex;
};

