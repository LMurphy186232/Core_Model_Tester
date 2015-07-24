//---------------------------------------------------------------------------
// TestBoleVolumeCalculator
//---------------------------------------------------------------------------
#if !defined(TestBoleVolumeCalculator_H)
#define TestBoleVolumeCalculator_H

#include <fstream>

/**
 * Writes a parameter file for normal processing.  There are 8 species (of
 * which 7 are used), and the bole volume behavior is the only one in the
 * run.
 * @return Filename written.
 */
const char* WriteBoleVolumeCalculatorXMLFile1();

/**
 * Writes an error file where a form class value is less than 60.
 * @return Filename written.
 */
const char* WriteBoleVolumeCalculatorXMLErrorFile1();

/**
 * Writes an error file where a form class value is greater than 100.
 * @return Filename written.
 */
const char* WriteBoleVolumeCalculatorXMLErrorFile2();

/**
 * Writes an error file where the volume behavior is applied to seedlings.
 * @return Filename written.
 */
const char* WriteBoleVolumeCalculatorXMLErrorFile3();

/**
 * Writes common portions of the test parameter files (tree pop, plot, etc).
 * Ends with &lt;/trees&gt;.
 * @param oOut File stream to write to.
 */
void WriteBoleVolumeCalculatorCommonStuff(std::fstream &oOut);
//---------------------------------------------------------------------------
#endif // TestBoleVolumeCalculator_H
