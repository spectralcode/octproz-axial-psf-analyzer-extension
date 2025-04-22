QT += core gui widgets testlib
TARGET = axialpsf-analyzer-tests
TEMPLATE = app

# Path to plugin source
SRCDIR = $$shell_path($$PWD/../src)

# Add Eigen include path (adjust as needed for your setup)
INCLUDEPATH += \
	$$SRCDIR \
	$$PWD/../src/thirdparty/eigen_3_4_0 \
	$$PWD/../src/thirdparty/eigen_3_4_0/unsupported

SOURCES += \
	main.cpp \
	test_bitdepthconverter.cpp \
	test_peakfit.cpp \
	test_gaussfit.cpp \
	test_gaussfunction.cpp \
	$$SRCDIR/bitdepthconverter.cpp \
	$$SRCDIR/peakfit.cpp \
	$$SRCDIR/gaussfit.cpp \
	$$SRCDIR/gaussfunction.cpp

HEADERS += \
	test_bitdepthconverter.h \
	test_peakfit.h \
	test_gaussfit.h \
	test_gaussfunction.h \
	$$SRCDIR/bitdepthconverter.h \
	$$SRCDIR/peakfit.h \
	$$SRCDIR/gaussfit.h \
	$$SRCDIR/gaussfunction.h \
	$$SRCDIR/optimizationfunctor.h \
	$$SRCDIR/peakdetectorparameters.h \
	$$SRCDIR/axialpsfanalyzerparameters.h