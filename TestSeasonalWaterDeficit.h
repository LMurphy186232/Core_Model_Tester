//---------------------------------------------------------------------------
// TestSeasonalWaterDeficit
//---------------------------------------------------------------------------
#if !defined(TestSeasonalWaterDeficit_H)
#define TestSeasonalWaterDeficit_H

#include <fstream>

/**
 * Writes a parameter file for normal proceessing, run 1.
 * @return Filename written.
 */
const char* WriteSeasonalWaterDeficitXMLFile1();

/**
 * Writes a parameter file for error processing. A rainfall proportion is not
 * between 0 and 1.
 * @return Filename written.
 */
const char* WriteSeasonalWaterDeficitXMLErrorFile1();

/**
 * Writes a parameter file for error processing. Rainfall proportions do not
 * add up to 1.
 * @return Filename written.
 */
const char* WriteSeasonalWaterDeficitXMLErrorFile2();

//---------------------------------------------------------------------------
#endif // TestDensityLight_H
