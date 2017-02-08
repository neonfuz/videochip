typedef struct {
    char type[8];
    int length;
    unsigned char *data;
} Packet;

Packet getPacket(Packet *p);
void printPacket(Packet p);
