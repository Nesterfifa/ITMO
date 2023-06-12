import org.jetbrains.annotations.NotNull;

/**
 * В теле класса решения разрешено использовать только финальные переменные типа RegularInt.
 * Нельзя volatile, нельзя другие типы, нельзя блокировки, нельзя лазить в глобальные переменные.
 *
 * @author : Nesterenko Viktor
 */
public class Solution implements MonotonicClock {
    private final RegularInt c1 = new RegularInt(0);
    private final RegularInt c2 = new RegularInt(0);
    private final RegularInt c3 = new RegularInt(0);
    private final RegularInt cc1 = new RegularInt(0);
    private final RegularInt cc2 = new RegularInt(0);

    @Override
    public void write(@NotNull Time time) {
        cc1.setValue(time.getD1());
        cc2.setValue(time.getD2());
        c3.setValue(time.getD3());
        c2.setValue(time.getD2());
        c1.setValue(time.getD1());
    }

    @NotNull
    @Override
    public Time read() {
        RegularInt d1 = new RegularInt(c1.getValue());
        RegularInt d2 = new RegularInt(c2.getValue());
        RegularInt d3 = new RegularInt(c3.getValue());
        RegularInt dd2 = new RegularInt(cc2.getValue());
        RegularInt dd1 = new RegularInt(cc1.getValue());
        return new Time(dd1.getValue(),
                d1.getValue() == dd1.getValue() ? dd2.getValue() : 0,
                d1.getValue() == dd1.getValue() && d2.getValue() == dd2.getValue() ? d3.getValue() : 0);
    }
}
