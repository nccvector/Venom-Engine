# Venom Engine

# Dependencies
- clone ogre https://github.com/OGRECave/ogre.git
- at this point, explore the ogre build manual to find and download any requirements. As of now they could be installed with `sudo apt-get install libgles2-mesa-dev libvulkan-dev glslang-dev` and `sudo apt-get install libsdl2-dev libxt-dev libxaw7-dev doxygen`
- create a build directory inside Ogre and run `cmake ..` in build directory to download all the remaining dependencies
- look closely, it downloaded imgui as well, replace the imgui folder with the latest docking branch of imgui from https://github.com/ocornut/imgui.git, that is because we are going to use the docking branch
- try running `make` to build, it will fail while building target OgreBites at OgreImguiInputListener.cpp. Just open up the line of error and change `ImGuiKey_KeyPadEnter` to `ImGuiKey_KeypadEnter`. Save the file and run make again
---

As of now, only the above change fixes the build error. If in near future there are more difference between Ogre's imgui and actual dearimgui then just keep in mind that at this very step you have to fix all the errors and somehow make the latest docking branch work with Ogre

---
- once the build completes, run `make install` or `sudo make install` if previlage issues

The Ogre is finally setup and you're good to go.

make this project now