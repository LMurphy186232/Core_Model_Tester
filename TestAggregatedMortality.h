//---------------------------------------------------------------------------
// TestAggregatedMortality
//---------------------------------------------------------------------------
#if !defined(TestAggregatedMortality_H)
#define TestAggregatedMortality_H

#include <fstream>

/**
 * Tests the clAggregatedMortality class.
 */

/**
 * Writes the parameter file for TestNormalProcessing1().
 * @return File name of the freshly written parameter file.
 */
const char* WriteAggregatedMortalityXMLFile1();

/**
 * Writes the parameter file for TestNormalProcessing2().
 * @return File name of the freshly written parameter file.
 */
const char* WriteAggregatedMortalityXMLFile2();

/**
 * Writes the parameter file for TestNormalProcessing3().
 * @return File name of the freshly written parameter file.
 */
const char* WriteAggregatedMortalityXMLFile3();

/**
 * Writes the parameter file for TestNormalProcessing4().
 * @return File name of the freshly written parameter file.
 */
const char* WriteAggregatedMortalityXMLFile4();

/**
 * Writes the parameter file for TestNormalProcessing5().
 * @return File name of the freshly written parameter file.
 */
const char* WriteAggregatedMortalityXMLFile5();

/**
 * Writes the parameter file for TestNormalProcessing6().
 * @return File name of the freshly written parameter file.
 */
const char* WriteAggregatedMortalityXMLFile6();

/**
 * Writes an error file where the value for amount to cut is not between
 * 0 and 1.
 * @return File name of the freshly written parameter file.
 */
const char* WriteAggregatedMortalityXMLErrorFile1();

/**
 * Writes an error file where the return interval is less than 0.
 * @return File name of the freshly written parameter file.
 */
const char* WriteAggregatedMortalityXMLErrorFile2();
/**
 * Writes common portions of the test parameter files.  Starts with
 * &lt;randomSeed&gt; and ends with &lt;/allometry&gt;.
 * @param oOut File stream to write to.
 */
void WriteAggregatedMortalityCommonStuff(std::fstream &oOut);
//---------------------------------------------------------------------------
#endif //TestAggregatedMortality_H
