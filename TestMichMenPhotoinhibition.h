//---------------------------------------------------------------------------
// TestMichMenPhotoinhibition
//---------------------------------------------------------------------------
#if !defined(TestMichMenPhotoinhibition_H)
#define TestMichMenPhotoinhibition_H

#include <fstream>

/**
 * Writes a parameter file to direct testing. Timestep length is 1
 * year. This contains four species. Relative height growth is applied to all
 * species. Diameter incrementer applied to all as well.
 *
 * @return Filename written.
 */
const char* WriteMichMenPhotoinhibitionXMLFile1();

/**
 * Writes a parameter file to direct testing. Timestep length is 3
 * years. This contains four species. Relative height growth is applied to all
 * species. Diameter incrementer applied to all as well.
 *
 * @return Filename written.
 */
const char* WriteMichMenPhotoinhibitionXMLFile2();

/**
 * Writes an error file where the beta parameter = 0.
 * @return File name of the freshly written parameter file.
 */
const char* WriteMichMenPhotoinhibitionXMLErrorFile1();

/**
 * Writes common portions of the test parameter files.
 * @param oOut File stream to write to.
 */
void WriteMichMenPhotoinhibitionCommonStuff(std::fstream &oOut);
//---------------------------------------------------------------------------
#endif // TestMichMenPhotoinhibition_H
