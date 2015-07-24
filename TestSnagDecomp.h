//---------------------------------------------------------------------------
// TestSnagDecomp
//---------------------------------------------------------------------------
#if !defined(TestSnagDecomp_H)
#define TestSnagDecomp_H

/**
 * Tests the SnagDecomp class descended from clBehaviorBase.
 * @author Mark Vanderwel
 */

/**
 * Writes a parameter file with the specifications given for
 * TestSnagDecomp(), run 1.
 * @return Filename written.
 */
const char* WriteSnagDecompXMLFile1();


/**
 * Writes a parameter file with the specifications given for
 * TestSnagDecomp(), run 2.
 * @return Filename written.
 */
const char* WriteSnagDecompXMLFile2();


/**
 * Writes a parameter file with the specifications given for
 * TestSnagDecomp(), error condition 1.
 * @return Filename written.
 */
const char* WriteSnagDecompXMLErrorFile1();

/**
 * Writes a parameter file with the specifications given for
 * TestSnagDecomp(), error condition 2.
 * @return Filename written.
 */
const char* WriteSnagDecompXMLErrorFile2();
//---------------------------------------------------------------------------
#endif // TestSnagDecomp_H
