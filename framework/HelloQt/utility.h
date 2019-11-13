#ifndef HELLOQT_UTILITY_H
#define HELLOQT_UTILITY_H

#include "qelapsedtimer.h"
#include "qstring.h"
#include <iostream>

class ScopedTimer
{
public:
	ScopedTimer(QString text) : m_text(text.toStdString()) { m_timer.start(); };
	~ScopedTimer() { std::cout << m_text << "  " <<  (m_timer.nsecsElapsed()/(1000000)) << "ms" << std::endl; }

private:
	std::string m_text;
	QElapsedTimer m_timer;
};

#define _TIMER(x) ScopedTimer __scopedTimer(QString("[Timer @%1@ LINE%2] %3").arg(__FUNCTION__).arg(__LINE__).arg((x)));

#endif //!HELLOQT_UTILITY_H
