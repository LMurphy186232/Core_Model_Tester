//---------------------------------------------------------------------------

#ifndef TestSimManagerH
#define TestSimManagerH


/**
 * Tests the class clSimManager.
 */


/**
 * Writes the text of an XML file.
 * This contains a positive random seed, which should become negative.
 * @return The filename of the XML file to parse.
 */
const char* WriteSimManagerXMLFile1();

/**
 * Writes the text of an XML file.
 * This contains a random seed of 0, which should become negative.
 * @return The filename of the XML file to parse.
 */
const char* WriteSimManagerXMLFile2();

/**
 * Writes the text of an XML file.
 * This contains a negative random seed, which should be left alone.
 * @return The filename of the XML file to parse.
 */
const char* WriteSimManagerXMLFile3();

/**
 * Writes an XML file which contains a data error, to test if the test
 * object will throw an exception. Number of timesteps is negative.
 * @return The filename of the XML file to parse.
 */
const char* WriteSimManagerXMLErrorFile1();

/**
 * Writes an XML file which contains a data error, to test if the test
 * object will throw an exception. Current timestep is too big.
 * @return The filename of the XML file to parse.
 */
const char* WriteSimManagerXMLErrorFile2();

/**
 * Writes an XML file which contains a data error, to test if the test
 * object will throw an exception. Years per timestep is 0.
 * @return The filename of the XML file to parse.
 */
const char* WriteSimManagerXMLErrorFile3();

//---------------------------------------------------------------------------
#endif
