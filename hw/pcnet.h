#define PCNET_IOPORT_SIZE       0x20
#define PCNET_PNPMMIO_SIZE      0x20

#define PCNET_LOOPTEST_CRC	1
#define PCNET_LOOPTEST_NOCRC	2


typedef struct PCNetState_st PCNetState;

struct PCNetState_st {
    VLANClientState *vc;
    NICConf conf;
    QEMUTimer *poll_timer;
    int rap, isr, lnkst;
    uint32_t rdra, tdra;
    uint8_t prom[16];
    uint16_t csr[128];
    uint16_t bcr[32];
    uint64_t timer;
    int mmio_index, xmit_pos;
    uint8_t buffer[4096];
    int tx_busy;
    qemu_irq irq;
    void (*phys_mem_read)(void *dma_opaque, target_phys_addr_t addr,
                         uint8_t *buf, int len, int do_bswap);
    void (*phys_mem_write)(void *dma_opaque, target_phys_addr_t addr,
                          uint8_t *buf, int len, int do_bswap);
    void *dma_opaque;
    int looptest;
};

void pcnet_h_reset(void *opaque);
void pcnet_ioport_writew(void *opaque, uint32_t addr, uint32_t val);
uint32_t pcnet_ioport_readw(void *opaque, uint32_t addr);
void pcnet_common_cleanup(PCNetState *d);
int pcnet_common_init(DeviceState *dev, PCNetState *s,
                      NetCleanup *cleanup);
extern const VMStateDescription vmstate_pcnet;
