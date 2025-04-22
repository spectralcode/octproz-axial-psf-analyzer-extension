#include "test_peakfit.h"
#include <QtMath>

void TestPeakFit::testFitPeak()
{
	PeakFit peakFit;
	
	const int expectedPeakPosition = 500;
	const double sigma = 0.950;
	const double expectedFWHM = 2*sqrt(2*qLn(2)) * sigma;
	
	//create Gaussian test data
	//f(x) = k + (a - k) * exp(-((x - m)²/(2*s²)))
	const unsigned int width = 1024;
	const unsigned int height = 1;
	unsigned char* inputData = new unsigned char[width * height];
	
	const double k = 0.0;
	const double a = 150.0;
	const double m = expectedPeakPosition;
	const double s = sigma;
	
	for (unsigned int i = 0; i < width; i++) {
		double x = i;
		double value = k + (a - k) * qExp(-((x - m) * (x - m)) / (2.0 * s * s));
		inputData[i] = static_cast<unsigned char>(qBound(0, static_cast<int>(value), 255));
	}
	
	//set ROI to cover the entire frame
	AxialPsfAnalyzerParameters params;
	params.roi = QRect(0, 0, width, height);
	peakFit.setParams(params);
	
	//set up signal spies to capture the required signals
	QSignalSpy peakPositionSpy(&peakFit, &PeakFit::peakPositionFound);
	QSignalSpy fwhmSpy(&peakFit, &PeakFit::fwhmCalculated);
	
	peakFit.fitPeak(inputData, 8, width, height);

	delete[] inputData;
	
	//verify signals were emitted
	QCOMPARE(peakPositionSpy.count(), 1);
	QCOMPARE(fwhmSpy.count(), 1);
	

	double peakPosition = peakPositionSpy.at(0).at(0).toDouble();
	double fwhm = fwhmSpy.at(0).at(0).toDouble();
	qDebug() << "Actual peak position:" << peakPosition;
	qDebug() << "Expected peak position:" << expectedPeakPosition;
	qDebug() << "Actual FWHM:" << fwhm;
	qDebug() << "Expected FWHM:" << expectedFWHM;
	
	//verify the peak position and FWHM are within acceptable tolerance
	QVERIFY(qAbs(peakPosition - expectedPeakPosition) < 5.0);
	QVERIFY(qAbs(fwhm - expectedFWHM) < 0.5);
}