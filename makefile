include ../makefile.conf
NAME=minimum
STARTUP_DEFS=-D__STARTUP_CLEAR_BSS -D__START=main

LDSCRIPTS=-L. -L$(BASE)/ldscripts -T gcc.ld
LFLAGS=$(USE_NANO) $(USE_NOHOST) $(LDSCRIPTS) $(GC) $(MAP) -g

$(NAME)-$(CORE).axf: $(NAME).c $(STARTUP)
	$(CC) $^ $(CFLAGS) $(LFLAGS) -o $@
	arm-none-eabi-size $@

clean: 
	rm -f $(NAME)*.axf *.map

run: $(NAME)-$(CORE).axf
	/Applications/lpcxpresso_5.1.0_2048/lpcxpresso/bin/crt_emu_lpc11_13_nxp -2 -pLPC1114FN/102 -wire=winusb -flash-load=minimum-CM0.axf -load-base=0x0000

debug: $(NAME)-$(CORE).axf
	arm-none-eabi-gdb -x ../gdb_commands $(NAME)-$(CORE).axf

debugtui: $(NAME)-$(CORE).axf
	arm-none-eabi-gdbtui -x ../gdb_commands $(NAME)-$(CORE).axf