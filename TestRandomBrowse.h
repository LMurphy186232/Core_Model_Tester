//---------------------------------------------------------------------------
// TestRandomBrowse
//---------------------------------------------------------------------------
#if !defined(TestRandomBrowse_H)
#define TestRandomBrowse_H

/**
 * Tests the clRandomBrowse class.
 * @author Lora E. Murphy
 */

/**
 * Writes a parameter file with the specifications given for
 * TestRandomBrowse(), run 1.
 * @return Filename written.
 */
const char* WriteRandomBrowseXMLFile1();

/**
 * Writes a parameter file with the specifications given for
 * TestRandomBrowse(), run 2.
 * @return Filename written.
 */
const char* WriteRandomBrowseXMLFile2();

/**
 * Writes a parameter file with the specifications given for
 * TestRandomBrowse(), run 3.
 * @return Filename written.
 */
const char* WriteRandomBrowseXMLFile3();

/**
 * Writes a parameter file where the browse probabilities are not all between
 * 0 and 1.
 * @return Filename written.
 */
const char* WriteRandomBrowseXMLErrorFile1();
//---------------------------------------------------------------------------
#endif // TestRandomBrowse_H
