//---------------------------------------------------------------------------
// TestPowerHeightGrowth
//---------------------------------------------------------------------------
#if !defined(TestPowerHeightGrowth_H)
#define TestPowerHeightGrowth_H

#include <fstream>

/**
 * Tests the clPowerHeightGrowth class.
 */

/**
 * Writes a parameter file to direct testing for run 1. Timestep length is 1
 * year. This contains four species. Power height growth is applied to 3
 * species. Diameter incrementer applied as well.
 *
 * @return Filename written.
 */
const char* WritePowerHeightGrowthXMLFile1();

/**
 * Writes a parameter file to direct testing for run 1. Timestep length is 3
 * years. This contains four species. Relative height growth is applied to 3
 * species. Diameter incrementer applied as well.
 *
 * @return Filename written.
 */
const char* WritePowerHeightGrowthXMLFile2();

/**
 * Writes common portions of the test parameter files.
 * @param oOut File stream to write to.
 */
void WritePowerHeightGrowthCommonStuff(std::fstream &oOut);
//---------------------------------------------------------------------------
#endif // TestPowerHeightGrowth_H
