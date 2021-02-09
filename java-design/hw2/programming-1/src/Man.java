class Man extends BasePerson implements Person {
    private final String name;
    private final String description;
    protected Integer count = 0;

    Man(final String name, final String description) {
        this.name = name;
        this.description = description;
    }

    protected void move(){
        System.out.println("I'm moving...");
    }

    @Override
    public String getName() {
        return name;
    }

    @Override
    public String getDescription() {
        return description;
    }

    @Override
    public int changeSomething() {
        count--;
        return count;
    }
}

class SuperMan extends Man {
    SuperMan(final String name, final String description) {
        super(name, description);
    }

    SuperMan(){
        this("superMan", "I can fly.");
    }

    @Override
    protected void move() {
        System.out.println("I am flying...");
    }

    void fly(){
        System.out.println("“Fly! SuperMan!");
    }

    @Override
    public int changeSomething() {
        count++;
        return count;
    }
}
