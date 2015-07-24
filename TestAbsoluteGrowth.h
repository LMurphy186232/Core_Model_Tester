//---------------------------------------------------------------------------
// TestAbsoluteGrowth
//---------------------------------------------------------------------------
#if !defined(TestAbsoluteGrowth_H)
#define TestAbsoluteGrowth_H


/**
 * Tests the clAbsoluteGrowth class.  This tests all six types of absolute
 * growth - unlimited absolute growth, absolute growth limited to constant
 * radial increment, absolute growth limited to constant basal area increment,
 * unlimited absolute growth - diameter update only, absolute growth limited to
 * constant radial increment - diameter update only, and absolute growth limited
 * to constant basal area increment - diameter update only.
 *
 * I have not yet put in testing of suppression/release.
 */

/**
 * Writes a parameter file to direct testing. This contains three species.
 * Behaviors:
 * <ul>
 * <li>Unlimited absolute growth is applied to Species 1 saplings.
 * <li>Absolute growth limited to constant radial increment is applied to
 * Species 1 adults.
 * <li>Absolute growth limited to basal area increment is applied to Species
 * 2 adults.
 * <li>Unlimited absolute growth - diameter only is applied to Species 2
 * saplings.
 * <li>Absolute growth limited to constant radial increment - diameter only is
 * applied to Species 3 saplings.
 * <li>Absolute growth limited to basal area increment - diameter only is
 * applied to Species 3 adults.
 * Height incrementer applied to all with diameter only behaviors.
 * </ul>
 * @param iYrsPerTimestep Number of years per timestep.
 * @return Filename written.
 */
const char* WriteAbsoluteGrowthXMLFile1(int iYrsPerTimestep);

//#ifdef MEMORY_TEST
void AbsoluteGrowthTest1YearPerTimestep();
void AbsoluteGrowthTest3YearsPerTimestep();
//#endif
//---------------------------------------------------------------------------
#endif // TestAbsoluteGrowth_H
