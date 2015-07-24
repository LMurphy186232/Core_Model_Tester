//---------------------------------------------------------------------------
// TestSubstrateDepSeedSurvival
//---------------------------------------------------------------------------
#if !defined(TestSubstrateDepSeedSurvival_H)
#define TestSubstrateDepSeedSurvival_H
#include <fstream>

/**
 * This class tests the clSubstrateDepSeedSurvival class.
 */

/**
 * Writes a parameter file to direct testing for NormalProcessingRun1.
 * @return Filename written.
 */
const char* WriteSubstrateDepSeedSurvivalXMLFile1();

/**
 * Writes a parameter file to direct testing for NormalProcessingRun2.
 * @return Filename written.
 */
const char* WriteSubstrateDepSeedSurvivalXMLFile2();

/**
 * Writes a parameter file to direct testing for NormalProcessingRun3.
 * @return Filename written.
 */
const char* WriteSubstrateDepSeedSurvivalXMLFile3();

/**
 * Writes a parameter file to direct testing for NormalProcessingRun4.
 * @return Filename written.
 */
const char* WriteSubstrateDepSeedSurvivalXMLFile4();

/**
 * Writes a parameter file with a substrate favorability not between 0 and 1.
 * @return Filename written.
 */
const char* WriteSubstrateDepSeedSurvivalXMLErrorFile1();

/**
 * Writes a parameter file where substrate isn't used.
 * @return Filename written.
 */
const char* WriteSubstrateDepSeedSurvivalXMLErrorFile2();

/**
 * Writes a parameter file where a disperse behavior isn't used.
 * @return Filename written.
 */
const char* WriteSubstrateDepSeedSurvivalXMLErrorFile3();

/**
 * Writes common portions of the test parameter files (tree pop, plot, etc).
 * This ends with &lt;/allometry&gt;.
 * @param oOut File stream to write to.
 */
void WriteSubstrateDepSeedSurvivalCommonStuff(std::fstream &oOut);
//---------------------------------------------------------------------------
#endif // TestEstablishment
