include Jade.mk

build: $(JADE_CORE_OUTPUT_TARGET) $(JADE_CLIENT_OUTPUT_TARGET) $(JADE_SERVER_OUTPUT_TARGET) $(JADE_EDITOR_OUTPUT_TARGET)

run: build
	$(JADE_EDITOR_OUTPUT_TARGET)

dbgrun: build
	$(JD_DEBUGGER) $(JADE_EDITOR_OUTPUT_TARGET)

clean:
	del /s /q "$(JADE_CORE_DIR)/Binaries"
	del /s /q "$(JADE_CLIENT_DIR)/Binaries"
	del /s /q "$(JADE_SERVER_DIR)/Binaries"
	del /s /q "$(JADE_EDITOR_DIR)/Binaries"

include Jade/JadeCore/JadeCore.mk
include Jade/JadeClient/JadeClient.mk
include Jade/JadeServer/JadeServer.mk
include Jade/JadeEditor/JadeEditor.mk