//---------------------------------------------------------------------------
// TestBrowsedRelativeGrowth
//---------------------------------------------------------------------------
#if !defined(TestBrowsedRelativeGrowth_H)
#define TestBrowsedRelativeGrowth_H

#include <fstream>

/**
 * Writes a parameter file for normal run 1.
 * @return Filename written.
 */
const char* WriteBrowsedRelativeGrowthXMLFile1();

/**
 * Writes a parameter file for normal run 2.
 * @return Filename written.
 */
const char* WriteBrowsedRelativeGrowthXMLFile2();

/**
 * Writes a parameter file for normal run 3.
 * @return Filename written.
 */
const char* WriteBrowsedRelativeGrowthXMLFile3();

/**
 * Writes a parameter file where not all trees also have light.
 * @return Filename written.
 */
const char* WriteBrowsedRelativeGrowthXMLErrorFile1();

/**
 * Writes a parameter file where not all trees also have browsing.
 * @return Filename written.
 */
const char* WriteBrowsedRelativeGrowthXMLErrorFile2();

/**
 * Writes common portions of the test parameter files (tree pop, plot,
 * etc).
 * @param oOut File stream to write to.
 */
void WriteBrowsedRelativeGrowthPlotAndTrees(std::fstream &oOut);

/**
 * Writes common parameters of the test parameter file.
 * @param oOut File stream to write to.
 */
void WriteBrowsedRelativeGrowthCommonParameters(std::fstream &oOut);
//---------------------------------------------------------------------------
#endif // TestBrowsedRelativeGrowth_H
