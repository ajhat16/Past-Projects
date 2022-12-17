# 3081 Homework 4 - Team-010-38
Read Stanton - stant198 <br>
Alex Hatoum - hatou003 <br>
Abdi Ali - ali00235 <br>

## Overview
The focus of this project was to develop a semi-realistic autonomous Uber simulation where drones move around the map of the University of Minnesota and pick up robots. These robots are then dropped off at their respective destinations like how a real-life Uber trip would work.

## Running the Simulation
### Method 1: In a Linux Environment
First, navigate to the directory where the simulation folders are stored in.
```bash
cd path/to/repo/project
```
Next, use the command “make -j” to compile and build the simulation.
```bash
make -j
```
Finally, run the simulation
```bash
./build/bin/transit_service 8081 apps/transit_service/web/
```
Now, navigate to http://127.0.0.1:8081 to see the simulation, and http://127.0.0.1:8081/schedule.html to see the scheduler.
### Method 2: ssh into a Linux Environment
If you are a UMN staff member or student, you can ssh into a CSE lab machine:
```bash
ssh -L 8081:127.0.0.1:8081 x500@csel-xxxx.cselabs.umn.edu
```
For example:
```bash
ssh -L 8081:127.0.0.1:8081 kaung006@csel-kh1250-05.cselabs.umn.edu
```
Next, follow the above steps from method 1, except instead navigate to localhost:8081 and localhost:8081/schedule.html to see the simulation and schedule respectively.
### Interacting with the Simulation
Robots (passengers) can be scheduled from the scheduling webpage by first entering a name for the robot, then clicking on an interactive map to choose the pickup and drop off points. Once those steps are complete, navigate to the bottom of the page where you will see a “Schedule” button. Pressing this will send the robot to the simulation where you can watch the drone pick up the robot and bring it to its destination. You change which entity you are currently viewing via the dropdown menu in the top right corner of the simulation page. Helicopter entities can also be added from the schedule page if you want more helicopters in the simulation. You may also add upgrades to the entities via the section below choosing the entity you are viewing. These upgrades can be applied by pressing the “Add upgrade” button in the simulation. Upgrades can be reset with the “Reset upgrade" button. Upgrades can only be applied after a certain amount of experience is earned by an entity. Experience can be viewed in therminal when either "Add upgrade" or "Reset upgrade" are pressed.


## What the Simulation Does
The simulation is supposed to be a semi-accurate representation of what a world with autonomous Uber vehicles would be like, including picking up and dropping off passengers wherever they please. The simulation does this with a scheduler for the robots (and helicopters). Different vehicles also move around the map in real-time, including the helicopters previously mentioned and cars that follow roads and different paths on the campus. The upgrades can add some variability to the simulation, as well as some uniqueness for each entity.

## New Feature
The new feature we implemented was an upgrade and experience system that can apply to any entity in the simulation. These upgrades are a speed and a color upgrade for the entities in the simulation. These upgrades can be applied on the 3D visualization page located under the “entities” dropdown menu and “simulation speed” slider. However, these upgrades are not free. They are earned through an experience system/algorithm for each entity in the simulation. Experience is gained each time a `Move()` function is called throughout the simulation, in which the experience counter increments by one. It is then multiplied by an experience multiplier calculated by how complicated the chosen entity’s path is. The more nodes the path has, the greater the experience multiplier. The beeline movement strategy has the smallest multiplier out of the movement strategy. Along with these features, there is also a reset upgrades button if the user decides to reverse their upgrades, or go with brand new upgrades all together.

This is significantly interesting because it adds uniqueness to each entity. It also acts as a sort of game for the user since they would be incentivized to schedule longer, more complicated paths for drones to follow so they can upgrade its speed or change the looks of it. The longer the simulation runs, the more experience and upgrades they will have to make each of the entities as crazy as they want. This could also allow people who prefer more real-world applications of the simulation to test entities at different speeds and see how they interact with the environment and each other.

The main design pattern we used to implement our Upgrade function is the Adapter pattern. We chose to implement Upgrade using this design pattern because it allows us to transform (upgrade) the IEntity objects to how the user chooses. We did not think the decorator would be the best for this since we thought it may have been difficult to wrap entities in so many layers and unwrap from all of those layers when they want to reset the upgrades. Because we used the adapter, we can store the upgrades and certain upgrade values in enumerations, and go through the user's choices with a switch statement. Finally, if the user decides to reset, we can fix that with one function call to our `ResetUpgrades()` function. It also allows our Upgrade class to be more flexible/maintainable since if the programmer wants to add a new upgrade, they just need to add it to the enumeration and make another case for the switch statement instead of having to create a brand new file like we would have had to do with the decorator pattern. This way of doing it also made it easier to integrate the upgrade with the simulation webpage, and call different commands based on the upgrades through the transit_service.cc file.

To use this upgrade, run the simulation with one of the two methods listed above. Then, on the right side of the 3D visualization page (not the scheduler), there should be a section under the entity select and simulation speed section where the user can select the upgrades they want. To apply the upgrades, first choose an entity from the dropdown menu in the top right corner of the screen. Next, choose the upgrade you want to use from the dropdown menu in the upgrade section. Then, another section should appear after selecting the upgrade where you can modify the values of the upgrade. For example, if you were to choose a speed upgrade, a slider where you can add the speed will be shown after choosing "Speed" from the dropdown menu. Finally, click the "Add Upgrade" button, and your upgrade will be applied to the entity. Remember, upgrades can only be applied once you have a certain amount of experience. Experience will be shown in the terminal when either the "Add upgrade" or "Reset upgrade" buttons are pressed. There is also a "Reset Upgrade" button if the user wants to reset all upgrades currently applied to that entity and start from scratch. All experience is refunded on a reset.

## Sprint Retrospective
Our team decided that a three-week sprint would be best for our design. We did not have officially scheduled meetings, but we typically met once a week when we had time. During these meetings, we would discuss and explain some of the ideas we had, and some of the new features that we had implemented the previous week. Then, one or two of us would start coding while the three of us bounced a few ideas off each other, and the people who were not coding would usually update the documentation/write-up portions of the project including the UML diagram. We developed iteratively, and we never pushed versions that did not compile to GitHub. We did some minor testing on the code as well before each push just to make sure that everything was functioning, and there were no obvious errors (with the exception of some features that were not working that we already knew about and were working on fixing).

## UML (Every New Function)
![Homework 4 (2)](https://media.github.umn.edu/user/23558/files/ffc299fc-ec93-4f1e-8e97-77094b6f75b6)

