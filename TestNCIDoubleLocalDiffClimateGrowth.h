//---------------------------------------------------------------------------
// TestNCIDoubleLocalDiffClimateGrowth
//---------------------------------------------------------------------------
#if !defined(TestNCIDoubleNoLocalDiffClimateGrowth_H)
#define TestNCIDoubleNoLocalDiffClimateGrowth_H
#include <fstream>
/**
 * Tests a configuration of clNCIMasterGrowth and clNCIMasterMortality.
 */

/**
 * Writes a 1-year timestep file. This contains 8 species. NCI growth
 * (auto-height) is assigned to saplings and adults of Species 2, 3, 4,
 * 5, 6, and 7.
 * @return Filename written.
 */
const char* WriteNCIDoubleLocalDiffClimateGrowthXMLFile1();

/**
 * Writes a 1-year timestep file. This contains 8 species. NCI growth
 * (auto-height) is assigned to saplings and adults of Species 2, 3, 4,
 * 5, 6, and 7.
 * @return Filename written.
 */
const char* WriteNCIDoubleLocalDiffClimateGrowthXMLFile2();

/**
 * Writes common parameter file stuff.
 * @param oOut File stream to write to.
 */
void WriteNCIDoubleLocalCommon(std::fstream &oOut);
//---------------------------------------------------------------------------
#endif // TestNCIDoubleLocalDiffClimateGrowth_H
