//---------------------------------------------------------------------------
// TestSimpleLinearGrowth
//---------------------------------------------------------------------------
#if !defined(TestSimpleLinearGrowth_H)
#define TestSimpleLinearGrowth_H

/**
 * Tests the clSimpleLinearGrowth class. This tests it in all versions - as a
 * diameter-only incrementer with no height updating, as a DiameterIncrementer
 * with auto-height updating, and as a HeightIncrementer.
 */

/**
 * Writes a parameter file to direct testing. Timestep length is 1 year.
 * This contains two species.
 * Behaviors:
 * <ul>
 * <li>simple linear growth diam only - applied to species 0 seedlings and
 * species 1 seedlings
 * <li>simple linear growth height only - applied to species 0 saplings and
 * species 1 seedlings
 * <li>constant radial growth - applied to species 0 saplings
 * <li>HeightIncrementer - applied to species 0 seedlings
 * <li> simple linear growth - applied to species 1 saplings
 * </ul>
 *
 * @return Filename written.
 */
const char* WriteSimpleLinearGrowthXMLFile1();

/**
 * Writes a parameter file to direct testing. Timestep length is 3 years.
 *  This contains two species.
 * Behaviors:
 * <ul>
 * <li>simple linear growth diam only - applied to species 0 seedlings and
 * species 1 seedlings
 * <li>simple linear growth height only - applied to species 0 saplings and
 * species 1 seedlings
 * <li>constant radial growth - applied to species 0 saplings
 * <li>HeightIncrementer - applied to species 0 seedlings
 * <li> simple linear growth - applied to species 1 saplings
 * </ul>
 *
 * @return Filename written.
 */
const char* WriteSimpleLinearGrowthXMLFile2();
//---------------------------------------------------------------------------
#endif // TestSimpleLinearGrowth_H
