void io_hlt(void);

void HariMain(void)
{

fin:
	/* ‚±‚±‚ÉHLT‚ğ“ü‚ê‚½‚¢‚Ì‚¾‚ªACŒ¾Œê‚Å‚ÍHLT‚ªg‚¦‚È‚¢I */
	io_hlt();
	goto fin;

}
