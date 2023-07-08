# technical-test-lirmm-michelin
Assumptions: mc_rtc is installed; Ubuntu 20.04 with ROS Noetic

Steps:
clone this repo in '/home/$HOME_FOLER'
sudo gedit /usr/etc/mc_rtc.yaml (to change the configuration file 'mc_rtc.yaml')
change 'Enabled: [CoM]' (or whatever controller inside) to 'Enabled: [AdelDennaouiController]'
roscore
go to another terminal and run: roslaunch mc_rtc_ticker display.launch (rviz will open with nothing inside)
go to a third terminal and run:
cd 
cmake ../ -DCMAKE_BUILD_TYPE=RelWithDebInfo
cd technical-test-lirmm-michelin/build
make
sudo make install (put the sudo password afterwards)
mc_rtc_ticker (you should be able to see the robot executing the task)

Brief description:
the moving arms are done through using the SurfaceTransformTask of the left and right wrists
the looking task is done using MetaTaskLoader of YAML files in technical-test-lirmm-michelin/src containing LookAtFrameTask tasks that make the dcamera frame look at l_wrist and r_wrist frames
parameters of stiffness, errors thresholds, weight (or anything else I forgot about) are inspired by the numbers seen in the tutorials