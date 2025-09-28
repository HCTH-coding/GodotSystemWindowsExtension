

#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H


#ifdef _WIN32
#include <windows.h> // we use windows api if on windows 
#include <shellapi.h>
#endif


#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/window.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/classes/display_server.hpp>


namespace godot {
 // On dragging we evaluate the windows if the interacting window handle is empty 
 // if it is not we are sitting and modifing strength needed to drag so it is slightly
 //  harder to stop dragging
 // When buddy sits it gets the title and handle of the window it is sitting on or gets taskbar an set is_on_taskbar
 // When sitting we check the position of the window with the given handle and update screen position of the window doing proper mapping

    class WindowManager: public Object {
        GDCLASS(WindowManager,Object)
        // no properties as i will use it only to get some information - I can always extend it 

        public:
        // Constructor and destructor           

            void make_window_click_through(int window_index,bool enable);

            // we get taskbar rect top left and bottom right 
            Array get_taskbar_points();
            
            // return godot array of Godot dictionaries
            // Array[Dictionary(window_size,window_title,window_screen_pos,window_handle)]
            Array get_window_informations();


            // return position of the given window 
           Dictionary get_given_window_info(uint64_t handle);

            bool is_window_minimized(uint64_t handle);

           protected:
           //bind methods function
           static void _bind_methods();                

    };
    
}

#endif
