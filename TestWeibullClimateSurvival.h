//---------------------------------------------------------------------------
// TestWeibullClimateSurvival
//---------------------------------------------------------------------------
#if !defined(TestWeibullClimateSurvival_H)
#define TestWeibullClimateSurvival_H
#include <fstream>

class clTreePopulation;

/**
 * Tests the clNCIMasterMortality class, as it now encompasses the old
 * clWeibullClimateSurvival class.
 */

void CreateWeibullClimateSurvivalTrees(clTreePopulation *p_oPop);

/**
 * Writes a parameter file with the designated number of years per time step.
 * @param iYearsPerTimestep The desired number of years per time step.
 * @return Filename written.
 */
const char* WriteWeibullClimateSurvivalXMLFile(int iYearsPerTimestep );

/**
 * Writes an error condition where max radius of neighbor effects is < 0.
 * @return Filename written.
 */
const char* WriteWeibullClimateSurvivalXMLErrorFile1();

/**
 * Writes an error condition where max survival for a species is < 0.
 * @return Filename written.
 */
const char* WriteWeibullClimateSurvivalXMLErrorFile2();

/**
 * Writes an error condition where Xb for a species = 0.
 * @return Filename written.
 */
const char* WriteWeibullClimateSurvivalXMLErrorFile3();

/**
 * Writes an error condition where X0 for a species = 0.
 * @return Filename written.
 */
const char* WriteWeibullClimateSurvivalXMLErrorFile4();

/**
 * Writes an error condition where a precipitation A = 0.
 * @return Filename written.
 */
const char* WriteWeibullClimateSurvivalXMLErrorFile5();

/**
 * Writes an error condition where a temperature A = 0.
 * @return Filename written.
 */
const char* WriteWeibullClimateSurvivalXMLErrorFile6();

/**
 * Writes common portions of the test parameter files (tree pop, plot, etc).
 * Picks up right after the number of years per timestep and finishes out the
 * file.
 * @param oOut File stream to write to.
 */
void WriteWeibullClimateSurvivalCommonStuff(std::fstream &oOut);

/**
 * Writes common portions of the test parameter files (tree pop, plot, etc).
 * @param oOut File stream to write to.
 */
void WriteWeibullClimateSurvivalTreeStuff(std::fstream &oOut);

/**
 * Writes common portions of the test error parameter files (tree pop, plot,
 * etc).  Starts at the beginning of the file and ends at the closing tree tag.
 * @param oOut File stream to write to.
 */
void WriteWeibullClimateSurvivalErrorFileCommonStuff(std::fstream &oOut);
//---------------------------------------------------------------------------
#endif // TestWeibullClimateSurvival_H
