#import <Cocoa/Cocoa.h>


@interface AppDelegate : NSObject
{
	IBOutlet NSWindow *window;
}

//
//
- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)theApplication;
- (BOOL)application:(NSApplication *)theApplication openTempFile:(NSString *)filename;

@end