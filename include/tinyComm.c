

void init_tiny_comm()
{
	/* Set MOSI and SCK output, all others input */
	DDRB |= _BV(PB2)|_BV(PB1);
	/* Enable SPI, Master, set clock rate fck/16, clock phase trailing */
	SPCR = _BV(SPE)| _BV(MSTR)| _BV(SPR0) | _BV(CPHA);
}


void transmitByteToTiny(uint8_t cData)
{
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));
}