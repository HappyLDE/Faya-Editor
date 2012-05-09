#import "AppDelegate.h"


@implementation AppDelegate

//
//
- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)theApplication
{
	return YES;
}

- (BOOL)application:(NSApplication *)theApplication openTempFile:(NSString *)filename
{
    //NSLog(@"opened file %s", [filename UTF8String]);
    
    return YES;
}

@end
