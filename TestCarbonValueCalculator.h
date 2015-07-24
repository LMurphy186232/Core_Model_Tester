//---------------------------------------------------------------------------
// TestCarbonValueCalculator
//---------------------------------------------------------------------------
#if !defined(TestCarbonValueCalculator_H)
#define TestCarbonValueCalculator_H

#include <fstream>

/**
 * Writes the parameter file for normal processing.  There are 19 species
 * (Species 13 is not used).  The biomass calculator is the only behavior and
 * is applied to saplings and adults of all used species.  All 18 used
 * species use dimension analysis equation 1.  The first 9 use a correction
 * factor; the second 9 don't.
 * @return Filename written.
 */
const char* WriteCarbonValueCalculatorXMLFile1();

/**
 * Writes an error file where the Dimension Analysis behavior is not enabled
 * for all trees for carbon value.
 * @return Filename written.
 */
const char* WriteCarbonValueCalculatorXMLErrorFile1();

/**
 * Writes an error file where the percentage of biomass that is carbon is
 * negative.
 * @return Filename written.
 */
const char* WriteCarbonValueCalculatorXMLErrorFile2();

/**
 * Writes an error file where the percentage of biomass that is carbon is
 * more than 100.
 * @return Filename written.
 */
const char* WriteCarbonValueCalculatorXMLErrorFile3();

/**
 * Writes common portions of the test parameter files (tree pop, plot, etc).
 * This ends with &lt;/behaviorList&gt.  There are only two species for this
 * file.
 * @param oOut File stream to write to.
 */
void WriteCarbonValueCalculatorCommonErrorStuff(std::fstream &oOut);
//---------------------------------------------------------------------------
#endif // TestBiomassCalculator_H
