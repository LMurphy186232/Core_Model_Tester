//---------------------------------------------------------------------------
// TestLogisticGrowth
//---------------------------------------------------------------------------
#if !defined(TestLogisticGrowth_H)
#define TestLogisticGrowth_H

/**
 * Tests the clLogisticGrowth class. This tests it in all versions - as a
 * diameter-only incrementer with no height updating, as a DiameterIncrementer
 * with auto-height updating, and as a HeightIncrementer.
 */

/**
 * Writes a parameter file to direct testing. Timestep length is 1 year.
 * This contains two species.
 * Behaviors:
 * <ul>
 * <li>logistic growth diam only - applied to species 0 seedlings and species
 * 1 seedlings
 * <li>logistic growth height only - applied to species 0 saplings and species 1 seedlings
 * <li>constant radial growth - applied to species 0 saplings
 * <li>HeightIncrementer - applied to species 0 seedlings
 * <li> logistic growth - applied to species 1 saplings
 * </ul>
 *
 * @return Filename written.
 */
const char* WriteLogisticGrowthXMLFile1();

/**
 * Writes a parameter file to direct testing. Timestep length is 3 years.
 *  This contains two species.
 * Behaviors:
 * <ul>
 * <li>logistic growth diam only - applied to species 0 seedlings and species
 * 1 seedlings
 * <li>logistic growth height only - applied to species 0 saplings and species 1 seedlings
 * <li>constant radial growth - applied to species 0 saplings
 * <li>HeightIncrementer - applied to species 0 seedlings
 * <li> logistic growth - applied to species 1 saplings
 * </ul>
 *
 * @return Filename written.
 */
const char* WriteLogisticGrowthXMLFile2();
//---------------------------------------------------------------------------
#endif // TestLogisticGrowth_H
