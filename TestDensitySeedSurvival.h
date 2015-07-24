//---------------------------------------------------------------------------
// TestDensitySeedSurvival
//---------------------------------------------------------------------------
#if !defined(TestDensitySeedSurvival_H)
#define TestDensitySeedSurvival_H

#include <fstream>

/**
 * Writes a parameter file to direct testing.  The behaviors are non-spatial
 * disperse (designed to add no seeds) and density-dependent seed survival.
 * There are 4 species but only the last three are used.
 * @return Filename written.
 */
const char* WriteDensitySeedSurvivalXMLFile1();

/**
 * Writes a parameter file to direct testing.  The behaviors are non-spatial
 * disperse (designed to add no seeds) and density-dependent seed survival.
 * There are 4 species but only the last three are used.
 * @return Filename written.
 */
const char* WriteDensitySeedSurvivalXMLFile2();

/**
 * Writes a parameter file to direct testing.  The behaviors are non-spatial
 * disperse (designed to add no seeds) and density-dependent seed survival.
 * There are 4 species but only the last three are used.
 * @return Filename written.
 */
const char* WriteDensitySeedSurvivalXMLFile3();

/**
 * Writes a parameter file to direct testing for normal processing Run 4.
 * @return Filename written.
 */
const char* WriteDensitySeedSurvivalXMLFile4();

/**
 * Writes allometry parameters common to all parameter files.
 * @param oOut
 */
void WriteDensitySeedSurvivalCommonStuff(std::fstream &oOut);

//---------------------------------------------------------------------------

#endif // TestDensitySeedSurvival_H
