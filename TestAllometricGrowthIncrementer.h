//---------------------------------------------------------------------------
// TestAllometricGrowthIncrementer
//---------------------------------------------------------------------------
#if !defined(TestAllometricGrowthIncrementer_H)
#define TestAllometricGrowthIncrementer_H

/**
 * Tests the clAllometricGrowthIncrementer class. I'm also allowing this to form
 * part of the test of clConstBAGrowth and clConstantRadialGrowth.  Ironically,
 * since I wrote this, this is also now partly a test of clGrowthOrg, and
 * TestGrowthOrg is partly a test of clGrowthHeightIncrementer, because I
 * switched some functionality between classes.  But I am much too lazy to
 * switch the test code too.  After all, it's all there, right?
 */

/**
 * Writes a parameter file to direct testing.  This contains two species, with
 * either constant basal area or constant radial growth assigned.
 *
 * @return Filename written.
 */
const char* WriteAllometricGrowthIncrementerXMLFile1();

/**
 * Writes a parameter file for normal processing run 2.
 *
 * @return Filename written.
 */
const char* WriteAllometricGrowthIncrementerXMLFile2();
//---------------------------------------------------------------------------
#endif // TestAllometricGrowthIncrementer_H
