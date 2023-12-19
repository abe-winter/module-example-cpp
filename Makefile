BUILD_DIR ?= build
CMAKE ?= cmake

$(BUILD_DIR)/module-example-cpp:
	rm -rf build
	$(CMAKE) --version
	$(CMAKE) -G Ninja -B $(BUILD_DIR) .
	$(CMAKE) --build $(BUILD_DIR) --target module-example-cpp

module.tar.gz: $(BUILD_DIR)/module-example-cpp run.sh
	rm -f $@
	cd build && tar czf ../$@ module-example-cpp libviam*.so* -C .. run.sh

clean:
	rm -rf build module.tar.gz

setup:
	# setup step for cloud builds
	apt-get update
	./apt-setup.sh
	apt-get install -qy cmake
