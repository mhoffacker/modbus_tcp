CPP=g++
#Available defines
#  -DEXCESSIVE_READ_TEST         Run reading test on all possible holding register with all possible length
#  -DMBT_SUPPORT_HOLDING_REG     Enable support for holding register
#  -DMBT_SUPPORT_INPUT_REG       Enable support for input register
#  -DMBT_SUPPORT_COILS	         Enable support for coils
#  -DMBT_SUPPORT_DISCRETE_INPUT  Enable support for discrete input
CXXFLAGS=-DMBT_SUPPORT_HOLDING_REG 
DEPS = ../src/modbus_tcp.h ../src/modbus_tcp_config.h ../src/modbus_tcp.c
OBJ = main.o

%.o: %.cpp $(DEPS)
	$(CPP) -c -o $@ $< $(CXXFLAGS)

modbus_tcp_test: $(OBJ)
	$(CPP) -o $@ $^ $(CXXFLAGS)

test: modbus_tcp_test
	./modbus_tcp_test -s

.PHONY: clean

clean:
	rm -f *.o modbus_tcp_test
