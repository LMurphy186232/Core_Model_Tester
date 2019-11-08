//---------------------------------------------------------------------------
// TestInsectInfestation
//---------------------------------------------------------------------------
#if !defined(TestInsectInfestation_H)
#define TestInsectInfestation_H

class clTreePopulation;
#include <fstream>

/**
 * Writes the parameter file for TestNormalProcessingX().
 * @param iNumYrsTimestep Number of years per timestep.
 * @param iTSStart Timestep to start infection.
 * @param iTSEnd Timestep to end infection. If it is 0, it won't be
 * written at all (to check backwards compatibility).
 * @return File name of the freshly written parameter file.
 */
const char* WriteInsectInfestationXMLNormalFile(int iNumYrsTimestep, int iTSStart, int iTSEnd);

/**
 * Writes the parameter file for TestNormalProcessing3().
 * @return File name of the freshly written parameter file.
 */
const char* WriteInsectInfestationXMLFile3();

/**
 * Writes an error file where the minimum DBH is negative.
 * @return File name of the freshly written parameter file.
 */
const char* WriteInsectInfestationXMLErrorFile1();

/**
 * Writes an error file where the insect infestation behavior is applied
 * to seedlings.
 * @return File name of the freshly written parameter file.
 */
const char* WriteInsectInfestationXMLErrorFile2();

/**
 * Writes an error file where the timestep to start infestation is negative.
 * @return File name of the freshly written parameter file.
 */
const char* WriteInsectInfestationXMLErrorFile3();

/**
 * Writes an error file where the intercept is not between 0 and 1.
 * @return File name of the freshly written parameter file.
 */
const char* WriteInsectInfestationXMLErrorFile4();

/**
 * Writes an error file where max infestation is not between 0 and 1.
 * @return File name of the freshly written parameter file.
 */
const char* WriteInsectInfestationXMLErrorFile5();

/**
 * Writes an error file where X0 = zero.
 * @return File name of the freshly written parameter file.
 */
const char* WriteInsectInfestationXMLErrorFile6();

/**
 * Writes common portions of the test parameter files.
 * @param oOut File stream to write to.
 */
void WriteInsectInfestationErrorCommonStuff(std::fstream &oOut);

/**
 * Counts trees.
 * @param p_oPop Tree population
 * @param p_iTotal Total trees per species, sized 5.
 * @param p_iInfested Infested trees per species, sized 5.
 * @param bNoInfestation If true, there will be no checking of the years
 * infested value.
 */
void GetTreeCount1Yr(clTreePopulation *p_oPop, long *p_iTotal, long *p_iInfested,
    bool bNoInfestation);

/**
 * Counts trees.
 * @param p_oPop Tree population
 * @param p_iTotal Total trees per species, sized 5.
 * @param p_iInfested Infested trees per species, sized 5.
 * @param bNoInfestation If true, there will be no checking of the years
 * infested value.
 */
void GetTreeCount3Yrs(clTreePopulation *p_oPop, long *p_iTotal, long *p_iInfested,
    bool bNoInfestation);
//---------------------------------------------------------------------------
#endif //TestInsectInfestation_H
