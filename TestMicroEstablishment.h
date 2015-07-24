//---------------------------------------------------------------------------
// TestMicroEstablishment
//---------------------------------------------------------------------------
#if !defined(TestMicroEstablishment_H)
#define TestMicroEstablishment_H

#include <fstream>

/**
 * Writes a parameter file that sets up 6 species, 3 of which get
 * establishment.
 * @return Filename written.
 */
const char* WriteMicroEstablishmentXMLFile1();

/**
 * Writes a parameter file that sets up 1 species. All favorabilities are set
 * to 1. Mound proportion is set to 1. Mound mean height is 3 m. Mound
 * standard deviation is 0.5 m.
 * @return Filename written.
 */
const char* WriteMicroEstablishmentXMLFile2();

/**
 * Writes a parameter file that sets up 6 species, 3 of which get
 * establishment. All favorabilities are set to 1. Mound proportion is set
 * to 0.
 * @return Filename written.
 */
const char* WriteMicroEstablishmentXMLFile3();

/**
 * Writes a parameter file that contains a mound proportion that is
 * negative.
 * @return Filename written.
 */
const char* WriteMicroEstablishmentXMLErrorFile1();

/**
 * Writes common portions of the test parameter files (tree pop, plot, etc).
 * This ends with &lt;/allometry&gt.
 * @param oOut File stream to write to.
 */
void WriteMicroEstablishmentCommonStuff(std::fstream &oOut);
//---------------------------------------------------------------------------
#endif // TestMicroEstablishment_H
