//---------------------------------------------------------------------------
// TestNCICrowdingEffectBARatio
//---------------------------------------------------------------------------
#if !defined(TestNCICrowdingEffectBARatio_H)
#define TestNCICrowdingEffectBARatio_H
#include <fstream>

/**
 * Writes a 1-year timestep file. This contains 4 species. NCI growth
 * (auto-height) is assigned to saplings and adults of Species 2, 3, and 4.
 * @return Filename written.
 */
const char* WriteNCIXMLFile1();

/**
 * Writes a 3-year timestep file. This contains 4 species. NCI growth
 * (auto-height) is assigned to saplings and adults of Species 2, 3, and 4.
 * @return Filename written.
 */
const char* WriteNCIXMLFile2();

/**
 * Writes a 1-year timestep file. This contains 4 species. NCI quadrat growth
 * (auto-height) is assigned to saplings and adults of Species 2, 3, and 4.
 * @return Filename written.
 */
const char* WriteNCIXMLFile3();


/**
 * Writes common portions of the test parameter files (tree pop, plot, etc).
 * @param oOut File stream to write to.
 */
void WriteNCICommonStuff(std::fstream &oOut);

/**
 * Writes common portions of the test parameter files (tree pop, plot, etc).
 * @param oOut File stream to write to.
 */
void WriteNCITreeStuff(std::fstream &oOut);

//---------------------------------------------------------------------------
#endif
