//---------------------------------------------------------------------------
// TestMastingNonSpatialDisperse
//---------------------------------------------------------------------------
#if !defined(TestNonSpatialDisperse_H)
#define TestNonSpatialDisperse_H

#include <fstream>

/**
 * Writes a parameter file to direct testing for run 1.
 * @return Filename written.
 */
const char* WriteNonSpatialDisperseXMLFile1();

/**
 * Writes a parameter file to direct testing for run 2.
 * @return Filename written.
 */
const char* WriteNonSpatialDisperseXMLFile2();

/**
 * Writes a parameter file to direct testing for run 3.
 * @return Filename written.
 */
const char* WriteNonSpatialDisperseXMLFile3();

/**
 * Writes an error file where masting inverse gaussian mu is not > 0.
 * @return Filename written.
 */
const char* WriteNonSpatialDisperseXMLErrorFile1();

/**
 * Writes an error file where non-masting inverse gaussian mu is not > 0.
 * @return Filename written.
 */
const char* WriteNonSpatialDisperseXMLErrorFile2();

/**
 * Writes an error file where masting inverse gaussian lambda is not > 0.
 * @return Filename written.
 */
const char* WriteNonSpatialDisperseXMLErrorFile3();

/**
 * Writes an error file where non-masting inverse gaussian lambda is not > 0.
 * @return Filename written.
 */
const char* WriteNonSpatialDisperseXMLErrorFile4();

/**
 * Writes tree stuff.
 * @param oOut File stream to write to.
 */
void WriteNonSpatialDisperseTrees(std::fstream &oOut);

/**
 * Writes allometry stuff.
 * @param oOut File stream to write to.
 */
void WriteNonSpatialDisperseAllometry(std::fstream &oOut);
//---------------------------------------------------------------------------
#endif // TestMastingNonSpatialDispersal_H
