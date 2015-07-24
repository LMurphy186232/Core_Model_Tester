//---------------------------------------------------------------------------
// TestSailLight
//---------------------------------------------------------------------------
#if !defined(TestSailLight_H)
  #define TestSailLight_H

/**
 * Writes a parameter file to direct testing. Timestep length is 1 year.
 * This contains one species.
 * Sail light is applied to Species 1 saplings.
 * @return Filename written.
 */
const char* WriteSailLightXMLFile1();

/**
 * Writes a parameter file to direct testing. Timestep length is 1 year.
 * This contains one species.
 * Sail light is applied to Species 1 saplings and seedlings.
 * @return Filename written.
 */
const char* WriteSailLightXMLFile2();
//---------------------------------------------------------------------------
#endif // TestSailLight_H
