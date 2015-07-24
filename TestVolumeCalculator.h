//---------------------------------------------------------------------------
// TestVolumeCalculator
//---------------------------------------------------------------------------
#if !defined(TestVolumeCalculator_H)
#define TestVolumeCalculator_H
#include <fstream>

/**
 * Tests the class clVolumeCalculator.
 */

/**
 * Writes the parameter file for NormalRun1().
 * @return Filename written.
 */
const char* WriteVolumeCalculatorXMLFile1();

/**
 * Writes the parameter file for NormalRun2().
 * @return Filename written.
 */
const char* WriteVolumeCalculatorXMLFile2();

/**
 * Writes the parameter file for NormalRun3().
 * @return Filename written.
 */
const char* WriteVolumeCalculatorXMLFile3();

/**
 * Writes the parameter file for NormalRun4().
 * @return Filename written.
 */
const char* WriteVolumeCalculatorXMLFile4();

/**
 * Writes the parameter file for NormalRun5().
 * @return Filename written.
 */
const char* WriteVolumeCalculatorXMLFile5();

/**
 * Writes an error file where the stump height is less than 0.
 */
const char* WriteVolumeCalculatorXMLErrorFile1();

/**
 * Writes an error file where the minimum usable diameter is less than 0.
 */
const char* WriteVolumeCalculatorXMLErrorFile2();

/**
 * Writes an error file where the segment length is less than 0.
 */
const char* WriteVolumeCalculatorXMLErrorFile3();

/**
 * Writes an error file where the volume behavior is applied to seedlings.
 */
const char* WriteVolumeCalculatorXMLErrorFile4();

/**
 * Writes common portions of the test parameter files (tree pop, plot, etc).
 * @param oOut File stream to write to.
 */
void WriteVolumeCalculatorCommonStuff(std::fstream &oOut);
//---------------------------------------------------------------------------
#endif // TestVolumeCalculator_H
