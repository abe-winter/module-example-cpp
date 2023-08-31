module.tar.gz: build/module-example-cpp build/libviam*.so*
	rm -f $@
	cd build && tar czf ../$@ module-example-cpp libviam*.so*
