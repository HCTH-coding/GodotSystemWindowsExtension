# WindowsWindowExtension
C++GodotGDExtension for interaction with Windows OS system windows.

Works with Godot 4.4 and 4.5 - for now. I am thinking about improving it later,
when I have more time and my main project Dotami-vrm (check on itch.io) needs it. 

Use if you need it. Check if you can learn something. 

Used: windows.h c++ library, godot c++ headers and gdscript bindings 

# How to use:

## Easy way (release):
Either download my release, extract and copy into addons folder in your project

## Manual way:

1: Install Scons on your system
2: Install c++ compiler - you can use Visual Studio Community (I use this one)
3: Go into the directory with SConstruct file and open terminal here, then type scons target=template release for release build
4: In bin folder you should have the release file (the same that you can download)


# Simple documentation
It is a very simple script - I needed it so my desktop pet could sit on taskbar and windows (Windows OS)
It has two functions that you can use in GDScript:

 - get_taskbar_points() - you get and array with two Vector2 structures:
 first element - upper_left taskbar corner
 second element - bottom_right taskbar corner

 - get_window_informations() - you get an array of godot dictionaries with information about currently opened windows:
 each dictionary is as follows:

 {"handle": int value of window handle,
  "size": vector2 value of window size,
  "title": window title,
  "position": vector2 window position in screen coordinates}

  Advice: There will be many strange windows like e.g. Windows Input Experience with fullscreen size - you can make some
  filtering inside Godot.

  I personally filtered all windows titled "untitled" and with fullscreen values so my pet sits only on those windows that are
  meaningful for it.

  - is_window_minimized(window_handle) - This will return true if the window is minimized - useful for example for me when player was having 
  his pet sitting on the window and then minimized it. 

  - there is also one useful function that I needed for my transparent windows
  make_window_click_through(window_index, bool value - true to make window not receiving input and false to make it back to normal) - this will make WindowsOS window transparent and you will be able
  to click on desktop - Unfortunately Godot will not receive Input, you will need to find a way.


  # Feel free to write in issues - suggestions, maybe some bugs, I will try to relate to them
    Please note - currently I develop games as a hobby co my time might be limited 