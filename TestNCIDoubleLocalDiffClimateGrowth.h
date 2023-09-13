//---------------------------------------------------------------------------
// TestNCIDoubleLocalDiffClimateGrowth
//---------------------------------------------------------------------------
#if !defined(TestNCIDoubleNoLocalDiffClimateGrowth_H)
#define TestNCIDoubleNoLocalDiffClimateGrowth_H
#include <fstream>
/**
 * Tests a configuration of clNCIMasterGrowth.
 */

/**
 * Writes a 1-year timestep file. This contains 8 species. NCI growth
 * (auto-height) is assigned to saplings and adults of Species 2, 3, 4,
 * 5, 6, and 7.
 * @return Filename written.
 */
const char* WriteNCIDoubleLocalDiffClimateGrowthXMLFile1();
//---------------------------------------------------------------------------
#endif // TestNCIDoubleLocalDiffClimateGrowth_H
