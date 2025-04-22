#ifndef TEST_BITDEPTHCONVERTER_H
#define TEST_BITDEPTHCONVERTER_H

#include <QtTest>
#include "bitdepthconverter.h"

class TestBitDepthConverter : public QObject
{
	Q_OBJECT

private slots:
	void testConvert8BitData();
	void testConvert16BitData();
	void testErrorHandling();
};

#endif // TEST_BITDEPTHCONVERTER_H