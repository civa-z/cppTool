#include <stdio.h>  
#include <X11/Xlib.h>  
#include <unistd.h>
#include <memory.h>
#include <ctime>
  

class XlibWrapper{
public:
    XlibWrapper(){
        if( (display = XOpenDisplay(NULL)) == NULL )
            return;
        window = DefaultRootWindow(display);
    }

    bool getCursorPos(int& x, int& y){
        if (NULL == display)
            return false;
        int tmp;
        unsigned int tmp2;
        Window fromroot, tmpwin;
        XQueryPointer(display, window, &fromroot, &tmpwin, &x, &y, &tmp, &tmp, &tmp2);
        return true;
    }

    bool setCursorPos(int x, int y){
        if (NULL == display)
            return false;
        XWarpPointer(display, None, window, 0, 0, 0, 0, x, y);
        XFlush(display);
        return true;
    }

    bool buttonPress(int button, int state = 0x0){
        XEvent event;
 
        if (display == NULL)
            return false;
 
        memset (&event, 0x00, sizeof (event));
        event.type = ButtonPress;
        event.xbutton.button = button;
        event.xbutton.same_screen = True;
        event.xbutton.time = std::time(0);

        XQueryPointer(display, RootWindow(display, DefaultScreen(display)),
            &event.xbutton.root, &event.xbutton.window,
            &event.xbutton.x_root, &event.xbutton.y_root,
            &event.xbutton.x, &event.xbutton.y,
            &event.xbutton.state);

        event.xbutton.subwindow = event.xbutton.window;

        while (event.xbutton.subwindow)
        {
            event.xbutton.window = event.xbutton.subwindow;
            XQueryPointer(display, event.xbutton.window,
                &event.xbutton.root, &event.xbutton.subwindow,
                &event.xbutton.x_root, &event.xbutton.y_root,
                &event.xbutton.x, &event.xbutton.y,
                &event.xbutton.state);
        }

        event.xbutton.state = state;
        if (XSendEvent(display, PointerWindow, True, ButtonPressMask, &event) == 0) 
            printf ( "Errore nell'invio dell'evento !!!/n" );
        XFlush(display);

        return true;
    }

    bool buttonRelease(int button, int state = 0x100){
        XEvent event;
 
        if (display == NULL)
            return false;
 
        memset (&event, 0x00, sizeof (event));
        event.type = ButtonRelease;
        event.xbutton.button = button;
        event.xbutton.same_screen = True;
        event.xbutton.time = std::time(0);

        XQueryPointer(display, RootWindow(display, DefaultScreen(display)),
            &event.xbutton.root, &event.xbutton.window,
            &event.xbutton.x_root, &event.xbutton.y_root,
            &event.xbutton.x, &event.xbutton.y,
            &event.xbutton.state);

        event.xbutton.subwindow = event.xbutton.window;

        while (event.xbutton.subwindow)
        {
            event.xbutton.window = event.xbutton.subwindow;
            XQueryPointer(display, event.xbutton.window,
                &event.xbutton.root, &event.xbutton.subwindow,
                &event.xbutton.x_root, &event.xbutton.y_root,
                &event.xbutton.x, &event.xbutton.y,
                &event.xbutton.state);
        }


        event.xbutton.state = state;
        if (XSendEvent(display, PointerWindow, True, ButtonReleaseMask, &event) == 0)
            printf ( "Errore nell'invio dell'evento !!!/n" );
        XFlush(display);
        return true;
    }

private:
    Display *display;
    Window window;
};
/*  
int main(int argc, char **argv)  
{  
    XlibWrapper xlibWrapper;
    int x,y;
    xlibWrapper.getCursorPos(x,y);
    x = x+10;
    y = y+10;
    xlibWrapper.setCursorPos(x,y);
    xlibWrapper.buttonClick(Button1);

    return 0;  
} 
*/ 
