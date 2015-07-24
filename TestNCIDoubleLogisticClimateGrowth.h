//---------------------------------------------------------------------------
// TestNCIDoubleLogisticClimateGrowth
//---------------------------------------------------------------------------
#if !defined(TestNCIDoubleLogisticClimateGrowth_H)
#define TestNCIDoubleLogisticClimateGrowth_H
#include <fstream>
/**
 * Tests a configuration of clNCIMasterGrowth.
 */

/**
 * Writes a 1-year timestep file. This contains 4 species. NCI growth
 * (auto-height) is assigned to saplings and adults of Species 2, 3, and 4.
 * @return Filename written.
 */
const char* WriteNCIDoubleLogisticClimateGrowthXMLFile1();

/**
 * Writes a 3-year timestep file. This contains 4 species. NCI growth
 * (auto-height) is assigned to saplings and adults of Species 2, 3, and 4.
 * @return Filename written.
 */
const char* WriteNCIDoubleLogisticClimateGrowthXMLFile2();

/**
 * Writes a 1-year timestep file with stochastic growth.
 * @return Filename written.
 */
const char* WriteNCIDoubleLogisticClimateGrowthXMLFile3();

/**
 * Writes an error condition where size Xb for a species = 0.
 * @return Filename written.
 */
const char* WriteNCIDoubleLogisticClimateGrowthXMLErrorFile1();

/**
 * Writes an error condition where size X0 for a species = 0.
 * @return Filename written.
 */
const char* WriteNCIDoubleLogisticClimateGrowthXMLErrorFile2();

/**
 * Writes common portions of the test parameter files (tree pop, plot, etc).
 * @param oOut File stream to write to.
 */
void WriteNCIDoubleLogisticClimateGrowthCommonStuff(std::fstream &oOut);

/**
 * Writes common portions of the test parameter files (tree pop, plot, etc).
 * @param oOut File stream to write to.
 */
void WriteNCIDoubleLogisticClimateGrowthTreeStuff(std::fstream &oOut);

/**
 * Writes common portions of the test error parameter files (tree pop, plot,
 * etc).  Starts at the beginning of the file and ends at the closing tree tag.
 * @param oOut File stream to write to.
 */
void WriteNCIDoubleLogisticClimateGrowthErrorFileCommonStuff(std::fstream &oOut);
//---------------------------------------------------------------------------
#endif // TestNCIDoubleLogisticClimateGrowth_H
