//---------------------------------------------------------------------------
// TestDetailedSubstrate
//---------------------------------------------------------------------------
#if !defined(TestDetailedSubstrate_H)
#define TestDetailedSubstrate_H

class clGrid;

/**
 * Verifies the substrate proportions for timestep 1 of TestSubstrateRun1().
 */
void VerifyDetailedSubstrateRun1TS1Proportions(clGrid *p_oSubstrateGrid);

/**
 * Verifies the substrate proportions for timestep 2 of TestSubstrateRun1().
 */
void VerifyDetailedSubstrateRun1TS2Proportions(clGrid *p_oSubstrateGrid);

/**
 * Verifies the substrate proportions for timestep 3 of TestSubstrateRun1().
 */
void VerifyDetailedSubstrateRun1TS3Proportions(clGrid *p_oSubstrateGrid);

/**
 * Verifies the substrate proportions for timestep 4 of TestSubstrateRun1().
 */
void VerifyDetailedSubstrateRun1TS4Proportions(clGrid *p_oSubstrateGrid);

/**
 * Verifies the substrate proportions for timestep 1 of TestSubstrateRun2().
 */
void VerifyDetailedSubstrateRun2TS1Proportions(clGrid *p_oSubstrateGrid);

/**
 * Writes a parameter file for testing grid setup and normal processing runs 1 and 2.
 * @return Filename written.
 */
const char* WriteDetailedSubstrateXMLFile1(int iYearsPerTS);

/**
 * Writes a file for testing grid setup with map files.
 * @return Filename written.
 */
const char* WriteDetailedSubstrateXMLFile2();


/**
 * Writes a parameter file for testing new substrate inputs.
 * @return Filename written.
 */
const char* WriteDetailedSubstrateXMLFile3();
//---------------------------------------------------------------------------
#endif // TestSubstrate
