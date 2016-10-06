CC ?= gcc
CFLAGS_common ?= -Wall -std=gnu99
CFLAGS_bubble = -O0 -g -pg
CFLAGS_merge  = -O0 -g -pg

EXEC = bubble merge
all: $(EXEC)

SRCS_common = main.c

bubble: $(SRCS_common) bubble.c bubble.h
	$(CC) $(CFLAGS_common) $(CFLAGS_bubble) \
		-DBUBBLE="\"$@.h\"" -o $@ \
		$(SRCS_common) $@.c merge.c merge.h
		./bubble

merge: $(SRCS_common) merge.c merge.h
	$(CC) $(CFLAGS_common) $(CFLAGS_merge) \
		-DMERGE="\"$@.h\"" -o $@ \
		$(SRCS_common) $@.c
		./merge

run: $(EXEC)
	echo 3 | sudo tee /proc/sys/vm/drop_caches
	watch -d -t "./merge && echo 3 | sudo tee /proc/sys/vm/drop_caches"

cache-test: $(EXEC)
	perf stat --repeat 100 \
		-e cache-misses,cache-references,instructions,cycles \
		./merge

plot:	bubble.txt merge.txt
	gnuplot plot.gp
	eog runtime.png

.PHONY: clean
clean:
	$(RM) $(EXEC) *.o perf.* \
	      	 output.txt runtime.png merge.txt bubble.txt
