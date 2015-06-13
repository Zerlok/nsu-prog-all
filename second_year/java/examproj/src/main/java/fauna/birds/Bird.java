package fauna.birds;

import fauna.Animal;

/**
 * Created by zerlok on 6/12/15.
 */
public class Bird extends Animal {
    public Bird(String name) {
        super(name);
        System.out.println("Constructor: Bird");
        this.name = name;
        footsNum = 2;
    }

    public void move() {
        System.out.println(name + " is flying...");
    }
}
