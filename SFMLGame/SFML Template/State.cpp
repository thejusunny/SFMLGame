#include "State.h"



const bool State::GetQuit() const
{

	return this->quit;
}

void State::EndGame()
{
	quit = true;
}
