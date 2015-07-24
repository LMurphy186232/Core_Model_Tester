//---------------------------------------------------------------------------
// TestLogisticBiLevelMortality_H
//---------------------------------------------------------------------------
#if !defined(TestLogisticBiLevelMortality_H)
#define TestLogisticBiLevelMortality_H

#include <fstream>

/**
 * Writes a parameter file for normal processing run 1.
 * @return Filename written.
 */
const char* WriteLogisticBiLevelMortalityXMLFile1();

/**
 * Writes a parameter file for normal processing run 2.
 * @return Filename written.
 */
const char* WriteLogisticBiLevelMortalityXMLFile2();

/**
 * Writes a parameter file for normal processing run 3.
 * @return Filename written.
 */
const char* WriteLogisticBiLevelMortalityXMLFile3();

/**
 * Writes a parameter file where a value for high-light growth threshold is
 * not between 0 and 100.
 * @return Filename written.
 */
const char* WriteLogisticBiLevelMortalityXMLErrorFile1();

/**
 * Writes common portions of the test parameter files.  This starts with
 * &lt;randomSeed&gt; and ends with &lt;/allometry&gt;.
 * @param oOut File stream to write to.
 */
void WriteLogisticBiLevelMortalityCommonStuff(std::fstream &oOut);

/**
 * Writes mortality parameters for the test parameter files.
 * @param oOut File stream to write to.
 */
void WriteLogisticBiLevelMortalityMortParameters(std::fstream &oOut);

#endif // TestLogisticBiLevelMortality_H
//---------------------------------------------------------------------------


