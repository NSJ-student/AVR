

unsigned char GetHexf(float input, unsigned char ifNum, unsigned char digit)
{
	float fNum;
	unsigned char tmp;
	int i;

	if(ifNum == 1)
	{
		tmp = (unsigned char)input;
	}
	else
	{
		fNum = input - (unsigned char)input;

		for(i=0; i<digit; i++) fNum = fNum*10;
		tmp	= (unsigned char)( (unsigned int)fNum%10);
	}

	return '0'+tmp;
}

unsigned char GetHexi(unsigned int uiNum, unsigned char ucNum)
{
	unsigned int tmp = uiNum;

	tmp = (uiNum>>(4*(ucNum-1)))&0x000F;

	if(tmp >= 10)
		return 'A'+tmp-10;
	else
		return '0'+tmp;
}

