package fauna.birds;

/**
 * Created by zerlok on 6/12/15.
 */
public class Straus extends Bird {
    public Straus(String name) {
        super(name);
    }

    @Override
    public void move() {
        System.out.println("Straus can't fly :( But I can run really fast!");
    }
}
