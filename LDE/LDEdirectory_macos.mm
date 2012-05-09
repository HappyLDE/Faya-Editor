/********************************************************************\
 *
 * Little Dream Engine 2
 *
 * Browse folders and files
\********************************************************************/

#include "LDEdirectory_macos.h"

/// FOLDER
LDEdirectory_folder::LDEdirectory_folder()
{

}

LDEdirectory_folder::~LDEdirectory_folder()
{

}

/// FILE
LDEdirectory_file::LDEdirectory_file()
{
    size = 0;
}

LDEdirectory_file::~LDEdirectory_file()
{

}

/// DIRECTORY
LDEdirectory::LDEdirectory()
{

}

LDEdirectory::~LDEdirectory()
{

}

void LDEdirectory::open( string path )
{
	if ( !path.length() )
		path = "/";
	
	folder.erase( folder.begin(), folder.end() );
	file.erase( file.begin(), file.end() );
	
	fileManager = [[NSFileManager alloc] init];
	
	NSString *the_path = [NSString stringWithUTF8String:path.c_str()];
	
	NSError *error = nil;
	NSArray *items = [fileManager contentsOfDirectoryAtPath:the_path error:&error];
	NSString *item_name;
	NSString *item_path;
	BOOL is_directory;
	
	if ( items != nil && [items count] != 0 )
	{
		for ( LDEuint i = 0; i < [items count]; ++i )	
		{
			item_name = [items objectAtIndex: i];
			item_path =  [the_path stringByAppendingPathComponent:item_name];

			[fileManager fileExistsAtPath:item_path isDirectory:&is_directory];

			if ( is_directory )
			{
				LDEdirectory_folder folder_temp;
				folder_temp.name = [item_name UTF8String];
				folder.push_back( folder_temp );
			}
			else
			{
				LDEdirectory_file file_temp;
                file_temp.name = [item_name UTF8String];
				
                // The extension (without the dot)
                file_temp.ext  = [[item_path pathExtension] UTF8String];

                file.push_back( file_temp );
			}
		}
	}
}
