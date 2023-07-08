# technical-test-lirmm-michelin
Assumptions: mc_rtc is installed; Ubuntu 20.04 with ROS Noetic <br />
<br />
Steps: <br />
clone this repo in '/home/$HOME_FOLER' <br />
sudo gedit /usr/etc/mc_rtc.yaml (to change the configuration file 'mc_rtc.yaml') <br />
change 'Enabled: [CoM]' (or whatever controller inside) to 'Enabled: [AdelDennaouiController]' <br />
run: roscore <br />
go to another terminal and run: roslaunch mc_rtc_ticker display.launch (rviz will open with nothing inside) <br />
go to a third terminal and run: <br />
cd technical-test-lirmm-michelin/build <br />
cmake ../ -DCMAKE_BUILD_TYPE=RelWithDebInfo <br />
make <br />
sudo make install (put the sudo password afterwards) <br />
mc_rtc_ticker (you should be able to see the robot executing the task in rviz) <br />
<br /> 
Brief description: <br />
the moving arms are done through using the SurfaceTransformTask of the left and right wrists <br />
the looking task is done using MetaTaskLoader of YAML files in technical-test-lirmm-michelin/src containing LookAtFrameTask functions that make the dcamera frame look at l_wrist and r_wrist frames <br />
parameters of stiffness, errors thresholds, weight (or anything else I forgot to mention) are inspired by the numbers seen in the tutorials <br />
