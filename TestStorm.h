//---------------------------------------------------------------------------
// TestStorm
//---------------------------------------------------------------------------
#if !defined(TestStorm_H)
#define TestStorm_H
#include <fstream>

/**
 * Writes a parameter file with the specifications given for
 * TestNormalDeterministic().
 * @return Filename written.
 */
const char* WriteStormXMLFile1();

/**
 * Writes a parameter file with the specifications given for
 * TestNormalMappedDeterministic().
 * @return Filename written.
 */
const char* WriteStormXMLFile2();

/**
 * Writes a parameter file with the specifications given for
 * TestNormalStochastic().
 * @return Filename written.
 */
const char* WriteStormXMLFile3();

/**
 * Writes a parameter file with the specifications given for
 * TestNormalMappedStochastic().
 * @return Filename written.
 */
const char* WriteStormXMLFile4();

/**
 * Writes a parameter file with the specifications given for
 * TestMultiYearTimesteps().
 * @return Filename written.
 */
const char* WriteStormXMLFile5();

/**
 * Writes a parameter file where there are grid maps for both "Storm Damage"
 * and "Storm Susceptibility" and the grid cell resolutions don't match.
 * @return Filename written.
 */
const char* WriteStormXMLErrorFile1();

/**
 * Writes a parameter file where the damage pattern is set to "mapped" but
 * there is no "Storm Susceptibility" grid map in the parameter file.
 * @return Filename written.
 */
const char* WriteStormXMLErrorFile2();

/**
 * Writes a parameter file where not all storm interval return values are
 * greater than 0.
 * @return Filename written.
 */
const char* WriteStormXMLErrorFile3();

/**
 * Writes a parameter file where the value for susceptibility pattern in the
 * parameter file is not recognized.
 * @return Filename written.
 */
const char* WriteStormXMLErrorFile4();

/**
 * Writes a parameter file where the damage pattern is "stochastic" and there
 * is no value for probability distribution function.
 * @return Filename written.
 */
const char* WriteStormXMLErrorFile5();

/**
 * Writes a parameter file where the damage pattern is "stochastic" and the
 * value for probability distribution function is not recognized.
 * @return Filename written.
 */
const char* WriteStormXMLErrorFile6();

/**
 * Writes a parameter file where the damage pattern is "stochastic", the
 * probability distribution function is "normal" or "lognormal", and there is
 * no value for standard deviation.
 * @return Filename written.
 */
const char* WriteStormXMLErrorFile7();

/**
 * Writes a parameter file where the value for stochasticity is not recognized.
 * @return Filename written.
 */
const char* WriteStormXMLErrorFile8();

/**
 * Writes a parameter file where a scheduled storm's minimum is greater than
 * its maximum.
 * @return Filename written.
 */
const char* WriteStormXMLErrorFile9();

/**
 * Writes a parameter file where a scheduled storm's minimum is not between
 * 0 and 1.
 * @return Filename written.
 */
const char* WriteStormXMLErrorFile10();

/**
 * Writes a parameter file where a scheduled storm's maximum is not between
 * 0 and 1.
 * @return Filename written.
 */
const char* WriteStormXMLErrorFile11();

/**
 * Writes the portion of the parameter file common to all test files.
 * @param oOut File stream to write to.
 */
void WriteStormCommonStuff(std::fstream &oOut);

//---------------------------------------------------------------------------
#endif // TestStorm_H
