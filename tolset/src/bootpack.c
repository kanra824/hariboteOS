void io_hlt(void);

void HariMain(void)
{

fin:
	/* ������HLT����ꂽ���̂����AC����ł�HLT���g���Ȃ��I */
	io_hlt();
	goto fin;

}
