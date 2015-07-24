//---------------------------------------------------------------------------
// TestMastingSpatialDisperse
//---------------------------------------------------------------------------
#if !defined(TestMastingSpatialDisperse_H)
#define TestMastingSpatialDisperse_H

#include <fstream>

/**
 * Writes a parameter file for normal processing run 1.
 * @return Filename written.
 */
const char* WriteMastingSpatialDisperseXMLFile1();

/**
 * Writes a parameter file for normal processing run 2.
 * @return Filename written.
 */
const char* WriteMastingSpatialDisperseXMLFile2();

/**
 * Writes a parameter file for normal processing run 3.
 * @return Filename written.
 */
const char* WriteMastingSpatialDisperseXMLFile3();

/**
 * Writes a parameter file for normal processing run 4.
 * @return Filename written.
 */
const char* WriteMastingSpatialDisperseXMLFile4();

/**
 * Writes a parameter file for normal processing run 5.
 * @param iRandomSeed Random seed.
 * @return Filename written.
 */
const char* WriteMastingSpatialDisperseXMLFile5(int iRandomSeed);

/**
 * Writes a file to test masting CDF setup.
 * @return Filename written.
 */
const char* WriteMastingSpatialDisperseXMLCheckFile1();

/**
 * Writes a file to test masting CDF setup.
 * @return Filename written.
 */
const char* WriteMastingSpatialDisperseXMLCheckFile2();

/**
 * Writes a file where the masting "a" parameter is zero.
 * @return Filename written.
 */
const char* WriteMastingSpatialDisperseXMLErrorFile1();

/**
 * Writes a file where the masting fraction participating is not between
 * 0 and 1.
 * @return Filename written.
 */
const char* WriteMastingSpatialDisperseXMLErrorFile2();

/**
 * Writes a file where the non-masting fraction participating is not between
 * 0 and 1.
 * @return Filename written.
 */
const char* WriteMastingSpatialDisperseXMLErrorFile3();

/**
 * Writes a file where the masting beta is greater than 25.
 * @return Filename written.
 */
const char* WriteMastingSpatialDisperseXMLErrorFile4();

/**
 * Writes a file where the non-masting beta is greater than 25.
 * @return Filename written.
 */
const char* WriteMastingSpatialDisperseXMLErrorFile5();

/**
 * Writes a file where the masting theta is greater than 50.
 * @return Filename written.
 */
const char* WriteMastingSpatialDisperseXMLErrorFile6();

/**
 * Writes a file where the non-masting theta is greater than 50.
 * @return Filename written.
 */
const char* WriteMastingSpatialDisperseXMLErrorFile7();

/**
 * Writes tree stuff.
 * @param oOut File stream to write to.
 */
void WriteMastingSpatialDisperseTrees(std::fstream &oOut);

/**
 * Writes allometry stuff.
 * @param oOut File stream to write to.
 */
void WriteMastingSpatialDisperseAllometry(std::fstream &oOut);
//---------------------------------------------------------------------------

#endif // TestMastingSpatialDisperse_H
