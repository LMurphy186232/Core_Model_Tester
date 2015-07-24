//---------------------------------------------------------------------------
// TestClimateChange
//---------------------------------------------------------------------------
#if !defined(TestClimateChange_H)
#define TestClimateChange_H

#include <fstream>

/**
 * Writes a parameter file for normal proceessing, run 1.
 * @return Filename written.
 */
const char* WriteClimateChangeXMLFile1();

/**
 * Writes a parameter file for normal proceessing, run 2.
 * @return Filename written.
 */
const char* WriteClimateChangeXMLFile2();

/**
 * Writes a parameter file for normal proceessing, run 3.
 * @return Filename written.
 */
const char* WriteClimateChangeXMLFile3();

/**
 * Writes a parameter file for normal proceessing, run 4.
 * @return Filename written.
 */
const char* WriteClimateChangeXMLFile4();

/**
 * Writes a parameter file for normal proceessing, run 5.
 * @return Filename written.
 */
const char* WriteClimateChangeXMLFile5();

/**
 * Writes a parameter file for normal proceessing, run 6.
 * @return Filename written.
 */
const char* WriteClimateChangeXMLFile6();

/**
 * Writes common portions of the test parameter files (allometry and tree
 * pop).
 * @param oOut File stream to write to.
 * @param iNumYrsPerTS Number of years per timestep.
 */
void WriteClimateChangeCommonStuff(std::fstream &oOut, int iNumYrsPerTS);
//---------------------------------------------------------------------------
#endif // TestDensityLight_H
