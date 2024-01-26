//---------------------------------------------------------------------------
// TestNCIDoubleNoLocalDiffClimateGrowth
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
const char* WriteNCIDoubleNoLocalDiffClimateGrowthXMLFile1();

/**
 * Writes a 1-year timestep file. This contains 4 species. NCI growth
 * (auto-height) is assigned to saplings and adults of Species 2, 3, and 4.
 * @return Filename written.
 */
const char* WriteNCIDoubleNoLocalDiffClimateGrowthXMLFile2();

/**
 * Writes a 1-year timestep file. This is solely to test the heteroscedastic
 * normal growth adjustment.
 * @return Filename written.
 */
const char* WriteNCIDoubleNoLocalDiffClimateGrowthXMLFile3();
//---------------------------------------------------------------------------
#endif // TestNCIDoubleNoLocalDiffClimateGrowth_H
