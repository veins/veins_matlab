# veins_matlab #

Sample combination of Veins and MATLAB

## Supported program versions ##

- Veins 5.0-alpha2 (see <http://veins.car2x.org/>)
- OMNeT++ 5.4.1 (see <https://omnetpp.org/>)
- MATLAB R2019a (see <https://www.mathworks.com/products/matlab/>)

## Supported platforms ##

- Windows 10
- Ubuntu 18.04
- macOS 10.14

## Setup ##

First, make sure that you are using compatible program versions (see above) on a compatible platform (see above).

Make sure that MATLAB is set up and working.

Open MATLAB.
Within MATLAB, change to the `matlab/` subdirectory of `veins_matlab`.
If you are using Windows, make sure to open MATLAB from the Start Menu or Explorer (do not open MATLAB from an OMNeT++ shell, as this changes environment variables that session sharing will rely on to work).

In MATLAB, open the `init.m` file and run it.
This will set up a shared session called `veins`.

Also, make sure that Veins is set up and working from the command line by opening an OMNeT++ shell, navigating to the Veins directory, and executing `./configure` followed by `make`.
Change to the `examples/veins` subdirectory and run `./run` to confirm Veins is working.
Use the same command line window for entering any of the following commands.

In the command line window, change to the `veins_matlab` directory.

Determine where your installation of MATLAB is located.
The directory you are looking for will contain a file `VersionInfo.xml` and should be one level up from where the `matlab` (or `matlab.exe`) binary is located.
Pass this path as an argument to `./configure --with-matlab=...`, similar to one of the following lines:
```
./configure --with-matlab=/opt/matlab/R2019a
./configure --with-matlab=/Applications/MATLAB_R2019a.app
./configure --with-matlab=/c/ProgramFiles/MATLAB/R2019a
```

Build `veins_matlab` by running
```
make
```

Try out `veins_matlab` by running

```
cd examples/veins_matlab
./run -u Cmdenv
```

You should see the following output (amidst other OMNeT++ output):

```
[INFO] General:0 MATLAB result is 11
[INFO] General:0 MATLAB result is 12
[INFO] General:0 MATLAB result is 13
```

## Bugs ##

- Building with MATLAB installed in a location containing spaces is not supported.
Creating a symlink (on Windows: a directory junction, that is, running something like `mklink /J ProgramFiles "Program Files"`) can work around this bug.

- Running in debug mode appends `_dbg` to the library names of MATLAB as well. This means, OMNeT++ will try to load libraries `libMatlabDataArray_dbg` and `libMatlabEngine_dbg`.
Creating a symlink from (or simply copying), e.g., `libMatlabEngine.dll` to `libMatlabEngine_dbg.dll` can work around this bug.


## License ##

Veins is composed of many parts. See the version control log for a full list of
contributors and modifications. Each part is protected by its own, individual
copyright(s), but can be redistributed and/or modified under an open source
license. License terms are available at the top of each file. Parts that do not
explicitly include license text shall be assumed to be governed by the "GNU
General Public License" as published by the Free Software Foundation -- either
version 2 of the License, or (at your option) any later version
(SPDX-License-Identifier: GPL-2.0-or-later). Parts that are not source code and
do not include license text shall be assumed to allow the Creative Commons
"Attribution-ShareAlike 4.0 International License" as an additional option
(SPDX-License-Identifier: GPL-2.0-or-later OR CC-BY-SA-4.0). Full license texts
are available with the source distribution.

