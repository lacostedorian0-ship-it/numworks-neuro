Q ?= @
CC = arm-none-eabi-gcc
CXX = arm-none-eabi-g++
BUILD_DIR = target
# Syntaxe officielle du template NumWorks : nwlink fournit eadk.h et ses options.
NWLINK = npx --yes -- nwlink@0.0.16

CPPFLAGS = -std=c++11 -fno-exceptions -Os -Wall
CPPFLAGS += $(shell $(NWLINK) eadk-cflags)
CPPFLAGS += -fdata-sections -ffunction-sections
LDFLAGS = -Wl,--relocatable -nostartfiles --specs=nano.specs
LDFLAGS += -Wl,-e,main -Wl,-u,eadk_app_name -Wl,-u,eadk_app_icon -Wl,-u,eadk_api_level -Wl,--gc-sections

.PHONY: build clean
build: $(BUILD_DIR)/GEO_DASH.nwa

$(BUILD_DIR)/GEO_DASH.nwa: $(BUILD_DIR)/main.o $(BUILD_DIR)/icon.o
	$(Q)$(CC) $(CPPFLAGS) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/main.o: src/main.cpp src/eadkpp.h | $(BUILD_DIR)
	$(Q)$(CXX) $(CPPFLAGS) -c $< -o $@

$(BUILD_DIR)/icon.o: src/icon.png | $(BUILD_DIR)
	$(Q)$(NWLINK) png-icon-o $< $@

$(BUILD_DIR):
	$(Q)mkdir -p $(BUILD_DIR)

clean:
	$(Q)rm -rf $(BUILD_DIR)
