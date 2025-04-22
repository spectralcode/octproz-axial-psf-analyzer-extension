#ifndef TEST_PEAKFIT_H
#define TEST_PEAKFIT_H

#include <QtTest>
#include "peakfit.h"

class TestPeakFit : public QObject
{
	Q_OBJECT

private slots:
	void testFitPeak();
};

#endif // TEST_PEAKFIT_H