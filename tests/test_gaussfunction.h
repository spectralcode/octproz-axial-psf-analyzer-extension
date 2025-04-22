#ifndef TEST_GAUSSFUNCTION_H
#define TEST_GAUSSFUNCTION_H

#include <QtTest>
#include "gaussfunction.h"

class TestGaussFunction : public QObject
{
	Q_OBJECT

private slots:
	void testConstructor();
	void testOperator();
	void testGettersAndSetters();
	void testFWHM();
};

#endif // TEST_GAUSSFUNCTION_H