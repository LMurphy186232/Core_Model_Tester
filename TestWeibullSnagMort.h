//---------------------------------------------------------------------------
// TestWeibullSnagMort
//---------------------------------------------------------------------------
#if !defined(TestWeibullSnagMort_H)
#define TestWeibullSnagMort_H

/**
 * Tests the clWeibullSnagMort class.
 * @author Lora E. Murphy
 */

/**
 * Writes a parameter file with the specifications given for
 * TestWeibullSnagMort(), run 1.
 * @return Filename written.
 */
const char* WriteWeibullSnagMortXMLFile1();

/**
 * Writes a parameter file with the specifications given for
 * TestWeibullSnagMort, run 2.
 * @return Filename written.
 */
const char* WriteWeibullSnagMortXMLFile2();

/**
 * Writes a file where the size classes overlap.
 * @return Filename written.
 */
const char* WriteWeibullSnagMortXMLErrorFile1();

/**
 * Writes a file where a tree type other than snag is assigned to the
 * behavior.
 * @return Filename written.
 */
const char* WriteWeibullSnagMortXMLErrorFile2();
//---------------------------------------------------------------------------
#endif // TestWeibullSnagMort_H
