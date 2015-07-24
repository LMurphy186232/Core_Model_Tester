//---------------------------------------------------------------------------
// TestWeibullClimateGrowth
//---------------------------------------------------------------------------
#if !defined(TestWeibullClimateGrowth_H)
#define TestWeibullClimateGrowth_H
#include <fstream>
/**
 * Tests a legacy configuration of clNCIMasterGrowth - the
 * clWeibullClimateGrowth class, whose functionality got folded into it.
 */

/**
 * Writes a 1-year timestep file. This contains 4 species.  Weibull climate
 * growth (auto-height) is assigned to saplings and adults of Species 2, 3,
 * and 4.
 * @return Filename written.
 */
const char* WriteWeibullClimateGrowthXMLFile1();

/**
 * Writes a 3-year timestep file. This contains 4 species.  Weibull climate
 * growth (auto-height) is assigned to saplings and adults of Species 2, 3,
 * and 4.
 * @return Filename written.
 */
const char* WriteWeibullClimateGrowthXMLFile2();

/**
 * Writes a 1-year timestep file. Same as File 1, but with a nitrogen effect
 * as well.
 * @return Filename written.
 */
const char* WriteWeibullClimateGrowthXMLFile3();

/**
 * Writes an error condition where max radius of neighbor effects is < 0.
 * @return Filename written.
 */
const char* WriteWeibullClimateGrowthXMLErrorFile1();

/**
 * Writes an error condition where max growth for a species is < 0.
 * @return Filename written.
 */
const char* WriteWeibullClimateGrowthXMLErrorFile2();

/**
 * Writes an error condition where Xb for a species = 0.
 * @return Filename written.
 */
const char* WriteWeibullClimateGrowthXMLErrorFile3();

/**
 * Writes an error condition where X0 for a species = 0.
 * @return Filename written.
 */
const char* WriteWeibullClimateGrowthXMLErrorFile4();

/**
 * Writes an error condition where a precipitation A = 0.
 * @return Filename written.
 */
const char* WriteWeibullClimateGrowthXMLErrorFile5();

/**
 * Writes an error condition where a temperature A = 0.
 * @return Filename written.
 */
const char* WriteWeibullClimateGrowthXMLErrorFile6();

/**
 * Writes an error condition where a nitrogen Xb = 0.
 * @return Filename written.
 */
const char* WriteWeibullClimateGrowthXMLErrorFile7();

/**
 * Writes common portions of the test parameter files (tree pop, plot, etc).
 * Picks up right after the number of years per timestep and finishes out the
 * file.
 * @param oOut File stream to write to.
 * @param iPrecipType Precipitation type.
 */
void WriteWeibullClimateGrowthCommonStuff(std::fstream &oOut, int iPrecipType);

/**
 * Writes common portions of the test parameter files (tree pop, plot, etc).
 * @param oOut File stream to write to.
 */
void WriteWeibullClimateGrowthTreeStuff(std::fstream &oOut);

/**
 * Writes common portions of the test error parameter files (tree pop, plot,
 * etc).  Starts at the beginning of the file and ends at the closing tree tag.
 * @param oOut File stream to write to.
 */
void WriteWeibullClimateGrowthErrorFileCommonStuff(std::fstream &oOut);
//---------------------------------------------------------------------------
#endif // TestWeibullClimateGrowth_H
