
#include <windows.h>
#include "ConsoleOutputHandler.h"

ConsoleOutputHandler::ConsoleOutputHandler()
{
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
}

ConsoleOutputHandler::~ConsoleOutputHandler()
{
//	CloseHandle(hOut);
//	delete hOut;
	hOut = NULL;
}

void ConsoleOutputHandler::opSetTextColor(ETextColor Color)
{
	WORD WINColor;

	switch(Color)
	{
	case TextColor_INTENSIVE_RED:
		WINColor = FOREGROUND_RED | FOREGROUND_INTENSITY;
		break;
	case TextColor_INTENSIVE_GREEN:
		WINColor = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		break;
	case TextColor_INTENSIVE_YELLOW:
		WINColor = FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;
		break;
	case TextColor_INTENSIVE_BLUE:
		WINColor = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		break;
	case TextColor_DEFAULT:
		WINColor = 7;
		break;
	default:
		WINColor = 0;
		break;
	}

	SetConsoleTextAttribute(hOut, WINColor);
}

ETextColor ConsoleOutputHandler::opGetTextColor()
{
	PCONSOLE_SCREEN_BUFFER_INFO info = new _CONSOLE_SCREEN_BUFFER_INFO;
	ETextColor retVal = TextColor_UNSUPPORTED;
	GetConsoleScreenBufferInfo(hOut, info);
	

	switch(info->wAttributes)
	{
	case (FOREGROUND_RED | FOREGROUND_INTENSITY):
		retVal = TextColor_INTENSIVE_RED;
		break;
	case (FOREGROUND_GREEN | FOREGROUND_INTENSITY):
		retVal = TextColor_INTENSIVE_GREEN;
		break;
	case (FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY):
		retVal = TextColor_INTENSIVE_BLUE;
		break;
	case 7:
		retVal = TextColor_DEFAULT;
		break;
	default:
		retVal = TextColor_UNSUPPORTED;
		break;
	}

	delete info;
	info = NULL;
	return retVal;
}