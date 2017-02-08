typedef struct {
    char type[8];
    int length;
    char *data;
} Packet;

Packet getPacket(void);
