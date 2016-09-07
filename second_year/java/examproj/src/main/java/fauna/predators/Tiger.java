package fauna.predators;

import java.lang.reflect.InvocationTargetException;

/**
 * Created by zerlok on 6/12/15.
 */
public class Tiger extends Predator {
    static {
        System.out.println("Tiger's static block");
    }

    public Tiger(String name) {
        super(name);
        System.out.println("Constructor: Tiger");

        try {
            System.out.println(super.getClass().getSuperclass().getMethod("getAnimalsNum").invoke(0));
        } catch (NoSuchMethodException e) {
            e.printStackTrace();
        } catch (InvocationTargetException e) {
            e.printStackTrace();
        } catch (IllegalAccessException e) {
            e.printStackTrace();
        }

        this.name = name;
    }
}
