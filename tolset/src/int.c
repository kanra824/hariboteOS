#include "bootpack.h"
#include <stdio.h>

void init_pic(void)
{
    io_out8(PIC0_IMR, 0xff); // 割り込み不可
    io_out8(PIC1_IMR, 0xff); // 割り込み不可

    io_out8(PIC0_ICW1, 0x11); // エッジトリガモード
    io_out8(PIC0_ICW2, 0x20); // IRQ0-7はINT20-27で受ける
    io_out8(PIC0_ICW3, 1<<2); // PIC1はIRQ2で接続
    io_out8(PIC0_ICW4, 0x01); // ノンバッファモード
    
    io_out8(PIC1_ICW1, 0x11); // エッジトリガモード
    io_out8(PIC1_ICW2, 0x28); // IRQ8-15はINT28-2fで受ける
    io_out8(PIC1_ICW3, 2);    // PIC1はIRQ2にて接続
    io_out8(PIC1_ICW4, 0x01); // ノンバッファモード
    
    io_out8(PIC0_IMR, 0xfb); // 11111011 PIC1以外すべて禁止
    io_out8(PIC1_IMR, 0xff); // 11111111 すべての割り込みを受け付けない

    return;
}

#define PORT_KEYDAT     0x0060

struct FIFO8 keyfifo;

void inthandler21(int *esp)
{
    unsigned char data;
    io_out8(PIC0_OCW2, 0x61);
    data = io_in8(PORT_KEYDAT);
    fifo8_put(&keyfifo, data);
    return;
}

void inthandler2c(int *esp)
{
    struct BOOTINFO *binfo = (struct BOOTINFO *) ADR_BOOTINFO;
    boxfill8(binfo->vram, binfo->scrnx, COL8_000000, 0, 0, 32 * 8 - 1, 15);
    putfonts8_asc(binfo->vram, binfo->scrnx, 0, 0, COL8_FFFFFF, "INT 2c (IRQ-12) : PS/2 mouse");
    for(;;) {
        io_hlt();
    }
}

void inthandler27(int *esp)
{
    // PIC0からの不完全割り込み対策
    // Athloa64X2機などで起きる
    // なんか初期化時の電気的ノイズで起きるらしい

    io_out8(PIC0_OCW2, 0x67);
    return;
}