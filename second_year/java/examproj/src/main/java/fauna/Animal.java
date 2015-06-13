package fauna;

/**
 * Created by zerlok on 6/12/15.
 */
public abstract class Animal {
    private static int totalNum;
    protected int footsNum;
    protected String name;

    static {
        System.out.println("Animal's static block");
        totalNum = 0;
    }

    public Animal(String name) {
        System.out.println("Constructor: Animal");
        this.name = name;
        ++totalNum;
    }

    public void call() {
        System.out.println("Hey, " + name + "!");
    }

    public void move() {
        System.out.println(name + " is moving...");
    }

    public static int getAnimalsNum() {
        return totalNum;
    }
}
