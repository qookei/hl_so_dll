hl_so_shim/stubs.cpp: misc/generate_stubs.py
#	nm $(ORIGINAL_HL_SO) | awk '/ T /{print $$3;}' | python misc/generate_stubs.py > $@
	python misc/generate_stubs.py > $@
