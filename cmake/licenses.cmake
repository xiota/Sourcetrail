# Generates the licenses.h file
# For adding a new 3rd Party License add the License File to the 3rd Party License Folder
# and a new AddLicense Line in below

# These global variables are referenced in 'licenses.h.in':
set(LICENSES "")
set(LICENSE_ARRAY "")
set(LICENSEFOLDER "${CMAKE_SOURCE_DIR}/bin/app/data/license/3rd_party_licenses")

function(ReadLicense licenseFile licenseVariable)
    file(READ ${licenseFile} tempVariable)
    STRING(REGEX REPLACE "\"" "\\\\\"" tempVariable "${tempVariable}")
    STRING(REGEX REPLACE "\n" "\\\\n\"\n\t\"" tempVariable "${tempVariable}")
    set(var "\n\nstatic const char *${licenseVariable}=\n\t\"")
    set(LICENSES "${LICENSES}${var}${tempVariable}\"\;" PARENT_SCOPE)
endfunction(ReadLicense)

function(AddLicense softwareName softwareVersion softwareURL licenseFile)
        ReadLicense(${licenseFile} ${softwareName}_license)
        set(LICENSES ${LICENSES} PARENT_SCOPE)
        set(LICENSE_ARRAY "${LICENSE_ARRAY}\n\tLicenseInfo(\"${softwareName}\", \"${softwareVersion}\", \"${softwareURL}\", ${softwareName}_license)," PARENT_SCOPE)
endfunction(AddLicense)

function(configureLicenseFile outputFile)
	ReadLicense(${CMAKE_SOURCE_DIR}/LICENSE.txt Sourcetrail_license)
	set(LICENSE_APP "LicenseInfo(\"Sourcetrail\", \"${Sourcetrail_VERSION}\", \"https://github.com/petermost/Sourcetrail\", Sourcetrail_license)")

	AddLicense("Boost" "" "http://www.boost.org" "${LICENSEFOLDER}/license_boost.txt")
	AddLicense("catch" "" "https://github.com/catchorg/Catch2" "${LICENSEFOLDER}/license_catch.txt")
	AddLicense("Clang" "" "http://clang.llvm.org/" "${LICENSEFOLDER}/license_clang.txt")
	AddLicense("CppSQLite" "" "http://www.codeproject.com/Articles/6343/CppSQLite-C-Wrapper-for-SQLite" "${LICENSEFOLDER}/license_cpp_sqlite.txt")
	AddLicense("EclipseJDT" "" "https://github.com/eclipse/eclipse.jdt.core" "${LICENSEFOLDER}/license_eclipse.txt")
	AddLicense("Gradle" "" "https://github.com/gradle/gradle" "${LICENSEFOLDER}/license_gradle.txt")
	AddLicense("OpenSSL" "" "https://www.openssl.org/" "${LICENSEFOLDER}/license_openssl.txt")
	AddLicense("Qt" "" "http://qt.io" "${LICENSEFOLDER}/license_qt.txt")
	AddLicense("TinyXML" "" "https://sourceforge.net/projects/tinyxml/" "${LICENSEFOLDER}/license_tinyxml.txt")

	set(LICENSE_ARRAY "${LICENSE_ARRAY}\n")

	configure_file(cmake/licenses.h.in ${outputFile})
endfunction()
