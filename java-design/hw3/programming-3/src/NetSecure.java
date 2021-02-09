class NetSecure {
    public static void check(String packet) throws NetException {
        // TODO throw NetException if the packet is malware
        if (packet.toLowerCase().endsWith(".exe"))
            throw new NetException(packet);
    }
}