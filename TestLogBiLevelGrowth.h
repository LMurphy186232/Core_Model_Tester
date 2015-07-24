//---------------------------------------------------------------------------
// TestLogBiLevelGrowth
//---------------------------------------------------------------------------
#if !defined(TestLogBiLevelGrowth_H)
#define TestLogBiLevelGrowth_H

#include <fstream>

/**
 * Writes a parameter file for normal processing run 1.
 * @return Filename written.
 */
const char* WriteLogBiLevelGrowthXMLFile1();

/**
 * Writes a parameter file for normal processing run 2.
 * @return Filename written.
 */
const char* WriteLogBiLevelGrowthXMLFile2();

/**
 * Writes a parameter file for normal processing run 3.
 * @return Filename written.
 */
const char* WriteLogBiLevelGrowthXMLFile3();

/**
 * Writes a parameter file where a value for high-light growth threshold is
 * not between 0 and 100.
 * @return Filename written.
 */
const char* WriteLogBiLevelGrowthXMLErrorFile1();

/**
 * Writes a parameter file where a value for low-light Xb is 0.
 * @return Filename written.
 */
const char* WriteLogBiLevelGrowthXMLErrorFile2();

/**
 * Writes a parameter file where a value for high-light Xb is 0.
 * @return Filename written.
 */
const char* WriteLogBiLevelGrowthXMLErrorFile3();

/**
 * Writes a parameter file where a value for low-light max growth is less
 * than 0.
 * @return Filename written.
 */
const char* WriteLogBiLevelGrowthXMLErrorFile4();

/**
 * Writes a parameter file where a value for high-light max growth is less
 * than 0.
 * @return Filename written.
 */
const char* WriteLogBiLevelGrowthXMLErrorFile5();

/**
 * Writes a parameter file where a value for low-light X0 is 0.
 * @return Filename written.
 */
const char* WriteLogBiLevelGrowthXMLErrorFile6();

/**
 * Writes a parameter file where a value for high-light X0 is 0.
 * @return Filename written.
 */
const char* WriteLogBiLevelGrowthXMLErrorFile7();

/**
 * Writes common portions of the test parameter files.  This starts with
 * &lt;randomSeed&gt; and ends with &lt;/allometry&gt;.
 * @param oOut File stream to write to.
 */
void WriteLogBiLevelGrowthCommonStuff(std::fstream &oOut);

/**
 * Writes growth parameters for the test parameter files.
 * @param oOut File stream to write to.
 */
void WriteLogBiLevelGrowthGrowthParameters(std::fstream &oOut);
//---------------------------------------------------------------------------
#endif // TestSimpleLinearGrowth_H
