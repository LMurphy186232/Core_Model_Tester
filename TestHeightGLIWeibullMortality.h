//---------------------------------------------------------------------------
// TestHeightGLIWeibullMortality_H
//---------------------------------------------------------------------------
#if !defined(TestHeightGLIWeibullMortality_H)
#define TestHeightGLIWeibullMortality_H

#include <fstream>

/**
 * Writes a parameter file for normal processing run 1.
 * @return Filename written.
 */
const char* WriteHeightGLIWeibullMortalityXMLFile1();

/**
 * Writes a parameter file for normal processing run 2.
 * @return Filename written.
 */
const char* WriteHeightGLIWeibullMortalityXMLFile2();

/**
 * Writes a parameter file where a value for unbrowsed max mortality is not
 * between 0 and 1.
 * @return Filename written.
 */
const char* WriteHeightGLIWeibullMortalityXMLErrorFile1();

/**
 * Writes a parameter file where there is no light behavior present.
 * @return Filename written.
 */
const char* WriteHeightGLIWeibullMortalityXMLErrorFile2();

/**
 * Writes a parameter file where a value for browsed max mortality is not
 * between 0 and 1.
 * @return Filename written.
 */
const char* WriteHeightGLIWeibullMortalityXMLErrorFile3();

/**
 * Writes common portions of the test parameter files.  This starts with
 * &lt;randomSeed&gt; and ends with &lt;/allometry&gt;.
 * @param oOut File stream to write to.
 */
void WriteHeightGLIWeibullMortalityCommonStuff(std::fstream &oOut);

#endif // TestHeightGLIWeibullMortality_H
//---------------------------------------------------------------------------


