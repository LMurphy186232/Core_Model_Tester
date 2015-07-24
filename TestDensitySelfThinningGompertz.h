//---------------------------------------------------------------------------
// TestDensitySelfThinningGompertz.h
//---------------------------------------------------------------------------
#if !defined(TestDensitySelfThinningGompertz_H)
  #define TestDensitySelfThinningGompertz_H

#include <fstream>

/**
 * Writes a parameter file for normal processing run 1.
 */
const char* WriteDensitySelfThinningGompertzXMLFile1();

/**
 * Writes a parameter file for normal processing run 2.
 */
const char* WriteDensitySelfThinningGompertzXMLFile2();

/**
 * Writes a parameter file with a negative radius parameter.
 */
const char* WriteDensitySelfThinningGompertzXMLErrorFile1();

/**
 * Writes a parameter file with a negative minimum height parameter.
 */
const char* WriteDensitySelfThinningGompertzXMLErrorFile2();

/**
 * Writes allometry parameters common to all parameter files.
 * @param oOut
 */
void WriteDensitySelfThinningGompertzCommonStuff(std::fstream &oOut);
//---------------------------------------------------------------------------
#endif // TestDensitySelfThinningGompertz_H

