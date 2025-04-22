#include <QtTest>
#include <QApplication>
#include "test_bitdepthconverter.h"
#include "test_peakfit.h"
#include "test_gaussfit.h"
#include "test_gaussfunction.h"

Q_DECLARE_METATYPE(uchar*)

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	qRegisterMetaType<uchar*>("uchar*");
	
	int status = 0;
	
	{
		TestBitDepthConverter tc;
		status |= QTest::qExec(&tc, argc, argv);
	}
	
	{
		TestPeakFit tc;
		status |= QTest::qExec(&tc, argc, argv);
	}
	
	{
		TestGaussFit tc;
		status |= QTest::qExec(&tc, argc, argv);
	}
	
	{
		TestGaussFunction tc;
		status |= QTest::qExec(&tc, argc, argv);
	}
	
	return status;
}