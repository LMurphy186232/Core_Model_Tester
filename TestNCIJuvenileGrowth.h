//---------------------------------------------------------------------------
// TestNCIJuvenileGrowth
//---------------------------------------------------------------------------
#if !defined(TestNCIJuvenileGrowth_H)
#define TestNCIJuvenileGrowth_H

#include <fstream>

//The NCIJuvenileGrowth behavior became folded into NCI master growth. This
//tests NCI when it is set up like NCIJuvenileGrowth.

/**
 * Writes a 1-year timestep file.  This contains 3 species.  NCI growth
 * (auto-height) is assigned to adults of Species 1.
 *
 * @return Filename written.
 */
const char* WriteNCIJuvenileGrowthXMLFile1();

/**
 * Writes a 3-year timestep file.  This contains 3 species.  NCI growth
 * (auto-height) is assigned to adults of Species 1.
 *
 * @return Filename written.
 */
const char* WriteNCIJuvenileGrowthXMLFile2();

/**
 * Writes a 1-year timestep file.  This contains 4 species, one unused
 * (species 3; this helps catch array-index problems).  NCI growth
 * (auto-height) is assigned to all saplings and adults.
 *
 * @return Filename written.
 */
const char* WriteNCIJuvenileGrowthXMLFile3();

/**
 * Writes a 3-year timestep file.  This contains 4 species, one unused
 * (species 3; this helps catch array-index problems).  NCI growth
 * (auto-height) is assigned to all saplings and adults.
 *
 * @return Filename written.
 */
const char* WriteNCIJuvenileGrowthXMLFile4();

/**
 * Writes an error condition where max radius of neighbor effects is < 0.
 *
 * @return Filename written.
 */
const char* WriteNCIJuvenileGrowthXMLErrorFile1();

/**
 * Writes an error condition where a min neighbor diam10 is less than 0.
 *
 * @return Filename written.
 */
const char* WriteNCIJuvenileGrowthXMLErrorFile2();

/**
 * Writes common portions of the test parameter files (tree pop, plot, etc).
 * Picks up right after the number of years per timestep and ends at the
 * closing tree tag.
 * @param oOut File stream to write to.
 */
void WriteNCIJuvenileGrowthCommonStuff(std::fstream &oOut);

/**
 * Writes common portions of the test parameter files for Run 1.
 * Picks up at the behavior list through the end of the file.
 * @param oOut File stream to write to.
 */
void WriteNCIJuvenileGrowthRunCommonStuff(std::fstream &oOut);

/**
 * Writes common portions of the test error parameter files (tree pop, plot,
 * etc).  Starts at the beginning of the file and ends at the closing tree tag.
 * @param oOut File stream to write to.
 */
void WriteNCIJuvenileGrowthErrorFileCommonStuff(std::fstream &oOut);
//---------------------------------------------------------------------------
#endif // TestNCIJuvenileGrowth_H
