//---------------------------------------------------------------------------
// TestOutputShort
//---------------------------------------------------------------------------
#if !defined(TestOutputShort_H)
#define TestOutputShort_H

#include <fstream>

/**
 * Writes a parameter file for normal processing run 1.
 * @return Filename written.
 */
const char* WriteOutputShortXMLFile1();

/**
 * Writes a parameter file for normal processing run 1.
 * @return Filename written.
 */
const char* WriteOutputShortXMLFile2();

/**
 * Writes a parameter file for normal processing run 3.
 * @return Filename written.
 */
const char* WriteOutputShortXMLFile3();

/**
 * Writes the tree map.
 * @param oOut File stream to write to.
 */
void WriteOutputShortTreeMap(std::fstream &oOut);
//---------------------------------------------------------------------------

#endif // TestOutputShort_H
