class MachinePhilosopher implements Runnable {
    public final int id;

    MachinePhilosopher(final int id) {
        this.id = id;
    }

    @Override
    public void run() {
        // TODO do as the problem description
        Com com = Com.getInstance();
        int messageId = com.getNumber();
        synchronized (com) {
            while (true) {
                try {
                    com.wait();
                } catch (InterruptedException e) {
                }
                int curMessageId = com.getNumber();
                if (curMessageId == messageId)
                    continue;
                messageId = curMessageId;
                com.star(messageId, id);
            }
        }
    }
}
