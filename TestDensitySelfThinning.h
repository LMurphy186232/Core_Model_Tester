//---------------------------------------------------------------------------
// TestDensitySelfThinning.h
//---------------------------------------------------------------------------
#if !defined(TestDensitySelfThinning_H)
#define TestDensitySelfThinning_H

/**
 * Writes a parameter file with legal parameter values for the behavior.
 */
const char* WriteDensitySelfThinningXMLFile1();

/**
 * Writes a parameter file with a timestep greater than 1.
 */
const char* WriteDensitySelfThinningXMLErrorFile1();

/**
 * Writes a parameter file that passes adults to the behavior.
 */
const char* WriteDensitySelfThinningXMLErrorFile2();

/**
 * Writes a parameter file with a negative SelfThinRadius parameter.
 */
const char* WriteDensitySelfThinningXMLErrorFile3();

/**
 * Writes a parameter file with a negative MinDensityForMort parameter.
 */
const char* WriteDensitySelfThinningXMLErrorFile4();

/**
 * Writes a parameter file with a negative SelfThinAsymptote parameter.
 */
const char* WriteDensitySelfThinningXMLErrorFile5();

/**
 * Writes a parameter file with a negative SelfThinDensityEffect parameter.
 */
const char* WriteDensitySelfThinningXMLErrorFile6();

//---------------------------------------------------------------------------
#endif // TestDensitySelfThinning_H

