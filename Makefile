module.tar.gz: build/module-example-cpp build/libviam*.so* run.sh
	rm -f $@
	cd build && tar czf ../$@ module-example-cpp libviam*.so* -C .. run.sh
