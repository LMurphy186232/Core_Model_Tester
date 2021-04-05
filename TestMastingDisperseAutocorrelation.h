//---------------------------------------------------------------------------
// TestMastingDisperseAutocorrelation
//---------------------------------------------------------------------------
#if !defined(TestMastingDisperseAutocorrelation_H)
#define TestMastingDisperseAutocorrelation_H

#include <fstream>

/**
 * Writes a parameter file for normal processing run 1.
 * Mast levels are a timeseries.
 * @return Filename written.
 */
const char* WriteMastingDisperseAutocorrelationXMLFile1();

/**
 * Writes a parameter file for normal processing run 2.
 * @return Filename written.
 */
const char* WriteMastingDisperseAutocorrelationXMLFile2();

/**
 * Writes a parameter file for normal processing run 3.
 * @return Filename written.
 */
const char* WriteMastingDisperseAutocorrelationXMLFile3();

/**
 * Writes a parameter file for normal processing run 4.
 * @return Filename written.
 */
const char* WriteMastingDisperseAutocorrelationXMLFile4();

/**
 * Writes a file where c in fraction participating is not between 0 and 1.
 * @return Filename written.
 */
const char* WriteMastingDisperseAutocorrelationXMLErrorFile1();

/**
 * Writes a file where masting level input is not between 0 and 1.
 * @return Filename written.
 */
const char* WriteMastingDisperseAutocorrelationXMLErrorFile2();

/**
 * Writes a file where Rho noise < 0
 * @return Filename written.
 */
const char* WriteMastingDisperseAutocorrelationXMLErrorFile3();

/**
 * Writes a file where Max DBH < min DBH
 * @return Filename written.
 */
const char* WriteMastingDisperseAutocorrelationXMLErrorFile4();

/**
 * Writes a file where A in fraction participating = 0
 * @return Filename written.
 */
const char* WriteMastingDisperseAutocorrelationXMLErrorFile5();

/**
 * Writes a file where seed producer score standard deviation < 0
 * @return Filename written.
 */
const char* WriteMastingDisperseAutocorrelationXMLErrorFile6();

/**
 * Writes tree stuff.
 * @param oOut File stream to write to.
 */
void WriteMastingDisperseAutocorrelationTrees(std::fstream &oOut);

/**
 * Writes allometry stuff.
 * @param oOut File stream to write to.
 */
void WriteMastingDisperseAutocorrelationAllometry(std::fstream &oOut);

/**
 * Writes tree stuff, for error files.
 * @param oOut File stream to write to.
 */
void WriteMastingDisperseAutocorrelationTreesForError(std::fstream &oOut);

/**
 * Writes allometry stuff for error files; fewer stuffs.
 * @param oOut File stream to write to.
 */
void WriteMastingDisperseAutocorrelationAllometryForError(std::fstream &oOut);
//---------------------------------------------------------------------------

#endif // TestMastingDisperseAutocorrelation_H
