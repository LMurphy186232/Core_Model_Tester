//---------------------------------------------------------------------------
// TestNCISizeEffectCompoundExponential
//---------------------------------------------------------------------------
#if !defined(TestNCISizeEffectCompoundExponential_H)
#define TestNCISizeEffectCompoundExponential_H
#include <fstream>
/**
 * Tests the NCI size effect compound exponential.
 */

/**
 * Writes a 1-year timestep file. This contains 4 species. NCI growth
 * (auto-height) is assigned to saplings and adults of Species 2, 3, and 4.
 * @return Filename written.
 */
const char* WriteNCISizeEffectXMLFile1();

/**
 * Writes a 3-year timestep file. This contains 4 species. NCI growth
 * (auto-height) is assigned to saplings and adults of Species 2, 3, and 4.
 * @return Filename written.
 */
const char* WriteNCISizeEffectXMLFile2();

/**
 * Writes common portions of the test parameter files (tree pop, plot, etc).
 * @param oOut File stream to write to.
 */
void WriteNCISizeEffectCommonStuff(std::fstream &oOut);

/**
 * Writes common portions of the test parameter files (tree pop, plot, etc).
 * @param oOut File stream to write to.
 */
void WriteNCISizeEffectTreeStuff(std::fstream &oOut);

//---------------------------------------------------------------------------
#endif
