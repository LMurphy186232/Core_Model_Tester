//---------------------------------------------------------------------------
// TestTreePopulation2
//---------------------------------------------------------------------------
#if !defined(TestTreePopulation2_H)
#define TestTreePopulation2_H

#include <fstream>

/**
 * Tests the clTreePopulation class.  This is because TestTreePopulation got
 * too big.
 */

/**
 * Writes a parameter file for testing.  This contains a tree map to test
 * tree map reading.
 * @return Filename written.
 */
const char* WriteTreePopulation2XMLFile1();

/**
 * Writes a parameter file for testing.  This contains no initial densities.
 * @return Filename written.
 */
const char* WriteTreePopulation2XMLFile2();

/**
 * Writes a parameter file for testing.  This contains no seedlings in any
 * form.
 * @return Filename written.
 */
const char* WriteTreePopulation2XMLFile3();

/**
 * Writes a parameter file for testing.  This contains all possible ways of
 * specifying seedlings.
 * @return Filename written.
 */
const char* WriteTreePopulation2XMLFile4();

/**
 * Writes a parameter file for testing.  This contains only seedlings in the
 * first height class.
 * @return Filename written.
 */
const char* WriteTreePopulation2XMLFile5();

/**
 * Writes a parameter file for testing.  This contains only seedlings in the
 * second height class.
 * @return Filename written.
 */
const char* WriteTreePopulation2XMLFile6();

/**
 * Writes a parameter file for testing.  This contains only seedlings in the
 * third height class.
 * @return Filename written.
 */
const char* WriteTreePopulation2XMLFile7();

/**
 * Writes a parameter file for testing.  This contains only seedlings in the
 * DBH class.
 * @return Filename written.
 */
const char* WriteTreePopulation2XMLFile8();

/**
 * Writes a parameter file for testing.  This contains a tree map to test
 * tree map reading to verify bug fixes.
 * @return Filename written.
 */
const char* WriteTreePopulation2XMLFile9();

/**
 * Writes a parameter file for testing. This contains a filename for a text-
 * based tree map.
 * @return Filename written.
 */
const char* WriteTreePopulation2XMLFile10();

/**
 * Writes a parameter file for testing. This contains a filename for a text-
 * based tree map.
 * @return Filename written.
 */
const char* WriteTreePopulation2XMLFile11();

/**
 * Writes a parameter file for error testing.  This contains an initial
 * density value that is negative.
 * @return Filename written.
 */
const char* WriteTreePopulation2XMLErrorFile1();

/**
 * Writes a parameter file for error testing.  This contains an initial
 * density value that cannot be converted into a number.
 * @return Filename written.
 */
const char* WriteTreePopulation2XMLErrorFile2();

/**
 * Writes a parameter file for error testing.  This contains initial
 * densities with no size classes.
 * @return Filename written.
 */
const char* WriteTreePopulation2XMLErrorFile3();

/**
 * Writes a parameter file for error testing.  This contains an initial
 * density value for an unrecognized species.
 * @return Filename written.
 */
const char* WriteTreePopulation2XMLErrorFile4();

/**
 * Writes a parameter file for error testing.  This contains an initial
 * density value with an unrecognized size class.
 * @return Filename written.
 */
const char* WriteTreePopulation2XMLErrorFile5();

/**
 * Writes a parameter file for error testing.  This contains an initial
 * density class that cannot be converted into a number.
 * @return Filename written.
 */
const char* WriteTreePopulation2XMLErrorFile6();

/**
 * Writes a parameter file for error testing.  This contains a seedling height
 * class taller than 135.
 * @return Filename written.
 */
const char* WriteTreePopulation2XMLErrorFile7();

/**
 * Writes a parameter file for error testing.  An upper bound for the first
 * seedling height class is above the value for the upper bound of the second
 * seedling height class for that species.
 * @return Filename written.
 */
const char* WriteTreePopulation2XMLErrorFile8();

/**
 * Writes a tab-delimited text tree map.
 * @return Filename written.
 */
const char* WriteTreePopulation2TextTreeMap();

/**
 * Writes a tab-delimited text tree map.
 * @return Filename written.
 */
const char* WriteTreePopulation2TextTreeMap2();

/**
 * Writes a common portion of the test parameter files.  This writes from
 * the beginning of the file to "&lt;/plot&gt;".
 * @param oOut File stream to write to.
 */
void WriteTreePopulation2CommonPlotStuff(std::fstream &oOut);

/**
 * Writes a common portion of the test parameter files.  This writes all
 * tree parameters and the rest of the plot.
 * @param oOut File stream to write to.
 */
void WriteTreePopulation2CommonFileStuff(std::fstream &oOut);
//---------------------------------------------------------------------------
#endif // TestTreePopulation2_H
