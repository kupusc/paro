#include "ConsoleOutputHandler.h"
#include <cstdio>

ConsoleOutputHandler::ConsoleOutputHandler()
{
}

ConsoleOutputHandler::~ConsoleOutputHandler()
{
}

void ConsoleOutputHandler::opSetTextColor(ETextColor Color)
{
    switch(Color)
    {
    case TextColor_INTENSIVE_RED:
        printf("\033[1;31m ");
        break;
    case TextColor_INTENSIVE_GREEN:
        printf("\033[1;32m ");
        break;
    case TextColor_INTENSIVE_BLUE:
        printf("\033[1;34m ");
        break;
    case TextColor_DEFAULT:
        printf("\033[0m ");
        break;
    default:
        printf("\033[0m ");
        break;
    }
    lastColor = Color;
}

ETextColor ConsoleOutputHandler::opGetTextColor()
{
    return TextColor_DEFAULT;
}
