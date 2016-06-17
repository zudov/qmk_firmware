MIDI_DIR = lib/midi

SRC += midi.c \
	   midi_device.c \
	   bytequeue/bytequeue.c \
	   bytequeue/interrupt_setting.c \
	   $(LUFA_SRC_USBCLASS)

VPATH += $(TOP_DIR)/$(MIDI_DIR)