//---------------------------------------------------------------------------
// TestInsectInfestationMortality_H
//---------------------------------------------------------------------------
#if !defined(TestInsectInfestationMortality_H)
  #define TestInsectInfestationMortality_H

#include <fstream>

/**
 * Writes a parameter file for normal processing run 1.
 * @return Filename written.
 */
const char* WriteInsectInfestationMortalityXMLFile1();

/**
 * Writes a parameter file where a value for mortality probability intercept
 * is not between 0 and 1.
 * @return Filename written.
 */
const char* WriteInsectInfestationMortalityXMLErrorFile1();

/**
 * Writes a parameter file where a value for max mortality probability
 * is not between 0 and 1.
 * @return Filename written.
 */
const char* WriteInsectInfestationMortalityXMLErrorFile2();

/**
 * Writes a parameter file where there is no insect infestation behavior.
 * @return Filename written.
 */
const char* WriteInsectInfestationMortalityXMLErrorFile3();

/**
 * Writes a parameter file where a value for X0 is 0.
 * @return Filename written.
 */
const char* WriteInsectInfestationMortalityXMLErrorFile4();

/**
 * Writes common portions of the test parameter files.  This starts with
 * &lt;randomSeed&gt; and ends with &lt;/allometry&gt;.
 * @param oOut File stream to write to.
 */
void WriteInsectInfestationMortalityErrorCommonStuff(std::fstream &oOut);

#endif // TestInsectInfestationMortality_H
//---------------------------------------------------------------------------


