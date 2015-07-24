//---------------------------------------------------------------------------
// TestStochasticGapGrowth
//---------------------------------------------------------------------------
#if !defined(TestStochasticGapGrowth_H)
#define TestStochasticGapGrowth_H

/**
 * Writes a parameter file for normal processing. There are three species.
 * The behaviors are gap light and stochastic gap growth.
 * @return Filename written.
 */
const char* WriteStochasticGapGrowthXMLFile1();

/**
 * Writes a parameter file for error processing. In this case, the stochastic
 * gap growth function is in the behavior list but the gap light behavior
 * is not.
 * @return Filename written.
 */
const char* WriteStochasticGapGrowthXMLErrorFile1();
//---------------------------------------------------------------------------
#endif // TestStochasticGapGrowth_H
