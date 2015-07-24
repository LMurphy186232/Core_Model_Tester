//---------------------------------------------------------------------------
// TestTreeRemover
//---------------------------------------------------------------------------
#if !defined(TestTreeRemover_H)
#define TestTreeRemover_H

/**
 * Tests the clTreeRemover class.
 */

/**
 * Writes a parameter file with the specifications given for
 * TestNormalProcessingRun1().
 * @return Filename written.
 */
const char* WriteTreeRemoverXMLFile1();

/**
 * Writes a parameter file with an error - the TreeRemover behavior is
 * assigned to a tree species/type combo that is not also assigned to a
 * mortality behavior.
 * @return Filename written.
 */
const char* WriteTreeRemoverXMLErrorFile1();
//---------------------------------------------------------------------------
#endif // TestTreeRemover_H
