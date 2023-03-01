//---------------------------------------------------------------------------
// TestSnagDecomp
//---------------------------------------------------------------------------
#if !defined(TestSnagDecomp_H)
#define TestSnagDecomp_H

#include <stddef.h>
#include <fstream>

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
 * Writes a parameter file to test decay class assignment for initial
 * conditions. This contains snags but no information on decay class
 * assignment.
 * @return Filename written.
 */
const char* WriteSnagsInitFile1();

/**
 * Writes a parameter file to test decay class assignment for initial
 * conditions. This contains snags and all are decay class 1.
 * @return Filename written.
 */
const char* WriteSnagsInitFile2();

/**
 * Writes a parameter file with the specifications given for
 * TestSnagDecomp(), error condition 1.
 * @return Filename written.
 */
const char* WriteSnagDecompXMLErrorFile1();

/**
 * Writes a parameter file where the transition probabilities for a class
 * don't add up to 1.
 * @return Filename written.
 */
const char* WriteSnagDecompXMLErrorFile2();

/**
 * Writes a common portion of the test parameter files. This writes all
 * tree parameters.
 * @param oOut File stream to write to.
 */
void WriteTreePopulationCommonStuff(std::fstream &oOut);

/**
 * Writes a common portion of the test parameter files. This writes some
 * snag parameters that we're going to use over and over.
 * @param oOut File stream to write to.
 */
void WriteSnagParsCommonStuff(std::fstream &oOut);
//---------------------------------------------------------------------------
#endif // TestSnagDecomp_H
