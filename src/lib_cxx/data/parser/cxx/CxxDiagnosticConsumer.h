#ifndef CXX_DIAGNOSTIC_CONSUMER
#define CXX_DIAGNOSTIC_CONSUMER

#include "clang/Frontend/TextDiagnosticPrinter.h"
#include "utility/file/FilePath.h"

class CanonicalFilePathCache;
class FileRegister;
class ParserClient;

class CxxDiagnosticConsumer
	: public clang::TextDiagnosticPrinter
{
public:
	CxxDiagnosticConsumer(
		clang::raw_ostream &os,
		clang::DiagnosticOptions *diags,
		std::shared_ptr<ParserClient> client,
		std::shared_ptr<FileRegister> fileRegister,
		std::shared_ptr<CanonicalFilePathCache> canonicalFilePathCache,
		const FilePath& sourceFilePath,
		bool useLogging = true
	);

	void BeginSourceFile(const clang::LangOptions& langOptions, const clang::Preprocessor* preProcessor) override;
	void EndSourceFile() override;

	void HandleDiagnostic(clang::DiagnosticsEngine::Level level, const clang::Diagnostic& info) override;

private:
	std::shared_ptr<ParserClient> m_client;
	std::shared_ptr<FileRegister> m_register;
	std::shared_ptr<CanonicalFilePathCache> m_canonicalFilePathCache;

	const FilePath m_sourceFilePath;
	bool m_isParsingFile;
	bool m_useLogging;
};

#endif // CXX_DIAGNOSTIC_CONSUMER
