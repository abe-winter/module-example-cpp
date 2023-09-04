# C++ example module

This is our example module for C++. It shows you how to:

- Build a minimal Viam module using our [C++ SDK](https://github.com/viamrobotics/viam-cpp-sdk)
- With CI builds for x86 and ARM
- Released through our registry

## Local build environment

Known good environments:
- Debian Bullseye (this is what our CI uses)
- Ubuntu 22.04

Setup and build instructions:
- Install the apt packages in [apt-setup.sh](apt-setup.sh)
- Install cmake
	- Check CMAKE_VERSION in the github workflow (3.27.4 as of this writing)
	- On Ubuntu 22.04, `snap install cmake` is new enough but `apt install cmake` is not
	- Otherwise follow [CMake's download instructions](https://cmake.org/download/)
- [Install rust](https://www.rust-lang.org/tools/install) (needed for viam_rust_utils)

## Deploy to robot

These instructions assume you're targeting something similar to Debian bullseye.

First install libraries on your target system:

```sh
sudo apt install -qqy libgrpc++1 libboost-log1.74.0
```

Then set this JSON config for your robot in the app.viam.com webapp.

Go to 'Config' tab, then change the 'Mode:' selector from 'Builder' to 'Raw JSON', then paste in the following.

```json
{
  "components": [{
	"attributes": {},
	"model": "viam:wifi:cpp",
	"depends_on": [],
	"name": "wifi-cpp",
	"type": "generic"
  }],
  "modules": [{
	"module_id": "viam:module-example-cpp",
	"type": "registry",
	"name": "cpp",
	"version": "0.0.0-main.15"
  }]
}
```

If you make your own build and upload it, you'll need to change `components.0.model` and `modules.0.module_id` to your values. If you don't upload your build to our registry, you can also `scp` it to your robot and run with [executable_path / local exec mode](https://docs.viam.com/extend/modular-resources/configure/#configure-your-module).

## Setting up CI

This repo uses Buildjet runners so we can build natively for ARM. (Look at the `uses` line in [build.yml](.github/workflows/build.yml)). If you fork this repo and you don't have Buildjet connected to Github, your CI jobs won't start.

Your options are:
- Target x86 only. Switch to a github runner (`uses: ubuntu-latest`) and remove arm64 from `strategy: matrix` in build.yml
- Build on an arm emulator using QEMU with the docker/build-push-action, per [instructions here](https://github.com/docker/build-push-action#git-context). This will be slow (~5x slower than native)
- Set up cross compilation (but this will be a project)

## Troubleshooting

### Library paths

`ldd` is your friend. Run `ldd module-example-cpp` in the unpacked tar directory to see which libraries are not resolvable.

- Can't find some libviam (libviamsdk.so.noabi, for example)?
	- Make sure libvimapi + libviamsdk are being bundled in your module.tar.gz
	- Make sure you have `LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD` (the run.sh wrapper in this repo does that for you)
- Can't find something else?
	- You probably need to `apt-get install` it. Check the `apt-get install` command in [Deploy to robot](#deploy-to-robot) above

### Connecting a debugger

For unexplained phenomena, especially crashes or disconnects, a debugger will take you where the logs can't go.

These steps are easier if you use your development machine as the 'robot', i.e. install viam-server on your laptop.

To connect gdb:

1. Configure your robot to use the module + make sure it's running
1. Find the pid of your running module with `ps aux | grep module-example-cpp` (replace the executable name if you've changed it)
1. `sudo gdb --pid $PID` with the pid you found (sudo because the robot is probably running in sudo)
1. `continue` in gdb to restart the process
1. Do the thing that is causing your module to crash. Gdb should catch it
