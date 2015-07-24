//---------------------------------------------------------------------------
// TestMichMenNegGrowth
//---------------------------------------------------------------------------
#if !defined(TestMichMenNegGrowth_H)
#define TestMichMenNegGrowth_H

/**
 * Tests the clMichMenNegGrowth class.
 */

/**
 * Writes a parameter file to direct testing. Timestep length is 1
 * year. This contains four species. Relative height growth is applied to all
 * species. Diameter incrementer applied to all as well.
 *
 * @return Filename written.
 */
const char* WriteMichMenNegGrowthXMLFile1();

/**
 * Writes a parameter file to direct testing. Timestep length is 3
 * years. This contains four species. Relative height growth is applied to all
 * species. Diameter incrementer applied to all as well.
 *
 * @return Filename written.
 */
const char* WriteMichMenNegGrowthXMLFile2();

/**
 * Writes a parameter file to direct testing. Timestep length is 1
 * year. This contains five species. Relative height growth is applied to all
 * species. Diameter incrementer applied to all as well.
 *
 * @return Filename written.
 */
const char* WriteMichMenNegGrowthXMLFile3();

/**
 * Writes an error file where the beta parameter = 0.
 * @return File name of the freshly written parameter file.
 */
const char* WriteMichMenNegGrowthXMLErrorFile1();

/**
 * Writes an error file where the autocorrelation chance is not between 0 and
 * 1.
 * @return File name of the freshly written parameter file.
 */
const char* WriteMichMenNegGrowthXMLErrorFile2();

/**
 * Writes common portions of the test parameter files.
 * @param oOut File stream to write to.
 */
void WriteMichMenNegGrowthRun1CommonStuff(std::fstream &oOut);

/**
 * Writes common portions of the test parameter files.
 * @param oOut File stream to write to.
 */
void WriteMichMenNegGrowthRun2CommonStuff(std::fstream &oOut);

/**
 * Writes common portions of the test parameter files.
 * @param oOut File stream to write to.
 */
void WriteMichMenNegGrowthErrorCommonStuff(std::fstream &oOut);
//---------------------------------------------------------------------------
#endif // TestMichMenNegGrowth_H
