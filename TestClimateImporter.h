//---------------------------------------------------------------------------
// TestClimateImporter
//---------------------------------------------------------------------------
#if !defined(TestClimateImporter_H)
#define TestClimateImporter_H

#include <fstream>

/**
 * Writes a parameter file for normal proceessing, run 1.
 * @return Filename written.
 */
const char* WriteClimateImporterXMLFile1();

/**
 * Writes a parameter file for normal proceessing, run 2.
 * @return Filename written.
 */
const char* WriteClimateImporterXMLFile2();

/**
 * Writes a parameter file for normal proceessing, run 3.
 * @return Filename written.
 */
const char* WriteClimateImporterXMLFile3();


/**
 * Writes a parameter file for error processing. There is a negative precip
 * value.
 * @return Filename written.
 */
const char* WriteClimateImporterXMLErrorFile1();

/**
 * Writes a parameter file for error processing. There is a negative soil
 * water storage value.
 * @return Filename written.
 */
const char* WriteClimateImporterXMLErrorFile2();

/**
 * Writes a parameter file for error processing. There is a negative solar
 * radiation value.
 * @return Filename written.
 */
const char* WriteClimateImporterXMLErrorFile3();

/**
 * Writes common portions of the test parameter files.
 * @param oOut File stream to write to.
 */
void WriteClimateImporterCommonStuff(std::fstream &oOut);

//---------------------------------------------------------------------------
#endif // TestClimateImporter_H
