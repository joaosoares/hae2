all: 
	$(MAKE) -C src -f linux.mak
	$(MAKE) -C kcek -f linux.mak
	$(MAKE) -C progs -f linux.mak

.PHONY: clean
clean:
	$(MAKE) -C src -f linux.mak clean
	$(MAKE) -C kcek -f linux.mak clean
	$(MAKE) -C progs -f linux.mak clean



