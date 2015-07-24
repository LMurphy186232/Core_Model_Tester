//---------------------------------------------------------------------------
// TestFoliarChemistry
//---------------------------------------------------------------------------
#if !defined(TestFoliarChemistry_H)
#define TestFoliarChemistry_H

#include <fstream>

class clTreePopulation;

/**
 * Writes the parameter file for normal processing run 1.
 * @return Filename written.
 */
const char* WriteFoliarChemistryXMLFile1();

/**
 * Writes the parameter file for normal processing run 2.
 * @return Filename written.
 */
const char* WriteFoliarChemistryXMLFile2();

/**
 * Writes an error file where the Foliar Chemistry behavior is applied to
 * seedlings.
 * @return Filename written.
 */
const char* WriteFoliarChemistryXMLErrorFile1();

/**
 * Creates the test tree set.
 * @param p_oPop Tree population object.
 */
void CreateFoliarChemistryTrees(clTreePopulation *p_oPop);

/**
 * Writes common beginning of the test parameter files, which is everything
 * after the grid settings.
 * @param oOut File stream to write to.
 */
void WriteFoliarChemistryCommonFileBegin(std::fstream &oOut);

/**
 * Writes common ending of the test parameter files, which is everything
 * after the grid settings.
 * @param oOut File stream to write to.
 */
void WriteFoliarChemistryCommonFileEnd(std::fstream &oOut);
//---------------------------------------------------------------------------
#endif // TestFoliarChemistry_H
