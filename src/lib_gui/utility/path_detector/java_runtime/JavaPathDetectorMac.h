#ifndef JAVA_PATH_DETECTOR_MAC_H
#define JAVA_PATH_DETECTOR_MAC_H

#include "utility/path_detector/java_runtime/JavaPathDetector.h"

class JavaPathDetectorMac
	: public JavaPathDetector
{
public:
	JavaPathDetectorMac(const std::string javaVersion);
	virtual ~JavaPathDetectorMac();

	virtual std::vector<FilePath> getPaths() const;
};

#endif // JAVA_PATH_DETECTOR_MAC_H