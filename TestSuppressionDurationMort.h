//---------------------------------------------------------------------------
// TestSuppressionDurationMort_H
//---------------------------------------------------------------------------
#if !defined(TestSuppressionDurationMort_H)
  #define TestSuppressionDurationMort_H
#include <fstream>

/**
* Tests the clSuppressionDurationMort class.
*/
/**
 * Writes a parameter file for normal processing run 1.
 * @return Filename written.
 */
const char* WriteSuppressionDurationMortXMLFile1();

/**
 * Writes a parameter file where a value for max mortality probability
 * is not between 0 and 1.
 * @return Filename written.
 */
const char* WriteSuppressionDurationMortXMLErrorFile1();

/**
 * Writes a parameter file where there is no tree age behavior.
 * @return Filename written.
 */
const char* WriteSuppressionDurationMortXMLErrorFile2();

/**
 * Writes a parameter file where a value for X0 is 0.
 * @return Filename written.
 */
const char* WriteSuppressionDurationMortXMLErrorFile3();

/**
 * Writes common portions of the test parameter files.  This starts with
 * &lt;randomSeed&gt; and ends with &lt;/allometry&gt;.
 * @param oOut File stream to write to.
 */
void WriteSuppressionDurationMortErrorCommonStuff(std::fstream &oOut);
#endif // TestSuppressionDurationMort_H
//---------------------------------------------------------------------------


