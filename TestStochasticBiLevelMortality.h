//---------------------------------------------------------------------------
// TestStochasticBiLevelMortality_H
//---------------------------------------------------------------------------
#if !defined(TestStochasticBiLevelMortality_H)
#define TestStochasticBiLevelMortality_H
#include <fstream>

/**
 * Writes a parameter file for normal processing run 1.
 * @return Filename written.
 */
const char* WriteStochasticBiLevelMortalityXMLFile1();

/**
 * Writes a parameter file for normal processing run 2.
 * @return Filename written.
 */
const char* WriteStochasticBiLevelMortalityXMLFile2();

/**
 * Writes a parameter file for normal processing run 3.
 * @return Filename written.
 */
const char* WriteStochasticBiLevelMortalityXMLFile3();

/**
 * Writes a parameter file for normal processing run 4.
 * @return Filename written.
 */
const char* WriteStochasticBiLevelMortalityXMLFile4();

/**
 * Writes a parameter file where a value for high-light mortality threshold is
 * not between 0 and 100.
 * @return Filename written.
 */
const char* WriteStochasticBiLevelMortalityXMLErrorFile1();

/**
 * Writes a parameter file where a value for low-light mortality probability
 * is not between 0 and 1.
 * @return Filename written.
 */
const char* WriteStochasticBiLevelMortalityXMLErrorFile2();

/**
 * Writes a parameter file where a value for high-light mortality probability
 * is not between 0 and 1.
 * @return Filename written.
 */
const char* WriteStochasticBiLevelMortalityXMLErrorFile3();

/**
 * Writes a parameter file where there is no storm light grid.
 * @return Filename written.
 */
const char* WriteStochasticBiLevelMortalityXMLErrorFile4();

/**
 * Writes a parameter file where this is GLI but there is no light behavior.
 * @return Filename written.
 */
const char* WriteStochasticBiLevelMortalityXMLErrorFile5();

/**
 * Writes common portions of the test parameter files. This starts with
 * &lt;randomSeed&gt; and ends with &lt;/allometry&gt;.
 * @param oOut File stream to write to.
 */
void WriteStochasticBiLevelMortalityCommonStuff(std::fstream &oOut);

/**
 * Writes mortality parameters for the test parameter files.
 * @param oOut File stream to write to.
 */
void WriteStochasticBiLevelMortalityMortParameters(std::fstream &oOut);
#endif // TestStochasticBiLevelMortality_H
//---------------------------------------------------------------------------


