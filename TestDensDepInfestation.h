//---------------------------------------------------------------------------
// TestDensDepInfestation
//---------------------------------------------------------------------------
#if !defined(TestDensDepInfestation_H)
#define TestDensDepInfestation_H

class clTreePopulation;
#include <fstream>

/**
 * Writes the parameter file for TestNormalProcessing1().
 * @param iNumYrsTimestep Number of years per timestep.
 * @return File name of the freshly written parameter file.
 */
const char* WriteDensDepInfestationXMLFile1();

/**
 * Writes the parameter file for TestNormalProcessing2().
 * @return File name of the freshly written parameter file.
 */
const char* WriteDensDepInfestationXMLFile2();

/**
 * Writes the parameter file for TestNormalProcessing3().
 * @return File name of the freshly written parameter file.
 */
const char* WriteDensDepInfestationXMLFile3();

/**
 * Writes an error file where the minimum DBH is negative.
 * @return File name of the freshly written parameter file.
 */
const char* WriteDensDepInfestationXMLErrorFile1();

/**
 * Writes an error file where the insect infestation behavior is applied
 * to seedlings.
 * @return File name of the freshly written parameter file.
 */
const char* WriteDensDepInfestationXMLErrorFile2();

/**
 * Writes an error file where the probability of conditional susceptibility is
 * not between 0 and 1.
 * @return File name of the freshly written parameter file.
 */
const char* WriteDensDepInfestationXMLErrorFile3();

/**
 * Writes an error file where a value in the cohort cutoff DBH is less than 0.
 * @return File name of the freshly written parameter file.
 */
const char* WriteDensDepInfestationXMLErrorFile4();

/**
 * Writes an error file where max infestation is not between 0 and 1.
 * @return File name of the freshly written parameter file.
 */
const char* WriteDensDepInfestationXMLErrorFile5();

/**
 * Writes an error file where the probability of resistance is not between 0 and 1
 * @return File name of the freshly written parameter file.
 */
const char* WriteDensDepInfestationXMLErrorFile6();

/**
 * Writes common portions of the test parameter files.
 * @param oOut File stream to write to.
 */
void WriteDensDepInfestationErrorCommonStuff(std::fstream &oOut);

/**
 * Writes common portions of the test parameter files.
 * @param oOut File stream to write to.
 */
void WriteDensDepNormalProcessingCommonStuff(std::fstream &oOut);

//---------------------------------------------------------------------------
#endif //TestDensDepInfestation_H
