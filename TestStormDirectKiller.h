//---------------------------------------------------------------------------
// TestStormDirectKiller
//---------------------------------------------------------------------------
#if !defined(TestStormDirectKiller_H)
#define TestStormDirectKiller_H


/**
 * Tests the clStormDirectKiller class.
 */

/**
 * Writes the parameter file for TestNormalProcessing1().
 * @return File name of the freshly written parameter file.
 */
const char* WriteStormDirectKillerXMLFile1();

/**
 * Writes an error file where the storm behavior is not also enabled.
 * @return File name of the freshly written parameter file.
 */
const char* WriteStormDirectKillerXMLErrorFile1();

/**
 * Writes an error file where mortality behaviors aren't applied to all
 * storm trees.
 * @return File name of the freshly written parameter file.
 */
const char* WriteStormDirectKillerXMLErrorFile2();
//---------------------------------------------------------------------------
#endif //TestStormDirectKiller_H
