//---------------------------------------------------------------------------
// TestDimensionAnalysis
//---------------------------------------------------------------------------
#if !defined(TestDimensionAnalysis_H)
#define TestDimensionAnalysis_H

#include <fstream>
class clTreePopulation;
class clTree;

/**
 * Writes the parameter file for run 1.  There are 19 species (Species 13 is
 * not used).  The biomass calculator is the only behavior and is applied to
 * saplings and adults of all used species.  All 18 used species use equation
 * 1.  The first 9 use a correction factor; the second 9 don't.
 * @return Filename written.
 */
const char* WriteDimensionAnalysisXMLFile1();

/**
 * Writes the parameter file for run 2.  There are 19 species (Species 13 is
 * not used).  The biomass calculator is the only behavior and is applied to
 * saplings and adults of all used species.  All 18 used species use equation
 * 2.  The first 9 use a correction factor; the second 9 don't.
 * @return Filename written.
 */
const char* WriteDimensionAnalysisXMLFile2();

/**
 * Writes the parameter file for run 3.  There are 19 species (Species 13 is
 * not used).  The biomass calculator is the only behavior and is applied to
 * saplings and adults of all used species.  All 18 used species use equation
 * 3.  The first 9 use a correction factor; the second 9 don't.
 * @return Filename written.
 */
const char* WriteDimensionAnalysisXMLFile3();

/**
 * Writes the parameter file for run 4.  There are 19 species (Species 13 is
 * not used).  The biomass calculator is the only behavior and is applied to
 * saplings and adults of all used species.  The first 9 species use equation
 * 4; the second 9 use equation 5.
 * @return Filename written.
 */
const char* WriteDimensionAnalysisXMLFile4();

/**
 * Writes the parameter file for run 5.  There are 19 species (Species 13 is
 * not used).  The biomass calculator is the only behavior and is applied to
 * saplings and adults of all used species.  The first 9 species use equation
 * 6; the second 9 use equation 7.
 * @return Filename written.
 */
const char* WriteDimensionAnalysisXMLFile5();

/**
 * Writes the parameter file for run 6.  There are 19 species (Species 13 is
 * not used).  The biomass calculator is the only behavior and is applied to
 * saplings and adults of all used species.  All 18 used species use equation
 * 8.  The first 9 use a correction factor; the second 9 don't.
 * @return Filename written.
 */
const char* WriteDimensionAnalysisXMLFile6();

/**
 * Writes the parameter file for run 7.  There are 19 species (Species 13 is
 * not used).  The biomass calculator is the only behavior and is applied to
 * saplings and adults of all used species.  All 18 used species use equation
 * 9.  The first 9 use a correction factor; the second 9 don't.
 * @return Filename written.
 */
const char* WriteDimensionAnalysisXMLFile7();

/**
 * Writes the parameter file for run 8. There are 19 species but only the first
 * 9 are used. The biomass calculator is the only behavior and is applied to
 * saplings and adults of all used species. All used species use dia=DBH^2.
 * @return Filename written.
 */
const char* WriteDimensionAnalysisXMLFile8();

/**
 * Writes an error file where an equation ID is unrecognized.
 * @return Filename written.
 */
const char* WriteDimensionAnalysisXMLErrorFile1();

/**
 * Writes an error file where a DBH units value is unrecognized.
 * @return Filename written.
 */
const char* WriteDimensionAnalysisXMLErrorFile2();

/**
 * Writes an error file where the biomass calculator is applied to a seedling.
 * @return Filename written.
 */
const char* WriteDimensionAnalysisXMLErrorFile3();

/**
 * Writes an error file where a biomass units value is unrecognized.
 * @return Filename written.
 */
const char* WriteDimensionAnalysisXMLErrorFile4();

/**
 * Writes an error file where a correction factor flag value is unrecognized.
 * @return Filename written.
 */
const char* WriteDimensionAnalysisXMLErrorFile5();

/**
 * Writes an error file where a dia meaning value is unrecognized.
 * @return Filename written.
 */
const char* WriteDimensionAnalysisXMLErrorFile6();

/**
 * Writes common portions of the test parameter files (tree pop, plot, etc).
 * This ends with &lt;/behaviorList&gt.
 * @param oOut File stream to write to.
 */
void WriteDimensionAnalysisCommonStuff(std::fstream &oOut);

/**
 * Writes common portions of the test parameter files (tree pop, plot, etc).
 * This ends with &lt;/behaviorList&gt.  There are only two species for this
 * file.
 * @param oOut File stream to write to.
 */
void WriteDimensionAnalysisCommonErrorStuff(std::fstream &oOut);

/**
 * Creates the trees.  3 of each species are created (Species 1 to Species 19,
 * Species 13 excepted).  There is one of DBH 5 cm, one of DBH 50 cm, and
 * one of DBH 100 cm.  Pointers to the new trees are placed in the passed
 * array.
 * @param p_oPop Tree population object.
 * @return Array of created trees, 54 trees long.
 */
clTree** CreateDimensionAnalysisTrees(clTreePopulation *p_oPop);
//---------------------------------------------------------------------------
#endif // TestBiomassCalculator_H
