//---------------------------------------------------------------------------
#ifndef TestLightFilterH
#define TestLightFilterH


class clTreePopulation;

/**
 * Verifies the values after WriteLightFilterXMLFile1 has been executed.
 *
 * @param p_oPop Tree population.
 */
void VerifyXMLFile1(clTreePopulation *p_oPop);

/**
 * Sets the initial conditions for each tree prior to running the light filter
 * behavior.  This assumes the trees have already been created.  Each tree
 * will have its "Z" and "Light" value set according to the test script.
 * @param p_oPop Tree population.
 */
void SetTreeValues(clTreePopulation *p_oPop);

/**
 * Writes a parameter file to direct testing.  This contains all tree
 * information and light filter information, and a behavior list that
 * includes quadratlight (for correct registration of "light" tree data
 * member) and the light filter behavior.  It also has a tree map so we'll be
 * dealing with a known list of trees.
 * @return Filename written.
 */
const char* WriteLightFilterXMLFile1();

/**
 * Writes a file designed to produce an error in setup.  The error is that
 * there is not a light behavior assigned to all species/types that use
 * light filtering.
 */
const char* WriteLightFilterXMLErrorFile1();
//---------------------------------------------------------------------------
#endif
