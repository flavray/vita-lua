TITLE_ID = vita-lua
TARGET   = vitalua
OBJECTS  = $(patsubst src/%.c, objects/%.o, $(wildcard src/*.c))

BUILD   = build
INCLUDE = include/

LIBS = lib/liblua.a \
	-lvita2d -lSceKernel_stub -lSceDisplay_stub -lSceGxm_stub \
	-lSceSysmodule_stub -lSceCtrl_stub -lScePgf_stub \
	-lSceCommonDialog_stub -lpng -ljpeg -lz -lm -lc

PREFIX  = arm-vita-eabi
CC      = $(PREFIX)-gcc
CFLAGS  = -Wl,-q -Wall -Werror -O3 -DLUA_32BITS

all: directories $(TARGET).vpk

directories:
	mkdir -p $(BUILD) objects

%.vpk: eboot.bin
	vita-mksfoex -s TITLE_ID=$(TITLE_ID) "$(TARGET)" $(BUILD)/param.sfo
	vita-pack-vpk -s $(BUILD)/param.sfo -b $(BUILD)/eboot.bin $@

eboot.bin: $(BUILD)/$(TARGET).velf
	vita-make-fself $< $(BUILD)/$@

%.velf: %.elf
	vita-elf-create $< $@

$(BUILD)/$(TARGET).elf: $(OBJECTS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

objects/%.o : src/%.c
	$(CC) -I$(INCLUDE) $(CFLAGS) -c -o $@ $<

%.o: %.png
	$(PREFIX)-ld -r -b binary -o $@ $^

clean:
	@rm -rf $(TARGET).vpk $(BUILD)/$(TARGET).velf $(BUILD)/$(TARGET).elf \
		$(BUILD)/eboot.bin $(BUILD)/param.sfo objects/

vpksend: $(TARGET).vpk
	curl -T $(TARGET).vpk ftp://$(PSVITAIP):1337/ux0:/
	@echo "Sent."

send: eboot.bin
	curl -T build/eboot.bin ftp://$(PSVITAIP):1337/ux0:/app/$(TITLE_ID)/
	@echo "Sent."
