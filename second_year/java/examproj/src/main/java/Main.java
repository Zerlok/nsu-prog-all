import fauna.*;
import fauna.birds.*;
import fauna.predators.*;

import java.util.Arrays;

/**
 * Created by zerlok on 6/12/15.
 */
public class Main {
    private int z;
    private static int zzz = 123;

    public static void main(String[] args) {
        Inner i = new Inner();

        Animal tiger = new Tiger("Pushok");
        Animal parrot = new Bird("Kesha") {
            public void watchTV() {
                System.out.println(name + "is watching the TV...");
            }
        };
        Animal strauss = new Straus("Runner");
        Animal wolf = new Predator("Layka") {
            public void sing () {
                System.out.println("Awuuuuuuuuuuu!");
            }
        };
        Animal bear = new Predator("Greezly") {
            public void fallAsleep() {
                System.out.println("Winter is coming.");
            }
        };
        Animal dinosaur = new Animal("Trantosaur") {
            public void die() {
                System.out.println("All dinosaurs are dead.");
            }
        };
        Animal human = new Human("Dan", 20);
        Animal bird = new Sparrow();

        Animal[] array = new Animal[] {
                tiger, parrot, strauss, wolf, bear, dinosaur, human
        };

        System.out.println("--------------------------");
        callAnimals(array);
        System.out.println("--------------------------");
        moveAnimals(array);
        System.out.println("--------------------------");
        printObjects(array);
        System.out.println("--------------------------");

        System.out.println("Total animals num: " + Animal.getAnimalsNum());
        System.out.println("Total predators num: " + Predator.getTotalNum());
        System.out.println(Arrays.toString(Predator.class.getMethods()));
    }

    private static void printObjects(Object[] array) {
        for (Object o : array) {
            System.out.println(o + " instance of " + o.getClass());

            if (o.getClass().isAnonymousClass())
                System.out.println(o.getClass().getSuperclass());

            if (o instanceof Human)
                System.out.println(o.getClass().isAnonymousClass() + " Hello, people!");
        }
    }

    private static void moveAnimals(Animal[] array) {
        for (Animal a : array)
            a.move();
    }

    public static void callAnimals(Animal[] array) {
        for (Animal a : array)
            a.call();
    }

    private static class Human extends Animal {
        public int age;
        public Human(String name, int age) {
            super(name);
            this.age = age;
        }
    }
}

class Inner {
    public Inner() {
        System.out.println("Inner created!");
    }
}