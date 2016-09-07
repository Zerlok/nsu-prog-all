package fauna.predators;

import fauna.Animal;

/**
 * Created by zerlok on 6/12/15.
 */
public class Predator extends Animal {
    private static int totalNum;

    static {
        System.out.println("Predator's static block");
        totalNum = 0;
    }

    public Predator(String name) {
        super(name);
        System.out.println("Constructor: Hunter");
        footsNum = 4;
        ++totalNum;
    }

    @Override
    public void move() {
        System.out.println(name + " is running step-by-step...");
    }

    public void searchForFood() {
        System.out.println(name + " wants to eat...");
    }

    public static int getTotalNum() {
        return totalNum;
    }
}
