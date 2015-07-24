//---------------------------------------------------------------------------
// TestMerchValueCalculator
//---------------------------------------------------------------------------
#if !defined(TestMerchValueCalculator_H)
#define TestMerchValueCalculator_H

#include <fstream>

/**
 * Tests the class clMerchValueCalculator.
 */

/**
 * Writes a parameter file for normal processing. There are 7 species (of
 * which 6 are used), and the merchantable timber value behavior is the only
 * one in the run.
 * @return Filename written.
 */
const char* WriteMerchValueCalculatorXMLFile1();

/**
 * Writes an error file where a form class value is not an allowed value.
 * @return Filename written.
 */
const char* WriteMerchValueCalculatorXMLErrorFile1();

/**
 * Writes an error file where the volume behavior is applied to seedlings.
 * @return Filename written.
 */
const char* WriteMerchValueCalculatorXMLErrorFile2();

/**
 * Writes common portions of the test parameter files (tree pop, plot, etc).
 * Ends with &lt;/trees&gt.
 * @param oOut File stream to write to.
 */
void WriteMerchValueCalculatorCommonStuff(std::fstream &oOut);
//---------------------------------------------------------------------------
#endif // TestMerchValueCalculator_H
