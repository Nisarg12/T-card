AS=arm-none-eabi-as
LD=arm-none-eabi-ld
OBJCOPY=arm-none-eabi-objcopy
CC=arm-none-eabi-gcc

ASFLAGS=-mthumb
CFLAGS= -std=gnu11 -mthumb -mthumb-interwork -mcpu=arm7tdmi -fno-inline -mlong-calls -march=armv4t -Wall -Wextra -Wconversion -O2
LDFLAGS=-z muldefs

all: engine
	$(LD) $(LDFLAGS) -T linker.lsc -T bpre.ld -o "build\linked.o" "build\main.o"
	$(OBJCOPY) -O binary "build\linked.o" "main.bin"
	
engine:
	$(CC) $(CFLAGS) -c "src\main.c" -o "build\main.o"
	
clean:
	rm build\*.*