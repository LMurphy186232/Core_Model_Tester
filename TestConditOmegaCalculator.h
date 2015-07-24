//---------------------------------------------------------------------------
// TestConditOmegaCalculator
//---------------------------------------------------------------------------
#if !defined(TestConditOmegaCalculator_H)
#define TestConditOmegaCalculator_H

#include <fstream>

class clTreePopulation;
class clPlot;
class clGrid;

/**
 * Creates the set of testing trees.
 * @param p_oPop Tree population
 * @param p_oPlot Plot object
 * @param fOffset Any offset to be applied to the tree coordinates
 */
void CreateTrees(clTreePopulation *p_oPop, clPlot *p_oPlot, float fOffset);

/**
 * Checks the results of the Condit's Omega grid for the first run.
 * @param p_oGrid Condit's Omega grid.
 */
void CheckConditOmegaCalculatorRun1Results(clGrid *p_oGrid);

/**
 * Writes the parameter file for normal processing. There are 4 species;
 * timestep length is 1 year; there is only one behavior, the Condit's Omega
 * calculator behavior.
 * @return Filename written.
 */
const char* WriteConditOmegaCalculatorXMLFile1();

/**
 * Writes the parameter file for normal processing. There are 4 species;
 * timestep length is 1 year; there is only one behavior, the Condit's Omega
 * calculator behavior.
 * @return Filename written.
 */
const char* WriteConditOmegaCalculatorXMLFile2();

/**
 * Writes the parameter file for normal processing. There are 4 species;
 * timestep length is 1 year; there is only one behavior, the Condit's Omega
 * calculator behavior.
 * @return Filename written.
 */
const char* WriteConditOmegaCalculatorXMLFile3();

/**
 * Writes the parameter file for normal processing. There are 4 species;
 * timestep length is 1 year; there is only one behavior, the Condit's Omega
 * calculator behavior.
 * @return Filename written.
 */
const char* WriteConditOmegaCalculatorXMLFile4();

/**
 * Writes an error file where the max distance is less than the increment.
 * @return Filename written.
 */
const char* WriteConditOmegaCalculatorXMLErrorFile1();

/**
 * Writes an error file where the max distance is less than zero.
 * @return Filename written.
 */
const char* WriteConditOmegaCalculatorXMLErrorFile2();

/**
 * Writes an error file where the increment is less than zero.
 * @return Filename written.
 */
const char* WriteConditOmegaCalculatorXMLErrorFile3();

/**
 * Writes common portions of the test parameter files between the plot and
 * the analysis parameters.
 * @param oOut File stream to write to.
 */
void WriteConditOmegaCalculatorCommonStuff(std::fstream &oOut);

//---------------------------------------------------------------------------
#endif // TestConditOmegaCalculator_H
