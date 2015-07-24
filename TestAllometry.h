//---------------------------------------------------------------------------
// TestAllometry
//---------------------------------------------------------------------------
#if !defined(TestAllometry_H)
#define TestAllometry_H


/**
 * Tests the clAllometry class.
 */

/**
 * Writes a parameter file to test allometry.  This contains six species, with
 * functions mixed up between them.
 * @return Filename written.
 */
const char* WriteAllometryXMLFile1();

/**
 * This writes a file with only standard functions and parameters, to make
 * sure that the others aren't required if not needed.
 * @return Filename written.
 */
const char* WriteAllometryXMLFile2();

/**
 * This writes a file with only linear functions and parameters, to make
 * sure that the others aren't required if not needed.
 * @return Filename written.
 */
const char* WriteAllometryXMLFile3();

/**
 * This writes a file with only reverse linear functions and parameters, to
 * make sure that the others aren't required if not needed.
 * @return Filename written.
 */
const char* WriteAllometryXMLFile4();

/**
 * This writes a file with linear height-DBH and standard crown adult
 * parameters, and standard height-DBH and Chapman-Richards sapling
 * parameters, to make sure arrays are declared correctly.
 * @return Filename written.
 */
const char* WriteAllometryXMLFile5();

/**
 * This writes a file with linear height-DBH and Chapman-Richards crown adult
 * parameters, and standard sapling parameters, to make sure arrays are
 * declared correctly.
 * @return Filename written.
 */
const char* WriteAllometryXMLFile6();

/**
 * This writes a file with non-spatial density dependent crown allometry
 * parameters.
 * @return Filename written.
 */
const char* WriteAllometryXMLFile7();

/**
 * This writes a file with NCI crown allometry parameters.
 * @return Filename written.
 */
const char* WriteAllometryXMLFile8();

/**
 * This writes a file with an unrecognized function for adult allometry.
 * @return Filename written.
 */
const char* WriteAllometryXMLErrorFile1();

/**
 * This writes a file with an unrecognized function for sapling allometry.
 * @return Filename written.
 */
const char* WriteAllometryXMLErrorFile2();

/**
 * This writes a file with an unrecognized function for seedling allometry.
 * @return Filename written.
 */
const char* WriteAllometryXMLErrorFile3();

/**
 * This writes a file with a 0 value for adult linear slope.
 * @return Filename written.
 */
const char* WriteAllometryXMLErrorFile4();

/**
 * This writes a file with a 0 value for adult reverse linear slope.
 * @return Filename written.
 */
const char* WriteAllometryXMLErrorFile5();

/**
 * This writes a file with a 0 value for sapling linear slope.
 * @return Filename written.
 */
const char* WriteAllometryXMLErrorFile6();

/**
 * This writes a file with a 0 value for sapling reverse linear slope.
 * @return Filename written.
 */
const char* WriteAllometryXMLErrorFile7();

/**
 * This writes a file with a 0 value for seedling linear slope.
 * @return Filename written.
 */
const char* WriteAllometryXMLErrorFile8();

/**
 * This writes a file with a 0 value for seedling reverse linear slope.
 * @return Filename written.
 */
const char* WriteAllometryXMLErrorFile9();

/**
 * This writes a file with a 0 value for diam10 to dbh ratio.
 * @return Filename written.
 */
const char* WriteAllometryXMLErrorFile10();

/**
 * This writes a file with an unrecognized function for adult crown radius.
 * @return Filename written.
 */
const char* WriteAllometryXMLErrorFile11();

/**
 * This writes a file with an unrecognized function for adult crown height.
 * @return Filename written.
 */
const char* WriteAllometryXMLErrorFile12();

/**
 * This writes a file with an unrecognized function for sapling crown radius.
 * @return Filename written.
 */
const char* WriteAllometryXMLErrorFile13();

/**
 * This writes a file with an unrecognized function for sapling crown height.
 * @return Filename written.
 */
const char* WriteAllometryXMLErrorFile14();

//---------------------------------------------------------------------------
#endif // TestTree_H
