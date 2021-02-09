@SuppressWarnings("serial")
class NetException extends Exception {
    // TODO create constructor for NetException
    private String fileName;

    public NetException(String fileName) {
        this.fileName = fileName;
    }

    @Override
    public String toString() {
        return "NetException: network attack: " + fileName;
    }
}