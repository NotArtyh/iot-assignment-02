#!/bin/bash
mkdir -p bin
javac -cp "lib/jssc-2.9.4.jar" -d bin src/*.java
java -cp "bin:lib/jssc-2.9.4.jar" DroneRemoteUnit.DashboardLauncher
