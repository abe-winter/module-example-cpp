# C++ example module

This example module demonstrates the use of the [C++ SDK](https://github.com/viamrobotics/viam-cpp-sdk) to build a minimal Viam module.
It is [available for use on the registry](https://app.viam.com/module/viam/module-example-cpp) and shows how to include CI (Continuous Integration) builds for both x86 and ARM architectures.

You can use this as a reference along with the C++ instructions for [coding your own modules](https://docs.viam.com/registry/create/).


## Requirements

Before building this module, verify your operating system's development environment is compatible.
The tested ideal environment for building this module is Debian Bullseye (used in our CI).

You can also use Ubuntu 22.04 for testing, but the resulting C++ builds will not be binary compatible with Bullseye.


To setup for building this module:

1. Install the apt packages in [apt-setup.sh](apt-setup.sh).
2. Install the latest version of CMake to ensure compatibility with this module's CI.
<br/><br/>To install CMake on **Ubuntu 22.04**, run the following command:<br/><br/>
	```sh
	snap install cmake
	```
            
> [!WARNING]
> Avoid using `apt-get` as it may install an older version of CMake.

* See [CMake's download instructions](https://cmake.org/download/) for more information.<br/>
  	
3. [Install rust](https://www.rust-lang.org/tools/install) (needed for `viam_rust_utils`).


## Build and Run

You can build this example module by either the following steps to build it directly from the registry or by opting for the local build instructions.

### Build from the Registry

To build this module and it's executable sourced from the registry, follow this set of instructions.
These instructions assume a target system similar to Debian Bullseye.
First, install the required libraries on your target system:

```sh
sudo apt install -qqy libgrpc++1 libboost-log1.74.0
```

Then follow the C++ instructions to [add a module from the Viam Registry](https://docs.viam.com/registry/configure/#add-a-modular-resource-from-the-viam-registry) and select the `wifi:cpp` model from the `module-example-cpp` module.

### Build Locally

These instructions assume a target system similar to Debian Bullseye.

Before you can build this module's executable, you must follow the steps to [prepare a module for execution](https://docs.viam.com/registry/create/#prepare-the-module-for-execution).

You can use the sections linked in the [Module Contents](#module-contents) section as a reference when creating and building your own C++ module.

## Configure your Example C++ Module

> [!NOTE]
> Before configuring your example module, you must [add a machine](https://docs.viam.com/fleet/machines/#add-a-new-machine).

Navigate to the **Config** tab of your machine’s page in [the Viam app](https://app.viam.com/).
Click on the **Components** subtab and click **Create component**.
Select **Sensor**, then search for the `wifi:cpp` model. Give your resource a name of your choice, click **Create** and then click **Save config**.

Next, change the **Mode:** selector from **Builder** to **Raw JSON**, and verify that `"components"` array now includes the `viam:wifi:cpp` model and that `"modules"` array includes the `module-example-cpp` module. 

Your `Raw JSON` configuration should now include both: 

```json {class="line-numbers linkable-line-numbers"}
{
  "modules": [
    {
      "type": "registry",
      "name": "viam_module-example-cpp",
      "module_id": "viam:module-example-cpp",
      "version": "0.0.3"
    }
  ],
  "components": [
    {
      "name": "my-wifi-cpp",
      "model": "viam:wifi:cpp",
      "type": "sensor",
      "namespace": "rdk",
      "attributes": {},
      "depends_on": []
    }
  ]
}
```

If you upload your version to the Viam registry after building it, remember to update `model` and `module_id` with your values.
If you aren't using the registry, you can also use `scp` to transfer the build to your machine and run it in 
[executable_path / local exec mode](https://docs.viam.com/extend/modular-resources/configure/#configure-your-module).

> [!NOTE]  
> For more information, see [Configure a Machine](https://docs.viam.com/manage/configuration/).


## Module Contents

You can use this repository's files as a reference when building your C++ module:

| Name  | Content | Location |
| ------------- | ------------- | ------------- |
| `CMakeLists.txt` | The configuration for compiling the binary and managing dependencies. | `-` |
| `Makefile` | The command to create the module tarball dependencies. | `-` |
| `.github/workflows/` | The CI build and deployment logic for the registry. | `-` |
| `run.sh` and `apt-setup.sh` | The entrypoint and dependency installation for running the module on a machine. | `-` |
| `meta.json` | The Viam module configuration. | `-` |
| `main.cpp`  | The module's entry point file.</br>See [Code a main entry point program](https://docs.viam.com/registry/create/#code-a-main-entry-point-program) for more information. | `src`|
| `wifi.cpp` | The resource model which implements all the methods that the Viam RDK require.</br>See [Code a new resource model](https://docs.viam.com/registry/create/#code-a-new-resource-model) for more information. | `src` |
| `wifi.hpp` | The defined implementation of the derivative `WifiSensor` class in `wifi.cpp`.</br>See [Find your reference files](https://docs.viam.com/registry/create/#find-your-reference-files) for more information. | `src` |


## Setting Up CI

This module uses [Buildjet runners](https://buildjet.com/for-github-actions) to build natively for ARM.
If you fork this repository and don't have Buildjet connected to GitHub, your CI jobs won't start.

You can choose one option for CI setup:
- Exlusively targetting x86
- Building on an ARM emulator using [QEMU](https://www.qemu.org/download/) with [docker/build-push-action](https://github.com/docker/build-push-action)
- Setting up cross-compilation

Refer to the [fork instructions](https://github.com/viam-labs/python-example-module#forking-this-repo) in the Python example module for more details on deploying your fork. 


## Troubleshooting

> [!NOTE]
> Ensure you have `viam-server` installed your machine.


### Library Paths

Use `ldd` to identify library path issues.
s
For example:

- If you are unable to find one of the `libviam` packages (for example: `libviamsdk.so.noabi`), ensure `libvimapi` and `libviamsdk` are bundled in your `module.tar.gz`.
- Confirm that `LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD` (handled by the `run.sh` wrapper) is set.
- If any other libraries are missing, use `apt-get install` to install them.


### Connecting a Debugger

For unexplained issues, you can use a debugger to investigate crashes or disconnects.
The debugger referenced in this case is [GDB](https://www.onlinegdb.com/).

1. Configure your machine to use the module and ensure it's running.
2. Find the PID of your running module with `ps aux | grep module-example-cpp`.
3. Run `sudo gdb --pid $PID` with the obtained PID (use `sudo` as `viam-server` is likely running in sudo).
4. Type `continue` in gdb to restart the process.
5. Trigger the action causing the issue, and gdb should catch it.

For a more involved C++ module example, which defines both a component and service API, see the [C++ complex module example](https://github.com/viamrobotics/viam-cpp-sdk/tree/main/src/viam/examples/modules/complex).