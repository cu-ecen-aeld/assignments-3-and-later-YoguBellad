writer: writer.o
	$(CROSS_COMPILE)gcc $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS) -o $@
%.o: %.c
	$(CROSS_COMPILE)gcc -c $(CPPFLAGS) $(CFLAGS) $^ -o $@

clean:
	rm -rf *.o
	rm -rf writer