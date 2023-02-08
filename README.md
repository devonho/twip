# twip - Two Wheeled Inverted Pendulum


![Gazebo Sim](./docs/fig1.png "Gazebo Sim")

## Introduction

This is an attempt at implementing a PID controller for a Two Wheeled Inverted Pendulum (a.k.a. Segway) mobile robot. Traditional approaches to this problem have relied on control engineering approaches of modeling the robot (i.e. the plant) and then designing the feedback controller using pole-zero analysis [Ogata2010](https://www.pearson.com/en-us/subject-catalog/p/modern-control-engineering/P200000003521/9780137551064) or solution via state-space modeling [Kim2005](https://idp.springer.com/authorize/casa?redirect_uri=https://link.springer.com/content/pdf/10.1007/s10846-005-9022-4.pdf&casa_token=-iNYZSwBI68AAAAA:toxu4aT68voEpljCI5h_c5MHtPpvbaKAp0ToJrsorzMb_3C1dwlQE7s26gMPtC_K23ODzExWvDiA9Wg3bw). 

With the availability of environments like Gazebo Sim, solving the PID gain parameters by simulating the robot with a range of parameters becomes a simple approach to solving a complicated problem. Modeling of an arbitrary physical model is simplified to modeling of representative geometry with approximate moment of inertia calculations using [readily available tools](https://amesweb.info/inertia/mass-moment-of-inertia-calculator.aspx).

## Building

### Install prerequisites

Add keyrings for Gazebo

```
sudo apt-get update && sudo apt-get install cmake lsb-release wget gnupg 

sudo wget https://packages.osrfoundation.org/gazebo.gpg -O /usr/share/keyrings/pkgs-osrf-archive-keyring.gpg && echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/pkgs-osrf-archive-keyring.gpg] http://packages.osrfoundation.org/gazebo/ubuntu-stable $(lsb_release -cs) main" | sudo tee /etc/apt/sources.list.d/gazebo-stable.list > /dev/null 
```

Run install

```
sudo apt-get install cmake sqlite3 libgz-msgs9-dev libgz-transport12-dev liblog4cpp5-dev
```



### Build

[![CMake](https://github.com/devonho/twip/actions/workflows/cmake.yml/badge.svg)](https://github.com/devonho/twip/actions/workflows/cmake.yml)

```
git clone https://github.com/devonho/twip.git
cd twip
mkdir build
cd build
cmake ../
```

## Running 
![Gazebo Sim](./docs/fig2.gif "Gazebo Sim")

### Start Gazebo
```
cd ./twip/gz
gz sim world.sdf -r
```
Add `Key Publisher` via the plugin menu.

### Start controller  
```
./twip/build/src/controller
```
[YouTube](https://youtu.be/IyWVEmLUmFI)

## References

Ogata2010 - Ogata K. Modern control engineering. Upper Saddle River, NJ: Prentice hall; 2010 Jan.

Kim2005 - Kim, Y., Kim, S. H., & Kwak, Y. K. (2005). Dynamic analysis of a nonholonomic two-wheeled inverted pendulum robot. Journal of Intelligent and Robotic Systems, 44, 25-46.