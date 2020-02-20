#pragma once
class KeyboardEvent
{
public:
	enum EventType
	{
		Press,
		Release,
		Invalid
	};
	KeyboardEvent(const EventType type, const unsigned char key);
private:
	EventType type;
	char key;
};


