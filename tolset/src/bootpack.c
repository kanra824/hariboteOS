void io_hlt(void);

void HariMain(void)
{

fin:
	/* ここにHLTを入れたいのだが、C言語ではHLTが使えない！ */
	io_hlt();
	goto fin;

}
