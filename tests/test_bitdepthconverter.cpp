#include "test_bitdepthconverter.h"

void TestBitDepthConverter::testConvert8BitData()
{
	BitDepthConverter converter;
	
	//create test data (8-bit)
	const int width = 4;
	const int height = 2;
	unsigned char inputData[width * height];
	
	for (int i = 0; i < width * height; i++) {
		inputData[i] = 50 + i;
	}
	
	bool dataCorrect = false;
	
	//connect to signal to catch results
	connect(&converter, &BitDepthConverter::converted8bitData,
		[&dataCorrect, &inputData, width, height](uchar *output, unsigned int outWidth, unsigned int outHeight) {
			if (outWidth != width || outHeight != height) {
				return;
			}
			
			//verify data - for 8-bit input, output should match input
			dataCorrect = true;
			for (int i = 0; i < width * height; i++) {
				if (output[i] != inputData[i]) {
					dataCorrect = false;
					break;
				}
			}
		});
	
	converter.convertDataTo8bit(inputData, 8, width, height);

	QVERIFY(dataCorrect);
}

void TestBitDepthConverter::testConvert16BitData()
{
	BitDepthConverter converter;
	
	//create test data (16-bit)
	const int width = 4;
	const int height = 2;
	unsigned short inputData[width * height];
	
	for (int i = 0; i < width * height; i++) {
		inputData[i] = 1000 + i * 1000;
	}
	
	bool dataCorrect = false;
	
	//connect to signal to catch results
	connect(&converter, &BitDepthConverter::converted8bitData,
		[&dataCorrect, &inputData, width, height](uchar *output, unsigned int outWidth, unsigned int outHeight) {
			if (outWidth != width || outHeight != height) {
				return;
			}
			
			//for 16-bit to 8-bit conversion, the code uses:
			// float factor = 255 / (qPow(2,bitDepth) - 1);
			float factor = 255.0f / (qPow(2, 16) - 1);
			
			//verify each value is correctly scaled
			dataCorrect = true;
			for (int i = 0; i < width * height; i++) {
				int expected = static_cast<int>(inputData[i] * factor + 0.5f);
				//allow for rounding differences (±1)
				if (qAbs(output[i] - expected) > 1) {
					qDebug() << "Conversion mismatch at" << i << ":" 
						<< "got" << output[i] 
						<< "expected" << expected;
					dataCorrect = false;
					break;
				}
			}
		});
	
	converter.convertDataTo8bit(inputData, 16, width, height);
	
	QVERIFY(dataCorrect);
}

void TestBitDepthConverter::testErrorHandling()
{
	BitDepthConverter converter;
	
	QSignalSpy spy(&converter, &BitDepthConverter::error);
	
	//test with invalid parameters (bitDepth = 0)
	unsigned char dummyData[10] = {0};
	converter.convertDataTo8bit(dummyData, 0, 0, 0);
	
	//error signal should be emitted
	QVERIFY(spy.count() > 0);
}