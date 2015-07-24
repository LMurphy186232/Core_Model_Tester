//---------------------------------------------------------------------------
// TestEstablishment
//---------------------------------------------------------------------------
#if !defined(TestEstablishment_H)
#define TestEstablishment_H

/**
 * Writes a parameter file to direct testing.
 * @return Filename written.
 */
const char* WriteEstablishmentXMLFile1();

/**
 * Writes a parameter file to direct testing.
 * @return Filename written.
 */
const char* WriteEstablishmentXMLFile2();

/**
 * Writes a parameter file with no disperse behaviors whatsoever.
 * @return Filename written.
 */
const char* WriteEstablishmentXMLErrorFile1();

//---------------------------------------------------------------------------
#endif // TestEstablishment
