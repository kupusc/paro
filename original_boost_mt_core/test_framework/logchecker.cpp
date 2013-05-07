#include "logchecker.h"
#include "testif.h"

LogCheckerBase::LogCheckerBase()
{
    //ctor
}

LogCheckerBase::~LogCheckerBase()
{
    //dtor
}

LogCheckerBase::TMatches& LogCheckerBase::getMatches()
{
	return m_matches;
}
