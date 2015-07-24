//---------------------------------------------------------------------------
// TestLightOrg
//---------------------------------------------------------------------------
#if !defined(TestLightOrg_H)
#define TestLightOrg_H

/**
 * Writes a parameter file to direct testing.  Timestep length is 1 year.
 * This contains one species.
 * Sail light is applied to Species 1 saplings.
 * @return Filename written.
 */
const char* WriteLightOrgXMLFile1();

/**
 * Writes a parameter file to direct testing.  Has no snags, nor any snag
 * light extinction coefficient parameters.
 * @return Filename written.
 */
const char* WriteLightOrgXMLFile2();

/**
 * Writes a parameter file to direct error testing.  Snag age classes
 * overlap.
 * @return Filename written.
 */
const char* WriteLightOrgXMLErrorFile1();

/**
 * Writes a parameter file to direct error testing.  One of the regular
 * light extinction coefficients is not between 0 and 1.
 * @return Filename written.
 */
const char* WriteLightOrgXMLErrorFile2();

/**
 * Writes a parameter file to direct error testing.  One of the snag
 * light extinction coefficients is not between 0 and 1.
 * @return Filename written.
 */
const char* WriteLightOrgXMLErrorFile3();
//---------------------------------------------------------------------------
#endif // TestLightOrg_H
