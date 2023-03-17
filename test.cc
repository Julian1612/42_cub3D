#include <ApplicationServices/ApplicationServices.h>

int main() {
    // Get the current cursor position
    CGEventRef currentEvent = CGEventCreate(NULL);
    CGPoint currentCursorPos = CGEventGetLocation(currentEvent);
    CFRelease(currentEvent);

    // Set the new cursor position
    while (true) {
        CGPoint newCursorPos = CGPointMake(100, 100); // Replace with your desired coordinates
        CGWarpMouseCursorPosition(newCursorPos);

        // Click the left mouse button
        CGEventRef clickEvent = CGEventCreateMouseEvent(
            NULL, kCGEventLeftMouseDown,
            newCursorPos, kCGMouseButtonLeft
        );
        CGEventPost(kCGHIDEventTap, clickEvent);
        CFRelease(clickEvent);

        // Release the left mouse button
        clickEvent = CGEventCreateMouseEvent(
            NULL, kCGEventLeftMouseUp,
            newCursorPos, kCGMouseButtonLeft
        );
        CGEventPost(kCGHIDEventTap, clickEvent);
        CFRelease(clickEvent);
    }

    return 0;
}
