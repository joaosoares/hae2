all: 
	$(MAKE) -C src -f ocv3.mak

.PHONY: clean
clean:
	$(MAKE) -C src -f ocv3.mak clean



