#ifndef TEST_GAUSSFIT_H
#define TEST_GAUSSFIT_H

#include <QtTest>
#include "gaussfit.h"

class TestGaussFit : public QObject
{
	Q_OBJECT

private slots:
	void testConstructor();
	void testFit();
	void testSetInitialGuesses();
	void testGetParams();
};

#endif // TEST_GAUSSFIT_H