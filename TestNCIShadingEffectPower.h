//---------------------------------------------------------------------------
// TestNCIShadingEffectPower
//---------------------------------------------------------------------------
#if !defined(TestNCIShadingEffectPower_H)
#define TestNCIShadingEffectPower_H
#include <fstream>
/**
 * Tests the NCI shading effect that is a power function of GLI.
 */

/**
 * Writes a 1-year timestep file. This contains 4 species. NCI growth
 * (auto-height) is assigned to saplings and adults of Species 2, 3, and 4.
 * @return Filename written.
 */
const char* WriteNCIShadingPowerXMLFile1();

/**
 * Writes a 3-year timestep file. This contains 4 species. NCI growth
 * (auto-height) is assigned to saplings and adults of Species 2, 3, and 4.
 * @return Filename written.
 */
const char* WriteNCIShadingPowerXMLFile2();

/**
 * Writes common portions of the test parameter files (tree pop, plot, etc).
 * @param oOut File stream to write to.
 */
void WriteNCIShadingPowerCommonStuff(std::fstream &oOut);

/**
 * Writes common portions of the test parameter files (tree pop, plot, etc).
 * @param oOut File stream to write to.
 */
void WriteNCIShadingPowerTreeStuff(std::fstream &oOut);

//---------------------------------------------------------------------------
#endif
