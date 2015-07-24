//---------------------------------------------------------------------------
// TestRipleysKCalculator
//---------------------------------------------------------------------------
#if !defined(TestRipleysKCalculator_H)
#define TestRipleysKCalculator_H
#include <fstream>

class clTreePopulation;
class clGrid;
class clPlot;

/**
 * Tests the class clRipleysKCalculator.
 */

/**
 * Creates the set of testing trees.
 * @param p_oPop Tree population
 * @param p_oPlot Plot object
 * @param fOffset Any offset to be applied to the tree coordinates
 */
void CreateTrees(clTreePopulation *p_oPop, clPlot *p_oPlot, float fOffset);

/**
 * Checks the results of the Ripley's K grid for the first run.
 * @param p_oGrid Ripley's K grid.
 */
void CheckRipleysKRun1Results (clGrid *p_oGrid);

/**
 * Writes the parameter file for normal processing. There are 4 species;
 * timestep length is 1 year; there is only one behavior, the Ripley's K
 * calculator behavior.
 * @return Filename written.
 */
const char* WriteRipleysKCalculatorXMLFile1();

/**
 * Writes the parameter file for normal processing. There are 4 species;
 * timestep length is 1 year; there is only one behavior, the Ripley's K
 * calculator behavior.
 * @return Filename written.
 */
const char* WriteRipleysKCalculatorXMLFile2();

/**
 * Writes the parameter file for normal processing. There are 4 species;
 * timestep length is 1 year; there is only one behavior, the Ripley's K
 * calculator behavior.
 * @return Filename written.
 */
const char* WriteRipleysKCalculatorXMLFile3();

/**
 * Writes the parameter file for normal processing. There are 4 species;
 * timestep length is 1 year; there is only one behavior, the Ripley's K
 * calculator behavior.
 * @return Filename written.
 */
const char* WriteRipleysKCalculatorXMLFile4();

/**
 * Writes an error file where the max distance is less than the increment.
 * @return Filename written.
 */
const char* WriteRipleysKCalculatorXMLErrorFile1();

/**
 * Writes an error file where the max distance is less than zero.
 * @return Filename written.
 */
const char* WriteRipleysKCalculatorXMLErrorFile2();

/**
 * Writes an error file where the increment is less than zero.
 * @return Filename written.
 */
const char* WriteRipleysKCalculatorXMLErrorFile3();

/**
 * Writes common portions of the test parameter files between the plot and
 * the analysis parameters.
 * @param oOut File stream to write to.
 */
void WriteRipleysKCalculatorCommonStuff(std::fstream &oOut);
//---------------------------------------------------------------------------
#endif // TestRipleysKCalculator_H
