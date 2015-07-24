//---------------------------------------------------------------------------
// TestGeneralizedHarvestRegime
//---------------------------------------------------------------------------
#if !defined(TestGeneralizedHarvestRegime_H)
#define TestGeneralizedHarvestRegime_H

#include <fstream>

/**
 * Tests the clGeneralizedHarvestRegime class.
 */
/**
 * Writes a parameter file to direct testing.
 * @return Filename written.
 */
const char* WriteGeneralizedHarvestRegimeXMLFile1();

/**
 * Writes a parameter file to direct testing.
 * @return Filename written.
 */
const char* WriteGeneralizedHarvestRegimeXMLFile2();

/**
 * Writes a parameter file to direct testing.
 * @return Filename written.
 */
const char* WriteGeneralizedHarvestRegimeXMLFile3();

/**
 * Writes a parameter file to direct testing.
 * @return Filename written.
 */
const char* WriteGeneralizedHarvestRegimeXMLFile4();

/**
 * Writes a parameter file to direct testing.
 * @return Filename written.
 */
const char* WriteGeneralizedHarvestRegimeXMLFile4a();

/**
 * Writes a parameter file to direct testing.
 * @return Filename written.
 */
const char* WriteGeneralizedHarvestRegimeXMLFile5();

/**
 * Writes a parameter file to direct testing.
 * @return Filename written.
 */
const char* WriteGeneralizedHarvestRegimeXMLFile6();

void WriteGeneralizedHarvestRegimeDimensionAnalysis(std::fstream &oOut);
void WriteGeneralizedHarvestRegimeAllometry(std::fstream &oOut);
//---------------------------------------------------------------------------
#endif // TestGeneralizedHarvestRegime_H
