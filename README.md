<div align="center">
	<h1> VR Point Cloud Editor </h1>
</div>

The VR Point Cloud Editor is an open-source VR application for cleaning/editing 3D point clouds. This project represents a complete rewrite of the [original Unity-based VR Point Cloud Editor](https://vislab-ccom.unh.edu/tools/point_cloud_editor/), now built on the [Focal Engine](https://github.com/Azzinoth/FocalEngine) for enhanced performance and advanced rendering capabilities.

Point clouds from terrestrial lidar surveys, bathymetric sonar surveys, and 3D scanning applications often contain noise and artifacts that require manual cleaning. This VR editor addresses the inherent challenges of manipulating 3D point cloud data on traditional 2D displays by providing an immersive environment that leverages natural depth perception and two-handed interaction.
 
## Performance Comparison

The Focal Engine-based implementation offers significant performance improvements compared to the original Unity version, particularly in:
- Point cloud rendering performance
- Memory efficiency (up to 90% reduction in RAM usage)
- Frame rate stability overall and during deletion operations
- Support for larger datasets (old version had a hard limit of 260 million points)

### Benchmark Results

Performance testing was conducted on three real-world datasets using the following system:
- **CPU**: Intel Core Ultra 9 285k
- **RAM**: 64 GB DDR5-6400
- **GPU**: NVIDIA RTX 5090

#### Test Dataset 1: Mississippi River Survey
**70 million points** (on-ship lidar scan)

| Metric | Unity Version | Focal Engine Version |
|--------|---------------|---------------------|
| Loading Time | 24.4 sec | 14.8 sec |
| RAM Usage | 11.9 GB | 1.2 GB |
| Frame Time | 9-48 ms | 0.7-1.3 ms |

#### Test Dataset 2: Tokyo Aerial Survey
**253 million points** (aerial lidar scan)

| Metric | Unity Version | Focal Engine Version |
|--------|---------------|---------------------|
| Loading Time | 150.8 sec | 97.5 sec |
| RAM Usage | 34.6 GB | 4.0 GB |
| Frame Time | 17-1670 ms | 2.2-4.7 ms |

#### Test Dataset 3: Extended Tokyo Survey
**455 million points** (expanded aerial lidar dataset)

| Metric | Unity Version | Focal Engine Version |
|--------|---------------|---------------------|
| RAM Usage | N/A | 6.9 GB |
| Frame Time | N/A | 7-10 ms |

## Current Status

**⚠️ This project is currently in proof-of-concept stage.** Core editing functionality and rendering systems are already working; however, advanced features such as automated outlier detection and annotation tools from the Unity version are not yet implemented.

## How To Get
- **Download ready-to-use application:** [Latest release](https://github.com/Azzinoth/VR-PointCloud-Editor/releases/tag/v0.1.0)
- **Download source code and compile:** Look for instructions below.

## How to compile
The compilation process was tested with Windows 10 (and 11) and Visual Studio 2022. To compile, you would need Git, CMake, and Visual Studio.
```bash
# Initialize a new Git repository
git init

# Add the remote repository
git remote add origin https://github.com/Azzinoth/VR-PointCloud-Editor

# Pull the contents of the remote repository
git pull origin master

# Initialize and update submodules
git submodule update --init --recursive

# Generate the build files using CMake
# CMake should be added to a PATH
# if not then use CMAKE GUI
cmake CMakeLists.txt
```
After running these commands, you should have a Visual Studio project that is ready to be compiled.

## Acknowledgements

This research was made possible through the support of NOAA Grant NA20NOS4000196.

This is a project of [Data Visualization Research Lab](https://ccom.unh.edu/vislab) within the [Center for Coastal and Ocean Mapping](https://ccom.unh.edu) at the [University of New Hampshire](https://unh.edu).

## Third Party Licenses

This project uses the following third-party libraries:

1) **Focal Engine**: This library is licensed under MIT License. The full license text can be found at [Focal Engine's GitHub repository](https://github.com/Azzinoth/FocalEngine/blob/master/LICENSE.md)
2) **ImFileDialog**: This library is licensed under MIT License. The full license text can be found at [ImFileDialog's GitHub repository](https://github.com/dfranx/ImFileDialog?tab=MIT-1-ov-file)
