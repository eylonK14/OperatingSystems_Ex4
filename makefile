all:
	$(MAKE) -C Ex1-4 all
	$(MAKE) -C Ex5-6 all
	$(MAKE) -C Ex7 all

clean: 
	$(MAKE) -C Ex1-4 clean
	$(MAKE) -C Ex5-6 clean
	$(MAKE) -C Ex7 clean