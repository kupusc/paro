#ifndef ConsoleOutputHandler_H 
#define ConsoleOutputHandler_H

enum ETextColor 
{
	TextColor_INTENSIVE_RED     = 1,
	TextColor_INTENSIVE_GREEN   = 2,
	TextColor_DEFAULT           = 3,
	TextColor_UNSUPPORTED       = 4,
	TextColor_INTENSIVE_YELLOW  = 5,
	TextColor_INTENSIVE_BLUE    = 6
};

class ConsoleOutputHandler
{
private:
	void* hOut;
	ETextColor lastColor;

public:
	ConsoleOutputHandler();
	~ConsoleOutputHandler();
	void opSetTextColor(ETextColor Color);
	ETextColor opGetTextColor();
};
#endif
