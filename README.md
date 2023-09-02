# CPP example module

This is our example module for C++. It shows you how to:

- Build a minimal Viam module using our [C++ SDK](todo link)
- In github CI
- For x86 and ARM
- And upload it to our registry

## Local build environment

- Debian bullseye or newer (ubuntu is also fine)
- Install the apt packages in apt-setup.sh
- Install cmake
	- Check CMAKE_VERSION in the github workflow (3.27.4 as of this writing)
	- On ubuntu, the cmake snap is probably new enough
	- Otherwise [follow CMake's instructions](todo link)
- [Install rust](https://www.rust-lang.org/tools/install) (needed for viam_rust_utils)

## Get a build working

TODO

Note: buildjet runners (todo)

## Deploy to robot

Dependencies to run on your target machine:

```sh
sudo apt install libprotobuf23 libboost-log1.74.0 libgrpc++1
```

JSON config:

```json
{}
```

## Troubleshooting

### Library paths

In general, `ldd` is your friend. Run `ldd module-example-cpp` in the unpacked tar directory to see which libraries are not resolvable.

- Can't find libviam (libviamsdk.so.noabi, for example)
	- Need `LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD`
- Can't find something else
	- You probably need to `apt-get install` it. Check .github/workflows/build.yml for package names (without the `-dev` suffix)

### Connecting a debugger

If you are getting unexplained phenomena, especially crashes or disconnects, gdb is your friend!

These steps are easier if you use your development machine as the 'robot', i.e. install viam-server on your laptop.

To connect gdb:

1. Configure your robot to use the module + make sure it's running
1. Find the pid of your running module with `ps aux | grep module-example-cpp` (replace the executable name if you've changed it)
1. `sudo gdb --pid $PID` with the pid you found (sudo because the robot is probably running in sudo)
1. `continue` in gdb to restart the process
1. Do the thing that is causing your module to crash. Gdb should catch it
