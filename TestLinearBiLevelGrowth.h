//---------------------------------------------------------------------------
// TestLinearBiLevelGrowth
//---------------------------------------------------------------------------
#if !defined(TestLinearBiLevelGrowth_H)
#define TestLinearBiLevelGrowth_H

#include <fstream>

/**
 * Writes a parameter file for normal processing run 1.
 * @return Filename written.
 */
const char* WriteLinearBiLevelGrowthXMLFile1();

/**
 * Writes a parameter file for normal processing run 2.
 * @return Filename written.
 */
const char* WriteLinearBiLevelGrowthXMLFile2();

/**
 * Writes a parameter file for normal processing run 3.
 * @return Filename written.
 */
const char* WriteLinearBiLevelGrowthXMLFile3();

/**
 * Writes a parameter file for normal processing run 4.
 * @return Filename written.
 */
const char* WriteLinearBiLevelGrowthXMLFile4();

/**
 * Writes a parameter file where a value for high-light growth threshold is
 * not between 0 and 100.
 * @return Filename written.
 */
const char* WriteLinearBiLevelGrowthXMLErrorFile1();

/**
 * Writes common portions of the test parameter files.  This starts with
 * &lt;randomSeed&gt; and ends with &lt;/allometry&gt;.
 * @param oOut File stream to write to.
 */
void WriteLinearBiLevelGrowthCommonStuff(std::fstream &oOut);

/**
 * Writes growth parameters for the test parameter files.
 * @param oOut File stream to write to.
 */
void WriteLinearBiLevelGrowthGrowthParameters(std::fstream &oOut);
//---------------------------------------------------------------------------
#endif // TestSimpleLinearGrowth_H
