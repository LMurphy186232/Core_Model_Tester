//---------------------------------------------------------------------------
// TestPRStormBiLevelGrowth
//---------------------------------------------------------------------------
#if !defined(TestPRStormBiLevelGrowth_H)
#define TestPRStormBiLevelGrowth_H

#include <fstream>

/**
 * Writes a parameter file for normal processing run 1.
 * @return Filename written.
 */
const char* WritePRStormBiLevelGrowthXMLFile1();

/**
 * Writes a parameter file for normal processing run 2.
 * @return Filename written.
 */
const char* WritePRStormBiLevelGrowthXMLFile2();

/**
 * Writes a parameter file where a value for high-light growth threshold is
 * not between 0 and 100.
 * @return Filename written.
 */
const char* WritePRStormBiLevelGrowthXMLErrorFile1();

/**
 * Writes a parameter file where there is no "Storm Light" grid (because the
 * storm light behavior is missing).
 * @return Filename written.
 */
const char* WritePRStormBiLevelGrowthXMLErrorFile2();

/**
 * Writes a parameter file where there is no "Storm" grid (because the
 * storm behavior is missing).
 * @return Filename written.
 */
const char* WritePRStormBiLevelGrowthXMLErrorFile3();

/**
 * Writes common portions of the test parameter files. This starts with
 * &lt;randomSeed&gt; and ends with &lt;/allometry&gt;.
 * @param oOut File stream to write to.
 */
void WritePRStormBiLevelGrowthCommonStuff(std::fstream &oOut);

/**
 * Writes growth parameters for the test parameter files.
 * @param oOut File stream to write to.
 * @param iListPosition List position.
 */
void WritePRStormBiLevelGrowthGrowthParameters(std::fstream &oOut, int iListPosition);
//---------------------------------------------------------------------------
#endif // TestSimpleLinearGrowth_H
