#include "test_gaussfunction.h"

void TestGaussFunction::testConstructor()
{
	// Test constructor with parameters
	const double a = 10.0;
	const double k = 2.0;
	const double m = 5.0;
	const double s = 1.5;
	
	GaussFunction gaussFunction(a, k, m, s);
	
	// Verify the parameters were set correctly
	QCOMPARE(gaussFunction.getA(), a);
	QCOMPARE(gaussFunction.getK(), k);
	QCOMPARE(gaussFunction.getM(), m);
	QCOMPARE(gaussFunction.getS(), s);
}

void TestGaussFunction::testOperator()
{
	// Test function call operator
	GaussFunction gaussFunction(10.0, 2.0, 5.0, 1.5);
	
	// At x = mean, function should return amplitude
	QCOMPARE(gaussFunction(5.0), 10.0);
	
	// At x = infinity, function should approach k
	QVERIFY(qAbs(gaussFunction(500.0) - 2.0) < 0.01);
	
	// Symmetric property - values should be the same at equal distances from mean
	QCOMPARE(gaussFunction(4.0), gaussFunction(6.0));
	
	// Test with known function values (hand-calculated)
	const double expectedAtX3 = 2.0 + (10.0 - 2.0) * qExp(-4.0 / (2.0 * 1.5 * 1.5));
	QVERIFY(qAbs(gaussFunction(3.0) - expectedAtX3) < 0.0001);
}

void TestGaussFunction::testGettersAndSetters()
{
	// Create with initial values
	GaussFunction gaussFunction(10.0, 2.0, 5.0, 1.5);
	
	// Test getters
	QCOMPARE(gaussFunction.getA(), 10.0);
	QCOMPARE(gaussFunction.getK(), 2.0);
	QCOMPARE(gaussFunction.getM(), 5.0);
	QCOMPARE(gaussFunction.getS(), 1.5);
	
	// Test setters
	gaussFunction.setA(15.0);
	QCOMPARE(gaussFunction.getA(), 15.0);
	
	gaussFunction.setK(3.0);
	QCOMPARE(gaussFunction.getK(), 3.0);
	
	gaussFunction.setM(7.0);
	QCOMPARE(gaussFunction.getM(), 7.0);
	
	gaussFunction.setS(2.0);
	QCOMPARE(gaussFunction.getS(), 2.0);
	
	// Verify that the function value changes after parameters change
	// For example, at x = mean, function should return amplitude
	QCOMPARE(gaussFunction(7.0), 15.0);
}

void TestGaussFunction::testFWHM()
{
	// Create Gaussian function
	// Start with standard deviation = 1.0
	GaussFunction gaussFunction(10.0, 2.0, 5.0, 1.0);
	
	// FWHM should be 2.3548 * sigma
	const double expectedFWHM = 2.354820045;
	
	// Test FWHM calculation
	QVERIFY(qAbs(gaussFunction.getFWHM() - expectedFWHM) < 0.0001);
	
	// Change s and test again
	gaussFunction.setS(2.0);
	QVERIFY(qAbs(gaussFunction.getFWHM() - 2.0 * expectedFWHM) < 0.0001);
	
	// Test with negative s (should use absolute value)
	gaussFunction.setS(-3.0);
	QVERIFY(qAbs(gaussFunction.getFWHM() - 3.0 * expectedFWHM) < 0.0001);
}