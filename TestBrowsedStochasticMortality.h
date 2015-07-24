//---------------------------------------------------------------------------
// TestBrowsedStochasticMortality_H
//---------------------------------------------------------------------------
#if !defined(TestBrowsedStochasticMortality_H)
#define TestBrowsedStochasticMortality_H

#include <fstream>

/**
 * Writes a parameter file for normal processing run 1.
 * @return Filename written.
 */
const char* WriteBrowsedStochasticMortalityXMLFile1();

/**
 * Writes a parameter file for normal processing run 2.
 * @return Filename written.
 */
const char* WriteBrowsedStochasticMortalityXMLFile2();

/**
 * Writes a parameter file where a value for browsed mortality probability
 * is not between 0 and 1.
 * @return Filename written.
 */
const char* WriteBrowsedStochasticMortalityXMLErrorFile1();

/**
 * Writes a parameter file where a value for unbrowsed mortality probability
 * is not between 0 and 1.
 * @return Filename written.
 */
const char* WriteBrowsedStochasticMortalityXMLErrorFile2();

/**
 * Writes a parameter file where there is no browsed behavior.
 * @return Filename written.
 */
const char* WriteBrowsedStochasticMortalityXMLErrorFile3();

/**
 * Writes common portions of the test parameter files.  This starts with
 * &lt;randomSeed&gt; and ends with &lt;/allometry&gt;.
 * @param oOut File stream to write to.
 */
void WriteBrowsedStochasticMortalityCommonStuff(std::fstream &oOut);

/**
 * Writes mortality parameters for the test parameter files.
 * @param oOut File stream to write to.
 */
void WriteBrowsedStochasticMortalityMortParameters(std::fstream &oOut);

#endif // TestBrowsedStochasticMortality_H
//---------------------------------------------------------------------------


