//---------------------------------------------------------------------------
// TestNCISizeEffectExponentialHeight
//---------------------------------------------------------------------------
#if !defined(TestNCISizeEffectExponentialHeight_H)
#define TestNCISizeEffectExponentialHeight_H
#include <fstream>
/**
 * Tests the NCI size effect exponential function of height.
 */

/**
 * Writes a 1-year timestep file. This contains 4 species. NCI growth
 * (auto-height) is assigned to saplings and adults of Species 2, 3, and 4.
 * @return Filename written.
 */
const char* WriteNCISizeEffectExpHeightXMLFile1();

/**
 * Writes a 3-year timestep file. This contains 4 species. NCI growth
 * (auto-height) is assigned to saplings and adults of Species 2, 3, and 4.
 * @return Filename written.
 */
const char* WriteNCISizeEffectExpHeightXMLFile2();

/**
 * Writes common portions of the test parameter files (tree pop, plot, etc).
 * @param oOut File stream to write to.
 */
void WriteNCISizeEffectExpHeightCommonStuff(std::fstream &oOut);

/**
 * Writes common portions of the test parameter files (tree pop, plot, etc).
 * @param oOut File stream to write to.
 */
void WriteNCISizeEffectExpHeightTreeStuff(std::fstream &oOut);

//---------------------------------------------------------------------------
#endif
