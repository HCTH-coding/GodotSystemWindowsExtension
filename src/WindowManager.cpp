

#include "WindowManager.h"


using namespace godot;



// here we bind methods 
void WindowManager::_bind_methods(){

    ClassDB::bind_method(D_METHOD("make_window_click_through"), &WindowManager::make_window_click_through);
    ClassDB::bind_method(D_METHOD("get_taskbar_points"), &WindowManager::get_taskbar_points);

    ClassDB::bind_method(D_METHOD("get_window_informations"), &WindowManager::get_window_informations);
    ClassDB::bind_method(D_METHOD("get_given_window_info"), &WindowManager::get_given_window_info);
    ClassDB::bind_method(D_METHOD("is_window_minimized"), &WindowManager::is_window_minimized);




}


// Making the window allow click_throughs
void WindowManager::make_window_click_through(int window_index, bool enable){

    DisplayServer *display_server = DisplayServer::get_singleton();
    // we are getting native handle
    int64_t native_handle = display_server -> window_get_native_handle(DisplayServer::HandleType::WINDOW_HANDLE,window_index);

    // Windows functionality 
    #ifdef _WIN32
     HWND window_handle = reinterpret_cast<HWND>(native_handle);

     
     

     if (enable == true){
        LONG_PTR style = GetWindowLongPtr(window_handle, GWL_EXSTYLE);
        SetWindowLongPtr(window_handle, GWL_EXSTYLE, style | WS_EX_LAYERED| WS_EX_TRANSPARENT);
     }     

     if (enable == false){
        LONG_PTR clear_style = GetWindowLongPtr(window_handle,GWL_EXSTYLE);
        clear_style &= ~WS_EX_TRANSPARENT;
        
        SetWindowLongPtr(window_handle, GWL_EXSTYLE, clear_style);
     }
     // Make the window transparent
     
     SetLayeredWindowAttributes(window_handle, 0, 255, LWA_ALPHA);
     //RedrawWindow(window_handle, NULL, NULL, RDW_FRAME | RDW_INVALIDATE);

    #endif

}
// getting taskbar positioning points
Array WindowManager::get_taskbar_points(){

    Array bar_points;

    #ifdef _WIN32
    // Getting the rect of a taskbar
    APPBARDATA task_bar_data = {sizeof(APPBARDATA)};

    SHAppBarMessage(ABM_GETTASKBARPOS, &task_bar_data);

    RECT bar_rect = task_bar_data.rc; 

    Vector2 top_left = Vector2(bar_rect.left,bar_rect.top);
    Vector2 bottom_right = Vector2(bar_rect.right, bar_rect.bottom);

    #endif

    // this is godot specific code   will be the same for linux

    bar_points.append(top_left);
    bar_points.append(bottom_right);
    

    return bar_points;
}


// get info on opened windows
Array WindowManager:: get_window_informations(){

   
    Array inf;
    Vector<uint64_t> handles;
    #ifdef _WIN32
    

    // We enum top level windows - no embedded ones
    // and we pass lambda parameter and fill the dictionary vector 
    EnumWindows([](HWND hwnd, LPARAM lparam) -> BOOL {
        // title, pos and size of a window 
        if (!IsWindowVisible(hwnd)){
            return TRUE;}

        // we use only non minimized windows
        WINDOWPLACEMENT wp;
        GetWindowPlacement(hwnd, &wp);

        if (wp.showCmd == SW_SHOWMINIMIZED){
            return TRUE;
        }

        // if title is null we do not process the window 
        if (GetWindowTextLengthW == 0){
            return TRUE;
        }        
               
        
        auto *infos = reinterpret_cast<Vector<uint64_t>*>(lparam);
         infos -> append(reinterpret_cast<uint64_t>(hwnd));      
                  

        return TRUE;

    },reinterpret_cast<LPARAM>(&handles));  

    #endif

    for (uint64_t h:handles){        
        inf.append(get_given_window_info(h));
    }

    return inf;
}

// get window information based on handle 
Dictionary WindowManager::get_given_window_info(uint64_t handle){

    Vector2 window_pos = Vector2(0,0);
    Vector2 window_size = Vector2(0,0);
    String window_title = "title";
    uint64_t base_handle = -1;
    Dictionary window_inf;

    #ifdef _WIN32
    HWND window_handle = reinterpret_cast<HWND>(handle);
   

    if (window_handle != nullptr && IsWindow(window_handle)){
        RECT rect;
        wchar_t title[256];

        GetWindowRect(window_handle,&rect);

        // we get top left to get position
        window_pos.x = rect.left;
        window_pos.y = rect.top;

        // we get size of the window 
        window_size.x = Math::abs(rect.left - rect.right);
        window_size.y = Math::abs(rect.top - rect.bottom);

        base_handle = handle;

        // get window title - for testing maybe remove later 
        if (GetWindowTextW(window_handle,reinterpret_cast<LPWSTR>(title),sizeof(title)) > 0){
            window_title = String(title);
        }  

    }     
    #endif

    
    window_inf["handle"] = base_handle;
    window_inf["title"] = window_title;
    window_inf["size"] = window_size;
    window_inf["position"] = window_pos;

    return window_inf ;


}


bool WindowManager::is_window_minimized(uint64_t handle){

    bool is_minimized = false;

    #ifdef _WIN32

    if(IsIconic(reinterpret_cast<HWND>(handle))){
        is_minimized = true;
    }
    #endif


    return is_minimized;

}