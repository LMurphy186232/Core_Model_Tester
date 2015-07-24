//---------------------------------------------------------------------------
// TestDoubleMMRelGrowth
//---------------------------------------------------------------------------
#if !defined(TestDoubleMMRelGrowth_H)
  #define TestDoubleMMRelGrowth_H

/**
 * Writes a parameter file to direct testing.  Timestep length is 1 year.
 * This contains four species.
 * Behaviors:
 * <ul>
 * <li>Diam with auto height growth is applied to Species 2 and 4 saplings and
 * adults.</li>
 * <li>Diam only growth is applied to Species 1 and 3 saplings and
 * adults.</li>
 * <li>Height incrementer applied to all with diameter only behaviors.</li>
 * </ul>
 *
 * @return Filename written.
 */
const char* WriteDoubleMMRelGrowthXMLFile1();

/**
 * Writes a parameter file to direct testing.  Timestep length is 3 years.
 * This contains four species.
 * Behaviors:
 * <ul>
 * <li>Diam with auto height growth is applied to Species 2 and 4 saplings and
 * adults.</li>
 * <li>Diam only growth is applied to Species 1 and 3 saplings and
 * adults.</li>
 * <li>Height incrementer applied to all with diameter only behaviors.</li>
 * </ul>
 *
 * @return Filename written.
 */
const char* WriteDoubleMMRelGrowthXMLFile2();
//---------------------------------------------------------------------------
#endif // TestDoubleMMRelGrowth_H
