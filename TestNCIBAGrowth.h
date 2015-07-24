//---------------------------------------------------------------------------
// TestNCIBAGrowth
//---------------------------------------------------------------------------
#if !defined(TestNCIBAGrowth_H)
#define TestNCIBAGrowth_H

#include <fstream>

/**
 * Writes a parameter file to direct testing. This contains two species,
 * identical in all ways except Species 1 is assigned NCI growth
 * as a diameter-auto, and Species 2 is assigned NCI growth as diameter-only.
 *
 * @return Filename written.
 */
const char* WriteNCIBAGrowthXMLFile1();

/**
 * Writes a 1-year timestep file. This contains 4 species. NCI growth
 * (auto-height) is assigned to saplings and adults of Species 2, 3, and 4.
 *
 * @return Filename written.
 */
const char* WriteNCIBAGrowthXMLFile2();

/**
 * Writes a 3-year timestep file. This contains 4 species. NCI growth
 * (auto-height) is assigned to saplings and adults of Species 2, 3, and 4.
 *
 * @return Filename written.
 */
const char* WriteNCIBAGrowthXMLFile3();

/**
 * Writes a 1-year timestep file. This contains 4 species. NCI growth
 * (auto-height) is assigned to saplings and adults of Species 2, 3, and 4.
 *
 * @return Filename written.
 */
const char* WriteNCIBAGrowthXMLFile4();

/**
 * Writes an error condition where max radius of neighbor effects is < 0.
 *
 * @return Filename written.
 */
const char* WriteNCIBAGrowthXMLErrorFile1();

/**
 * Writes an error condition where a neighbor DBH is less than 0.
 *
 * @return Filename written.
 */
const char* WriteNCIBAGrowthXMLErrorFile2();

/**
 * Writes common portions of the test parameter files (tree pop, plot, etc).
 * Picks up right after the number of years per timestep and finishes out the
 * file.
 * @param oOut File stream to write to.
 */
void WriteNCIBAGrowthCommonStuff(std::fstream &oOut);

/**
 * Writes common portions of the test parameter files (tree pop, plot, etc).
 * @param oOut File stream to write to.
 */
void WriteNCIBAGrowthTreeStuff(std::fstream &oOut);

/**
 * Writes common portions of the test error parameter files (tree pop, plot,
 * etc). Starts at the beginning of the file and ends at the closing tree tag.
 * @param oOut File stream to write to.
 */
void WriteNCIBAGrowthErrorFileCommonStuff(std::fstream &oOut);
//---------------------------------------------------------------------------
#endif // TestNCIBAGrowth_H
