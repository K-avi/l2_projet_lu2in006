TARGET:= myGit
TEST :=test

ALLPROGS= $(TARGET) $(TEST)

.PHONY:	all clean

all: $(ALLPROGS)
progs: $(PROGRAMS)

$(TEST): 
	$(MAKE) -C src/ ../test

$(TARGET): 
	$(MAKE) -C src/ ../myGit


clean:
	$(MAKE) -C src/ clean
	rm -f $(ALLPROGS)

.PHONY: clean
