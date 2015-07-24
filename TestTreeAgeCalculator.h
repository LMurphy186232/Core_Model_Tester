//---------------------------------------------------------------------------
// TestTreeAgeCalculator
//---------------------------------------------------------------------------
#if !defined(TestTreeAgeCalculator_H)
#define TestTreeAgeCalculator_H

/**
 * Tests the class clTreeAgeCalculator.
 */

/**
 * Writes the parameter file for normal processing.  There is 1 species;
 * timestep length is 1 year; there is only one behavior, the tree age
 * calculator behavior.  There are 30 trees in a tree map, 10 of which have
 * an age specified, 10 of which do not, and 10 of which do not have the
 * age behavior applied.
 * @return Filename written.
 */
const char* WriteTreeAgeCalculatorXMLFile1();

/**
 * Writes the parameter file for normal processing.  There is 1 species;
 * timestep length is 3 years; there is only one behavior, the tree age
 * calculator behavior.  There are also 10 trees per hectare as initial
 * conditions.
 * @return Filename written.
 */
const char* WriteTreeAgeCalculatorXMLFile2();

/**
 * Writes an error file where the behavior is applied to snags.
 */
const char* WriteTreeAgeCalculatorXMLErrorFile1();
//---------------------------------------------------------------------------
#endif // TestTreeAgeCalculator_H
